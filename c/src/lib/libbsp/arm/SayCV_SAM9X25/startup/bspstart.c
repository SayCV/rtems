/*
 * SayCV_SAM9X25 - AT91SAM9X25 Startup Code
 *
 *  Copyright (c) 2004 by Cogent Computer Systems
 *  Written by Jay Monkman <jtm@lopingdog.com>
 *
 *  Modified by Joel Sherill 
 *  from OAR Corporation and 
 *  Fernando Nicodemos <fgnicodemos@terra.com.br>
 *  from NCB - Sistemas Embarcados Ltda. (Brazil)
 * 
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */

#include <bsp.h>
#include <bsp/irq-generic.h>
#include <at91sam9x5.h>
#include <at91_aic.h>
#include <at91_pmc.h>
#include <at91_clk.h>
#include <at91_gpio.h>
#include <at91_io.h>
#include <at91_emac.h>
#include <led.h>

/* Function prototypes */
extern void rtems_exception_init_mngt(void);
static void fix_mac_addr(void);
void bsp_usart_init(void);

/*
 * bsp_start_default - BSP initialization function
 *
 * This function is called before RTEMS is initialized and used
 * adjust the kernel's configuration.
 *
 * This function also configures the CPU's memory protection unit.
 *
 * RESTRICTIONS/LIMITATIONS:
 *   Since RTEMS is not configured, no RTEMS functions can be called.
 */
void bsp_start_default( void )
{
  /* disable interrupts */
  //AIC_CTL_REG(AIC_IDCR) = 0xffffffff;
  at91_sys_write(AT91_AIC_IDCR, 0xffffffff);
	//CSP_LED_NBR_on(CFG_LED_NBR_01);
  at91_clock_init(BSP_MAIN_FREQ);
	//CSP_LED_NBR_on(CFG_LED_NBR_02);
  /*
   * Some versions of the bootloader have the MAC address
   * reversed. This fixes it, if necessary.
   */
  fix_mac_addr();
//CSP_LED_NBR_on(CFG_LED_NBR_03);
  /*
   * Init rtems PIO configuration for USARTs
   */
  bsp_usart_init(); 
  printk("Init Finshed. rtems PIO configuration for USARTs\r\n");

  /*
   * Init rtems exceptions management
   */
  rtems_exception_init_mngt();
  printk("Init Finshed. rtems exceptions management\r\n");

  /*
   * Init rtems interrupt management
   */
  if (bsp_interrupt_initialize() != RTEMS_SUCCESSFUL) {
    _CPU_Fatal_halt(0xe);
  }

} /* bsp_start */

/*
 * Some versions of the bootloader shipped with the CSB337
 * reverse the MAC address. This function tests for that,
 * and fixes the MAC address.
 */
static void fix_mac_addr(void)
{
  uint8_t addr[6];
#if 0

  /* Read the MAC address */
  addr[0] = (EMAC_REG(EMAC_SA1L) >>  0) & 0xff;
  addr[1] = (EMAC_REG(EMAC_SA1L) >>  8) & 0xff;
  addr[2] = (EMAC_REG(EMAC_SA1L) >> 16) & 0xff;
  addr[3] = (EMAC_REG(EMAC_SA1L) >> 24) & 0xff;
  addr[4] = (EMAC_REG(EMAC_SA1H) >>  0) & 0xff;
  addr[5] = (EMAC_REG(EMAC_SA1H) >>  8) & 0xff;

  /* Check which 3 bytes have Cogent's OUI */
  if ((addr[5] == 0x00) && (addr[4] == 0x23) && (addr[3] == 0x31)) {
      EMAC_REG(EMAC_SA1L) = ((addr[5] <<  0) |
                             (addr[4] <<  8) |
                             (addr[3] << 16) |
                             (addr[2] << 24));

      EMAC_REG(EMAC_SA1H) = ((addr[1] <<  0) |
                             (addr[0] <<  8));
  }
#else
	at91_emac_t *emac = (at91_emac_t *) AT91_BASE_EMAC0;

	addr[0] = (readl(&emac->hsl) >>  0) & 0xff;
  	addr[1] = (readl(&emac->hsl) >>  8) & 0xff;
  	addr[2] = (readl(&emac->hsl) >> 16) & 0xff;
  	addr[3] = (readl(&emac->hsl) >> 24) & 0xff;
  	addr[4] = (readl(&emac->hsh) >>  0) & 0xff;
  	addr[5] = (readl(&emac->hsh) >>  8) & 0xff;

	  /* Check which 3 bytes have Cogent's OUI */
  if ((addr[5] == 0x00) && (addr[4] == 0x23) && (addr[3] == 0x31)) {
      writel(((addr[5] <<  0) |
                             (addr[4] <<  8) |
                             (addr[3] << 16) |
                             (addr[2] << 24)), &emac->hsl);

      writel(((addr[1] <<  0) |
                             (addr[0] <<  8)), &emac->hsl);
  	}
#endif
}

/*
 *
 * NAME: bsp_usart_init - Function to setup the PIO in USART mode
 *       before startup
 *
 * DESCRIPTION:
 *   This function is called before usart driver is initialized and is
 *   used to setup the proper mode of PIO operation for USART.
 *
 * NOTES:
 *   The initialization could be done smarter by programming only the
 *   bits you need to program for each USART when the port is ENABLED.
 *
 */
void bsp_usart_init(void)
{
	at91_pmc_t *pmc = (at91_pmc_t *) AT91_BASE_PMC;
	
	at91_set_A_periph(AT91_PIN_PA9, 0);			/* DRXD */
	at91_set_A_periph(AT91_PIN_PA10, 1);		/* DTXD */

	at91_set_A_periph(AT91_PIN_PA0, 1);		/* TXD0 */
	at91_set_A_periph(AT91_PIN_PA1, 0);		/* RXD0 */

	//if (pins & ATMEL_UART_RTS)
	//	at91_set_A_periph(AT91_PIN_PA2, 0);	/* RTS0 */
	//if (pins & ATMEL_UART_CTS)
	//	at91_set_A_periph(AT91_PIN_PA3, 0);	/* CTS0 */

	at91_set_A_periph(AT91_PIN_PA5, 1);		/* TXD1 */
	at91_set_A_periph(AT91_PIN_PA6, 0);		/* RXD1 */

	//if (pins & ATMEL_UART_RTS)
	//	at91_set_C_periph(AT91_PIN_PC27, 0);	/* RTS1 */
	//if (pins & ATMEL_UART_CTS)
	//	at91_set_C_periph(AT91_PIN_PC28, 0);	/* CTS1 */

	at91_set_A_periph(AT91_PIN_PA7, 1);		/* TXD2 */
	at91_set_A_periph(AT91_PIN_PA8, 0);		/* RXD2 */

	//if (pins & ATMEL_UART_RTS)
	//	at91_set_B_periph(AT91_PIN_PB0, 0);	/* RTS2 */
	//if (pins & ATMEL_UART_CTS)
	//	at91_set_B_periph(AT91_PIN_PB1, 0);	/* CTS2 */

	at91_set_B_periph(AT91_PIN_PC22, 1);		/* TXD3 */
	at91_set_B_periph(AT91_PIN_PC23, 0);		/* RXD3 */

	//if (pins & ATMEL_UART_RTS)
	//	at91_set_B_periph(AT91_PIN_PC24, 0);	/* RTS3 */
	//if (pins & ATMEL_UART_CTS)
	//	at91_set_B_periph(AT91_PIN_PC25, 0);	/* CTS3 */
#if 0
	at91_set_C_periph(AT91_PIN_PC8, 1);		/* UTXD0 */
	at91_set_C_periph(AT91_PIN_PC9, 0);		/* URXD0 */


	at91_set_C_periph(AT91_PIN_PC16, 1);		/* UTXD1 */
	at91_set_C_periph(AT91_PIN_PC17, 0);		/* URXD1 */
#endif
	pmc->pcer = (	AT91SAM9X5_ID_USART0	|
					AT91SAM9X5_ID_USART1	|
					AT91SAM9X5_ID_USART2	|
					AT91SAM9X5_ID_USART3	);
					//AT91SAM9X5_ID_UART0 	|
					//AT91SAM9X5_ID_UART1 	);
#if 0	
  /*
   * Configure shared pins for USARTs.
   * Disables the PIO from controlling the corresponding pin.
   */
  PIOA_REG(PIO_PDR) |= ( BIT5  |   /* USART3 TXD3  */
                         BIT6  |   /* USART3 RXD3  */
                         BIT17 |   /* USART0 TXD0  */
                         BIT18 |   /* USART0 RXD0  */
                         BIT22 |   /* USART2 RXD2  */
                         BIT23 );  /* USART2 TXD2  */

  PIOB_REG(PIO_PDR) |= ( BIT20 |   /* USART1 TXD1  */
                         BIT21 );  /* USART1 RXD1  */

  /**** PIO Controller A - Pins you want in mode B ****/
  PIOA_REG(PIO_BSR) |=  ( BIT5 |   /* USART3 TXD3  */ /* add */
                          BIT6 );  /* USART3 RXD3  */ 
  PIOA_REG(PIO_ASR) &= ~( BIT5 |   /* USART3 TXD3  */
                          BIT6 );  /* USART3 RXD3  */

  /**** PIO Controller A - Pins you want in mode A ****/
  PIOA_REG(PIO_ASR) |=  ( BIT17 |   /* USART0 TXD0  */
                          BIT18 |   /* USART0 RXD0  */
                          BIT22 |   /* USART2 RXD2  */
                          BIT23 );  /* USART2 TXD2  */
  PIOA_REG(PIO_BSR) &= ~( BIT17 |   /* USART0 TXD0  */ /* add */
                          BIT18 |   /* USART0 RXD0  */
                          BIT22 |   /* USART2 RXD2  */
                          BIT23 );  /* USART2 TXD2  */

  /**** PIO Controller B - Pins you want in mode A ****/
  PIOB_REG(PIO_ASR) |=  ( BIT20 |   /* USART1 TXD1  */
                          BIT21 );  /* USART1 RXD1  */
  PIOB_REG(PIO_BSR) &= ~( BIT20 |   /* USART1 TXD1  */
                          BIT21 );  /* USART1 RXD1  */

  /**** PIO Controller B - Pins you want in mode B ****/
  /**** none ****/

  /* Enable the clock to the USARTs */
  PMC_REG(PMC_PCER) |= ( PMC_PCR_PID_US0 |   /* USART 0 Peripheral Clock */
                         PMC_PCR_PID_US1 |   /* USART 1 Peripheral Clock */
                         PMC_PCR_PID_US2 |   /* USART 2 Peripheral Clock */ 
                         PMC_PCR_PID_US3 );  /* USART 3 Peripheral Clock */
#endif
} 

/*
 *  By making this a weak alias for bsp_start_default, a brave soul
 *  can override the actual bsp_start routine used.
 */
void bsp_start (void) __attribute__ ((weak, alias("bsp_start_default")));
