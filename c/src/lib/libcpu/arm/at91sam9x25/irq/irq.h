/*
 * Interrupt handler Header file
 *
 * Copyright (c) 2010 embedded brains GmbH.
 *
 * Copyright (c) 2004 by Jay Monkman <jtm@lopingdog.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */

#ifndef __IRQ_H__
#define __IRQ_H__

#ifndef __asm__

#include <rtems.h>
#include <rtems/irq.h>
#include <rtems/irq-extension.h>

#endif /* __asm__ */

/* possible interrupt sources on the AT91RM9200 */
#define AT91_INT_FIQ		0	/* Advanced Interrupt Controller (FIQ) */
#define AT91_INT_SYS		1	/* System Controller Interrupt */
#define AT91SAM9X5_INT_PIOAB	2	/* Parallel I/O Controller A and B */
#define AT91SAM9X5_INT_PIOCD	3	/* Parallel I/O Controller C and D */
#define AT91SAM9X5_INT_SMD	4	/* SMD Soft Modem (SMD) */
#define AT91SAM9X5_INT_USART0	5	/* USART 0 */
#define AT91SAM9X5_INT_USART1	6	/* USART 1 */
#define AT91SAM9X5_INT_USART2	7	/* USART 2 */
#define AT91SAM9X5_INT_USART3	8	/* USART 3 */
#define AT91SAM9X5_INT_TWI0	9	/* Two-Wire Interface 0 */
#define AT91SAM9X5_INT_TWI1	10	/* Two-Wire Interface 1 */
#define AT91SAM9X5_INT_TWI2	11	/* Two-Wire Interface 2 */
#define AT91SAM9X5_INT_MCI0	12	/* High Speed Multimedia Card Interface 0 */
#define AT91SAM9X5_INT_SPI0	13	/* Serial Peripheral Interface 0 */
#define AT91SAM9X5_INT_SPI1	14	/* Serial Peripheral Interface 1 */
#define AT91SAM9X5_INT_UART0	15	/* UART 0 */
#define AT91SAM9X5_INT_UART1	16	/* UART 1 */
#define AT91SAM9X5_INT_TCB	17	/* Timer Counter 0, 1, 2, 3, 4 and 5 */
#define AT91SAM9X5_INT_PWM	18	/* Pulse Width Modulation Controller */
#define AT91SAM9X5_INT_ADC	19	/* ADC Controller */
#define AT91SAM9X5_INT_DMA0	20	/* DMA Controller 0 */
#define AT91SAM9X5_INT_DMA1	21	/* DMA Controller 1 */
#define AT91SAM9X5_INT_UHPHS	22	/* USB Host High Speed */
#define AT91SAM9X5_INT_UDPHS	23	/* USB Device High Speed */
#define AT91SAM9X5_INT_EMAC0	24	/* Ethernet MAC0 */
#define AT91SAM9X5_INT_LCDC	25	/* LCD Controller */
#define AT91SAM9X5_INT_ISI	25	/* Image Sensor Interface */
#define AT91SAM9X5_INT_MCI1	26	/* High Speed Multimedia Card Interface 1 */
#define AT91SAM9X5_INT_EMAC1	27	/* Ethernet MAC1 */
#define AT91SAM9X5_INT_SSC	28	/* Synchronous Serial Controller */
#define AT91SAM9X5_INT_CAN0	29	/* CAN Controller 0 */
#define AT91SAM9X5_INT_CAN1	30	/* CAN Controller 1 */
#define AT91SAM9X5_INT_IRQ0	31	/* Advanced Interrupt Controller */
#define AT91SAM9X5_MAX_INT       32

#define BSP_INTERRUPT_VECTOR_MIN 0

#define BSP_INTERRUPT_VECTOR_MAX (AT91SAM9X5_MAX_INT - 1)

#endif /* __IRQ_H__ */
