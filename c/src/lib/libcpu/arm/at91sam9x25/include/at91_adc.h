/*
 * arch/arm/mach-at91/include/mach/at91_adc.h
 *
 * Copyright (C) SAN People
 *
 * Analog-to-Digital Converter (ADC) registers.
 * Based on AT91SAM9260 datasheet revision D.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef AT91_ADC_H
#define AT91_ADC_H

typedef struct {
  uint32_t cr;        /**< \brief (adc offset: 0x00) control register */
  uint32_t mr;        /**< \brief (adc offset: 0x04) mode register */
  uint32_t seqr1;     /**< \brief (adc offset: 0x08) channel sequence register 1 */
  uint32_t seqr2;     /**< \brief (adc offset: 0x0c) channel sequence register 2 */
  uint32_t cher;      /**< \brief (adc offset: 0x10) channel enable register */
  uint32_t chdr;      /**< \brief (adc offset: 0x14) channel disable register */
  uint32_t chsr;      /**< \brief (adc offset: 0x18) channel status register */
  uint32_t reserved1[1];
  uint32_t lcdr;      /**< \brief (adc offset: 0x20) last converted data register */
  uint32_t ier;       /**< \brief (adc offset: 0x24) interrupt enable register */
  uint32_t idr;       /**< \brief (adc offset: 0x28) interrupt disable register */
  uint32_t imr;       /**< \brief (adc offset: 0x2c) interrupt mask register */
  uint32_t isr;       /**< \brief (adc offset: 0x30) interrupt status register */
  uint32_t reserved2[2];
  uint32_t over;      /**< \brief (adc offset: 0x3c) overrun status register */
  uint32_t emr;       /**< \brief (adc offset: 0x40) extended mode register */
  uint32_t cwr;       /**< \brief (adc offset: 0x44) compare window register */
  uint32_t reserved3[2];
  uint32_t cdr[12];   /**< \brief (adc offset: 0x50) channel data register */
  uint32_t reserved4[16];
  uint32_t trgr;      /**< \brief (adc offset: 0xc0) trigger register */
  uint32_t reserved5[8];
  uint32_t wpmr;      /**< \brief (adc offset: 0xe4) write protect mode register */
  uint32_t wpsr;      /**< \brief (adc offset: 0xe8) write protect status register */
} at91_adc_t;

#define AT91_ADC_CR		0x00		/* Control Register */
#define		AT91_ADC_SWRST		(1 << 0)	/* Software Reset */
#define		AT91_ADC_START		(1 << 1)	/* Start Conversion */

#define AT91_ADC_MR		0x04		/* Mode Register */
#define		AT91_ADC_TRGEN		(1 << 0)	/* Trigger Enable */
#define		AT91_ADC_TRGSEL		(7 << 1)	/* Trigger Selection */
#define			AT91_ADC_TRGSEL_TC0		(0 << 1)
#define			AT91_ADC_TRGSEL_TC1		(1 << 1)
#define			AT91_ADC_TRGSEL_TC2		(2 << 1)
#define			AT91_ADC_TRGSEL_EXTERNAL	(6 << 1)
#define		AT91_ADC_LOWRES		(1 << 4)	/* Low Resolution */
#define		AT91_ADC_SLEEP		(1 << 5)	/* Sleep Mode */
#define		AT91_ADC_PRESCAL	(0x3f << 8)	/* Prescalar Rate Selection */
#define			AT91_ADC_PRESCAL_(x)	((x) << 8)
#define		AT91_ADC_STARTUP	(0x1f << 16)	/* Startup Up Time */
#define			AT91_ADC_STARTUP_(x)	((x) << 16)
#define		AT91_ADC_SHTIM		(0xf  << 24)	/* Sample & Hold Time */
#define			AT91_ADC_SHTIM_(x)	((x) << 24)

#define AT91_ADC_CHER		0x10		/* Channel Enable Register */
#define AT91_ADC_CHDR		0x14		/* Channel Disable Register */
#define AT91_ADC_CHSR		0x18		/* Channel Status Register */
#define		AT91_ADC_CH(n)		(1 << (n))	/* Channel Number */

#define AT91_ADC_SR		0x1C		/* Status Register */
#define		AT91_ADC_EOC(n)		(1 << (n))	/* End of Conversion on Channel N */
#define		AT91_ADC_OVRE(n)	(1 << ((n) + 8))/* Overrun Error on Channel N */
#define		AT91_ADC_DRDY		(1 << 16)	/* Data Ready */
#define		AT91_ADC_GOVRE		(1 << 17)	/* General Overrun Error */
#define		AT91_ADC_ENDRX		(1 << 18)	/* End of RX Buffer */
#define		AT91_ADC_RXFUFF		(1 << 19)	/* RX Buffer Full */

#define AT91_ADC_LCDR		0x20		/* Last Converted Data Register */
#define		AT91_ADC_LDATA		(0x3ff)

#define AT91_ADC_IER		0x24		/* Interrupt Enable Register */
#define AT91_ADC_IDR		0x28		/* Interrupt Disable Register */
#define AT91_ADC_IMR		0x2C		/* Interrupt Mask Register */

#define AT91_ADC_CHR(n)		(0x30 + ((n) * 4))	/* Channel Data Register N */
#define		AT91_ADC_DATA		(0x3ff)

#endif
