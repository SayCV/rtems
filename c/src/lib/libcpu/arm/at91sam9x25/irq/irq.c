/*
 * Atmel AT91RM9200 Interrupt handler
 *
 * Copyright (c) 2010 embedded brains GmbH.
 *
 * Copyright (c) 2004 by Jay Monkman <jtm@lopingdog.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */

#include <bsp.h>
#include <bsp/irq.h>
#include <bsp/irq-generic.h>

#include <at91sam9x5.h>
#include <at91_aic.h>
#include <at91_io.h>

/*
*********************************************************************************************************
*                                           EXCEPTION DEFINES
*********************************************************************************************************
*/

                                                 /* ARM exception IDs                                  */
#define  CPU_RELOCATE_ARM_EXCEPT_RESET                                                                    0x00
#define  CPU_RELOCATE_ARM_EXCEPT_UNDEF_INSTR                                                              0x01
#define  CPU_RELOCATE_ARM_EXCEPT_SWI                                                                      0x02
#define  CPU_RELOCATE_ARM_EXCEPT_PREFETCH_ABORT                                                           0x03
#define  CPU_RELOCATE_ARM_EXCEPT_DATA_ABORT                                                               0x04
#define  CPU_RELOCATE_ARM_EXCEPT_ADDR_ABORT                                                               0x05
#define  CPU_RELOCATE_ARM_EXCEPT_IRQ                                                                      0x06
#define  CPU_RELOCATE_ARM_EXCEPT_FIQ                                                                      0x07
#define  CPU_RELOCATE_ARM_EXCEPT_NBR                                                                      0x08
                                                 /* ARM exception vectors addresses                    */
#define  CPU_RELOCATE_ARM_EXCEPT_RESET_VECT_ADDR              (CPU_RELOCATE_ARM_EXCEPT_RESET          * 0x04 + 0x00)
#define  CPU_RELOCATE_ARM_EXCEPT_UNDEF_INSTR_VECT_ADDR        (CPU_RELOCATE_ARM_EXCEPT_UNDEF_INSTR    * 0x04 + 0x00)
#define  CPU_RELOCATE_ARM_EXCEPT_SWI_VECT_ADDR                (CPU_RELOCATE_ARM_EXCEPT_SWI            * 0x04 + 0x00)
#define  CPU_RELOCATE_ARM_EXCEPT_PREFETCH_ABORT_VECT_ADDR     (CPU_RELOCATE_ARM_EXCEPT_PREFETCH_ABORT * 0x04 + 0x00)
#define  CPU_RELOCATE_ARM_EXCEPT_DATA_ABORT_VECT_ADDR         (CPU_RELOCATE_ARM_EXCEPT_DATA_ABORT     * 0x04 + 0x00)
#define  CPU_RELOCATE_ARM_EXCEPT_ADDR_ABORT_VECT_ADDR         (CPU_RELOCATE_ARM_EXCEPT_ADDR_ABORT     * 0x04 + 0x00)
#define  CPU_RELOCATE_ARM_EXCEPT_IRQ_VECT_ADDR                (CPU_RELOCATE_ARM_EXCEPT_IRQ            * 0x04 + 0x00)
#define  CPU_RELOCATE_ARM_EXCEPT_FIQ_VECT_ADDR                (CPU_RELOCATE_ARM_EXCEPT_FIQ            * 0x04 + 0x00)

                                                 /* ARM exception handlers addresses                   */
#define  CPU_RELOCATE_ARM_EXCEPT_RESET_HANDLER_ADDR           (CPU_RELOCATE_ARM_EXCEPT_RESET          * 0x04 + 0x20)
#define  CPU_RELOCATE_ARM_EXCEPT_UNDEF_INSTR_HANDLER_ADDR     (CPU_RELOCATE_ARM_EXCEPT_UNDEF_INSTR    * 0x04 + 0x20)
#define  CPU_RELOCATE_ARM_EXCEPT_SWI_HANDLER_ADDR             (CPU_RELOCATE_ARM_EXCEPT_SWI            * 0x04 + 0x20)
#define  CPU_RELOCATE_ARM_EXCEPT_PREFETCH_ABORT_HANDLER_ADDR  (CPU_RELOCATE_ARM_EXCEPT_PREFETCH_ABORT * 0x04 + 0x20)
#define  CPU_RELOCATE_ARM_EXCEPT_DATA_ABORT_HANDLER_ADDR      (CPU_RELOCATE_ARM_EXCEPT_DATA_ABORT     * 0x04 + 0x20)
#define  CPU_RELOCATE_ARM_EXCEPT_ADDR_ABORT_HANDLER_ADDR      (CPU_RELOCATE_ARM_EXCEPT_ADDR_ABORT     * 0x04 + 0x20)
#define  CPU_RELOCATE_ARM_EXCEPT_IRQ_HANDLER_ADDR             (CPU_RELOCATE_ARM_EXCEPT_IRQ            * 0x04 + 0x20)
#define  CPU_RELOCATE_ARM_EXCEPT_FIQ_HANDLER_ADDR             (CPU_RELOCATE_ARM_EXCEPT_FIQ            * 0x04 + 0x20)

                                                 /* ARM "Jump To Self" asm instruction                 */
#define  CPU_RELOCATE_ARM_INSTR_JUMP_TO_SELF                   0xEAFFFFFE
                                                 /* ARM "Jump To Exception Handler" asm instruction    */
#define  CPU_RELOCATE_ARM_INSTR_JUMP_TO_HANDLER                0xE59FF018

void       Undefined_Handler   (void);
void       SWI_Handler          (void);
void       Prefetch_Handler(void);
void       Abort_Handler    (void);
//void       not_used    (void);
void       IRQ_Handler          (void);
void       FIQ_Handler          (void);

void  CPU_Relocate_InitExceptVect (void)
{
    (*(unsigned int *)CPU_RELOCATE_ARM_EXCEPT_UNDEF_INSTR_VECT_ADDR)       =         CPU_RELOCATE_ARM_INSTR_JUMP_TO_HANDLER;
    (*(unsigned int *)CPU_RELOCATE_ARM_EXCEPT_UNDEF_INSTR_HANDLER_ADDR)    = (unsigned int)Undefined_Handler;

    (*(unsigned int *)CPU_RELOCATE_ARM_EXCEPT_SWI_VECT_ADDR)               =         CPU_RELOCATE_ARM_INSTR_JUMP_TO_HANDLER;
    (*(unsigned int *)CPU_RELOCATE_ARM_EXCEPT_SWI_HANDLER_ADDR)            = (unsigned int)SWI_Handler;

    (*(unsigned int *)CPU_RELOCATE_ARM_EXCEPT_PREFETCH_ABORT_VECT_ADDR)    =         CPU_RELOCATE_ARM_INSTR_JUMP_TO_HANDLER;
    (*(unsigned int *)CPU_RELOCATE_ARM_EXCEPT_PREFETCH_ABORT_HANDLER_ADDR) = (unsigned int)Prefetch_Handler;

    (*(unsigned int *)CPU_RELOCATE_ARM_EXCEPT_DATA_ABORT_VECT_ADDR)        =         CPU_RELOCATE_ARM_INSTR_JUMP_TO_HANDLER;
    (*(unsigned int *)CPU_RELOCATE_ARM_EXCEPT_DATA_ABORT_HANDLER_ADDR)     = (unsigned int)Abort_Handler;

    (*(unsigned int *)CPU_RELOCATE_ARM_EXCEPT_ADDR_ABORT_VECT_ADDR)        =         CPU_RELOCATE_ARM_INSTR_JUMP_TO_HANDLER;
    (*(unsigned int *)CPU_RELOCATE_ARM_EXCEPT_ADDR_ABORT_HANDLER_ADDR)     = (unsigned int)CPU_RELOCATE_ARM_INSTR_JUMP_TO_SELF;

    (*(unsigned int *)CPU_RELOCATE_ARM_EXCEPT_IRQ_VECT_ADDR)               =         CPU_RELOCATE_ARM_INSTR_JUMP_TO_HANDLER;
    (*(unsigned int *)CPU_RELOCATE_ARM_EXCEPT_IRQ_HANDLER_ADDR)            = (unsigned int)IRQ_Handler;

    (*(unsigned int *)CPU_RELOCATE_ARM_EXCEPT_FIQ_VECT_ADDR)               =         CPU_RELOCATE_ARM_INSTR_JUMP_TO_HANDLER;
    (*(unsigned int *)CPU_RELOCATE_ARM_EXCEPT_FIQ_HANDLER_ADDR)            = (unsigned int)FIQ_Handler;
}
void bsp_interrupt_dispatch(void)
{
  rtems_vector_number vector = at91_sys_read(AT91_AIC_IVR);//AIC_CTL_REG(AIC_IVR);
  //rtems_vector_number vector = at91_sys_read(AT91_AIC_ISR) & 0x1F;
	dbgu_printf("bsp_interrupt_dispatch Start.\r\n");
	printk("bsp_interrupt_dispatch interrupt: %u\n", vector);
  bsp_interrupt_handler_dispatch(vector);

  at91_sys_write(AT91_AIC_EOICR, 0);//AIC_CTL_REG(AIC_EOICR) = 0;
}

rtems_status_code bsp_interrupt_vector_enable(rtems_vector_number vector)
{
  at91_sys_write(AT91_AIC_IECR, 1 << vector);//AIC_CTL_REG(AIC_IECR) = 1 << vector;

  return RTEMS_SUCCESSFUL;
}

rtems_status_code bsp_interrupt_vector_disable(rtems_vector_number vector)
{
  at91_sys_write(AT91_AIC_IDCR, 1 << vector);//AIC_CTL_REG(AIC_IDCR) = 1 << vector;

  return RTEMS_SUCCESSFUL;
}

rtems_status_code bsp_interrupt_facility_initialize(void)
{
  unsigned long i = 0;

  for (i = 0; i < 32; ++i) {
    /* Put irq number in Source Vector Register: */
		at91_sys_write(AT91_AIC_SVR(i), i);
		/* Active Low interrupt, with the specified priority */
		at91_sys_write(AT91_AIC_SMR(i), AT91_AIC_SRCTYPE_LOW);
		/* Perform 8 End Of Interrupt Command to make sure AIC will not Lock out nIRQ */
		if (i < 8)
			at91_sys_write(AT91_AIC_EOICR, 0);
  }
	/*
	 * Spurious Interrupt ID in Spurious Vector Register is NR_AIC_IRQS
	 * When there is no current interrupt, the IRQ Vector Register reads the value stored in AIC_SPU
	 */
	at91_sys_write(AT91_AIC_SPU, 32);

	/* No debugging in AIC: Debug (Protect) Control Register */
	//at91_sys_write(AT91_AIC_DCR, 0);

	/* Disable and clear all interrupts initially */
	at91_sys_write(AT91_AIC_IDCR, 0xFFFFFFFF);
	at91_sys_write(AT91_AIC_ICCR, 0xFFFFFFFF);
	
	CPU_Relocate_InitExceptVect();
	
	/*
	 * cpukit\score\cpu\arm\rtems\score\cpu.h ARM_EXCEPTION_IRQ = 6,
	 * cpukit\score\cpu\arm\arm_exc_interrupt.S arm_exc_interrupt
	 */
  _CPU_ISR_install_vector(ARM_EXCEPTION_IRQ, arm_exc_interrupt, NULL);
	
  return RTEMS_SUCCESSFUL;
}
