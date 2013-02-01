/*
 * SayCV_SAM9X25 startup code
 *
 * Copyright (c) 2004 by Jay Monkman <jtm@lopingdog.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
*/

#include <bsp/linker-symbols.h>

	/* External symbols */
	.extern	bsp_reset
	.extern	boot_card
	.extern	CSP_RemapRam
	.extern	CSP_LED_NBRs_Init
	.extern	CSP_LED_NBR1_on
	.extern	CSP_LED_NBR2_on

	/* Global symbols */
	.globl  _start
	.globl	_start_init
	
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
	
	.equ MMU_C1_M,       		0x0001  
	.equ MMU_C1_I,					0x1000  

#if 0
	.text
#else	
	.section	".bsp_start_text", "ax"
	.arm
#endif

_start:
/*
 * This is the exception vector table and the pointers to
 * the functions that handle the exceptions. It's a total
 * of 16 words (64 bytes)
 */

vector_block:

#if 0
        b	_start_init /* ldr     pc, Reset_Handler */
        ldr     pc, Undefined_Handler
        ldr     pc, SWI_Handler
        ldr     pc, Prefetch_Handler
        ldr     pc, Abort_Handler
        nop
        ldr     pc, IRQ_Handler
        ldr     pc, FIQ_Handler
#if 0
Reset_Handler:      
	b       _start_init
#endif
Undefined_Handler:      
	b       Undefined_Handler
SWI_Handler:            
	b       SWI_Handler
Prefetch_Handler:       
	b       Prefetch_Handler
Abort_Handler:          
	b       Abort_Handler
	nop
IRQ_Handler:            
	b       IRQ_Handler
FIQ_Handler:            
	b       FIQ_Handler

#else
#if 1
	B		_start_init
#else
	LDR	PC, Reset_Addr
#endif
	LDR	PC, Undefined_Addr
	LDR	PC, SWI_Addr
	LDR	PC, Prefetch_Addr
	LDR	PC, Abort_Addr
	NOP
	LDR	PC, IRQ_Addr
	LDR	PC, FIQ_Addr
#if 0
	.globl Reset_Addr
Reset_Addr:	
	.word   _start_init
#endif
Undefined_Addr:
	.word	Undefined_Handler
SWI_Addr:	
	.word	SWI_Handler
Prefetch_Addr:	
	.word	Prefetch_Handler
Abort_Addr:	
	.word	Abort_Handler
	/* Program signature checked by boot loader */
	.word	0xb8a06f58
IRQ_Addr:	
	.word	IRQ_Handler
FIQ_Addr:	
	.word	FIQ_Handler

	


_start_init:
				
        /*
         * Since I don't plan to return to the bootloader,
         * I don't have to save the registers.
         *
         * I'll just set the CPSR for SVC mode, interrupts
         * off, and ARM instructions.
         */
        mov     r0, #(PSR_MODE_SVC | PSR_I | PSR_F)
        msr     cpsr, r0
         
        /* bl  CSP_RemapRam */
        
#if	0
				/*
				 * relocate exception table
				 */
				ldr	r0, =_start
				ldr	r1, =0x0
				mov	r2, #16
copyex:
				subs	r2, r2, #1
				ldr	r3, [r0], #4
				str	r3, [r1], #4
				bne	copyex
#endif
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

#if 0    
        /*
         * Initialize the MMU. After we return, the MMU is enabled,
         * and memory may be remapped. I hope we don't remap this
         * memory away.
         */
        ldr     r0, =mem_map
        bl      mmu_init
#else    
        /*shut down mmu*/
        /* */
    		MRC P15, 0, R0, C1, C0, 0  
    		BIC R0, R0, #MMU_C1_M  
    		ORR R0, R0, #MMU_C1_I  
    		MCR P15, 0, R0, C1, C0, 0
    		/**/
#endif

#if 0
        /*
         * Initialize the exception vectors. This includes the
         * exceptions vectors (0x00000000-0x0000001c), and the
         * pointers to the exception handlers (0x00000020-0x0000003c).
         */
        mov     r0, #0
        adr     r1, vector_block
        ldmia   r1!, {r2-r9}
        stmia   r0!, {r2-r9}
        ldmia   r1!, {r2-r9}
        stmia   r0!, {r2-r9}
#endif
        /* Now we are prepared to start the BSP's C code */
#if 0 /* avoid cpu reset */
        bl  CSP_LED_NBRs_Init
        bl  CSP_LED_NBR1_on
        bl  CSP_LED_NBR2_on
#endif       
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
#endif
/* .globl Reset_Handler */
	.globl Undefined_Handler
	.globl SWI_Handler
	.globl Prefetch_Handler
	.globl Abort_Handler
	.globl IRQ_Handler
	.globl FIQ_Handler
