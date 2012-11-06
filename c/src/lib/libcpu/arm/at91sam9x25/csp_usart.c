/*
*********************************************************************************************************
*        CSP
* Chip Support Package
* Filename      : csp_usart.c
* Note(s)       : 
*
*  The license and distribution terms for this file may be
*  found in the file LICENSE in this distribution or at
*  http://www.rtems.com/license/LICENSE.
*********************************************************************************************************
*/



#include <bsp.h>
#include <rtems/libio.h>
#include <termios.h>

#include <csp.h>
#include <rtems/bspIo.h>
#include <libchip/serial.h>
#include <libchip/sersupp.h>

/* static function prototypes */
static int     usart_first_open(int major, int minor, void *arg);
static int     usart_last_close(int major, int minor, void *arg);
static int     usart_read_polled(int minor);
static ssize_t usart_write_polled_support(int minor, const char *buf, size_t len);
static void    usart_init(int minor);
static void    usart_write_polled(int minor, char c);
static int     usart_set_attributes(int minor, const struct termios *t);
CSP_USART_REG_TAG *usart_get_base(int minor);

/* Pointers to functions for handling the UART polled. */
console_fns usart_polling_fns = {
  libchip_serial_default_probe,       /* deviceProbe */
  usart_first_open,                   /* deviceFirstOpen */
  usart_last_close,                   /* deviceLastClose */
  usart_read_polled,                  /* deviceRead */
  usart_write_polled_support,         /* deviceWrite */
  usart_init,                         /* deviceInitialize */
  usart_write_polled,                 /* deviceWritePolled */
  usart_set_attributes,               /* deviceSetAttributes */
  FALSE                 /* TRUE if interrupt driven, FALSE if not. */
};

CSP_USART_REG_TAG *usart_get_base(int minor)
{
  console_tbl *console_entry;
  CSP_USART_REG_TAG *port;

  console_entry = BSP_get_uart_from_minor(minor);

  if (console_entry == NULL)
    return 0;

  port = (CSP_USART_REG_TAG *) console_entry->ulCtrlPort1;
  //printk( "minor=%d entry=%p port=%p\n", minor, console_entry, port );

  return port;
}

/*
 * Functions called via callbacks (i.e. the ones in uart_fns
 */

/*
 * This is called the first time each device is opened. Since
 * the driver is polled, we don't have to do anything. If the driver
 * were interrupt driven, we'd enable interrupts here.
 */
static int usart_first_open(int major, int minor, void *arg)
{
  CSP_USART_REG_TAG *usart;

  usart = usart_get_base(minor);
  if ( !usart )
    return -1;

  /* XXX port isn't being initialized or enabled */

  /* XXX I hope this is enough */
  usart->cr = (CSP_US_CR_RXEN | CSP_US_CR_TXEN);
  return 0;
}

/*
 * This is called the last time each device is closed.  Since
 * the driver is polled, we don't have to do anything. If the driver
 * were interrupt driven, we'd disable interrupts here.
 */
static int usart_last_close(int major, int minor, void *arg)
{
  CSP_USART_REG_TAG *usart;

  usart = usart_get_base(minor);
  if ( !usart )
    return -1;

  return 0;
}

/*
 * Read one character from UART.
 *
 * return -1 if there's no data, otherwise return
 * the character in lowest 8 bits of returned int.
 */
static int usart_read_polled(int minor)
{
  CSP_USART_REG_TAG *usart;

  usart = usart_get_base(minor);
  if ( !usart )
    return -1;

  /* if nothing ready return -1 */
  if ( (usart->sr & CSP_US_IER_RXRDY) == 0 )
    return -1;

  return usart->rhr;
}


/*
 *  Write character out
 */
static void usart_write_polled(int minor, char c)
{
  CSP_USART_REG_TAG *usart;

  usart = usart_get_base(minor);
  if ( !usart )
    return;

  /* delay until TX empty */
  while ( (usart->sr & CSP_US_IER_TXEMPTY) == 0 )
    ;

  usart->thr = c;
}

/*
 * Write buffer to UART
 *
 * return 1 on success, -1 on error
 */
static ssize_t usart_write_polled_support(int minor, const char *buf, size_t len)
{
  CSP_USART_REG_TAG *usart;
  int nwrite=0;

  /*
   *  Verify the minor number
   */
  usart = usart_get_base(minor);
  if ( !usart )
    return -1;

  /*
   * poll each byte in the string out of the port.
   */
  while (nwrite < len) {
    usart_write_polled(minor, *buf++);
    nwrite++;
  }

  /*
   * return the number of bytes written.
   */
  return nwrite;

  return 1;
}


/* Set up the UART. */
static void usart_init(int minor)
{
  CSP_USART_REG_TAG *usart;

  usart = usart_get_base(minor);
  if ( !usart )
    return;

}


/* This is for setting baud rate, bits, etc. */
static int usart_set_attributes(int minor, const struct termios *t)
{
  uint32_t      brgr;
  uint32_t      mode, baud, baud_requested;
  CSP_USART_REG_TAG *usart;

  usart = usart_get_base(minor);
  if ( !usart )
    return -1;

  /* Get current mode register */
  mode = usart->mr & ~(CSP_US_MR_USART_MODE_NORMAL | CSP_US_MR_USCLKS_SCK | CSP_US_MR_CHRL_8_BIT
			| CSP_US_MR_PAR_NO | CSP_US_MR_NBSTOP_1_BIT);

  /* Byte size */
  switch (t->c_cflag & CSIZE){
  case CS5:
    mode |= CSP_US_MR_CHRL_5_BIT;
    break;
  case CS6:
    mode |= CSP_US_MR_CHRL_6_BIT;
    break;
  case CS7:
    mode |= CSP_US_MR_CHRL_7_BIT;
    break;
  default:
    mode |= CSP_US_MR_CHRL_8_BIT;
    break;
  }

  /* Stop bits */
  if (t->c_cflag & CSTOPB){
	mode |= CSP_US_MR_NBSTOP_2_BIT; /* 2 stop bits */
  } else
    mode |= CSP_US_MR_NBSTOP_1_BIT;     /* 1 stop bits */

  /* Parity */
  if (t->c_cflag & PARENB){
      /* Mark or Space parity */
      if (t->c_cflag & PARODD){
	mode |= CSP_US_MR_PAR_ODD;
      } else
	mode |= CSP_US_MR_PAR_EVEN;
   } else
	mode |= CSP_US_MR_PAR_NO;

  baud_requested = t->c_cflag & CBAUD;

  /* If not, set the dbgu console baud as USART baud default */
  if (!baud_requested)
    baud_requested = BSP_get_baud();

  baud = rtems_termios_baud_to_number(baud_requested);

  brgr = (CSP_PMC_get_mck() / 16) / baud;

	if (brgr > 65535){    /* BRGR is 16-bit, so switch to slower clock */
		brgr /= 8;
		mode |= CSP_US_MR_USCLKS_DIV;
	}

  usart->mr = mode;
  usart->brgr = brgr;
  return 0;
}

/*
 * The following functions are not used by TERMIOS, but other RTEMS
 * functions use them instead.
 */

/*
 * Read from UART. This is used in the exit code, and can't
 * rely on interrupts.
 */
int usart_poll_read(int minor)
{
  return usart_read_polled(minor);
}
