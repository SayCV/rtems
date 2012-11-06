/*
*********************************************************************************************************
*        CSP
* Chip Support Package
* Filename      : csp_int.c
* Note(s)       : 
*
*  The license and distribution terms for this file may be
*  found in the file LICENSE in this distribution or at
*  http://www.rtems.com/license/LICENSE.
*********************************************************************************************************
*/




/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#define    CSP_INT_MODULE

#include <bsp.h>
#include <bsp/irq.h>
#include <bsp/irq-generic.h>
#include <csp.h>



/*
*********************************************************************************************************
*                                          DEFAULT CONFIGURATION
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  CSP_INT_AIC_BASE                   ((CPU_INT32U)0xFFFFF000U)

#define  CSP_INT_AIC_SMR(n)         (*(CPU_REG32 *)(CSP_INT_AIC_BASE  + 0x0000 + 4 * (n)))
#define  CSP_INT_AIC_SVR(n)         (*(CPU_REG32 *)(CSP_INT_AIC_BASE  + 0x0080 + 4 * (n)))
#define  CSP_INT_AIC_IVR            (*(CPU_REG32 *)(CSP_INT_AIC_BASE  + 0x0100))
#define  CSP_INT_AIC_FVR            (*(CPU_REG32 *)(CSP_INT_AIC_BASE  + 0x0104))
#define  CSP_INT_AIC_ISR            (*(CPU_REG32 *)(CSP_INT_AIC_BASE  + 0x0108))
#define  CSP_INT_AIC_IMR           (*(CPU_REG32 *)(CSP_INT_AIC_BASE  + 0x0110))
#define  CSP_INT_AIC_IECR           (*(CPU_REG32 *)(CSP_INT_AIC_BASE  + 0x0120))
#define  CSP_INT_AIC_IDCR           (*(CPU_REG32 *)(CSP_INT_AIC_BASE  + 0x0124))
#define  CSP_INT_AIC_ICCR           (*(CPU_REG32 *)(CSP_INT_AIC_BASE  + 0x0128))
#define  CSP_INT_AIC_EOICR          (*(CPU_REG32 *)(CSP_INT_AIC_BASE  + 0x0130))
#define  CSP_INT_AIC_SPU          (*(CPU_REG32 *)(CSP_INT_AIC_BASE  + 0x0134))
#define  CSP_INT_AIC_DCR          (*(CPU_REG32 *)(CSP_INT_AIC_BASE  + 0x0138))

/*
*********************************************************************************************************
*                                       EXTERN  GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void bsp_interrupt_dispatch(void)
{
  rtems_vector_number vector = CSP_INT_AIC_IVR;

  bsp_interrupt_handler_dispatch(vector);

  CSP_INT_AIC_EOICR = 0;
}

rtems_status_code bsp_interrupt_vector_enable(rtems_vector_number vector)
{
  CSP_INT_AIC_IECR = 1 << vector;

  return RTEMS_SUCCESSFUL;
}

rtems_status_code bsp_interrupt_vector_disable(rtems_vector_number vector)
{
  CSP_INT_AIC_IDCR = 1 << vector;

  return RTEMS_SUCCESSFUL;
}

rtems_status_code bsp_interrupt_facility_initialize(void)
{
  unsigned long i = 0;

  for (i = 0; i < 32; ++i) {
    CSP_INT_AIC_SVR(i<<2) = i;
  }

  /* disable all interrupts */
  CSP_INT_AIC_IDCR = 0xffffffff;

  _CPU_ISR_install_vector(ARM_EXCEPTION_IRQ, arm_exc_interrupt, NULL);

  return RTEMS_SUCCESSFUL;
}

