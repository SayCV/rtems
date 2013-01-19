/**
 * @file
 *
 * @brief Boot and system start code.
 */

/*
 * Copyright (c) 2008-2011 embedded brains GmbH.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Obere Lagerstr. 30
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#include <bsp/linker-symbols.h>

#define ARM_MULTILIB_ARCH_V4

/* Some standard definitions...*/
.equ PSR_MODE_USR,       0x10
.equ PSR_MODE_FIQ,       0x11
.equ PSR_MODE_IRQ,       0x12
.equ PSR_MODE_SVC,       0x13
.equ PSR_MODE_ABT,       0x17
.equ PSR_MODE_UNDEF,     0x1B
.equ PSR_MODE_SYS,       0x1F

.equ PSR_I,              0x80
.equ PSR_F,              0x40
.equ PSR_T,              0x20


	/* External symbols */
	.extern	bsp_reset
	.extern	boot_card
	.extern	CSP_LED_NBR1_on
	.extern	CSP_LED_NBR2_on

	/* Global symbols */
	.globl	_start
	.globl	bsp_start_vector_table_begin
	.globl	bsp_start_vector_table_end
	.globl	bsp_start_vector_table_size
	.globl	bsp_vector_table_size

	.section	".bsp_start_text", "ax"

#if defined(ARM_MULTILIB_ARCH_V4)

	.arm

/*
 * This is the exception vector table and the pointers to the default
 * exceptions handlers.
 */

bsp_start_vector_table_begin:
_start:
	ldr	pc, Reset_Addr
	ldr	pc, Undefined_Addr
	ldr	pc, SWI_Addr
	ldr	pc, Prefetch_Addr
	ldr	pc, Abort_Addr

	/* Program signature checked by boot loader */
	.word	0xb8a06f58

	ldr	pc, IRQ_Addr
	ldr	pc, FIQ_Addr

	.globl Reset_Addr
Reset_Addr:	.word   _reset
Undefined_Addr:	.word	Undefined_Handler
SWI_Addr:	.word	SWI_Handler
Prefetch_Addr:	.word	Prefetch_Handler
Abort_Addr:	.word	Abort_Handler
		.word	0
IRQ_Addr:	.word	IRQ_Handler
FIQ_Addr:	.word	FIQ_Handler

/* The following handlers do not do anything useful */
	.globl Undefined_Handler
Undefined_Handler:
        B       Undefined_Handler
	.globl SWI_Handler
SWI_Handler:
        B       SWI_Handler
	.globl Prefetch_Handler
Prefetch_Handler:
        B       Prefetch_Handler
	.globl Abort_Handler
Abort_Handler:
        B       Abort_Handler
	.globl IRQ_Handler
IRQ_Handler:
        B       IRQ_Handler
	.globl FIQ_Handler
FIQ_Handler:
        B       FIQ_Handler

bsp_start_vector_table_end:

/* Start entry */

_reset:

        /*
         * Since I don't plan to return to the bootloader,
         * I don't have to save the registers.
         *
         * I'll just set the CPSR for SVC mode, interrupts
         * off, and ARM instructions.
         */
        mov     r0, #(PSR_MODE_SVC | PSR_I | PSR_F)
        msr     cpsr, r0

        /* zero the bss */
        ldr     r1, =bsp_section_bss_end
        ldr     r0, =bsp_section_bss_begin

_bss_init:
        mov     r2, #0
        cmp     r0, r1
        strlot  r2, [r0], #4
        blo     _bss_init        /* loop while r0 < r1 */
        
        /* --- Initialize stack pointer registers */
        /* Enter IRQ mode and set up the IRQ stack pointer */
        mov     r0, #(PSR_MODE_IRQ | PSR_I | PSR_F)     /* No interrupts */
        msr     cpsr, r0
        ldr     r1, =bsp_stack_irq_size
        ldr     sp, =bsp_stack_irq_begin
        add     sp, sp, r1

        /* Enter FIQ mode and set up the FIQ stack pointer */
        mov     r0, #(PSR_MODE_FIQ | PSR_I | PSR_F)     /* No interrupts */
        msr     cpsr, r0
        ldr     r1, =bsp_stack_fiq_size
        ldr     sp, =bsp_stack_fiq_begin
        add     sp, sp, r1

        /* Enter ABT mode and set up the ABT stack pointer */
        mov     r0, #(PSR_MODE_ABT | PSR_I | PSR_F)     /* No interrupts */
        msr     cpsr, r0
        ldr     r1, =bsp_stack_abt_size
        ldr     sp, =bsp_stack_abt_begin
        add     sp, sp, r1

        /* Set up the SVC stack pointer last and stay in SVC mode */
        mov     r0, #(PSR_MODE_SVC | PSR_I | PSR_F)     /* No interrupts */
        msr     cpsr, r0
        ldr     r1, =bsp_stack_svc_size
        ldr     sp, =bsp_stack_svc_begin
        add     sp, sp, r1
        sub     sp, sp, #0x64

	/* disable mmu, I and D caches*/
	nop
	nop
	mrc p15, 0, r0, c1, c0, 0
	bic r0, r0, #0x01
	bic r0, r0, #0x04
	bic r0, r0, #0x01000
	mcr p15, 0, r0, c1, c0, 0
	nop
	nop

	/* clean data cache */
	/* mov   r1,#0x00
Loop1:
	mov   r2,#0x00
Loop2:
	mov r3, r2, lsl#26
	orr r3, r3, r1, lsl#5
	mcr p15, 0, r3, c7, c14, 2
	add r2, r2, #0x01
	cmp r2, #64
	bne Loop2
	add r1, r1, #0x01
	cmp r1, #8
	bne Loop1 */


        /*
         * Initialize the MMU. After we return, the MMU is enabled,
         * and memory may be remapped. I hope we don't remap this
         * memory away.
         */
        /*ldr     r0, =mem_map
        bl      mmu_init*/
        //bl CSP_RemapRam

	/*
	 * Initialize the exception vectors.  This includes the exceptions
	 * vectors and the pointers to the default exception handlers.
	 */
	    /*
         * Initialize the exception vectors. This includes the
         * exceptions vectors (0x00000000-0x0000001c), and the
         * pointers to the exception handlers (0x00000020-0x0000003c).
         */

	ldr	r0, =bsp_vector_table_begin
	adr	r1, bsp_start_vector_table_begin
	ldmia	r1!, {r2-r9}
	stmia	r0!, {r2-r9}
	ldmia	r1!, {r2-r9}
	stmia	r0!, {r2-r9}

        /* Now we are prepared to start the BSP's C code */
        mov     r0, #0
        bl      boot_card

        /*
         * Theoretically, we could return to what started us up,
         * but we'd have to have saved the registers and stacks.
         * Instead, we'll just reset.
         */
        bl      bsp_reset

        /* We shouldn't get here. If we do, hang */
_hang:  b       _hang

#elif defined(ARM_MULTILIB_ARCH_V7M)

	.syntax	unified

	.extern	bsp_stack_main_end

	.thumb

bsp_start_vector_table_begin:

	.word	bsp_stack_main_end
	.word	_start /* Reset */
	.word	bsp_reset /* NMI */
	.word	bsp_reset /* Hard Fault */
	.word	bsp_reset /* MPU Fault */
	.word	bsp_reset /* Bus Fault */
	.word	bsp_reset /* Usage Fault */
	.word	bsp_reset /* Reserved */
	.word	bsp_reset /* Reserved */
	.word	bsp_reset /* Reserved */
	.word	bsp_reset /* Reserved */
	.word	bsp_reset /* SVC */
	.word	bsp_reset /* Debug Monitor */
	.word	bsp_reset /* Reserved */
	.word	bsp_reset /* PendSV */
	.word	bsp_reset /* SysTick */
	.rept	BSP_INTERRUPT_VECTOR_MAX + 1
	.word	bsp_reset /* IRQ */
	.endr

bsp_start_vector_table_end:

	.thumb_func

_start:

	ldr	sp, =bsp_stack_main_end
	ldr	lr, =bsp_start_hook_0_done + 1
	b	bsp_start_hook_0

bsp_start_hook_0_done:

	bl	bsp_start_hook_1
	movs	r0, #0
	bl	boot_card

twiddle:

	bl	bsp_reset
	b	twiddle

#endif /* defined(ARM_MULTILIB_ARCH_V7M) */

	.set	bsp_start_vector_table_size, bsp_start_vector_table_end - bsp_start_vector_table_begin
	.set	bsp_vector_table_size, bsp_start_vector_table_size
