/*
 * Cirrus EP7312 Startup code
 *
 * Copyright (c) 2010 embedded brains GmbH.
 *
 * Copyright (c) 2002 by Jay Monkman <jtm@smoothsmoothie.com>
 *
 * Copyright (c) 2002 by Charlie Steader <charlies@poliac.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
*/

#include <bsp/linker-symbols.h>

	/* External symbols */
	.extern	bsp_reset
	.extern	boot_card
	.extern CSP_LED_NBR1_on
	.extern CSP_RemapRam
	.extern boot_card

	/* Global symbols */
	.globl	_start
	.globl	bsp_start_vector_table_begin
	.globl	bsp_start_vector_table_end
	.globl	bsp_start_vector_table_size
	.globl	bsp_vector_table_size

	.globl Reset_Handler
	.globl Undefined_Handler
	.globl SWI_Handler
	.globl Prefetch_Handler
	.globl Abort_Handler
	.globl IRQ_Handler
	.globl FIQ_Handler
	
/* Some standard definitions...*/

.equ Mode_USR,        	     0x10
.equ Mode_FIQ,        	     0x11
.equ Mode_IRQ,        	     0x12
.equ Mode_SVC,        	     0x13
.equ Mode_ABT,        	     0x17
.equ Mode_ABORT,             0x17
.equ Mode_UNDEF,      	     0x1B
.equ Mode_SYS,        	     0x1F /*only available on ARM Arch. v4*/

.equ I_Bit,           	     0x80
.equ F_Bit,           	     0x40

.section ".bsp_start_text", "ax"

	.arm
	
/*******************************************************
 standard exception vectors table
 *** Must be located at address 0
********************************************************/

bsp_start_vector_table_begin:
	LDR	PC, Reset_Addr
	LDR	PC, Undefined_Addr
	LDR	PC, SWI_Addr
	LDR	PC, Prefetch_Addr
	LDR	PC, Abort_Addr
	/* Program signature checked by boot loader */
	.word	0xb8a06f58
	LDR	PC, IRQ_Addr
	LDR	PC, FIQ_Addr

Reset_Addr:	.long	Reset_Handler
Undefined_Addr:	.long	Undefined_Handler
SWI_Addr:	.long	SWI_Handler
Prefetch_Addr:	.long	Prefetch_Handler
Abort_Addr:	.long	Abort_Handler
		.long	0
IRQ_Addr:	.long	IRQ_Handler
FIQ_Addr:	.long	FIQ_Handler


Reset_Handler:          b       _start
Undefined_Handler:      b       Undefined_Handler
SWI_Handler:            b       SWI_Handler
Prefetch_Handler:       b       Prefetch_Handler
Abort_Handler:          b       Abort_Handler
                        nop
IRQ_Handler:            b       IRQ_Handler
FIQ_Handler:            b       FIQ_Handler

bsp_start_vector_table_end:

_start:
	/* store the sp */
	mov	r12, sp
	
        /*
         * Since I don't plan to return to the bootloader,
         * I don't have to save the registers.
         *
         * I'll just set the CPSR for SVC mode, interrupts
         * off, and ARM instructions.
         */
        mov     r0, #(PSR_MODE_SVC | PSR_I | PSR_F)
        msr     cpsr, r0
        
/*
 * Here is the code to initialize the low-level BSP environment
 * (Chip Select, PLL, ....?)
 */

		bl			CSP_LED_NBR1_on
		
		bl			CSP_RemapRam
		
		/*
		 * relocate exception table
		 */
		ldr	r0, =bsp_start_vector_table_begin
		ldr	r1, =0x0
		mov	r2, #16
copyex:
		subs	r2, r2, #1
		ldr	r3, [r0], #4
		str	r3, [r1], #4
		bne	copyex

        /* zero the bss */
        ldr     r1, =bsp_section_bss_end
        ldr     r0, =bsp_section_bss_begin

_bss_init:
        mov     r2, #0
        cmp     r0, r1
        strlot  r2, [r0], #4
        blo     _bss_init        /* loop while r0 < r1 */

/* --- Initialise stack pointer registers */

/* Enter IRQ mode and set up the IRQ stack pointer */
    MOV     r0, #Mode_IRQ | I_Bit | F_Bit     /* No interrupts */
    MSR     cpsr, r0
    ldr	    r1, =bsp_stack_irq_size
    LDR     sp, =bsp_stack_irq_begin
    add	    sp, sp, r1
    sub     sp, sp, #0x64

/* Enter FIQ mode and set up the FIQ stack pointer */
    MOV     r0, #Mode_FIQ | I_Bit | F_Bit     /* No interrupts */
    MSR     cpsr, r0
    ldr	    r1, =bsp_stack_fiq_size
    LDR     sp, =bsp_stack_fiq_begin
    add	    sp, sp, r1
    sub     sp, sp, #0x64

/* Enter ABT mode and set up the ABT stack pointer */
    MOV     r0, #Mode_ABT | I_Bit | F_Bit     /* No interrupts */
    MSR     cpsr, r0
    ldr	    r1, =bsp_stack_abt_size
    LDR     sp, =bsp_stack_abt_begin
    add	    sp, sp, r1
    sub     sp, sp, #0x64

/* Set up the SVC stack pointer last and stay in SVC mode */
    MOV     r0, #Mode_SVC | I_Bit | F_Bit     /* No interrupts */
    MSR     cpsr, r0
    ldr	    r1, =bsp_stack_svc_size
    LDR     sp, =bsp_stack_svc_begin
    add	    sp, sp, r1
    sub     sp, sp, #0x64


		
	/* save the original registers */
	stmdb	sp!, {r4-r12, lr}

/* --- Now we enter the C code */

	mov     r0, #0
	bl	boot_card

	ldmia	sp!, {r4-r12, lr}
	mov	sp, r12
	mov	pc, lr

#if 0
Undefined_Handler:      b       Undefined_Handler
SWI_Handler:            b       SWI_Handler
Prefetch_Handler:       b       Prefetch_Handler
Abort_Handler:          b       Abort_Handler
                        nop
IRQ_Handler:            b       IRQ_Handler
FIQ_Handler:            b       FIQ_Handler


.globl Undefined_Handler
.globl SWI_Handler
.globl Prefetch_Handler
.globl Abort_Handler
.globl IRQ_Handler
.globl FIQ_Handler
#endif

	.set	bsp_start_vector_table_size, bsp_start_vector_table_end - bsp_start_vector_table_begin
	.set	bsp_vector_table_size, bsp_start_vector_table_size
	