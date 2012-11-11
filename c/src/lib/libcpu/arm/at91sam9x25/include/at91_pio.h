/*
 * [origin: Linux kernel include/asm-arm/arch-at91/at91_pio.h]
 *
 * Copyright (C) 2005 Ivan Kokshaysky
 * Copyright (C) SAN People
 * Copyright (C) 2009 Jens Scharsig (js_at_ng@scharsoft.de)
 *
 * Parallel I/O Controller (PIO) - System peripherals registers.
 * Based on AT91RM9200 datasheet revision E.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef AT91_PIO_H
#define AT91_PIO_H


#define AT91_ASM_PIO_RANGE	0x200
#define AT91_ASM_PIOC_ASR	\
	(AT91_PIO_BASE + AT91_PIO_PORTC * AT91_ASM_PIO_RANGE + 0x70)
#define AT91_ASM_PIOC_BSR	\
	(AT91_PIO_BASE + AT91_PIO_PORTC * AT91_ASM_PIO_RANGE + 0x74)
#define AT91_ASM_PIOC_PDR	\
	(AT91_PIO_BASE + AT91_PIO_PORTC * AT91_ASM_PIO_RANGE + 0x04)
#define AT91_ASM_PIOC_PUDR	\
	(AT91_PIO_BASE + AT91_PIO_PORTC * AT91_ASM_PIO_RANGE + 0x60)

#define AT91_ASM_PIOD_PDR	\
	(AT91_PIO_BASE + AT91_PIO_PORTD * AT91_ASM_PIO_RANGE + 0x04)
#define AT91_ASM_PIOD_PUDR	\
	(AT91_PIO_BASE + AT91_PIO_PORTD * AT91_ASM_PIO_RANGE + 0x60)
#define AT91_ASM_PIOD_ASR	\
	(AT91_PIO_BASE + AT91_PIO_PORTD * AT91_ASM_PIO_RANGE + 0x70)

#ifndef __ASSEMBLY__

typedef struct at91_port {
	uint32_t	per;		/* 0x00 PIO Enable Register */
	uint32_t	pdr;		/* 0x04 PIO Disable Register */
	uint32_t	psr;		/* 0x08 PIO Status Register */
	uint32_t	reserved0;
	uint32_t	oer;		/* 0x10 Output Enable Register */
	uint32_t	odr;		/* 0x14 Output Disable Registerr */
	uint32_t	osr;		/* 0x18 Output Status Register */
	uint32_t	reserved1;
	uint32_t	ifer;		/* 0x20 Input Filter Enable Register */
	uint32_t	ifdr;		/* 0x24 Input Filter Disable Register */
	uint32_t	ifsr;		/* 0x28 Input Filter Status Register */
	uint32_t	reserved2;
	uint32_t	sodr;		/* 0x30 Set Output Data Register */
	uint32_t	codr;		/* 0x34 Clear Output Data Register */
	uint32_t	odsr;		/* 0x38 Output Data Status Register */
	uint32_t	pdsr;		/* 0x3C Pin Data Status Register */
	uint32_t	ier;		/* 0x40 Interrupt Enable Register */
	uint32_t	idr;		/* 0x44 Interrupt Disable Register */
	uint32_t	imr;		/* 0x48 Interrupt Mask Register */
	uint32_t	isr;		/* 0x4C Interrupt Status Register */
	uint32_t	mder;		/* 0x50 Multi-driver Enable Register */
	uint32_t	mddr;		/* 0x54 Multi-driver Disable Register */
	uint32_t	mdsr;		/* 0x58 Multi-driver Status Register */
	uint32_t	reserved3;
	uint32_t	pudr;		/* 0x60 Pull-up Disable Register */
	uint32_t	puer;		/* 0x64 Pull-up Enable Register */
	uint32_t	pusr;		/* 0x68 Pad Pull-up Status Register */
	uint32_t	reserved4;
#if defined(CONFIG_AT91SAM9X5)
	uint32_t abcdsr1;	/* 0x70 Peripheral ABCD Select Register 1 */
#else
	uint32_t	asr;		/* 0x70 Select A Register */
#endif
#if defined(CONFIG_AT91SAM9X5)
	uint32_t abcdsr2;	/* 0x74 Peripheral ABCD Select Register 2 */
#else
	uint32_t	bsr;		/* 0x74 Select B Register */
#endif
	uint32_t	absr;		/* 0x78 AB Select Status Register */
#if defined(CONFIG_AT91SAM9X5)
	uint32_t reserved5;
	uint32_t ifscdr;	/* 0x80 Input Filter Slow Clock Disable Register */
	uint32_t ifscer;	/* 0x84 Input Filter Slow Clock Enable Register */
	uint32_t ifscsr;	/* 0x88 Input Filter Slow Clock Status Register */
	uint32_t scdr;	/* 0x8C Slow Clock Divider Debouncing Register */
	uint32_t ppddr;	/* 0x90 Pad Pull-down Disable Register */
	uint32_t ppder;	/* 0x94 Pad Pull-down Enable Register */
	uint32_t ppdsr;	/* 0x98 Pad Pull-down Status Register */
	uint32_t reserved6;	/*  */
#else
	uint32_t	reserved5[9];	/*  */
#endif
	uint32_t	ower;		/* 0xA0 Output Write Enable Register */
	uint32_t	owdr;		/* 0xA4 Output Write Disable Register */
	uint32_t	owsr;		/* OxA8 Output Write Status Register */
#if defined(CONFIG_AT91SAM9X5)
	uint32_t reserved7;	/*  */
	uint32_t aimer;	/* 0xB0 Additional Interrupt Modes Enable Register */
	uint32_t aimdr;	/* 0xB4 Additional Interrupt Modes Disable Register */
	uint32_t aimmr;	/* 0xB8 Additional Intterupt Modes Mask Register */
	uint32_t reserved8;	/* */
	uint32_t esr;		/* 0xC0 Edge Select Register */
	uint32_t lsr;		/* 0xC4 Level Select Register */
	uint32_t elsr;		/* 0xC8 Edge/Level Status Register */
	uint32_t reserved9;	/* 0xCC */
	uint32_t fellsr;	/* 0xD0 Falling Edge/Low Level Select Register */
	uint32_t rehlsr;	/* 0xD4 Rising Edge/High Level Select Register */
	uint32_t frlhsr;	/* 0xD8 Fall/Rise - Low/High Status Register */
	uint32_t reserved10[9];	/* */
	uint32_t schmitt;	/* 0x100 Schmitt Trigger Register */
	uint32_t reserved11[63];
#else
	uint32_t	reserved6[85];
#endif
} at91_port_t;

#define		PIO_SCDR_DIV	(0x3fff <<  0)	/* Slow Clock Divider Mask */

#if defined(CONFIG_AT91SAM9260) || defined(CONFIG_AT91SAM9261) || \
	defined(CONFIG_AT91SAM9G10) || defined(CONFIG_AT91SAM9G20)
#define AT91_PIO_PORTS	3
#elif defined(CONFIG_AT91SAM9263) || defined(CONFIG_AT91SAM9G45) || \
	defined(CONFIG_AT91SAM9M10G45)
#define AT91_PIO_PORTS	5
#elif defined(CONFIG_AT91RM9200) || defined(CONFIG_AT91CAP9) || \
	defined(CONFIG_AT91SAM9RL)
#define AT91_PIO_PORTS	4
#elif defined(CONFIG_AT91SAM9X5)
#define AT91_PIO_PORTS	4
#define CPU_HAS_PIO3	1
#else
#error "Unsupported cpu. Please update at91_pio.h"
#endif

typedef union at91_pio {
	struct {
		at91_port_t	pioa;
		at91_port_t	piob;
		at91_port_t	pioc;
	#if (AT91_PIO_PORTS > 3)
		at91_port_t	piod;
	#endif
	#if (AT91_PIO_PORTS > 4)
		at91_port_t	pioe;
	#endif
	} ;
	at91_port_t port[AT91_PIO_PORTS];
} at91_pio_t;

#ifdef CONFIG_AT91_GPIO
int at91_set_a_periph(unsigned port, unsigned pin, int use_pullup);
int at91_set_b_periph(unsigned port, unsigned pin, int use_pullup);
#if defined(CPU_HAS_PIO3)
int at91_set_c_periph(unsigned port, unsigned pin, int use_pullup);
int at91_set_d_periph(unsigned port, unsigned pin, int use_pullup);
int at91_set_pio_debounce(unsigned port, unsigned pin, int is_on, int div);
int at91_set_pio_pulldown(unsigned port, unsigned pin, int is_on);
int at91_set_pio_disable_schmitt_trig(unsigned port, unsigned pin);
#endif
int at91_set_pio_input(unsigned port, unsigned pin, int use_pullup);
int at91_set_pio_multi_drive(unsigned port, unsigned pin, int is_on);
int at91_set_pio_output(unsigned port, unsigned pin, int value);
int at91_set_pio_periph(unsigned port, unsigned pin, int use_pullup);
int at91_set_pio_pullup(unsigned port, unsigned pin, int use_pullup);
int at91_set_pio_deglitch(unsigned port, unsigned pin, int is_on);
int at91_set_pio_value(unsigned port, unsigned pin, int value);
int at91_get_pio_value(unsigned port, unsigned pin);
#endif
#endif

#define	AT91_PIO_PORTA		0x0
#define	AT91_PIO_PORTB		0x1
#define	AT91_PIO_PORTC		0x2
#define	AT91_PIO_PORTD		0x3
#define	AT91_PIO_PORTE		0x4

#ifdef CONFIG_AT91_LEGACY

#define PIO_PER		0x00	/* Enable Register */
#define PIO_PDR		0x04	/* Disable Register */
#define PIO_PSR		0x08	/* Status Register */
#define PIO_OER		0x10	/* Output Enable Register */
#define PIO_ODR		0x14	/* Output Disable Register */
#define PIO_OSR		0x18	/* Output Status Register */
#define PIO_IFER	0x20	/* Glitch Input Filter Enable */
#define PIO_IFDR	0x24	/* Glitch Input Filter Disable */
#define PIO_IFSR	0x28	/* Glitch Input Filter Status */
#define PIO_SODR	0x30	/* Set Output Data Register */
#define PIO_CODR	0x34	/* Clear Output Data Register */
#define PIO_ODSR	0x38	/* Output Data Status Register */
#define PIO_PDSR	0x3c	/* Pin Data Status Register */
#define PIO_IER		0x40	/* Interrupt Enable Register */
#define PIO_IDR		0x44	/* Interrupt Disable Register */
#define PIO_IMR		0x48	/* Interrupt Mask Register */
#define PIO_ISR		0x4c	/* Interrupt Status Register */
#define PIO_MDER	0x50	/* Multi-driver Enable Register */
#define PIO_MDDR	0x54	/* Multi-driver Disable Register */
#define PIO_MDSR	0x58	/* Multi-driver Status Register */
#define PIO_PUDR	0x60	/* Pull-up Disable Register */
#define PIO_PUER	0x64	/* Pull-up Enable Register */
#define PIO_PUSR	0x68	/* Pull-up Status Register */
#define PIO_ASR		0x70	/* Peripheral A Select Register */
#define PIO_ABCDSR1	0x70	/* Peripheral ABCD Select Register 1[sam9x5] */
#define PIO_BSR		0x74	/* Peripheral B Select Register */
#define PIO_ABCDSR2	0x74	/* Peripheral ABCD Select Register 2[sam9x5] */
#define PIO_ABSR	0x78	/* AB Status Register */
#define PIO_IFSCDR	0x80	/* Input Filter Slow Clock Disable Register */
#define PIO_IFSCER	0x84	/* Input Filter Slow Clock Enable Register */
#define PIO_IFSCSR	0x88	/* Input Filter Slow Clock Status Register */
#define PIO_SCDR	0x8c	/* Slow Clock Divider Debouncing Register */
#define		PIO_SCDR_DIV	(0x3fff <<  0)	/* Slow Clock Divider Mask */
#define PIO_PPDDR	0x90	/* Pad Pull-down Disable Register */
#define PIO_PPDER	0x94	/* Pad Pull-down Enable Register */
#define PIO_PPDSR	0x98	/* Pad Pull-down Status Register */
#define PIO_OWER	0xa0	/* Output Write Enable Register */
#define PIO_OWDR	0xa4	/* Output Write Disable Register */
#define PIO_OWSR	0xa8	/* Output Write Status Register */
#define PIO_AIMER	0xb0	/* Additional Interrupt Modes Enable Register */
#define PIO_AIMDR	0xb4	/* Additional Interrupt Modes Disable Register */
#define PIO_AIMMR	0xb8	/* Additional Interrupt Modes Mask Register */
#define PIO_ESR		0xc0	/* Edge Select Register */
#define PIO_LSR		0xc4	/* Level Select Register */
#define PIO_ELSR	0xc8	/* Edge/Level Status Register */
#define PIO_FELLSR	0xd0	/* Falling Edge/Low Level Select Register */
#define PIO_REHLSR	0xd4	/* Rising Edge/ High Level Select Register */
#define PIO_FRLHSR	0xd8	/* Fall/Rise - Low/High Status Register */
#define PIO_SCHMITT	0x100	/* Schmitt Trigger Register */

#define ABCDSR_PERIPH_A	0x0
#define ABCDSR_PERIPH_B	0x1
#define ABCDSR_PERIPH_C	0x2
#define ABCDSR_PERIPH_D	0x3

#endif

#endif
