/*
*********************************************************************************************************
*        CSP
* Chip Support Package
* Filename      : csp_pmc.h
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

#ifndef  CSP_PMC_PRESENT
#define  CSP_PMC_PRESENT

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/* Define clock timeout */
#define CSP_CLOCK_TIMEOUT                                   0xFFFFFFFF

                                                                /* ------------------- CLK SOURCES ------------------ */
#define CSP_PMC_CLK_SRC_SLOW                              0    /* Slow  clock                                        */
#define CSP_PMC_CLK_SRC_MAIN                              1    /* Main  clock                                        */
#define CSP_PMC_CLK_SRC_PLLA                              2    /* PLL   clock                                        */ 
#define CSP_PMC_CLK_SRC_PLLB                              3    /* PLL   clock                                        */ 

                                                                /* -------------- CLOCK PREESCALERS  ---------------- */
#define CSP_PMC_CLK_PRE1                                  0    /* Selected clock                                     */           
#define CSP_PMC_CLK_PRE2                                  1    /* Selected clock divided by  2                       */
#define CSP_PMC_CLK_PRE4                                  2    /* Selected clock divided by  4                       */
#define CSP_PMC_CLK_PRE8                                  3    /* Selected clock divided by  8                       */
#define CSP_PMC_CLK_PRE16                                 4    /* Selected clock divided by 16                       */
#define CSP_PMC_CLK_PRE32                                 5    /* Selected clock divided by 32                       */
#define CSP_PMC_CLK_PRE64                                 6    /* Selected clock divided by 64                       */

                                                                /* ------------------- USB DIVIDERS  ---------------- */
#define CSP_PMC_USB_CLK_DIV1                              0    /* Divider output is PLL clock output                 */           
#define CSP_PMC_USB_CLK_DIV2                              1    /* Divider output is PLL clock output divided by 2    */
#define CSP_PMC_USB_CLK_DIV4                              2    /* Divider output is PLL clock output divided by 2    */

                                                                /* -------------------- PLL IDs --------------------- */
#define CSP_PMC_PLL_ID_PLLA                               0 
#define CSP_PMC_PLL_ID_PLLB                               1
#define CSP_PMC_PLL_ID_SMD                               2
                                                                /* -------------------- SYS CLK ID ------------------ */

#define CSP_PMC_SYS_CLK_ID_DDRCK                            2
#define CSP_PMC_SYS_CLK_ID_SMDCK                            4
#define CSP_PMC_SYS_CLK_ID_UHP                             6
#define CSP_PMC_SYS_CLK_ID_UDP                             7
#define CSP_PMC_SYS_CLK_ID_PCK0                            8
#define CSP_PMC_SYS_CLK_ID_PCK1                            9
#define CSP_PMC_SYS_CLK_ID_HCK0                            16
#define CSP_PMC_SYS_CLK_ID_HCK1                            17

                                                                /* -------------- TIMEOUT & CONSTRIANS -------------- */
#define  CSP_PMC_PLL_TO                     0x0000FFFF
#define  CSP_PMC_PLL_MAX_MUL                      2047          /* Maximum PLL Multiplier value                       */
#define  CSP_PMC_MAIN_CLK_STARTUP_TO        0x000000FF          /* Main clk startup timeout                           */
#define  CSP_PMC_MAIN_OSC_MAINF_TO          0x000000FF          /* Main clk ready flag timeout                        */
#define  CSP_PMC_MCLK_TO                    0x000000FF          /* Master clk timeout                                 */





                                                                /* ------- MASTER CLOCK REGISTER BIT DEFINES -------- */
#define  CSP_PMC_MCKR_PRES_2                DEF_BIT_MASK(1, 4)
#define  CSP_PMC_MCKR_PRES_4                DEF_BIT_MASK(2, 4)
#define  CSP_PMC_MCKR_PRES_8                DEF_BIT_MASK(3, 4)
#define  CSP_PMC_MCKR_PRES_16               DEF_BIT_MASK(4, 4)
#define  CSP_PMC_MCKR_PRES_32               DEF_BIT_MASK(5, 4)
#define  CSP_PMC_MCKR_PRES_64               DEF_BIT_MASK(6, 4)

#define  CSP_PMC_MCKR_MDIV_2                DEF_BIT_MASK(1, 8)
#define  CSP_PMC_MCKR_MDIV_4                DEF_BIT_MASK(2, 8)

#define  CSP_PMC_REG_BASE_ADDR                   0xFFFFFC00U
#define  CSP_PMC_REG                        ((CSP_PMC_REG_TAG_PTR)(CSP_PMC_REG_BASE_ADDR))

                                                                /* ----- CLK GENERATOR PLL REGISTER BIT DEFINES ----- */
#define  CSP_PMC_PLL_DIV_MASK               DEF_BIT_FIELD(8,  0)
#define  CSP_PMC_PLL_CNT_MASK               DEF_BIT_FIELD(6,  8)
#define  CSP_PMC_PLL_OUT_MASK               DEF_BIT_FIELD(2,  14)
#define  CSP_PMC_PLL_MUL_MASK               DEF_BIT_FIELD(11, 16)

#define  CSP_PMC_PLLB_USBDIV_MASK           DEF_BIT_FIELD(4, 8)
#define  CSP_PMC_PLLB_USBDIV_1              DEF_BIT_NONE
#define  CSP_PMC_PLLB_USBDIV_2              DEF_BIT_MASK(1, 8)
#define  CSP_PMC_PLLB_USBDIV_4              DEF_BIT_MASK(2, 8)

                                                                /* ------ INTERNAL OSCILLATOR/CLOCK FREQUENCY ------- */
#define  CSP_PMC_SLOW_CLK_SRC_RC_INT                       1    /* Slow Clk source RC internal                        */
#define  CSP_PMC_SLOW_CLK_SRC_OSC32                        2    /* Slow clk source 32768 Hz crystal                   */
#define  CSP_PMC_SLOW_CLK_SRC_RC_INT_FREQ_HZ           32000    /* RC internal frequency (hz)                         */
#define  CSP_PMC_SLOW_CLK_SRC_OSC32_FREQ_HZ            32768    /* 32768 slow clk oscilator                           */

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
typedef struct csp_pm_reg{
  CPU_REG32 PMC_SCER;      /**< \brief (Pmc Offset: 0x0000) System Clock Enable Register */
  CPU_REG32 PMC_SCDR;      /**< \brief (Pmc Offset: 0x0004) System Clock Disable Register */
  CPU_REG32 PMC_SCSR;      /**< \brief (Pmc Offset: 0x0008) System Clock Status Register */
  CPU_REG32 Reserved1[1];
  CPU_REG32 PMC_PCER;      /**< \brief (Pmc Offset: 0x0010) Peripheral Clock Enable Register */
  CPU_REG32 PMC_PCDR;      /**< \brief (Pmc Offset: 0x0014) Peripheral Clock Disable Register */
  CPU_REG32 PMC_PCSR;      /**< \brief (Pmc Offset: 0x0018) Peripheral Clock Status Register */
  CPU_REG32 CKGR_UCKR;     /**< \brief (Pmc Offset: 0x001C) UTMI Clock Register */
  CPU_REG32 CKGR_MOR;      /**< \brief (Pmc Offset: 0x0020) Main Oscillator Register */
  CPU_REG32 CKGR_MCFR;     /**< \brief (Pmc Offset: 0x0024) Main Clock Frequency Register */
  CPU_REG32 CKGR_PLLAR;    /**< \brief (Pmc Offset: 0x0028) PLLA Register */
  CPU_REG32 Reserved2[1];
  CPU_REG32 PMC_MCKR;      /**< \brief (Pmc Offset: 0x0030) Master Clock Register */
  CPU_REG32 Reserved3[1];
  CPU_REG32 PMC_USB;       /**< \brief (Pmc Offset: 0x0038) USB Clock Register */
  CPU_REG32 PMC_SMD;       /**< \brief (Pmc Offset: 0x003C) Soft Modem Clock Register */
  CPU_REG32 PMC_PCK[2];    /**< \brief (Pmc Offset: 0x0040) Programmable Clock 0 Register */
  CPU_REG32 Reserved4[6];
  CPU_REG32 PMC_IER;       /**< \brief (Pmc Offset: 0x0060) Interrupt Enable Register */
  CPU_REG32 PMC_IDR;       /**< \brief (Pmc Offset: 0x0064) Interrupt Disable Register */
  CPU_REG32 PMC_SR;        /**< \brief (Pmc Offset: 0x0068) Status Register */
  CPU_REG32 PMC_IMR;       /**< \brief (Pmc Offset: 0x006C) Interrupt Mask Register */
  CPU_REG32 Reserved5[4];
  CPU_REG32 PMC_PLLICPR;   /**< \brief (Pmc Offset: 0x0080) PLL Charge Pump Current Register */
  CPU_REG32 Reserved6[24];
  CPU_REG32 PMC_WPMR;      /**< \brief (Pmc Offset: 0x00E4) Write Protect Mode Register */
  CPU_REG32 PMC_WPSR;      /**< \brief (Pmc Offset: 0x00E8) Write Protect Status Register */
  CPU_REG32 Reserved7[8];
  CPU_REG32 PMC_PCR;       /**< \brief (Pmc Offset: 0x010C) Peripheral Control Register */
} CSP_PMC_REG_TAG, *CSP_PMC_REG_TAG_PTR;

/* -------- PMC_SCER : (PMC Offset: 0x0000) System Clock Enable Register -------- */
#define CSP_PMC_SCER_DDRCK (0x1u << 2) /**< \brief (CSP_PMC_SCER) DDR Clock Enable */
#define CSP_PMC_SCER_LCDCK (0x1u << 3) /**< \brief (CSP_PMC_SCER) LCD Clock Enable */
#define CSP_PMC_SCER_SMDCK (0x1u << 4) /**< \brief (CSP_PMC_SCER) SMD Clock Enable */
#define CSP_PMC_SCER_UHP (0x1u << 6) /**< \brief (CSP_PMC_SCER) USB Host OHCI Clocks Enable */
#define CSP_PMC_SCER_UDP (0x1u << 7) /**< \brief (CSP_PMC_SCER) USB Device Clock Enable */
#define CSP_PMC_SCER_PCK0 (0x1u << 8) /**< \brief (CSP_PMC_SCER) Programmable Clock 0 Output Enable */
#define CSP_PMC_SCER_PCK1 (0x1u << 9) /**< \brief (CSP_PMC_SCER) Programmable Clock 1 Output Enable */
/* -------- PMC_SCDR : (PMC Offset: 0x0004) System Clock Disable Register -------- */
#define CSP_PMC_SCDR_PCK (0x1u << 0) /**< \brief (CSP_PMC_SCDR) Processor Clock Disable */
#define CSP_PMC_SCDR_DDRCK (0x1u << 2) /**< \brief (CSP_PMC_SCDR) DDR Clock Disable */
#define CSP_PMC_SCDR_LCDCK (0x1u << 3) /**< \brief (CSP_PMC_SCDR) LCD Clock Disable */
#define CSP_PMC_SCDR_SMDCK (0x1u << 4) /**< \brief (CSP_PMC_SCDR) SMD Clock Disable */
#define CSP_PMC_SCDR_UHP (0x1u << 6) /**< \brief (CSP_PMC_SCDR) USB Host OHCI Clock Disable */
#define CSP_PMC_SCDR_UDP (0x1u << 7) /**< \brief (CSP_PMC_SCDR) USB Device Clock Enable */
#define CSP_PMC_SCDR_PCK0 (0x1u << 8) /**< \brief (CSP_PMC_SCDR) Programmable Clock 0 Output Disable */
#define CSP_PMC_SCDR_PCK1 (0x1u << 9) /**< \brief (CSP_PMC_SCDR) Programmable Clock 1 Output Disable */
/* -------- PMC_SCSR : (PMC Offset: 0x0008) System Clock Status Register -------- */
#define CSP_PMC_SCSR_PCK (0x1u << 0) /**< \brief (CSP_PMC_SCSR) Processor Clock Status */
#define CSP_PMC_SCSR_DDRCK (0x1u << 2) /**< \brief (CSP_PMC_SCSR) DDR Clock Status */
#define CSP_PMC_SCSR_LCDCK (0x1u << 3) /**< \brief (CSP_PMC_SCSR) LCD Clock Status */
#define CSP_PMC_SCSR_SMDCK (0x1u << 4) /**< \brief (CSP_PMC_SCSR) SMD Clock Status */
#define CSP_PMC_SCSR_UHP (0x1u << 6) /**< \brief (CSP_PMC_SCSR) USB Host Port Clock Status */
#define CSP_PMC_SCSR_UDP (0x1u << 7) /**< \brief (CSP_PMC_SCSR) USB Device Port Clock Status */
#define CSP_PMC_SCSR_PCK0 (0x1u << 8) /**< \brief (CSP_PMC_SCSR) Programmable Clock 0 Output Status */
#define CSP_PMC_SCSR_PCK1 (0x1u << 9) /**< \brief (CSP_PMC_SCSR) Programmable Clock 1 Output Status */
/* -------- PMC_PCER : (PMC Offset: 0x0010) Peripheral Clock Enable Register -------- */
#define CSP_PMC_PCER_PID2 (0x1u << 2) /**< \brief (CSP_PMC_PCER) Peripheral Clock 2 Enable */
#define CSP_PMC_PCER_PID3 (0x1u << 3) /**< \brief (CSP_PMC_PCER) Peripheral Clock 3 Enable */
#define CSP_PMC_PCER_PID4 (0x1u << 4) /**< \brief (CSP_PMC_PCER) Peripheral Clock 4 Enable */
#define CSP_PMC_PCER_PID5 (0x1u << 5) /**< \brief (CSP_PMC_PCER) Peripheral Clock 5 Enable */
#define CSP_PMC_PCER_PID6 (0x1u << 6) /**< \brief (CSP_PMC_PCER) Peripheral Clock 6 Enable */
#define CSP_PMC_PCER_PID7 (0x1u << 7) /**< \brief (CSP_PMC_PCER) Peripheral Clock 7 Enable */
#define CSP_PMC_PCER_PID8 (0x1u << 8) /**< \brief (CSP_PMC_PCER) Peripheral Clock 8 Enable */
#define CSP_PMC_PCER_PID9 (0x1u << 9) /**< \brief (CSP_PMC_PCER) Peripheral Clock 9 Enable */
#define CSP_PMC_PCER_PID10 (0x1u << 10) /**< \brief (CSP_PMC_PCER) Peripheral Clock 10 Enable */
#define CSP_PMC_PCER_PID11 (0x1u << 11) /**< \brief (CSP_PMC_PCER) Peripheral Clock 11 Enable */
#define CSP_PMC_PCER_PID12 (0x1u << 12) /**< \brief (CSP_PMC_PCER) Peripheral Clock 12 Enable */
#define CSP_PMC_PCER_PID13 (0x1u << 13) /**< \brief (CSP_PMC_PCER) Peripheral Clock 13 Enable */
#define CSP_PMC_PCER_PID14 (0x1u << 14) /**< \brief (CSP_PMC_PCER) Peripheral Clock 14 Enable */
#define CSP_PMC_PCER_PID15 (0x1u << 15) /**< \brief (CSP_PMC_PCER) Peripheral Clock 15 Enable */
#define CSP_PMC_PCER_PID16 (0x1u << 16) /**< \brief (CSP_PMC_PCER) Peripheral Clock 16 Enable */
#define CSP_PMC_PCER_PID17 (0x1u << 17) /**< \brief (CSP_PMC_PCER) Peripheral Clock 17 Enable */
#define CSP_PMC_PCER_PID18 (0x1u << 18) /**< \brief (CSP_PMC_PCER) Peripheral Clock 18 Enable */
#define CSP_PMC_PCER_PID19 (0x1u << 19) /**< \brief (CSP_PMC_PCER) Peripheral Clock 19 Enable */
#define CSP_PMC_PCER_PID20 (0x1u << 20) /**< \brief (CSP_PMC_PCER) Peripheral Clock 20 Enable */
#define CSP_PMC_PCER_PID21 (0x1u << 21) /**< \brief (CSP_PMC_PCER) Peripheral Clock 21 Enable */
#define CSP_PMC_PCER_PID22 (0x1u << 22) /**< \brief (CSP_PMC_PCER) Peripheral Clock 22 Enable */
#define CSP_PMC_PCER_PID23 (0x1u << 23) /**< \brief (CSP_PMC_PCER) Peripheral Clock 23 Enable */
#define CSP_PMC_PCER_PID24 (0x1u << 24) /**< \brief (CSP_PMC_PCER) Peripheral Clock 24 Enable */
#define CSP_PMC_PCER_PID25 (0x1u << 25) /**< \brief (CSP_PMC_PCER) Peripheral Clock 25 Enable */
#define CSP_PMC_PCER_PID26 (0x1u << 26) /**< \brief (CSP_PMC_PCER) Peripheral Clock 26 Enable */
#define CSP_PMC_PCER_PID27 (0x1u << 27) /**< \brief (CSP_PMC_PCER) Peripheral Clock 27 Enable */
#define CSP_PMC_PCER_PID28 (0x1u << 28) /**< \brief (CSP_PMC_PCER) Peripheral Clock 28 Enable */
#define CSP_PMC_PCER_PID29 (0x1u << 29) /**< \brief (CSP_PMC_PCER) Peripheral Clock 29 Enable */
#define CSP_PMC_PCER_PID30 (0x1u << 30) /**< \brief (CSP_PMC_PCER) Peripheral Clock 30 Enable */
#define CSP_PMC_PCER_PID31 (0x1u << 31) /**< \brief (CSP_PMC_PCER) Peripheral Clock 31 Enable */
/* -------- PMC_PCDR : (PMC Offset: 0x0014) Peripheral Clock Disable Register -------- */
#define CSP_PMC_PCDR_PID2 (0x1u << 2) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 2 Disable */
#define CSP_PMC_PCDR_PID3 (0x1u << 3) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 3 Disable */
#define CSP_PMC_PCDR_PID4 (0x1u << 4) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 4 Disable */
#define CSP_PMC_PCDR_PID5 (0x1u << 5) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 5 Disable */
#define CSP_PMC_PCDR_PID6 (0x1u << 6) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 6 Disable */
#define CSP_PMC_PCDR_PID7 (0x1u << 7) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 7 Disable */
#define CSP_PMC_PCDR_PID8 (0x1u << 8) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 8 Disable */
#define CSP_PMC_PCDR_PID9 (0x1u << 9) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 9 Disable */
#define CSP_PMC_PCDR_PID10 (0x1u << 10) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 10 Disable */
#define CSP_PMC_PCDR_PID11 (0x1u << 11) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 11 Disable */
#define CSP_PMC_PCDR_PID12 (0x1u << 12) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 12 Disable */
#define CSP_PMC_PCDR_PID13 (0x1u << 13) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 13 Disable */
#define CSP_PMC_PCDR_PID14 (0x1u << 14) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 14 Disable */
#define CSP_PMC_PCDR_PID15 (0x1u << 15) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 15 Disable */
#define CSP_PMC_PCDR_PID16 (0x1u << 16) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 16 Disable */
#define CSP_PMC_PCDR_PID17 (0x1u << 17) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 17 Disable */
#define CSP_PMC_PCDR_PID18 (0x1u << 18) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 18 Disable */
#define CSP_PMC_PCDR_PID19 (0x1u << 19) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 19 Disable */
#define CSP_PMC_PCDR_PID20 (0x1u << 20) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 20 Disable */
#define CSP_PMC_PCDR_PID21 (0x1u << 21) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 21 Disable */
#define CSP_PMC_PCDR_PID22 (0x1u << 22) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 22 Disable */
#define CSP_PMC_PCDR_PID23 (0x1u << 23) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 23 Disable */
#define CSP_PMC_PCDR_PID24 (0x1u << 24) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 24 Disable */
#define CSP_PMC_PCDR_PID25 (0x1u << 25) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 25 Disable */
#define CSP_PMC_PCDR_PID26 (0x1u << 26) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 26 Disable */
#define CSP_PMC_PCDR_PID27 (0x1u << 27) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 27 Disable */
#define CSP_PMC_PCDR_PID28 (0x1u << 28) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 28 Disable */
#define CSP_PMC_PCDR_PID29 (0x1u << 29) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 29 Disable */
#define CSP_PMC_PCDR_PID30 (0x1u << 30) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 30 Disable */
#define CSP_PMC_PCDR_PID31 (0x1u << 31) /**< \brief (CSP_PMC_PCDR) Peripheral Clock 31 Disable */
/* -------- PMC_PCSR : (PMC Offset: 0x0018) Peripheral Clock Status Register -------- */
#define CSP_PMC_PCSR_PID2 (0x1u << 2) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 2 Status */
#define CSP_PMC_PCSR_PID3 (0x1u << 3) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 3 Status */
#define CSP_PMC_PCSR_PID4 (0x1u << 4) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 4 Status */
#define CSP_PMC_PCSR_PID5 (0x1u << 5) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 5 Status */
#define CSP_PMC_PCSR_PID6 (0x1u << 6) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 6 Status */
#define CSP_PMC_PCSR_PID7 (0x1u << 7) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 7 Status */
#define CSP_PMC_PCSR_PID8 (0x1u << 8) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 8 Status */
#define CSP_PMC_PCSR_PID9 (0x1u << 9) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 9 Status */
#define CSP_PMC_PCSR_PID10 (0x1u << 10) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 10 Status */
#define CSP_PMC_PCSR_PID11 (0x1u << 11) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 11 Status */
#define CSP_PMC_PCSR_PID12 (0x1u << 12) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 12 Status */
#define CSP_PMC_PCSR_PID13 (0x1u << 13) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 13 Status */
#define CSP_PMC_PCSR_PID14 (0x1u << 14) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 14 Status */
#define CSP_PMC_PCSR_PID15 (0x1u << 15) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 15 Status */
#define CSP_PMC_PCSR_PID16 (0x1u << 16) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 16 Status */
#define CSP_PMC_PCSR_PID17 (0x1u << 17) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 17 Status */
#define CSP_PMC_PCSR_PID18 (0x1u << 18) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 18 Status */
#define CSP_PMC_PCSR_PID19 (0x1u << 19) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 19 Status */
#define CSP_PMC_PCSR_PID20 (0x1u << 20) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 20 Status */
#define CSP_PMC_PCSR_PID21 (0x1u << 21) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 21 Status */
#define CSP_PMC_PCSR_PID22 (0x1u << 22) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 22 Status */
#define CSP_PMC_PCSR_PID23 (0x1u << 23) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 23 Status */
#define CSP_PMC_PCSR_PID24 (0x1u << 24) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 24 Status */
#define CSP_PMC_PCSR_PID25 (0x1u << 25) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 25 Status */
#define CSP_PMC_PCSR_PID26 (0x1u << 26) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 26 Status */
#define CSP_PMC_PCSR_PID27 (0x1u << 27) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 27 Status */
#define CSP_PMC_PCSR_PID28 (0x1u << 28) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 28 Status */
#define CSP_PMC_PCSR_PID29 (0x1u << 29) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 29 Status */
#define CSP_PMC_PCSR_PID30 (0x1u << 30) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 30 Status */
#define CSP_PMC_PCSR_PID31 (0x1u << 31) /**< \brief (CSP_PMC_PCSR) Peripheral Clock 31 Status */
/* -------- CKGR_UCKR : (PMC Offset: 0x001C) UTMI Clock Register -------- */
#define CSP_PMC_CKGR_UCKR_UPLLEN (0x1u << 16) /**< \brief (CSP_PMC_CKGR_UCKR) UTMI PLL Enable */
#define CSP_PMC_CKGR_UCKR_UPLLCOUNT_Pos 20
#define CSP_PMC_CKGR_UCKR_UPLLCOUNT_Msk (0xfu << CSP_PMC_CKGR_UCKR_UPLLCOUNT_Pos) /**< \brief (CSP_PMC_CKGR_UCKR) UTMI PLL Start-up Time */
#define CSP_PMC_CKGR_UCKR_UPLLCOUNT(value) ((CSP_PMC_CKGR_UCKR_UPLLCOUNT_Msk & ((value) << CSP_PMC_CKGR_UCKR_UPLLCOUNT_Pos)))
#define CSP_PMC_CKGR_UCKR_BIASEN (0x1u << 24) /**< \brief (CSP_PMC_CKGR_UCKR) UTMI BIAS Enable */
#define CSP_PMC_CKGR_UCKR_BIASCOUNT_Pos 28
#define CSP_PMC_CKGR_UCKR_BIASCOUNT_Msk (0xfu << CSP_PMC_CKGR_UCKR_BIASCOUNT_Pos) /**< \brief (CSP_PMC_CKGR_UCKR) UTMI BIAS Start-up Time */
#define CSP_PMC_CKGR_UCKR_BIASCOUNT(value) ((CSP_PMC_CKGR_UCKR_BIASCOUNT_Msk & ((value) << CSP_PMC_CKGR_UCKR_BIASCOUNT_Pos)))
/* -------- CKGR_MOR : (PMC Offset: 0x0020) Main Oscillator Register -------- */
#define CSP_PMC_CKGR_MOR_MOSCXTEN (0x1u << 0) /**< \brief (CSP_PMC_CKGR_MOR) Main Crystal Oscillator Enable */
#define CSP_PMC_CKGR_MOR_MOSCXTBY (0x1u << 1) /**< \brief (CSP_PMC_CKGR_MOR) Main Crystal Oscillator Bypass */
#define CSP_PMC_CKGR_MOR_MOSCRCEN (0x1u << 3) /**< \brief (CSP_PMC_CKGR_MOR) Main On-Chip RC Oscillator Enable */
#define CSP_PMC_CKGR_MOR_MOSCXTST_Pos 8
#define CSP_PMC_CKGR_MOR_MOSCXTST_Msk (0xffu << CSP_PMC_CKGR_MOR_MOSCXTST_Pos) /**< \brief (CSP_PMC_CKGR_MOR) Main Crystal Oscillator Start-up Time */
#define CSP_PMC_CKGR_MOR_MOSCXTST(value) ((CSP_PMC_CKGR_MOR_MOSCXTST_Msk & ((value) << CSP_PMC_CKGR_MOR_MOSCXTST_Pos)))
#define CSP_PMC_CKGR_MOR_KEY_Pos 16
#define CSP_PMC_CKGR_MOR_KEY_Msk (0xffu << CSP_PMC_CKGR_MOR_KEY_Pos) /**< \brief (CSP_PMC_CKGR_MOR) Password */
#define CSP_PMC_CKGR_MOR_KEY(value) ((CSP_PMC_CKGR_MOR_KEY_Msk & ((value) << CSP_PMC_CKGR_MOR_KEY_Pos)))
#define CSP_PMC_CKGR_MOR_MOSCSEL (0x1u << 24) /**< \brief (CSP_PMC_CKGR_MOR) Main Oscillator Selection */
#define CSP_PMC_CKGR_MOR_CFDEN (0x1u << 25) /**< \brief (CSP_PMC_CKGR_MOR) Clock Failure Detector Enable */
/* -------- CKGR_MCFR : (PMC Offset: 0x0024) Main Clock Frequency Register -------- */
#define CSP_PMC_CKGR_MCFR_MAINF_Pos 0
#define CSP_PMC_CKGR_MCFR_MAINF_Msk (0xffffu << CSP_PMC_CKGR_MCFR_MAINF_Pos) /**< \brief (CSP_PMC_CKGR_MCFR) Main Clock Frequency */
#define CSP_PMC_CKGR_MCFR_MAINFRDY (0x1u << 16) /**< \brief (CSP_PMC_CKGR_MCFR) Main Clock Ready */
/* -------- CKGR_PLLAR : (PMC Offset: 0x0028) PLLA Register -------- */
#define CSP_PMC_CKGR_PLLAR_DIVA_Pos 0
#define CSP_PMC_CKGR_PLLAR_DIVA_Msk (0xffu << CSP_PMC_CKGR_PLLAR_DIVA_Pos) /**< \brief (CSP_PMC_CKGR_PLLAR) Divider A */
#define CSP_PMC_CKGR_PLLAR_DIVA(value) ((CSP_PMC_CKGR_PLLAR_DIVA_Msk & ((value) << CSP_PMC_CKGR_PLLAR_DIVA_Pos)))
#define CSP_PMC_CKGR_PLLAR_PLLACOUNT_Pos 8
#define CSP_PMC_CKGR_PLLAR_PLLACOUNT_Msk (0x3fu << CSP_PMC_CKGR_PLLAR_PLLACOUNT_Pos) /**< \brief (CSP_PMC_CKGR_PLLAR) PLLA Counter */
#define CSP_PMC_CKGR_PLLAR_PLLACOUNT(value) ((CSP_PMC_CKGR_PLLAR_PLLACOUNT_Msk & ((value) << CSP_PMC_CKGR_PLLAR_PLLACOUNT_Pos)))
#define CSP_PMC_CKGR_PLLAR_OUTA_Pos 14
#define CSP_PMC_CKGR_PLLAR_OUTA_Msk (0x3u << CSP_PMC_CKGR_PLLAR_OUTA_Pos) /**< \brief (CSP_PMC_CKGR_PLLAR) PLLA Clock Frequency Range */
#define CSP_PMC_CKGR_PLLAR_OUTA(value) ((CSP_PMC_CKGR_PLLAR_OUTA_Msk & ((value) << CSP_PMC_CKGR_PLLAR_OUTA_Pos)))
#define CSP_PMC_CKGR_PLLAR_MULA_Pos 16
#define CSP_PMC_CKGR_PLLAR_MULA_Msk (0x7ffu << CSP_PMC_CKGR_PLLAR_MULA_Pos) /**< \brief (CSP_PMC_CKGR_PLLAR) PLLA Multiplier */
#define CSP_PMC_CKGR_PLLAR_MULA(value) ((CSP_PMC_CKGR_PLLAR_MULA_Msk & ((value) << CSP_PMC_CKGR_PLLAR_MULA_Pos)))
#define CSP_PMC_CKGR_PLLAR_STUCKTO1 (0x1u << 29) /**< \brief (CSP_PMC_CKGR_PLLAR)  */
/* -------- PMC_MCKR : (PMC Offset: 0x0030) Master Clock Register -------- */
#define CSP_PMC_MCKR_CSS_Pos 0
#define CSP_PMC_MCKR_CSS_Msk (0x3u << CSP_PMC_MCKR_CSS_Pos) /**< \brief (CSP_PMC_MCKR) Master/Processor Clock Source Selection */
#define  CSP_PMC_MCKR_CSS_SLOW_CLK (0x0u << 0) /**< \brief (CSP_PMC_MCKR) Slow Clock is selected */
#define  CSP_PMC_MCKR_CSS_MAIN_CLK (0x1u << 0) /**< \brief (CSP_PMC_MCKR) Main Clock is selected */
#define  CSP_PMC_MCKR_CSS_PLLA_CLK (0x2u << 0) /**< \brief (CSP_PMC_MCKR) PLLACK/PLLADIV2 is selected */
#define  CSP_PMC_MCKR_CSS_UPLL_CLK (0x3u << 0) /**< \brief (CSP_PMC_MCKR) UPLL Clock is selected */
#define CSP_PMC_MCKR_PRES_Pos 4
#define CSP_PMC_MCKR_PRES_Msk (0x7u << CSP_PMC_MCKR_PRES_Pos) /**< \brief (CSP_PMC_MCKR) Master/Processor Clock Prescaler */
#define  CSP_PMC_MCKR_PRES_CLOCK (0x0u << 4) /**< \brief (CSP_PMC_MCKR) Selected clock */
#define  CSP_PMC_MCKR_PRES_CLOCK_DIV2 (0x1u << 4) /**< \brief (CSP_PMC_MCKR) Selected clock divided by 2 */
#define  CSP_PMC_MCKR_PRES_CLOCK_DIV4 (0x2u << 4) /**< \brief (CSP_PMC_MCKR) Selected clock divided by 4 */
#define  CSP_PMC_MCKR_PRES_CLOCK_DIV8 (0x3u << 4) /**< \brief (CSP_PMC_MCKR) Selected clock divided by 8 */
#define  CSP_PMC_MCKR_PRES_CLOCK_DIV16 (0x4u << 4) /**< \brief (CSP_PMC_MCKR) Selected clock divided by 16 */
#define  CSP_PMC_MCKR_PRES_CLOCK_DIV32 (0x5u << 4) /**< \brief (CSP_PMC_MCKR) Selected clock divided by 32 */
#define  CSP_PMC_MCKR_PRES_CLOCK_DIV64 (0x6u << 4) /**< \brief (CSP_PMC_MCKR) Selected clock divided by 64 */
#define CSP_PMC_MCKR_MDIV_Pos 8
#define CSP_PMC_MCKR_MDIV_Msk (0x3u << CSP_PMC_MCKR_MDIV_Pos) /**< \brief (CSP_PMC_MCKR) Master Clock Division */
#define  CSP_PMC_MCKR_MDIV_EQ_PCK (0x0u << 8) /**< \brief (CSP_PMC_MCKR) Master Clock is Prescaler Output Clock divided by 1.Warning: SysClk DDR and DDRCK are not available. */
#define  CSP_PMC_MCKR_MDIV_PCK_DIV2 (0x1u << 8) /**< \brief (CSP_PMC_MCKR) Master Clock is Prescaler Output Clock divided by 2.SysClk DDR is equal to 2 x MCK. DDRCK is equal to MCK. */
#define  CSP_PMC_MCKR_MDIV_PCK_DIV4 (0x2u << 8) /**< \brief (CSP_PMC_MCKR) Master Clock is Prescaler Output Clock divided by 4.SysClk DDR is equal to 2 x MCK. DDRCK is equal to MCK. */
#define  CSP_PMC_MCKR_MDIV_PCK_DIV3 (0x3u << 8) /**< \brief (CSP_PMC_MCKR) Master Clock is Prescaler Output Clock divided by 3.SysClk DDR is equal to 2 x MCK. DDRCK is equal to MCK. */
#define CSP_PMC_MCKR_PLLADIV2 (0x1u << 12) /**< \brief (CSP_PMC_MCKR) PLLA divisor by 2 */
#define  CSP_PMC_MCKR_PLLADIV2_NOT_DIV2 (0x0u << 12) /**< \brief (CSP_PMC_MCKR) PLLA clock frequency is divided by 1. */
#define  CSP_PMC_MCKR_PLLADIV2_DIV2 (0x1u << 12) /**< \brief (CSP_PMC_MCKR) PLLA clock frequency is divided by 2. */
/* -------- PMC_USB : (PMC Offset: 0x0038) USB Clock Register -------- */
#define CSP_PMC_USB_USBS (0x1u << 0) /**< \brief (CSP_PMC_USB) USB OHCI Input Clock Selection */
#define CSP_PMC_USB_USBDIV_Pos 8
#define CSP_PMC_USB_USBDIV_Msk (0xfu << CSP_PMC_USB_USBDIV_Pos) /**< \brief (CSP_PMC_USB) Divider for USB OHCI Clock. */
#define CSP_PMC_USB_USBDIV(value) ((CSP_PMC_USB_USBDIV_Msk & ((value) << CSP_PMC_USB_USBDIV_Pos)))
/* -------- PMC_SMD : (PMC Offset: 0x003C) Soft Modem Clock Register -------- */
#define CSP_PMC_SMD_SMDS (0x1u << 0) /**< \brief (CSP_PMC_SMD) SMD input clock selection */
#define CSP_PMC_SMD_SMDDIV_Pos 8
#define CSP_PMC_SMD_SMDDIV_Msk (0x1fu << CSP_PMC_SMD_SMDDIV_Pos) /**< \brief (CSP_PMC_SMD) Divider for SMD Clock. */
#define CSP_PMC_SMD_SMDDIV(value) ((CSP_PMC_SMD_SMDDIV_Msk & ((value) << CSP_PMC_SMD_SMDDIV_Pos)))
/* -------- PMC_PCK[2] : (PMC Offset: 0x0040) Programmable Clock 0 Register -------- */
#define CSP_PMC_PCK_CSS_Pos 0
#define CSP_PMC_PCK_CSS_Msk (0x7u << CSP_PMC_PCK_CSS_Pos) /**< \brief (CSP_PMC_PCK[2]) Master Clock Source Selection */
#define  CSP_PMC_PCK_CSS_SLOW_CLK (0x0u << 0) /**< \brief (CSP_PMC_PCK[2]) Slow Clock is selected */
#define  CSP_PMC_PCK_CSS_MAIN_CLK (0x1u << 0) /**< \brief (CSP_PMC_PCK[2]) Main Clock is selected */
#define  CSP_PMC_PCK_CSS_PLLA_CLK (0x2u << 0) /**< \brief (CSP_PMC_PCK[2]) PLLACK/PLLADIV2 is selected */
#define  CSP_PMC_PCK_CSS_UPLL_CLK (0x3u << 0) /**< \brief (CSP_PMC_PCK[2]) UPLL Clock is selected */
#define  CSP_PMC_PCK_CSS_MCK_CLK (0x4u << 0) /**< \brief (CSP_PMC_PCK[2]) Master Clock is selected */
#define CSP_PMC_PCK_PRES_Pos 4
#define CSP_PMC_PCK_PRES_Msk (0x7u << CSP_PMC_PCK_PRES_Pos) /**< \brief (CSP_PMC_PCK[2]) Programmable Clock Prescaler */
#define  CSP_PMC_PCK_PRES_CLOCK (0x0u << 4) /**< \brief (CSP_PMC_PCK[2]) Selected clock */
#define  CSP_PMC_PCK_PRES_CLOCK_DIV2 (0x1u << 4) /**< \brief (CSP_PMC_PCK[2]) Selected clock divided by 2 */
#define  CSP_PMC_PCK_PRES_CLOCK_DIV4 (0x2u << 4) /**< \brief (CSP_PMC_PCK[2]) Selected clock divided by 4 */
#define  CSP_PMC_PCK_PRES_CLOCK_DIV8 (0x3u << 4) /**< \brief (CSP_PMC_PCK[2]) Selected clock divided by 8 */
#define  CSP_PMC_PCK_PRES_CLOCK_DIV16 (0x4u << 4) /**< \brief (CSP_PMC_PCK[2]) Selected clock divided by 16 */
#define  CSP_PMC_PCK_PRES_CLOCK_DIV32 (0x5u << 4) /**< \brief (CSP_PMC_PCK[2]) Selected clock divided by 32 */
#define  CSP_PMC_PCK_PRES_CLOCK_DIV64 (0x6u << 4) /**< \brief (CSP_PMC_PCK[2]) Selected clock divided by 64 */
/* -------- PMC_IER : (PMC Offset: 0x0060) Interrupt Enable Register -------- */
#define CSP_PMC_IER_MOSCXTS (0x1u << 0) /**< \brief (CSP_PMC_IER) Main Crystal Oscillator Status Interrupt Enable */
#define CSP_PMC_IER_LOCKA (0x1u << 1) /**< \brief (CSP_PMC_IER) PLLA Lock Interrupt Enable */
#define CSP_PMC_IER_MCKRDY (0x1u << 3) /**< \brief (CSP_PMC_IER) Master Clock Ready Interrupt Enable */
#define CSP_PMC_IER_LOCKU (0x1u << 6) /**< \brief (CSP_PMC_IER) UTMI PLL Lock Interrupt Enable */
#define CSP_PMC_IER_PCKRDY0 (0x1u << 8) /**< \brief (CSP_PMC_IER) Programmable Clock Ready 0 Interrupt Enable */
#define CSP_PMC_IER_PCKRDY1 (0x1u << 9) /**< \brief (CSP_PMC_IER) Programmable Clock Ready 1 Interrupt Enable */
#define CSP_PMC_IER_MOSCSELS (0x1u << 16) /**< \brief (CSP_PMC_IER) Main Oscillator Selection Status Interrupt Enable */
#define CSP_PMC_IER_MOSCRCS (0x1u << 17) /**< \brief (CSP_PMC_IER) Main On-Chip RC Status Interrupt Enable */
#define CSP_PMC_IER_CFDEV (0x1u << 18) /**< \brief (CSP_PMC_IER) Clock Failure Detector Event Interrupt Enable */
/* -------- PMC_IDR : (PMC Offset: 0x0064) Interrupt Disable Register -------- */
#define CSP_PMC_IDR_MOSCXTS (0x1u << 0) /**< \brief (CSP_PMC_IDR) Main Crystal Oscillator Status Interrupt Disable */
#define CSP_PMC_IDR_LOCKA (0x1u << 1) /**< \brief (CSP_PMC_IDR) PLLA Lock Interrupt Disable */
#define CSP_PMC_IDR_MCKRDY (0x1u << 3) /**< \brief (CSP_PMC_IDR) Master Clock Ready Interrupt Disable */
#define CSP_PMC_IDR_LOCKU (0x1u << 6) /**< \brief (CSP_PMC_IDR) UTMI PLL Lock Interrupt Enable */
#define CSP_PMC_IDR_PCKRDY0 (0x1u << 8) /**< \brief (CSP_PMC_IDR) Programmable Clock Ready 0 Interrupt Disable */
#define CSP_PMC_IDR_PCKRDY1 (0x1u << 9) /**< \brief (CSP_PMC_IDR) Programmable Clock Ready 1 Interrupt Disable */
#define CSP_PMC_IDR_MOSCSELS (0x1u << 16) /**< \brief (CSP_PMC_IDR) Main Oscillator Selection Status Interrupt Disable */
#define CSP_PMC_IDR_MOSCRCS (0x1u << 17) /**< \brief (CSP_PMC_IDR) Main On-Chip RC Status Interrupt Disable */
#define CSP_PMC_IDR_CFDEV (0x1u << 18) /**< \brief (CSP_PMC_IDR) Clock Failure Detector Event Interrupt Disable */
/* -------- PMC_SR : (PMC Offset: 0x0068) Status Register -------- */
#define CSP_PMC_SR_MOSCXTS (0x1u << 0) /**< \brief (CSP_PMC_SR) Main XTAL Oscillator Status */
#define CSP_PMC_SR_LOCKA (0x1u << 1) /**< \brief (CSP_PMC_SR) PLLA Lock Status */
#define CSP_PMC_SR_MCKRDY (0x1u << 3) /**< \brief (CSP_PMC_SR) Master Clock Status */
#define CSP_PMC_SR_LOCKU (0x1u << 6) /**< \brief (CSP_PMC_SR) UPLL Clock Status */
#define CSP_PMC_SR_OSCSELS (0x1u << 7) /**< \brief (CSP_PMC_SR) Slow Clock Oscillator Selection */
#define CSP_PMC_SR_PCKRDY0 (0x1u << 8) /**< \brief (CSP_PMC_SR) Programmable Clock Ready Status */
#define CSP_PMC_SR_PCKRDY1 (0x1u << 9) /**< \brief (CSP_PMC_SR) Programmable Clock Ready Status */
#define CSP_PMC_SR_MOSCSELS (0x1u << 16) /**< \brief (CSP_PMC_SR) Main Oscillator Selection Status */
#define CSP_PMC_SR_MOSCRCS (0x1u << 17) /**< \brief (CSP_PMC_SR) Main On-Chip RC Oscillator Status */
#define CSP_PMC_SR_CFDEV (0x1u << 18) /**< \brief (CSP_PMC_SR) Clock Failure Detector Event */
#define CSP_PMC_SR_CFDS (0x1u << 19) /**< \brief (CSP_PMC_SR) Clock Failure Detector Status */
#define CSP_PMC_SR_FOS (0x1u << 20) /**< \brief (CSP_PMC_SR) Clock Failure Detector Fault Output Status */
/* -------- PMC_IMR : (PMC Offset: 0x006C) Interrupt Mask Register -------- */
#define CSP_PMC_IMR_MOSCXTS (0x1u << 0) /**< \brief (CSP_PMC_IMR) Main Crystal Oscillator Status Interrupt Mask */
#define CSP_PMC_IMR_LOCKA (0x1u << 1) /**< \brief (CSP_PMC_IMR) PLLA Lock Interrupt Mask */
#define CSP_PMC_IMR_MCKRDY (0x1u << 3) /**< \brief (CSP_PMC_IMR) Master Clock Ready Interrupt Mask */
#define CSP_PMC_IMR_PCKRDY0 (0x1u << 8) /**< \brief (CSP_PMC_IMR) Programmable Clock Ready 0 Interrupt Mask */
#define CSP_PMC_IMR_PCKRDY1 (0x1u << 9) /**< \brief (CSP_PMC_IMR) Programmable Clock Ready 1 Interrupt Mask */
#define CSP_PMC_IMR_MOSCSELS (0x1u << 16) /**< \brief (CSP_PMC_IMR) Main Oscillator Selection Status Interrupt Mask */
#define CSP_PMC_IMR_MOSCRCS (0x1u << 17) /**< \brief (CSP_PMC_IMR) Main On-Chip RC Status Interrupt Mask */
#define CSP_PMC_IMR_CFDEV (0x1u << 18) /**< \brief (CSP_PMC_IMR) Clock Failure Detector Event Interrupt Mask */
/* -------- PMC_PLLICPR : (PMC Offset: 0x0080) PLL Charge Pump Current Register -------- */
#define CSP_PMC_PLLICPR_ICPLLA (0x1u << 0) /**< \brief (CSP_PMC_PLLICPR) Charge Pump Current */
/* -------- PMC_WPMR : (PMC Offset: 0x00E4) Write Protect Mode Register -------- */
#define CSP_PMC_WPMR_WPEN (0x1u << 0) /**< \brief (CSP_PMC_WPMR) Write Protect Enable */
#define CSP_PMC_WPMR_WPKEY_Pos 8
#define CSP_PMC_WPMR_WPKEY_Msk (0xffffffu << CSP_PMC_WPMR_WPKEY_Pos) /**< \brief (CSP_PMC_WPMR) Write Protect KEY */
#define CSP_PMC_WPMR_WPKEY(value) ((CSP_PMC_WPMR_WPKEY_Msk & ((value) << CSP_PMC_WPMR_WPKEY_Pos)))
/* -------- PMC_WPSR : (PMC Offset: 0x00E8) Write Protect Status Register -------- */
#define CSP_PMC_WPSR_WPVS (0x1u << 0) /**< \brief (CSP_PMC_WPSR) Write Protect Violation Status */
#define CSP_PMC_WPSR_WPVSRC_Pos 8
#define CSP_PMC_WPSR_WPVSRC_Msk (0xffffu << CSP_PMC_WPSR_WPVSRC_Pos) /**< \brief (CSP_PMC_WPSR) Write Protect Violation Source */
/* -------- PMC_PCR : (PMC Offset: 0x010C) Peripheral Control Register -------- */
#define CSP_PMC_PCR_PID_Pos 0
#define CSP_PMC_PCR_PID_Msk (0x3fu << CSP_PMC_PCR_PID_Pos) /**< \brief (CSP_PMC_PCR) Peripheral ID */
#define CSP_PMC_PCR_PID(value) ((CSP_PMC_PCR_PID_Msk & ((value) << CSP_PMC_PCR_PID_Pos)))
#define CSP_PMC_PCR_CMD (0x1u << 12) /**< \brief (CSP_PMC_PCR) Command */
#define CSP_PMC_PCR_DIV_Pos 16
#define CSP_PMC_PCR_DIV_Msk (0x3u << CSP_PMC_PCR_DIV_Pos) /**< \brief (CSP_PMC_PCR) Divisor Value */
#define  CSP_PMC_PCR_DIV_PERIPH_DIV_MCK (0x0u << 16) /**< \brief (CSP_PMC_PCR) Peripheral clock is MCK */
#define  CSP_PMC_PCR_DIV_PERIPH_DIV2_MCK (0x1u << 16) /**< \brief (CSP_PMC_PCR) Peripheral clock is MCK/2 */
#define  CSP_PMC_PCR_DIV_PERIPH_DIV4_MCK (0x2u << 16) /**< \brief (CSP_PMC_PCR) Peripheral clock is MCK/4 */
#define  CSP_PMC_PCR_DIV_PERIPH_DIV8_MCK (0x3u << 16) /**< \brief (CSP_PMC_PCR) Peripheral clock is MCK/8 */
#define CSP_PMC_PCR_EN (0x1u << 28) /**< \brief (CSP_PMC_PCR) Enable */



/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of CSP_PMC module include.                      */

