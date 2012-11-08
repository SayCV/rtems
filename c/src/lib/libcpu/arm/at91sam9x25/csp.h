/*
*********************************************************************************************************
*        CSP
* Chip Support Package
* Filename      : csp.h
* Note(s)       : 
*
*  The license and distribution terms for this file may be
*  found in the file LICENSE in this distribution or at
*  http://www.rtems.com/license/LICENSE.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*/

#ifndef  CSP_PRESENT
#define  CSP_PRESENT


/*$PAGE*/
/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/
#include  <csp_types.h>
#include  <csp_dev.h>
#include  <csp_grp.h>
#include  <csp_pmc.h>
#include  <csp_usart.h>


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   CSP_MODULE
#define  CSP_EXT
#else
#define  CSP_EXT  extern
#endif


/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                   SAM9X25 FAMILY DEVICE MEMBER DEFINITION
*********************************************************************************************************
*/
#define  CPU_REG_PIT_MR                (*((CPU_REG32 *)(0xFFFFFE30U)))    /* (PIT) Mode Register */
#define  CPU_REG_PIT_SR                (*((CPU_REG32 *)(0xFFFFFE34U)))    /* (PIT) Status Register */
#define  CPU_REG_PIT_PIVR              (*((CPU_REG32 *)(0xFFFFFE38U)))    /* (PIT) Periodic Interval Value Register */
#define  CPU_REG_PIT_PIIR              (*((CPU_REG32 *)(0xFFFFFE3CU)))    /* (PIT) Periodic Interval Image Register */

                                                                /* --------- PIT MODE REGISTER BIT DEFINES ---------- */

#define  CPU_REG_PIT_MR_PIV_VAL_MASK                      DEF_BIT_FIELD(20, 0)
                                                                /* Period interval timer enable                       */
#define  CPU_REG_PIT_MR_PITEN                             DEF_BIT_24
                                                              /* Period interval timer interrupt enable             */
#define  CPU_REG_PIT_MR_PITIEN                            DEF_BIT_25
                                                          /* --------- PIT STATUS REGISTER BIT DEFINES -------- */
#define  CPU_REG_PIT_SR_PITS                              DEF_BIT_00

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of CSP module include.                      */

