/*
 *  LED Driver for low level debug.
 *
 *  Copyright (c) 2003 by Cogent Computer Systems
 *  Written by Mike Kelly <mike@cogcomp.com>
 *         and Jay Monkman <jtm@lopingdog.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */

#include <bsp.h>
#include <rtems/libio.h>
#include <termios.h>

#include <at91sam9x5.h>
#include <at91_aic.h>
#include <at91_pmc.h>
#include <at91_io.h>
#include <at91_gpio.h>

#include <rtems/bspIo.h>

/* LED */
#define CONFIG_AT91_LED
#define	CONFIG_RED_LED		AT91_PIN_PD31	/* this is the user1 led */
#define	CONFIG_GREEN_LED	AT91_PIN_PC4	/* this is the user2 led */

/* PC4 */
#define	BSP_BRDCPU_LED_PIN_NBR_01		        DEF_BIT_04
/*
*********************************************************************************************************
* 
* PA27 WARNNING
* PA29 FA
*********************************************************************************************************
*/
#define	BSP_BRDCPU_LED_PIN_NBR_02		        DEF_BIT_27
#define	BSP_BRDCPU_LED_PIN_NBR_03		        DEF_BIT_29

/*
*********************************************************************************************************
* 
* CANTXD                    PA5
* CANRXD                    PA6
* USARTTXD                  PA10
* USARTRXD                  PA9
*********************************************************************************************************
*/
#define	BSP_BRDCPU_LED_PIN_NBR_04		        DEF_BIT_05
#define	BSP_BRDCPU_LED_PIN_NBR_05		        DEF_BIT_06
#define	BSP_BRDCPU_LED_PIN_NBR_06		        DEF_BIT_10
#define	BSP_BRDCPU_LED_PIN_NBR_07		        DEF_BIT_09

#if 0
#define	CFG_LED_NBR_01	AT91_PIN_PC04
#define	CFG_LED_NBR_02	AT91_PIN_PA27
#define	CFG_LED_NBR_03	AT91_PIN_PA29
#define	CFG_LED_NBR_04	AT91_PIN_PA05
#define	CFG_LED_NBR_05	AT91_PIN_PA06
#define	CFG_LED_NBR_06	AT91_PIN_PA10
#define	CFG_LED_NBR_07	AT91_PIN_PA09
#endif

void red_LED_on(void)
{
	at91_set_gpio_value(CONFIG_RED_LED, 1);
}

void red_LED_off(void)
{
	at91_set_gpio_value(CONFIG_RED_LED, 0);
}

void CSP_LED_NBR_on(uint32_t led_nbr)
{
	at91_set_gpio_value(led_nbr, 1);
}

void CSP_LED_NBR_off(uint32_t led_nbr)
{
	
	at91_set_gpio_value(led_nbr, 0);
}

void CSP_LED_NBRS_on(uint32_t led_nbr)
{
	int i;
	for(i=1; i<led_nbr;i++) {
		at91_set_gpio_value(i, 1);
	}
}

void CSP_LED_NBRS_off(uint32_t led_nbr)
{
	int i;
	for(i=1; i<led_nbr;i++) {
		at91_set_gpio_value(i, 0);
	}
}
