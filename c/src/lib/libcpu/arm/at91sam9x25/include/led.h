/*
 * arch/arm/mach-at91/include/mach/at91_tc.h
 *
 * Copyright (C) SAN People
 *
 * Timer/Counter Unit (TC) registers.
 * Based on AT91RM9200 datasheet revision E.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef AT91_LED_H
#define AT91_LED_H

#define	CFG_LED_NBR_01	AT91_PIN_PC4
#define	CFG_LED_NBR_02	AT91_PIN_PA27
#define	CFG_LED_NBR_03	AT91_PIN_PA29
#define	CFG_LED_NBR_04	AT91_PIN_PA5
#define	CFG_LED_NBR_05	AT91_PIN_PA6
#define	CFG_LED_NBR_06	AT91_PIN_PA10
#define	CFG_LED_NBR_07	AT91_PIN_PA9


void CSP_LED_NBR_on(uint32_t led_nbr);

void CSP_LED_NBR_off(uint32_t led_nbr);

void CSP_LED_NBRS_on(uint32_t led_nbr);

void CSP_LED_NBRS_off(uint32_t led_nbr);

#endif
