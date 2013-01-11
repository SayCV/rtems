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

#define	CFG_LED_NBR_00	AT91_PIN_PD31

void red_LED_on(void)
{
	at91_set_gpio_value(CONFIG_RED_LED, 1);
}

void red_LED_off(void)
{
	at91_set_gpio_value(CONFIG_RED_LED, 0);
}

