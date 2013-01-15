/*
 * arch/arm/mach-at91/include/mach/at91_aic.h
 *
 * Copyright (C) 2005 Ivan Kokshaysky
 * Copyright (C) SAN People
 *
 * Advanced Interrupt Controller (AIC) - System peripherals registers.
 * Based on AT91RM9200 datasheet revision E.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef AT91_AIC_H
#define AT91_AIC_H

typedef struct {
   uint32_t smr[32];   /**< \brief (aic offset: 0x00) source mode register */
   uint32_t svr[32];   /**< \brief (aic offset: 0x80) source vector register */
   uint32_t ivr;       /**< \brief (aic offset: 0x100) interrupt vector register */
   uint32_t fvr;       /**< \brief (aic offset: 0x104) fiq interrupt vector register */
   uint32_t isr;       /**< \brief (aic offset: 0x108) interrupt status register */
   uint32_t ipr;       /**< \brief (aic offset: 0x10c) interrupt pending register */
   uint32_t imr;       /**< \brief (aic offset: 0x110) interrupt mask register */
   uint32_t cisr;      /**< \brief (aic offset: 0x114) core interrupt status register */
   uint32_t reserved1[2];
   uint32_t iecr;      /**< \brief (aic offset: 0x120) interrupt enable command register */
   uint32_t idcr;      /**< \brief (aic offset: 0x124) interrupt disable command register */
   uint32_t iccr;      /**< \brief (aic offset: 0x128) interrupt clear command register */
   uint32_t iscr;      /**< \brief (aic offset: 0x12c) interrupt set command register */
   uint32_t eoicr;     /**< \brief (aic offset: 0x130) end of interrupt command register */
   uint32_t spu;       /**< \brief (aic offset: 0x134) spurious interrupt vector register */
   uint32_t dcr;       /**< \brief (aic offset: 0x138) debug control register */
   uint32_t reserved2[1];
   uint32_t ffer;      /**< \brief (aic offset: 0x140) fast forcing enable register */
   uint32_t ffdr;      /**< \brief (aic offset: 0x144) fast forcing disable register */
   uint32_t ffsr;      /**< \brief (aic offset: 0x148) fast forcing status register */
   uint32_t reserved3[38];
   uint32_t wpmr;      /**< \brief (aic offset: 0x1e4) write protect mode register */
   uint32_t wpsr;      /**< \brief (aic offset: 0x1e8) write protect status register */
} at91_aic_t;

#define AT91_AIC_SMR(n)		(AT91_AIC + ((n) * 4))	/* Source Mode Registers 0-31 */
#define		AT91_AIC_PRIOR		(7 << 0)		/* Priority Level */
#define		AT91_AIC_SRCTYPE	(3 << 5)		/* Interrupt Source Type */
#define			AT91_AIC_SRCTYPE_LOW		(0 << 5)
#define			AT91_AIC_SRCTYPE_FALLING	(1 << 5)
#define			AT91_AIC_SRCTYPE_HIGH		(2 << 5)
#define			AT91_AIC_SRCTYPE_RISING		(3 << 5)

#define AT91_AIC_SVR(n)		(AT91_AIC + 0x80 + ((n) * 4))	/* Source Vector Registers 0-31 */
#define AT91_AIC_IVR		(AT91_AIC + 0x100)	/* Interrupt Vector Register */
#define AT91_AIC_FVR		(AT91_AIC + 0x104)	/* Fast Interrupt Vector Register */
#define AT91_AIC_ISR		(AT91_AIC + 0x108)	/* Interrupt Status Register */
#define		AT91_AIC_IRQID		(0x1f << 0)		/* Current Interrupt Identifier */

#define AT91_AIC_IPR		(AT91_AIC + 0x10c)	/* Interrupt Pending Register */
#define AT91_AIC_IMR		(AT91_AIC + 0x110)	/* Interrupt Mask Register */
#define AT91_AIC_CISR		(AT91_AIC + 0x114)	/* Core Interrupt Status Register */
#define		AT91_AIC_NFIQ		(1 << 0)		/* nFIQ Status */
#define		AT91_AIC_NIRQ		(1 << 1)		/* nIRQ Status */

#define AT91_AIC_IECR		(AT91_AIC + 0x120)	/* Interrupt Enable Command Register */
#define AT91_AIC_IDCR		(AT91_AIC + 0x124)	/* Interrupt Disable Command Register */
#define AT91_AIC_ICCR		(AT91_AIC + 0x128)	/* Interrupt Clear Command Register */
#define AT91_AIC_ISCR		(AT91_AIC + 0x12c)	/* Interrupt Set Command Register */
#define AT91_AIC_EOICR		(AT91_AIC + 0x130)	/* End of Interrupt Command Register */
#define AT91_AIC_SPU		(AT91_AIC + 0x134)	/* Spurious Interrupt Vector Register */
#define AT91_AIC_DCR		(AT91_AIC + 0x138)	/* Debug Control Register */
#define		AT91_AIC_DCR_PROT	(1 << 0)		/* Protection Mode */
#define		AT91_AIC_DCR_GMSK	(1 << 1)		/* General Mask */

#define AT91_AIC_FFER		(AT91_AIC + 0x140)	/* Fast Forcing Enable Register [SAM9 only] */
#define AT91_AIC_FFDR		(AT91_AIC + 0x144)	/* Fast Forcing Disable Register [SAM9 only] */
#define AT91_AIC_FFSR		(AT91_AIC + 0x148)	/* Fast Forcing Status Register [SAM9 only] */

#endif
