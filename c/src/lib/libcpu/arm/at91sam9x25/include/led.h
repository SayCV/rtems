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

void CSP_LED_NBR_on(uint32_t led_nbr);

void CSP_LED_NBR_off(uint32_t led_nbr);

void CSP_LED_NBRS_on(uint32_t led_nbr);

void CSP_LED_NBRS_off(uint32_t led_nbr);

#endif
