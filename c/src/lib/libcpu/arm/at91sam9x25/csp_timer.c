/*
 * Cogent CSB337 Timer driver
 *
 * This uses timer 0 for timing measurments.
 *
 * Copyright (c) 2004 by Jay Monkman <jtm@lopingdog.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 * Notes:
 *  This file manages the benchmark timer used by the RTEMS Timing Test
 *  Suite.  Each measured time period is demarcated by calls to
 *  benchmark_timer_initialize() and benchmark_timer_read().  benchmark_timer_read() usually returns
 *  the number of microseconds since benchmark_timer_initialize() exitted.
 *
 *  It is important that the timer start/stop overhead be determined
 *  when porting or modifying this code.
 */

#include <rtems.h>
#include <bsp.h>
#include <csp.h>


#define CSP_TMR_CH_NBR_MAX                   3U
#define CSP_TMR_NBR_MAX                      6U

//TC0
#define  CSP_TMR_REG_BASE_ADDR_TMR0              (CPU_INT32U)(0xF8008000U)
#define  CSP_TMR_REG_BASE_ADDR_TMR1              (CPU_INT32U)(0xF8008040U)
#define  CSP_TMR_REG_BASE_ADDR_TMR2              (CPU_INT32U)(0xF8008080U)
//TC1
#define  CSP_TMR_REG_BASE_ADDR_TMR3              (CPU_INT32U)(0xF800C000U)
#define  CSP_TMR_REG_BASE_ADDR_TMR4              (CPU_INT32U)(0xF800C040U)
#define  CSP_TMR_REG_BASE_ADDR_TMR5              (CPU_INT32U)(0xF800C080U)

/* (Tc Offset: 0xC0) Block Control Register */
#define  CSP_TMR_CH0_BCR_REG_BASE_ADDR       (CPU_INT32U)(0xF80080C0U)
#define  CSP_TMR_CH1_BCR_REG_BASE_ADDR       (CPU_INT32U)(0xF800C0C0U)
/* (Tc Offset: 0xC4) Block Mode Register */
#define  CSP_TMR_CH0_BMR_REG_BASE_ADDR       (CPU_INT32U)(0xF80080C4U)
#define  CSP_TMR_CH1_BMR_REG_BASE_ADDR       (CPU_INT32U)(0xF800C0C4U)

#define  CSP_TMR_REG_TMR0                        ((CSP_TMR_REG_TAG_PTR)(CSP_TMR_REG_BASE_ADDR_TMR0))
#define  CSP_TMR_REG_TMR1                        ((CSP_TMR_REG_TAG_PTR)(CSP_TMR_REG_BASE_ADDR_TMR1))
#define  CSP_TMR_REG_TMR2                        ((CSP_TMR_REG_TAG_PTR)(CSP_TMR_REG_BASE_ADDR_TMR2))
#define  CSP_TMR_REG_TMR3                        ((CSP_TMR_REG_TAG_PTR)(CSP_TMR_REG_BASE_ADDR_TMR3))
#define  CSP_TMR_REG_TMR4                        ((CSP_TMR_REG_TAG_PTR)(CSP_TMR_REG_BASE_ADDR_TMR4))
#define  CSP_TMR_REG_TMR5                        ((CSP_TMR_REG_TAG_PTR)(CSP_TMR_REG_BASE_ADDR_TMR5))

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
typedef struct {
  CPU_REG32      TC_CCR;        /**< \brief (TcChannel Offset: 0x0) Channel Control Register */
  CPU_REG32      TC_CMR;        /**< \brief (TcChannel Offset: 0x4) Channel Mode Register */
  CPU_REG32      Reserved1[2];
  CPU_REG32      TC_CV;         /**< \brief (TcChannel Offset: 0x10) Counter Value */
  CPU_REG32      TC_RA;         /**< \brief (TcChannel Offset: 0x14) Register A */
  CPU_REG32      TC_RB;         /**< \brief (TcChannel Offset: 0x18) Register B */
  CPU_REG32      TC_RC;         /**< \brief (TcChannel Offset: 0x1C) Register C */
  CPU_REG32      TC_SR;         /**< \brief (TcChannel Offset: 0x20) Status Register */
  CPU_REG32      TC_IER;        /**< \brief (TcChannel Offset: 0x24) Interrupt Enable Register */
  CPU_REG32      TC_IDR;        /**< \brief (TcChannel Offset: 0x28) Interrupt Disable Register */
  CPU_REG32      TC_IMR;        /**< \brief (TcChannel Offset: 0x2C) Interrupt Mask Register */
  CPU_REG32      Reserved2[4];
} CSP_TMR_REG_TAG, *CSP_TMR_REG_TAG_PTR;
/** \brief Tc hardware registers */


typedef  struct {
  CSP_TMR_REG_TAG  TC_CH[CSP_TMR_CH_NBR_MAX]; /**< \brief (Tc Offset: 0x0) channel = 0 .. 2 */
  CPU_REG32      TC_BCR;        /**< \brief (Tc Offset: 0xC0) Block Control Register */
  CPU_REG32      TC_BMR;        /**< \brief (Tc Offset: 0xC4) Block Mode Register */
} CSP_TMR_CH_REG_TAG, *CSP_TMR_CH_REG_TAG_PTR;

/* -------- TC_CCR : (TC Offset: N/A) Channel Control Register -------- */
#define CSP_TMR_CCR_CLKEN (0x1u << 0) /**< \brief (TC_CCR) Counter Clock Enable Command */
#define CSP_TMR_CCR_CLKDIS (0x1u << 1) /**< \brief (TC_CCR) Counter Clock Disable Command */
#define CSP_TMR_CCR_SWTRG (0x1u << 2) /**< \brief (TC_CCR) Software Trigger Command */
/* -------- TC_CMR : (TC Offset: N/A) Channel Mode Register -------- */
#define CSP_TMR_CMR_TCCLKS_Pos 0
#define CSP_TMR_CMR_TCCLKS_Msk (0x7u << TC_CMR_TCCLKS_Pos) /**< \brief (TC_CMR) Clock Selection */
#define CSP_TMR_CMR_TCCLKS_TIMER_CLOCK1 (0x0u << 0) /**< \brief (TC_CMR) Clock selected: TCLK1 */
#define CSP_TMR_CMR_TCCLKS_TIMER_CLOCK2 (0x1u << 0) /**< \brief (TC_CMR) Clock selected: TCLK2 */
#define CSP_TMR_CMR_TCCLKS_TIMER_CLOCK3 (0x2u << 0) /**< \brief (TC_CMR) Clock selected: TCLK3 */
#define CSP_TMR_CMR_TCCLKS_TIMER_CLOCK4 (0x3u << 0) /**< \brief (TC_CMR) Clock selected: TCLK4 */
#define CSP_TMR_CMR_TCCLKS_TIMER_CLOCK5 (0x4u << 0) /**< \brief (TC_CMR) Clock selected: TCLK5 */
#define CSP_TMR_CMR_TCCLKS_XC0 (0x5u << 0) /**< \brief (TC_CMR) Clock selected: XC0 */
#define CSP_TMR_CMR_TCCLKS_XC1 (0x6u << 0) /**< \brief (TC_CMR) Clock selected: XC1 */
#define CSP_TMR_CMR_TCCLKS_XC2 (0x7u << 0) /**< \brief (TC_CMR) Clock selected: XC2 */
#define CSP_TMR_CMR_CLKI (0x1u << 3) /**< \brief (TC_CMR) Clock Invert */
#define CSP_TMR_CMR_BURST_Pos 4
#define CSP_TMR_CMR_BURST_Msk (0x3u << TC_CMR_BURST_Pos) /**< \brief (TC_CMR) Burst Signal Selection */
#define CSP_TMR_CMR_BURST_NONE (0x0u << 4) /**< \brief (TC_CMR) The clock is not gated by an external signal. */
#define CSP_TMR_CMR_BURST_XC0 (0x1u << 4) /**< \brief (TC_CMR) XC0 is ANDed with the selected clock. */
#define CSP_TMR_CMR_BURST_XC1 (0x2u << 4) /**< \brief (TC_CMR) XC1 is ANDed with the selected clock. */
#define CSP_TMR_CMR_BURST_XC2 (0x3u << 4) /**< \brief (TC_CMR) XC2 is ANDed with the selected clock. */
#define CSP_TMR_CMR_LDBSTOP (0x1u << 6) /**< \brief (TC_CMR) Counter Clock Stopped with RB Loading */
#define CSP_TMR_CMR_LDBDIS (0x1u << 7) /**< \brief (TC_CMR) Counter Clock Disable with RB Loading */
#define CSP_TMR_CMR_ETRGEDG_Pos 8
#define CSP_TMR_CMR_ETRGEDG_Msk (0x3u << TC_CMR_ETRGEDG_Pos) /**< \brief (TC_CMR) External Trigger Edge Selection */
#define CSP_TMR_CMR_ETRGEDG_NONE (0x0u << 8) /**< \brief (TC_CMR) The clock is not gated by an external signal. */
#define CSP_TMR_CMR_ETRGEDG_RISING (0x1u << 8) /**< \brief (TC_CMR) Rising edge */
#define CSP_TMR_CMR_ETRGEDG_FALLING (0x2u << 8) /**< \brief (TC_CMR) Falling edge */
#define CSP_TMR_CMR_ETRGEDG_EDGE (0x3u << 8) /**< \brief (TC_CMR) Each edge */
#define CSP_TMR_CMR_ABETRG (0x1u << 10) /**< \brief (TC_CMR) TIOA or TIOB External Trigger Selection */
#define CSP_TMR_CMR_CPCTRG (0x1u << 14) /**< \brief (TC_CMR) RC Compare Trigger Enable */
#define CSP_TMR_CMR_WAVE (0x1u << 15) /**< \brief (TC_CMR)  */
#define CSP_TMR_CMR_LDRA_Pos 16
#define CSP_TMR_CMR_LDRA_Msk (0x3u << TC_CMR_LDRA_Pos) /**< \brief (TC_CMR) RA Loading Selection */
#define CSP_TMR_CMR_LDRA_NONE (0x0u << 16) /**< \brief (TC_CMR) None */
#define CSP_TMR_CMR_LDRA_RISING (0x1u << 16) /**< \brief (TC_CMR) Rising edge of TIOA */
#define CSP_TMR_CMR_LDRA_FALLING (0x2u << 16) /**< \brief (TC_CMR) Falling edge of TIOA */
#define CSP_TMR_CMR_LDRA_EDGE (0x3u << 16) /**< \brief (TC_CMR) Each edge of TIOA */
#define CSP_TMR_CMR_LDRB_Pos 18
#define CSP_TMR_CMR_LDRB_Msk (0x3u << TC_CMR_LDRB_Pos) /**< \brief (TC_CMR) RB Loading Selection */
#define CSP_TMR_CMR_LDRB_NONE (0x0u << 18) /**< \brief (TC_CMR) None */
#define CSP_TMR_CMR_LDRB_RISING (0x1u << 18) /**< \brief (TC_CMR) Rising edge of TIOA */
#define CSP_TMR_CMR_LDRB_FALLING (0x2u << 18) /**< \brief (TC_CMR) Falling edge of TIOA */
#define CSP_TMR_CMR_LDRB_EDGE (0x3u << 18) /**< \brief (TC_CMR) Each edge of TIOA */
#define CSP_TMR_CMR_CPCSTOP (0x1u << 6) /**< \brief (TC_CMR) Counter Clock Stopped with RC Compare */
#define CSP_TMR_CMR_CPCDIS (0x1u << 7) /**< \brief (TC_CMR) Counter Clock Disable with RC Compare */
#define CSP_TMR_CMR_EEVTEDG_Pos 8
#define CSP_TMR_CMR_EEVTEDG_Msk (0x3u << TC_CMR_EEVTEDG_Pos) /**< \brief (TC_CMR) External Event Edge Selection */
#define CSP_TMR_CMR_EEVTEDG_NONE (0x0u << 8) /**< \brief (TC_CMR) None */
#define CSP_TMR_CMR_EEVTEDG_RISING (0x1u << 8) /**< \brief (TC_CMR) Rising edge */
#define CSP_TMR_CMR_EEVTEDG_FALLING (0x2u << 8) /**< \brief (TC_CMR) Falling edge */
#define CSP_TMR_CMR_EEVTEDG_EDGE (0x3u << 8) /**< \brief (TC_CMR) Each edge */
#define CSP_TMR_CMR_EEVT_Pos 10
#define CSP_TMR_CMR_EEVT_Msk (0x3u << TC_CMR_EEVT_Pos) /**< \brief (TC_CMR) External Event Selection */
#define CSP_TMR_CMR_EEVT_TIOB (0x0u << 10) /**< \brief (TC_CMR) TIOB */
#define CSP_TMR_CMR_EEVT_XC0 (0x1u << 10) /**< \brief (TC_CMR) XC0 */
#define CSP_TMR_CMR_EEVT_XC1 (0x2u << 10) /**< \brief (TC_CMR) XC1 */
#define CSP_TMR_CMR_EEVT_XC2 (0x3u << 10) /**< \brief (TC_CMR) XC2 */
#define CSP_TMR_CMR_ENETRG (0x1u << 12) /**< \brief (TC_CMR) External Event Trigger Enable */
#define CSP_TMR_CMR_WAVSEL_Pos 13
#define CSP_TMR_CMR_WAVSEL_Msk (0x3u << TC_CMR_WAVSEL_Pos) /**< \brief (TC_CMR) Waveform Selection */
#define CSP_TMR_CMR_WAVSEL_UP (0x0u << 13) /**< \brief (TC_CMR) UP mode without automatic trigger on RC Compare */
#define CSP_TMR_CMR_WAVSEL_UPDOWN (0x1u << 13) /**< \brief (TC_CMR) UPDOWN mode without automatic trigger on RC Compare */
#define CSP_TMR_CMR_WAVSEL_UP_RC (0x2u << 13) /**< \brief (TC_CMR) UP mode with automatic trigger on RC Compare */
#define CSP_TMR_CMR_WAVSEL_UPDOWN_RC (0x3u << 13) /**< \brief (TC_CMR) UPDOWN mode with automatic trigger on RC Compare */
#define CSP_TMR_CMR_ACPA_Pos 16
#define CSP_TMR_CMR_ACPA_Msk (0x3u << TC_CMR_ACPA_Pos) /**< \brief (TC_CMR) RA Compare Effect on TIOA */
#define CSP_TMR_CMR_ACPA_NONE (0x0u << 16) /**< \brief (TC_CMR) None */
#define CSP_TMR_CMR_ACPA_SET (0x1u << 16) /**< \brief (TC_CMR) Set */
#define CSP_TMR_CMR_ACPA_CLEAR (0x2u << 16) /**< \brief (TC_CMR) Clear */
#define CSP_TMR_CMR_ACPA_TOGGLE (0x3u << 16) /**< \brief (TC_CMR) Toggle */
#define CSP_TMR_CMR_ACPC_Pos 18
#define CSP_TMR_CMR_ACPC_Msk (0x3u << TC_CMR_ACPC_Pos) /**< \brief (TC_CMR) RC Compare Effect on TIOA */
#define CSP_TMR_CMR_ACPC_NONE (0x0u << 18) /**< \brief (TC_CMR) None */
#define CSP_TMR_CMR_ACPC_SET (0x1u << 18) /**< \brief (TC_CMR) Set */
#define CSP_TMR_CMR_ACPC_CLEAR (0x2u << 18) /**< \brief (TC_CMR) Clear */
#define CSP_TMR_CMR_ACPC_TOGGLE (0x3u << 18) /**< \brief (TC_CMR) Toggle */
#define CSP_TMR_CMR_AEEVT_Pos 20
#define CSP_TMR_CMR_AEEVT_Msk (0x3u << TC_CMR_AEEVT_Pos) /**< \brief (TC_CMR) External Event Effect on TIOA */
#define CSP_TMR_CMR_AEEVT_NONE (0x0u << 20) /**< \brief (TC_CMR) None */
#define CSP_TMR_CMR_AEEVT_SET (0x1u << 20) /**< \brief (TC_CMR) Set */
#define CSP_TMR_CMR_AEEVT_CLEAR (0x2u << 20) /**< \brief (TC_CMR) Clear */
#define CSP_TMR_CMR_AEEVT_TOGGLE (0x3u << 20) /**< \brief (TC_CMR) Toggle */
#define CSP_TMR_CMR_ASWTRG_Pos 22
#define CSP_TMR_CMR_ASWTRG_Msk (0x3u << TC_CMR_ASWTRG_Pos) /**< \brief (TC_CMR) Software Trigger Effect on TIOA */
#define CSP_TMR_CMR_ASWTRG_NONE (0x0u << 22) /**< \brief (TC_CMR) None */
#define CSP_TMR_CMR_ASWTRG_SET (0x1u << 22) /**< \brief (TC_CMR) Set */
#define CSP_TMR_CMR_ASWTRG_CLEAR (0x2u << 22) /**< \brief (TC_CMR) Clear */
#define CSP_TMR_CMR_ASWTRG_TOGGLE (0x3u << 22) /**< \brief (TC_CMR) Toggle */
#define CSP_TMR_CMR_BCPB_Pos 24
#define CSP_TMR_CMR_BCPB_Msk (0x3u << TC_CMR_BCPB_Pos) /**< \brief (TC_CMR) RB Compare Effect on TIOB */
#define CSP_TMR_CMR_BCPB_NONE (0x0u << 24) /**< \brief (TC_CMR) None */
#define CSP_TMR_CMR_BCPB_SET (0x1u << 24) /**< \brief (TC_CMR) Set */
#define CSP_TMR_CMR_BCPB_CLEAR (0x2u << 24) /**< \brief (TC_CMR) Clear */
#define CSP_TMR_CMR_BCPB_TOGGLE (0x3u << 24) /**< \brief (TC_CMR) Toggle */
#define CSP_TMR_CMR_BCPC_Pos 26
#define CSP_TMR_CMR_BCPC_Msk (0x3u << TC_CMR_BCPC_Pos) /**< \brief (TC_CMR) RC Compare Effect on TIOB */
#define CSP_TMR_CMR_BCPC_NONE (0x0u << 26) /**< \brief (TC_CMR) None */
#define CSP_TMR_CMR_BCPC_SET (0x1u << 26) /**< \brief (TC_CMR) Set */
#define CSP_TMR_CMR_BCPC_CLEAR (0x2u << 26) /**< \brief (TC_CMR) Clear */
#define CSP_TMR_CMR_BCPC_TOGGLE (0x3u << 26) /**< \brief (TC_CMR) Toggle */
#define CSP_TMR_CMR_BEEVT_Pos 28
#define CSP_TMR_CMR_BEEVT_Msk (0x3u << TC_CMR_BEEVT_Pos) /**< \brief (TC_CMR) External Event Effect on TIOB */
#define CSP_TMR_CMR_BEEVT_NONE (0x0u << 28) /**< \brief (TC_CMR) None */
#define CSP_TMR_CMR_BEEVT_SET (0x1u << 28) /**< \brief (TC_CMR) Set */
#define CSP_TMR_CMR_BEEVT_CLEAR (0x2u << 28) /**< \brief (TC_CMR) Clear */
#define CSP_TMR_CMR_BEEVT_TOGGLE (0x3u << 28) /**< \brief (TC_CMR) Toggle */
#define CSP_TMR_CMR_BSWTRG_Pos 30
#define CSP_TMR_CMR_BSWTRG_Msk (0x3u << TC_CMR_BSWTRG_Pos) /**< \brief (TC_CMR) Software Trigger Effect on TIOB */
#define CSP_TMR_CMR_BSWTRG_NONE (0x0u << 30) /**< \brief (TC_CMR) None */
#define CSP_TMR_CMR_BSWTRG_SET (0x1u << 30) /**< \brief (TC_CMR) Set */
#define CSP_TMR_CMR_BSWTRG_CLEAR (0x2u << 30) /**< \brief (TC_CMR) Clear */
#define CSP_TMR_CMR_BSWTRG_TOGGLE (0x3u << 30) /**< \brief (TC_CMR) Toggle */
/* -------- TC_CV : (TC Offset: N/A) Counter Value -------- */
#define CSP_TMR_CV_CV_Pos 0
#define CSP_TMR_CV_CV_Msk (0xffffffffu << TC_CV_CV_Pos) /**< \brief (TC_CV) Counter Value */
/* -------- TC_RA : (TC Offset: N/A) Register A -------- */
#define CSP_TMR_RA_RA_Pos 0
#define CSP_TMR_RA_RA_Msk (0xffffffffu << TC_RA_RA_Pos) /**< \brief (TC_RA) Register A */
#define CSP_TMR_RA_RA(value) ((TC_RA_RA_Msk & ((value) << TC_RA_RA_Pos)))
/* -------- TC_RB : (TC Offset: N/A) Register B -------- */
#define CSP_TMR_RB_RB_Pos 0
#define CSP_TMR_RB_RB_Msk (0xffffffffu << TC_RB_RB_Pos) /**< \brief (TC_RB) Register B */
#define CSP_TMR_RB_RB(value) ((TC_RB_RB_Msk & ((value) << TC_RB_RB_Pos)))
/* -------- TC_RC : (TC Offset: N/A) Register C -------- */
#define CSP_TMR_RC_RC_Pos 0
#define CSP_TMR_RC_RC_Msk (0xffffffffu << TC_RC_RC_Pos) /**< \brief (TC_RC) Register C */
#define CSP_TMR_RC_RC(value) ((TC_RC_RC_Msk & ((value) << TC_RC_RC_Pos)))
/* -------- TC_SR : (TC Offset: N/A) Status Register -------- */
#define CSP_TMR_SR_COVFS (0x1u << 0) /**< \brief (TC_SR) Counter Overflow Status */
#define CSP_TMR_SR_LOVRS (0x1u << 1) /**< \brief (TC_SR) Load Overrun Status */
#define CSP_TMR_SR_CPAS (0x1u << 2) /**< \brief (TC_SR) RA Compare Status */
#define CSP_TMR_SR_CPBS (0x1u << 3) /**< \brief (TC_SR) RB Compare Status */
#define CSP_TMR_SR_CPCS (0x1u << 4) /**< \brief (TC_SR) RC Compare Status */
#define CSP_TMR_SR_LDRAS (0x1u << 5) /**< \brief (TC_SR) RA Loading Status */
#define CSP_TMR_SR_LDRBS (0x1u << 6) /**< \brief (TC_SR) RB Loading Status */
#define CSP_TMR_SR_ETRGS (0x1u << 7) /**< \brief (TC_SR) External Trigger Status */
#define CSP_TMR_SR_CLKSTA (0x1u << 16) /**< \brief (TC_SR) Clock Enabling Status */
#define CSP_TMR_SR_MTIOA (0x1u << 17) /**< \brief (TC_SR) TIOA Mirror */
#define CSP_TMR_SR_MTIOB (0x1u << 18) /**< \brief (TC_SR) TIOB Mirror */
/* -------- TC_IER : (TC Offset: N/A) Interrupt Enable Register -------- */
#define CSP_TMR_IER_COVFS (0x1u << 0) /**< \brief (TC_IER) Counter Overflow */
#define CSP_TMR_IER_LOVRS (0x1u << 1) /**< \brief (TC_IER) Load Overrun */
#define CSP_TMR_IER_CPAS (0x1u << 2) /**< \brief (TC_IER) RA Compare */
#define CSP_TMR_IER_CPBS (0x1u << 3) /**< \brief (TC_IER) RB Compare */
#define CSP_TMR_IER_CPCS (0x1u << 4) /**< \brief (TC_IER) RC Compare */
#define CSP_TMR_IER_LDRAS (0x1u << 5) /**< \brief (TC_IER) RA Loading */
#define CSP_TMR_IER_LDRBS (0x1u << 6) /**< \brief (TC_IER) RB Loading */
#define CSP_TMR_IER_ETRGS (0x1u << 7) /**< \brief (TC_IER) External Trigger */
/* -------- TC_IDR : (TC Offset: N/A) Interrupt Disable Register -------- */
#define CSP_TMR_IDR_COVFS (0x1u << 0) /**< \brief (TC_IDR) Counter Overflow */
#define CSP_TMR_IDR_LOVRS (0x1u << 1) /**< \brief (TC_IDR) Load Overrun */
#define CSP_TMR_IDR_CPAS (0x1u << 2) /**< \brief (TC_IDR) RA Compare */
#define CSP_TMR_IDR_CPBS (0x1u << 3) /**< \brief (TC_IDR) RB Compare */
#define CSP_TMR_IDR_CPCS (0x1u << 4) /**< \brief (TC_IDR) RC Compare */
#define CSP_TMR_IDR_LDRAS (0x1u << 5) /**< \brief (TC_IDR) RA Loading */
#define CSP_TMR_IDR_LDRBS (0x1u << 6) /**< \brief (TC_IDR) RB Loading */
#define CSP_TMR_IDR_ETRGS (0x1u << 7) /**< \brief (TC_IDR) External Trigger */
/* -------- TC_IMR : (TC Offset: N/A) Interrupt Mask Register -------- */
#define CSP_TMR_IMR_COVFS (0x1u << 0) /**< \brief (TC_IMR) Counter Overflow */
#define CSP_TMR_IMR_LOVRS (0x1u << 1) /**< \brief (TC_IMR) Load Overrun */
#define CSP_TMR_IMR_CPAS (0x1u << 2) /**< \brief (TC_IMR) RA Compare */
#define CSP_TMR_IMR_CPBS (0x1u << 3) /**< \brief (TC_IMR) RB Compare */
#define CSP_TMR_IMR_CPCS (0x1u << 4) /**< \brief (TC_IMR) RC Compare */
#define CSP_TMR_IMR_LDRAS (0x1u << 5) /**< \brief (TC_IMR) RA Loading */
#define CSP_TMR_IMR_LDRBS (0x1u << 6) /**< \brief (TC_IMR) RB Loading */
#define CSP_TMR_IMR_ETRGS (0x1u << 7) /**< \brief (TC_IMR) External Trigger */
/* -------- TC_BCR : (TC Offset: 0xC0) Block Control Register -------- */
#define CSP_TMR_BCR_SYNC (0x1u << 0) /**< \brief (TC_BCR) Synchro Command */
/* -------- TC_BMR : (TC Offset: 0xC4) Block Mode Register -------- */
#define CSP_TMR_BMR_TC0XC0S_Pos 0
#define CSP_TMR_BMR_TC0XC0S_Msk (0x3u << TC_BMR_TC0XC0S_Pos) /**< \brief (TC_BMR) External Clock Signal 0 Selection */
#define CSP_TMR_BMR_TC0XC0S_TCLK0 (0x0u << 0) /**< \brief (TC_BMR) Signal connected to XC0: TCLK0 */
#define CSP_TMR_BMR_TC0XC0S_TIOA1 (0x2u << 0) /**< \brief (TC_BMR) Signal connected to XC0: TIOA1 */
#define CSP_TMR_BMR_TC0XC0S_TIOA2 (0x3u << 0) /**< \brief (TC_BMR) Signal connected to XC0: TIOA2 */
#define CSP_TMR_BMR_TC1XC1S_Pos 2
#define CSP_TMR_BMR_TC1XC1S_Msk (0x3u << TC_BMR_TC1XC1S_Pos) /**< \brief (TC_BMR) External Clock Signal 1 Selection */
#define CSP_TMR_BMR_TC1XC1S_TCLK1 (0x0u << 2) /**< \brief (TC_BMR) Signal connected to XC1: TCLK1 */
#define CSP_TMR_BMR_TC1XC1S_TIOA0 (0x2u << 2) /**< \brief (TC_BMR) Signal connected to XC1: TIOA0 */
#define CSP_TMR_BMR_TC1XC1S_TIOA2 (0x3u << 2) /**< \brief (TC_BMR) Signal connected to XC1: TIOA2 */
#define CSP_TMR_BMR_TC2XC2S_Pos 4
#define CSP_TMR_BMR_TC2XC2S_Msk (0x3u << TC_BMR_TC2XC2S_Pos) /**< \brief (TC_BMR) External Clock Signal 2 Selection */
#define CSP_TMR_BMR_TC2XC2S_TCLK2 (0x0u << 4) /**< \brief (TC_BMR) Signal connected to XC2: TCLK2 */
#define CSP_TMR_BMR_TC2XC2S_TIOA1 (0x2u << 4) /**< \brief (TC_BMR) Signal connected to XC2: TIOA1 */
#define CSP_TMR_BMR_TC2XC2S_TIOA2 (0x3u << 4) /**< \brief (TC_BMR) Signal connected to XC2: TIOA2 */


uint16_t tstart;
bool benchmark_timer_find_average_overhead;
uint32_t tick_time;
/*
 * Set up TC0 -
 *   timer_clock2 (MCK/8)
 *   capture mode - this shouldn't matter
 */
void benchmark_timer_initialize( void )
{
    uint32_t tmr_freq;

    /* since we are using timer_clock2, divide mck by 8 */
    tmr_freq = CSP_PMC_get_mck() / 8;

    CSP_TMR_REG_TMR0->TC_CMR = CSP_TMR_CMR_TCCLKS_TIMER_CLOCK2;   /* timer_clock2 */
    CSP_TMR_REG_TMR0->TC_CCR = (CSP_TMR_CCR_CLKEN       /* enable the counter */
                          		| CSP_TMR_CCR_SWTRG);   /* start it up */

    /* tick time in nanoseconds */
    tick_time = 1000000000/tmr_freq;

}

/*
 *  The following controls the behavior of benchmark_timer_read().
 *
 *  AVG_OVEREHAD is the overhead for starting and stopping the timer.  It
 *  is usually deducted from the number returned.
 *
 *  LEAST_VALID is the lowest number this routine should trust.  Numbers
 *  below this are "noise" and zero is returned.
 */

#define AVG_OVERHEAD      0  /* It typically takes X.X microseconds */
                             /* (Y countdowns) to start/stop the timer. */
                             /* This value is in microseconds. */
#define LEAST_VALID       1  /* Don't trust a clicks value lower than this */

int benchmark_timer_read( void )
{
  uint16_t t;
  uint32_t total;
  t = CSP_TMR_REG_TMR0->TC_CV;

  /*
   *  Total is calculated by taking into account the number of timer overflow
   *  interrupts since the timer was initialized and clicks since the last
   *  interrupts.
   */

  total = t * tick_time;

  if ( benchmark_timer_find_average_overhead == 1 )
    return total;          /* in nanosecond units */
  else {
    if ( total < LEAST_VALID )
      return 0;            /* below timer resolution */
  /*
   *  Somehow convert total into microseconds
   */
      return (total - AVG_OVERHEAD);
    }
}

void benchmark_timer_disable_subtracting_average_overhead(bool find_flag)
{
  benchmark_timer_find_average_overhead = find_flag;
}

