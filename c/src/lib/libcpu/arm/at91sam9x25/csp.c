/*
*********************************************************************************************************
*        CSP
* Chip Support Package
* Filename      : csp.c
* Note(s)       : 
*
*  The license and distribution terms for this file may be
*  found in the file LICENSE in this distribution or at
*  http://www.rtems.com/license/LICENSE.
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/


#define  CSP_MODULE
#define  CSP_GRP_MODULE
#define  CSP_DEV_MODULE

#include <csp.h>



/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/
#define  CSP_CCFG_EBICSA_ADDR            (CPU_REG32 *)(0xFFFFDE00 + 0x120)

#define  CSP_MATRIXPR_NBR_MAX            (CSP_DEV_NBR)(10u)
#define  CSP_SMCCS_NBR_MAX               (CSP_DEV_NBR)(6u)

#define  CSP_MATRIX_REG_BASE_ADDR        0xFFFFDE00U
#define  CSP_MATRIX_REG                  ((CSP_MATRIX_REG_TAG_PTR)(CSP_MATRIX_REG_BASE_ADDR))

#define  CSP_SMC_REG_BASE_ADDR           0xFFFFEA00U
#define  CSP_SMC_REG                     ((CSP_SMC_REG_TAG_PTR)(CSP_SMC_REG_BASE_ADDR))

#if 0
#define SMD      CAST(Smd     , 0x00400000U) /**< \brief (SMD     ) Base Address */
#define SPI0     CAST(Spi     , 0xF0000000U) /**< \brief (SPI0    ) Base Address */
#define SPI1     CAST(Spi     , 0xF0004000U) /**< \brief (SPI1    ) Base Address */
#define HSMCI0   CAST(Hsmci   , 0xF0008000U) /**< \brief (HSMCI0  ) Base Address */
#define HSMCI1   CAST(Hsmci   , 0xF000C000U) /**< \brief (HSMCI1  ) Base Address */
#define SSC      CAST(Ssc     , 0xF0010000U) /**< \brief (SSC     ) Base Address */
#define CAN0     CAST(Can     , 0xF8000000U) /**< \brief (CAN0    ) Base Address */
#define CAN1     CAST(Can     , 0xF8004000U) /**< \brief (CAN1    ) Base Address */
#define TC0      CAST(Tc      , 0xF8008000U) /**< \brief (TC0     ) Base Address */
#define TC1      CAST(Tc      , 0xF800C000U) /**< \brief (TC1     ) Base Address */
#define TWI0     CAST(Twi     , 0xF8010000U) /**< \brief (TWI0    ) Base Address */
#define TWI1     CAST(Twi     , 0xF8014000U) /**< \brief (TWI1    ) Base Address */
#define TWI2     CAST(Twi     , 0xF8018000U) /**< \brief (TWI2    ) Base Address */
#define USART0   CAST(Usart   , 0xF801C000U) /**< \brief (USART0  ) Base Address */
#define USART1   CAST(Usart   , 0xF8020000U) /**< \brief (USART1  ) Base Address */
#define USART2   CAST(Usart   , 0xF8024000U) /**< \brief (USART2  ) Base Address */
#define USART3   CAST(Usart   , 0xF8028000U) /**< \brief (USART3  ) Base Address */
#define EMAC0    CAST(Emac    , 0xF802C000U) /**< \brief (EMAC0   ) Base Address */
#define EMAC1    CAST(Emac    , 0xF8030000U) /**< \brief (EMAC1   ) Base Address */
#define PWM      CAST(Pwm     , 0xF8034000U) /**< \brief (PWM     ) Base Address */
#define UDPHS    CAST(Udphs   , 0xF803C000U) /**< \brief (UDPHS   ) Base Address */
#define UART0    CAST(Uart    , 0xF8040000U) /**< \brief (UART0   ) Base Address */
#define UART1    CAST(Uart    , 0xF8044000U) /**< \brief (UART1   ) Base Address */
#define ADC      CAST(Adc     , 0xF804C000U) /**< \brief (ADC     ) Base Address */
#define CSP_MATRIX   CAST(Matrix  , 0xFFFFDE00U) /**< \brief (MATRIX  ) Base Address */
#define PMECC    CAST(Pmecc   , 0xFFFFE000U) /**< \brief (PMECC   ) Base Address */
#define PMERRLOC CAST(Pmerrloc, 0xFFFFE600U) /**< \brief (PMERRLOC) Base Address */
#define DDRSDRC  CAST(Ddrsdrc , 0xFFFFE800U) /**< \brief (DDRSDRC ) Base Address */
#define SMC      CAST(Smc     , 0xFFFFEA00U) /**< \brief (SMC     ) Base Address */
#define DMAC0    CAST(Dmac    , 0xFFFFEC00U) /**< \brief (DMAC0   ) Base Address */
#define DMAC1    CAST(Dmac    , 0xFFFFEE00U) /**< \brief (DMAC1   ) Base Address */
#define AIC      CAST(Aic     , 0xFFFFF000U) /**< \brief (AIC     ) Base Address */
#define DBGU     CAST(Dbgu    , 0xFFFFF200U) /**< \brief (DBGU    ) Base Address */
#define PIOA     CAST(Pio     , 0xFFFFF400U) /**< \brief (PIOA    ) Base Address */
#define PIOB     CAST(Pio     , 0xFFFFF600U) /**< \brief (PIOB    ) Base Address */
#define PIOC     CAST(Pio     , 0xFFFFF800U) /**< \brief (PIOC    ) Base Address */
#define PIOD     CAST(Pio     , 0xFFFFFA00U) /**< \brief (PIOD    ) Base Address */
#define PMC      CAST(Pmc     , 0xFFFFFC00U) /**< \brief (PMC     ) Base Address */
#define RSTC     CAST(Rstc    , 0xFFFFFE00U) /**< \brief (RSTC    ) Base Address */
#define SHDWC    CAST(Shdwc   , 0xFFFFFE10U) /**< \brief (SHDWC   ) Base Address */
#define PIT      CAST(Pit     , 0xFFFFFE30U) /**< \brief (PIT     ) Base Address */
#define WDT      CAST(Wdt     , 0xFFFFFE40U) /**< \brief (WDT     ) Base Address */
#define GPBR     CAST(Gpbr    , 0xFFFFFE60U) /**< \brief (GPBR    ) Base Address */
#define RTC      CAST(Rtc     , 0xFFFFFEB0U) /**< \brief (RTC     ) Base Address */
#endif

/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
* SOFTWARE API DEFINITION FOR AHB Bus Matrix
* AT91SAM9X25_MATRIX AHB Bus Matrix
*********************************************************************************************************
*/

#ifndef __ASSEMBLY__
/* MatrixPr hardware registers */
typedef struct {
  CPU_REG32     MATRIX_PRAS;     /**< \brief (MatrixPr Offset: 0x0) Priority Register A for Slave 0 */
  CPU_REG32     CSP_MATRIX_PRBS;     /**< \brief (MatrixPr Offset: 0x4) Priority Register B for Slave 0 */
} __MatrixPr;
/** \brief Matrix hardware registers */

typedef struct {
  CPU_REG32     MATRIX_MCFG0;    /**< \brief (Matrix Offset: 0x0000) Master Configuration Register 0 */
  CPU_REG32     MATRIX_MCFG1;    /**< \brief (Matrix Offset: 0x0004) Master Configuration Register 1 */
  CPU_REG32     MATRIX_MCFG2;    /**< \brief (Matrix Offset: 0x0008) Master Configuration Register 2 */
  CPU_REG32     MATRIX_MCFG3;    /**< \brief (Matrix Offset: 0x000C) Master Configuration Register 3 */
  CPU_REG32     MATRIX_MCFG4;    /**< \brief (Matrix Offset: 0x0010) Master Configuration Register 4 */
  CPU_REG32     MATRIX_MCFG5;    /**< \brief (Matrix Offset: 0x0014) Master Configuration Register 5 */
  CPU_REG32     MATRIX_MCFG6;    /**< \brief (Matrix Offset: 0x0018) Master Configuration Register 6 */
  CPU_REG32     MATRIX_MCFG7;    /**< \brief (Matrix Offset: 0x001C) Master Configuration Register 7 */
  CPU_REG32     MATRIX_MCFG8;    /**< \brief (Matrix Offset: 0x0020) Master Configuration Register 8 */
  CPU_REG32     Reserved1[1];
  CPU_REG32     MATRIX_MCFG10;   /**< \brief (Matrix Offset: 0x0028) Master Configuration Register 10 */
  CPU_REG32     MATRIX_MCFG11;   /**< \brief (Matrix Offset: 0x002C) Master Configuration Register 11 */
  CPU_REG32     Reserved2[4];
  CPU_REG32     MATRIX_SCFG[10]; /**< \brief (Matrix Offset: 0x0040) Slave Configuration Register */
  CPU_REG32     Reserved3[6];
  __MatrixPr    MATRIX_PR[CSP_MATRIXPR_NBR_MAX]; /**< \brief (Matrix Offset: 0x0080) 0 .. 9 */
  CPU_REG32     Reserved4[12];
  CPU_REG32     MATRIX_MRCR;     /**< \brief (Matrix Offset: 0x0100) Master Remap Control Register */
  CPU_REG32     Reserved5[56];
  CPU_REG32     CSP_MATRIX_WPMR;     /**< \brief (Matrix Offset: 0x01E4) Write Protect Mode Register */
  CPU_REG32     CSP_MATRIX_WPSR;     /**< \brief (Matrix Offset: 0x01E8) Write Protect Status Register */
} CSP_MATRIX_REG_TAG, *CSP_MATRIX_REG_TAG_PTR;
#endif /* __ASSEMBLY__ */
/* -------- CSP_MATRIX_MCFG0 : (MATRIX Offset: 0x0000) Master Configuration Register 0 -------- */
#define CSP_MATRIX_MCFG0_ULBT_Pos 0
#define CSP_MATRIX_MCFG0_ULBT_Msk (0x7u << CSP_MATRIX_MCFG0_ULBT_Pos) /**< \brief (CSP_MATRIX_MCFG0) Undefined Length Burst Type */
#define CSP_MATRIX_MCFG0_ULBT(value) ((CSP_MATRIX_MCFG0_ULBT_Msk & ((value) << CSP_MATRIX_MCFG0_ULBT_Pos)))
/* -------- CSP_MATRIX_MCFG1 : (MATRIX Offset: 0x0004) Master Configuration Register 1 -------- */
#define CSP_MATRIX_MCFG1_ULBT_Pos 0
#define CSP_MATRIX_MCFG1_ULBT_Msk (0x7u << CSP_MATRIX_MCFG1_ULBT_Pos) /**< \brief (CSP_MATRIX_MCFG1) Undefined Length Burst Type */
#define CSP_MATRIX_MCFG1_ULBT(value) ((CSP_MATRIX_MCFG1_ULBT_Msk & ((value) << CSP_MATRIX_MCFG1_ULBT_Pos)))
/* -------- CSP_MATRIX_MCFG2 : (MATRIX Offset: 0x0008) Master Configuration Register 2 -------- */
#define CSP_MATRIX_MCFG2_ULBT_Pos 0
#define CSP_MATRIX_MCFG2_ULBT_Msk (0x7u << CSP_MATRIX_MCFG2_ULBT_Pos) /**< \brief (CSP_MATRIX_MCFG2) Undefined Length Burst Type */
#define CSP_MATRIX_MCFG2_ULBT(value) ((CSP_MATRIX_MCFG2_ULBT_Msk & ((value) << CSP_MATRIX_MCFG2_ULBT_Pos)))
/* -------- CSP_MATRIX_MCFG3 : (MATRIX Offset: 0x000C) Master Configuration Register 3 -------- */
#define CSP_MATRIX_MCFG3_ULBT_Pos 0
#define CSP_MATRIX_MCFG3_ULBT_Msk (0x7u << CSP_MATRIX_MCFG3_ULBT_Pos) /**< \brief (CSP_MATRIX_MCFG3) Undefined Length Burst Type */
#define CSP_MATRIX_MCFG3_ULBT(value) ((CSP_MATRIX_MCFG3_ULBT_Msk & ((value) << CSP_MATRIX_MCFG3_ULBT_Pos)))
/* -------- CSP_MATRIX_MCFG4 : (MATRIX Offset: 0x0010) Master Configuration Register 4 -------- */
#define CSP_MATRIX_MCFG4_ULBT_Pos 0
#define CSP_MATRIX_MCFG4_ULBT_Msk (0x7u << CSP_MATRIX_MCFG4_ULBT_Pos) /**< \brief (CSP_MATRIX_MCFG4) Undefined Length Burst Type */
#define CSP_MATRIX_MCFG4_ULBT(value) ((CSP_MATRIX_MCFG4_ULBT_Msk & ((value) << CSP_MATRIX_MCFG4_ULBT_Pos)))
/* -------- CSP_MATRIX_MCFG5 : (MATRIX Offset: 0x0014) Master Configuration Register 5 -------- */
#define CSP_MATRIX_MCFG5_ULBT_Pos 0
#define CSP_MATRIX_MCFG5_ULBT_Msk (0x7u << CSP_MATRIX_MCFG5_ULBT_Pos) /**< \brief (CSP_MATRIX_MCFG5) Undefined Length Burst Type */
#define CSP_MATRIX_MCFG5_ULBT(value) ((CSP_MATRIX_MCFG5_ULBT_Msk & ((value) << CSP_MATRIX_MCFG5_ULBT_Pos)))
/* -------- CSP_MATRIX_MCFG6 : (MATRIX Offset: 0x0018) Master Configuration Register 6 -------- */
#define CSP_MATRIX_MCFG6_ULBT_Pos 0
#define CSP_MATRIX_MCFG6_ULBT_Msk (0x7u << CSP_MATRIX_MCFG6_ULBT_Pos) /**< \brief (CSP_MATRIX_MCFG6) Undefined Length Burst Type */
#define CSP_MATRIX_MCFG6_ULBT(value) ((CSP_MATRIX_MCFG6_ULBT_Msk & ((value) << CSP_MATRIX_MCFG6_ULBT_Pos)))
/* -------- CSP_MATRIX_MCFG7 : (MATRIX Offset: 0x001C) Master Configuration Register 7 -------- */
#define CSP_MATRIX_MCFG7_ULBT_Pos 0
#define CSP_MATRIX_MCFG7_ULBT_Msk (0x7u << CSP_MATRIX_MCFG7_ULBT_Pos) /**< \brief (CSP_MATRIX_MCFG7) Undefined Length Burst Type */
#define CSP_MATRIX_MCFG7_ULBT(value) ((CSP_MATRIX_MCFG7_ULBT_Msk & ((value) << CSP_MATRIX_MCFG7_ULBT_Pos)))
/* -------- CSP_MATRIX_MCFG8 : (MATRIX Offset: 0x0020) Master Configuration Register 8 -------- */
#define CSP_MATRIX_MCFG8_ULBT_Pos 0
#define CSP_MATRIX_MCFG8_ULBT_Msk (0x7u << CSP_MATRIX_MCFG8_ULBT_Pos) /**< \brief (CSP_MATRIX_MCFG8) Undefined Length Burst Type */
#define CSP_MATRIX_MCFG8_ULBT(value) ((CSP_MATRIX_MCFG8_ULBT_Msk & ((value) << CSP_MATRIX_MCFG8_ULBT_Pos)))
/* -------- CSP_MATRIX_MCFG10 : (MATRIX Offset: 0x0028) Master Configuration Register 10 -------- */
#define CSP_MATRIX_MCFG10_ULBT_Pos 0
#define CSP_MATRIX_MCFG10_ULBT_Msk (0x7u << CSP_MATRIX_MCFG10_ULBT_Pos) /**< \brief (CSP_MATRIX_MCFG10) Undefined Length Burst Type */
#define CSP_MATRIX_MCFG10_ULBT(value) ((CSP_MATRIX_MCFG10_ULBT_Msk & ((value) << CSP_MATRIX_MCFG10_ULBT_Pos)))
/* -------- CSP_MATRIX_MCFG11 : (MATRIX Offset: 0x002C) Master Configuration Register 11 -------- */
#define CSP_MATRIX_MCFG11_ULBT_Pos 0
#define CSP_MATRIX_MCFG11_ULBT_Msk (0x7u << CSP_MATRIX_MCFG11_ULBT_Pos) /**< \brief (CSP_MATRIX_MCFG11) Undefined Length Burst Type */
#define CSP_MATRIX_MCFG11_ULBT(value) ((CSP_MATRIX_MCFG11_ULBT_Msk & ((value) << CSP_MATRIX_MCFG11_ULBT_Pos)))
/* -------- MATRIX_SCFG[10] : (MATRIX Offset: 0x0040) Slave Configuration Register -------- */
#define CSP_MATRIX_SCFG_SLOT_CYCLE_Pos 0
#define CSP_MATRIX_SCFG_SLOT_CYCLE_Msk (0x1ffu << CSP_MATRIX_SCFG_SLOT_CYCLE_Pos) /**< \brief (MATRIX_SCFG[10]) Maximum Bus Grant Duration for Masters */
#define CSP_MATRIX_SCFG_SLOT_CYCLE(value) ((CSP_MATRIX_SCFG_SLOT_CYCLE_Msk & ((value) << CSP_MATRIX_SCFG_SLOT_CYCLE_Pos)))
#define CSP_MATRIX_SCFG_DEFMSTR_TYPE_Pos 16
#define CSP_MATRIX_SCFG_DEFMSTR_TYPE_Msk (0x3u << CSP_MATRIX_SCFG_DEFMSTR_TYPE_Pos) /**< \brief (MATRIX_SCFG[10]) Default Master Type */
#define CSP_MATRIX_SCFG_DEFMSTR_TYPE(value) ((CSP_MATRIX_SCFG_DEFMSTR_TYPE_Msk & ((value) << CSP_MATRIX_SCFG_DEFMSTR_TYPE_Pos)))
#define CSP_MATRIX_SCFG_FIXED_DEFMSTR_Pos 18
#define CSP_MATRIX_SCFG_FIXED_DEFMSTR_Msk (0xfu << CSP_MATRIX_SCFG_FIXED_DEFMSTR_Pos) /**< \brief (MATRIX_SCFG[10]) Fixed Default Master */
#define CSP_MATRIX_SCFG_FIXED_DEFMSTR(value) ((CSP_MATRIX_SCFG_FIXED_DEFMSTR_Msk & ((value) << CSP_MATRIX_SCFG_FIXED_DEFMSTR_Pos)))
/* -------- MATRIX_PRAS : (MATRIX Offset: N/A) Priority Register A for Slave 0 -------- */
#define CSP_MATRIX_PRAS_M0PR_Pos 0
#define CSP_MATRIX_PRAS_M0PR_Msk (0x3u << CSP_MATRIX_PRAS_M0PR_Pos) /**< \brief (MATRIX_PRAS) Master 0 Priority */
#define CSP_MATRIX_PRAS_M0PR(value) ((CSP_MATRIX_PRAS_M0PR_Msk & ((value) << CSP_MATRIX_PRAS_M0PR_Pos)))
#define CSP_MATRIX_PRAS_M1PR_Pos 4
#define CSP_MATRIX_PRAS_M1PR_Msk (0x3u << CSP_MATRIX_PRAS_M1PR_Pos) /**< \brief (MATRIX_PRAS) Master 1 Priority */
#define CSP_MATRIX_PRAS_M1PR(value) ((CSP_MATRIX_PRAS_M1PR_Msk & ((value) << CSP_MATRIX_PRAS_M1PR_Pos)))
#define CSP_MATRIX_PRAS_M2PR_Pos 8
#define CSP_MATRIX_PRAS_M2PR_Msk (0x3u << CSP_MATRIX_PRAS_M2PR_Pos) /**< \brief (MATRIX_PRAS) Master 2 Priority */
#define CSP_MATRIX_PRAS_M2PR(value) ((CSP_MATRIX_PRAS_M2PR_Msk & ((value) << CSP_MATRIX_PRAS_M2PR_Pos)))
#define CSP_MATRIX_PRAS_M3PR_Pos 12
#define CSP_MATRIX_PRAS_M3PR_Msk (0x3u << CSP_MATRIX_PRAS_M3PR_Pos) /**< \brief (MATRIX_PRAS) Master 3 Priority */
#define CSP_MATRIX_PRAS_M3PR(value) ((CSP_MATRIX_PRAS_M3PR_Msk & ((value) << CSP_MATRIX_PRAS_M3PR_Pos)))
#define CSP_MATRIX_PRAS_M4PR_Pos 16
#define CSP_MATRIX_PRAS_M4PR_Msk (0x3u << CSP_MATRIX_PRAS_M4PR_Pos) /**< \brief (MATRIX_PRAS) Master 4 Priority */
#define CSP_MATRIX_PRAS_M4PR(value) ((CSP_MATRIX_PRAS_M4PR_Msk & ((value) << CSP_MATRIX_PRAS_M4PR_Pos)))
#define CSP_MATRIX_PRAS_M5PR_Pos 20
#define CSP_MATRIX_PRAS_M5PR_Msk (0x3u << CSP_MATRIX_PRAS_M5PR_Pos) /**< \brief (MATRIX_PRAS) Master 5 Priority */
#define CSP_MATRIX_PRAS_M5PR(value) ((CSP_MATRIX_PRAS_M5PR_Msk & ((value) << CSP_MATRIX_PRAS_M5PR_Pos)))
#define CSP_MATRIX_PRAS_M6PR_Pos 24
#define CSP_MATRIX_PRAS_M6PR_Msk (0x3u << CSP_MATRIX_PRAS_M6PR_Pos) /**< \brief (MATRIX_PRAS) Master 6 Priority */
#define CSP_MATRIX_PRAS_M6PR(value) ((CSP_MATRIX_PRAS_M6PR_Msk & ((value) << CSP_MATRIX_PRAS_M6PR_Pos)))
#define CSP_MATRIX_PRAS_M7PR_Pos 28
#define CSP_MATRIX_PRAS_M7PR_Msk (0x3u << CSP_MATRIX_PRAS_M7PR_Pos) /**< \brief (MATRIX_PRAS) Master 7 Priority */
#define CSP_MATRIX_PRAS_M7PR(value) ((CSP_MATRIX_PRAS_M7PR_Msk & ((value) << CSP_MATRIX_PRAS_M7PR_Pos)))
/* -------- CSP_MATRIX_PRBS : (MATRIX Offset: N/A) Priority Register B for Slave 0 -------- */
#define CSP_MATRIX_PRBS_M8PR_Pos 0
#define CSP_MATRIX_PRBS_M8PR_Msk (0x3u << CSP_MATRIX_PRBS_M8PR_Pos) /**< \brief (CSP_MATRIX_PRBS) Master 8 Priority */
#define CSP_MATRIX_PRBS_M8PR(value) ((CSP_MATRIX_PRBS_M8PR_Msk & ((value) << CSP_MATRIX_PRBS_M8PR_Pos)))
#define CSP_MATRIX_PRBS_M10PR_Pos 8
#define CSP_MATRIX_PRBS_M10PR_Msk (0x3u << CSP_MATRIX_PRBS_M10PR_Pos) /**< \brief (CSP_MATRIX_PRBS) Master 10 Priority */
#define CSP_MATRIX_PRBS_M10PR(value) ((CSP_MATRIX_PRBS_M10PR_Msk & ((value) << CSP_MATRIX_PRBS_M10PR_Pos)))
#define CSP_MATRIX_PRBS_M11PR_Pos 12
#define CSP_MATRIX_PRBS_M11PR_Msk (0x3u << CSP_MATRIX_PRBS_M11PR_Pos) /**< \brief (CSP_MATRIX_PRBS) Master 11 Priority */
#define CSP_MATRIX_PRBS_M11PR(value) ((CSP_MATRIX_PRBS_M11PR_Msk & ((value) << CSP_MATRIX_PRBS_M11PR_Pos)))
/* -------- MATRIX_MRCR : (MATRIX Offset: 0x0100) Master Remap Control Register -------- */
#define CSP_MATRIX_MRCR_RCB0 (0x1u << 0) /**< \brief (MATRIX_MRCR) Remap Command Bit for Master 0 */
#define CSP_MATRIX_MRCR_RCB1 (0x1u << 1) /**< \brief (MATRIX_MRCR) Remap Command Bit for Master 1 */
#define CSP_MATRIX_MRCR_RCB2 (0x1u << 2) /**< \brief (MATRIX_MRCR) Remap Command Bit for Master 2 */
#define CSP_MATRIX_MRCR_RCB3 (0x1u << 3) /**< \brief (MATRIX_MRCR) Remap Command Bit for Master 3 */
#define CSP_MATRIX_MRCR_RCB4 (0x1u << 4) /**< \brief (MATRIX_MRCR) Remap Command Bit for Master 4 */
#define CSP_MATRIX_MRCR_RCB5 (0x1u << 5) /**< \brief (MATRIX_MRCR) Remap Command Bit for Master 5 */
#define CSP_MATRIX_MRCR_RCB6 (0x1u << 6) /**< \brief (MATRIX_MRCR) Remap Command Bit for Master 6 */
#define CSP_MATRIX_MRCR_RCB7 (0x1u << 7) /**< \brief (MATRIX_MRCR) Remap Command Bit for Master 7 */
#define CSP_MATRIX_MRCR_RCB8 (0x1u << 8) /**< \brief (MATRIX_MRCR) Remap Command Bit for Master 8 */
#define CSP_MATRIX_MRCR_RCB10 (0x1u << 10) /**< \brief (MATRIX_MRCR) Remap Command Bit for Master 10 */
#define CSP_MATRIX_MRCR_RCB11 (0x1u << 11) /**< \brief (MATRIX_MRCR) Remap Command Bit for Master 11 */
/* -------- CSP_MATRIX_WPMR : (MATRIX Offset: 0x01E4) Write Protect Mode Register -------- */
#define CSP_MATRIX_WPMR_WPEN (0x1u << 0) /**< \brief (CSP_MATRIX_WPMR) Write Protect ENable */
#define CSP_MATRIX_WPMR_WPKEY_Pos 8
#define CSP_MATRIX_WPMR_WPKEY_Msk (0xffffffu << CSP_MATRIX_WPMR_WPKEY_Pos) /**< \brief (CSP_MATRIX_WPMR) Write Protect KEY (Write-only) */
#define CSP_MATRIX_WPMR_WPKEY(value) ((CSP_MATRIX_WPMR_WPKEY_Msk & ((value) << CSP_MATRIX_WPMR_WPKEY_Pos)))
/* -------- CSP_MATRIX_WPSR : (MATRIX Offset: 0x01E8) Write Protect Status Register -------- */
#define CSP_MATRIX_WPSR_WPVS (0x1u << 0) /**< \brief (CSP_MATRIX_WPSR) Write Protect Violation Status */
#define CSP_MATRIX_WPSR_WPVSRC_Pos 8
#define CSP_MATRIX_WPSR_WPVSRC_Msk (0xffffu << CSP_MATRIX_WPSR_WPVSRC_Pos) /**< \brief (CSP_MATRIX_WPSR) Write Protect Violation Source */


/*
*********************************************************************************************************
*  SOFTWARE API DEFINITION FOR Static Memory Controller
* AT91SAM9X25_SMC Static Memory Controller
*********************************************************************************************************
*/

#ifndef __ASSEMBLY__
/** \brief SmcCs_number hardware registers */
typedef struct {
  CPU_REG32         SMC_SETUP;        /**< \brief (SmcCs_number Offset: 0x0) SMC Setup Register */
  CPU_REG32         SMC_PULSE;        /**< \brief (SmcCs_number Offset: 0x4) SMC Pulse Register */
  CPU_REG32         SMC_CYCLE;        /**< \brief (SmcCs_number Offset: 0x8) SMC Cycle Register */
  CPU_REG32         SMC_MODE;         /**< \brief (SmcCs_number Offset: 0xC) SMC Mode Register */
} __SMCCS_DEV;
/** \brief Smc hardware registers */

typedef struct {
  __SMCCS_DEV      SMC_CS_NUMBER[CSP_SMCCS_NBR_MAX]; /**< \brief (Smc Offset: 0x0) CS_number = 0 .. 5 */
  CPU_REG32         Reserved1[24];
  CPU_REG32         SMC_DELAY1;       /**< \brief (Smc Offset: 0xC0) SMC Delay on I/O */
  CPU_REG32         SMC_DELAY2;       /**< \brief (Smc Offset: 0xC4) SMC Delay on I/O */
  CPU_REG32         SMC_DELAY3;       /**< \brief (Smc Offset: 0xC8) SMC Delay on I/O */
  CPU_REG32         SMC_DELAY4;       /**< \brief (Smc Offset: 0xCC) SMC Delay on I/O */
  CPU_REG32         SMC_DELAY5;       /**< \brief (Smc Offset: 0xD0) SMC Delay on I/O */
  CPU_REG32         SMC_DELAY6;       /**< \brief (Smc Offset: 0xD4) SMC Delay on I/O */
  CPU_REG32         SMC_DELAY7;       /**< \brief (Smc Offset: 0xD8) SMC Delay on I/O */
  CPU_REG32         SMC_DELAY8;       /**< \brief (Smc Offset: 0xDC) SMC Delay on I/O */
  CPU_REG32         Reserved2[1];
  CPU_REG32         SMC_WPMR;         /**< \brief (Smc Offset: 0xE4) SMC Write Protect Mode Register */
  CPU_REG32         SMC_WPSR;         /**< \brief (Smc Offset: 0xE8) SMC Write Protect Status Register */
} CSP_SMC_REG_TAG, *CSP_SMC_REG_TAG_PTR;
#endif /* __ASSEMBLY__ */
/* -------- SMC_SETUP : (SMC Offset: N/A) SMC Setup Register -------- */
#define SMC_SETUP_NWE_SETUP_Pos 0
#define SMC_SETUP_NWE_SETUP_Msk (0x3fu << SMC_SETUP_NWE_SETUP_Pos) /**< \brief (SMC_SETUP) NWE Setup Length */
#define SMC_SETUP_NWE_SETUP(value) ((SMC_SETUP_NWE_SETUP_Msk & ((value) << SMC_SETUP_NWE_SETUP_Pos)))
#define SMC_SETUP_NCS_WR_SETUP_Pos 8
#define SMC_SETUP_NCS_WR_SETUP_Msk (0x3fu << SMC_SETUP_NCS_WR_SETUP_Pos) /**< \brief (SMC_SETUP) NCS Setup Length in WRITE Access */
#define SMC_SETUP_NCS_WR_SETUP(value) ((SMC_SETUP_NCS_WR_SETUP_Msk & ((value) << SMC_SETUP_NCS_WR_SETUP_Pos)))
#define SMC_SETUP_NRD_SETUP_Pos 16
#define SMC_SETUP_NRD_SETUP_Msk (0x3fu << SMC_SETUP_NRD_SETUP_Pos) /**< \brief (SMC_SETUP) NRD Setup Length */
#define SMC_SETUP_NRD_SETUP(value) ((SMC_SETUP_NRD_SETUP_Msk & ((value) << SMC_SETUP_NRD_SETUP_Pos)))
#define SMC_SETUP_NCS_RD_SETUP_Pos 24
#define SMC_SETUP_NCS_RD_SETUP_Msk (0x3fu << SMC_SETUP_NCS_RD_SETUP_Pos) /**< \brief (SMC_SETUP) NCS Setup Length in READ Access */
#define SMC_SETUP_NCS_RD_SETUP(value) ((SMC_SETUP_NCS_RD_SETUP_Msk & ((value) << SMC_SETUP_NCS_RD_SETUP_Pos)))
/* -------- SMC_PULSE : (SMC Offset: N/A) SMC Pulse Register -------- */
#define SMC_PULSE_NWE_PULSE_Pos 0
#define SMC_PULSE_NWE_PULSE_Msk (0x7fu << SMC_PULSE_NWE_PULSE_Pos) /**< \brief (SMC_PULSE) NWE Pulse Length */
#define SMC_PULSE_NWE_PULSE(value) ((SMC_PULSE_NWE_PULSE_Msk & ((value) << SMC_PULSE_NWE_PULSE_Pos)))
#define SMC_PULSE_NCS_WR_PULSE_Pos 8
#define SMC_PULSE_NCS_WR_PULSE_Msk (0x7fu << SMC_PULSE_NCS_WR_PULSE_Pos) /**< \brief (SMC_PULSE) NCS Pulse Length in WRITE Access */
#define SMC_PULSE_NCS_WR_PULSE(value) ((SMC_PULSE_NCS_WR_PULSE_Msk & ((value) << SMC_PULSE_NCS_WR_PULSE_Pos)))
#define SMC_PULSE_NRD_PULSE_Pos 16
#define SMC_PULSE_NRD_PULSE_Msk (0x7fu << SMC_PULSE_NRD_PULSE_Pos) /**< \brief (SMC_PULSE) NRD Pulse Length */
#define SMC_PULSE_NRD_PULSE(value) ((SMC_PULSE_NRD_PULSE_Msk & ((value) << SMC_PULSE_NRD_PULSE_Pos)))
#define SMC_PULSE_NCS_RD_PULSE_Pos 24
#define SMC_PULSE_NCS_RD_PULSE_Msk (0x7fu << SMC_PULSE_NCS_RD_PULSE_Pos) /**< \brief (SMC_PULSE) NCS Pulse Length in READ Access */
#define SMC_PULSE_NCS_RD_PULSE(value) ((SMC_PULSE_NCS_RD_PULSE_Msk & ((value) << SMC_PULSE_NCS_RD_PULSE_Pos)))
/* -------- SMC_CYCLE : (SMC Offset: N/A) SMC Cycle Register -------- */
#define SMC_CYCLE_NWE_CYCLE_Pos 0
#define SMC_CYCLE_NWE_CYCLE_Msk (0x1ffu << SMC_CYCLE_NWE_CYCLE_Pos) /**< \brief (SMC_CYCLE) Total Write Cycle Length */
#define SMC_CYCLE_NWE_CYCLE(value) ((SMC_CYCLE_NWE_CYCLE_Msk & ((value) << SMC_CYCLE_NWE_CYCLE_Pos)))
#define SMC_CYCLE_NRD_CYCLE_Pos 16
#define SMC_CYCLE_NRD_CYCLE_Msk (0x1ffu << SMC_CYCLE_NRD_CYCLE_Pos) /**< \brief (SMC_CYCLE) Total Read Cycle Length */
#define SMC_CYCLE_NRD_CYCLE(value) ((SMC_CYCLE_NRD_CYCLE_Msk & ((value) << SMC_CYCLE_NRD_CYCLE_Pos)))
/* -------- SMC_MODE : (SMC Offset: N/A) SMC Mode Register -------- */
#define SMC_MODE_READ_MODE (0x1u << 0) /**< \brief (SMC_MODE)  */
#define SMC_MODE_WRITE_MODE (0x1u << 1) /**< \brief (SMC_MODE)  */
#define SMC_MODE_EXNW_MODE_Pos 4
#define SMC_MODE_EXNW_MODE_Msk (0x3u << SMC_MODE_EXNW_MODE_Pos) /**< \brief (SMC_MODE) NWAIT Mode */
#define SMC_MODE_EXNW_MODE(value) ((SMC_MODE_EXNW_MODE_Msk & ((value) << SMC_MODE_EXNW_MODE_Pos)))
#define SMC_MODE_BAT (0x1u << 8) /**< \brief (SMC_MODE) Byte Access Type */
#define SMC_MODE_DBW_Pos 12
#define SMC_MODE_DBW_Msk (0x3u << SMC_MODE_DBW_Pos) /**< \brief (SMC_MODE) Data Bus Width */
#define SMC_MODE_DBW(value) ((SMC_MODE_DBW_Msk & ((value) << SMC_MODE_DBW_Pos)))
#define SMC_MODE_TDF_CYCLES_Pos 16
#define SMC_MODE_TDF_CYCLES_Msk (0xfu << SMC_MODE_TDF_CYCLES_Pos) /**< \brief (SMC_MODE) Data Float Time */
#define SMC_MODE_TDF_CYCLES(value) ((SMC_MODE_TDF_CYCLES_Msk & ((value) << SMC_MODE_TDF_CYCLES_Pos)))
#define SMC_MODE_TDF_MODE (0x1u << 20) /**< \brief (SMC_MODE) TDF Optimization */
#define SMC_MODE_PMEN (0x1u << 24) /**< \brief (SMC_MODE) Page Mode Enabled */
#define SMC_MODE_PS_Pos 28
#define SMC_MODE_PS_Msk (0x3u << SMC_MODE_PS_Pos) /**< \brief (SMC_MODE) Page Size */
#define SMC_MODE_PS(value) ((SMC_MODE_PS_Msk & ((value) << SMC_MODE_PS_Pos)))
/* -------- SMC_DELAY1 : (SMC Offset: 0xC0) SMC Delay on I/O -------- */
#define SMC_DELAY1_Delay1_Pos 0
#define SMC_DELAY1_Delay1_Msk (0xfu << SMC_DELAY1_Delay1_Pos) /**< \brief (SMC_DELAY1)  */
#define SMC_DELAY1_Delay1(value) ((SMC_DELAY1_Delay1_Msk & ((value) << SMC_DELAY1_Delay1_Pos)))
#define SMC_DELAY1_Delay2_Pos 4
#define SMC_DELAY1_Delay2_Msk (0xfu << SMC_DELAY1_Delay2_Pos) /**< \brief (SMC_DELAY1)  */
#define SMC_DELAY1_Delay2(value) ((SMC_DELAY1_Delay2_Msk & ((value) << SMC_DELAY1_Delay2_Pos)))
#define SMC_DELAY1_Delay3_Pos 8
#define SMC_DELAY1_Delay3_Msk (0xfu << SMC_DELAY1_Delay3_Pos) /**< \brief (SMC_DELAY1)  */
#define SMC_DELAY1_Delay3(value) ((SMC_DELAY1_Delay3_Msk & ((value) << SMC_DELAY1_Delay3_Pos)))
#define SMC_DELAY1_Delay4_Pos 12
#define SMC_DELAY1_Delay4_Msk (0xfu << SMC_DELAY1_Delay4_Pos) /**< \brief (SMC_DELAY1)  */
#define SMC_DELAY1_Delay4(value) ((SMC_DELAY1_Delay4_Msk & ((value) << SMC_DELAY1_Delay4_Pos)))
#define SMC_DELAY1_Delay5_Pos 16
#define SMC_DELAY1_Delay5_Msk (0xfu << SMC_DELAY1_Delay5_Pos) /**< \brief (SMC_DELAY1)  */
#define SMC_DELAY1_Delay5(value) ((SMC_DELAY1_Delay5_Msk & ((value) << SMC_DELAY1_Delay5_Pos)))
#define SMC_DELAY1_Delay6_Pos 20
#define SMC_DELAY1_Delay6_Msk (0xfu << SMC_DELAY1_Delay6_Pos) /**< \brief (SMC_DELAY1)  */
#define SMC_DELAY1_Delay6(value) ((SMC_DELAY1_Delay6_Msk & ((value) << SMC_DELAY1_Delay6_Pos)))
#define SMC_DELAY1_Delay7_Pos 24
#define SMC_DELAY1_Delay7_Msk (0xfu << SMC_DELAY1_Delay7_Pos) /**< \brief (SMC_DELAY1)  */
#define SMC_DELAY1_Delay7(value) ((SMC_DELAY1_Delay7_Msk & ((value) << SMC_DELAY1_Delay7_Pos)))
#define SMC_DELAY1_Delay8_Pos 28
#define SMC_DELAY1_Delay8_Msk (0xfu << SMC_DELAY1_Delay8_Pos) /**< \brief (SMC_DELAY1)  */
#define SMC_DELAY1_Delay8(value) ((SMC_DELAY1_Delay8_Msk & ((value) << SMC_DELAY1_Delay8_Pos)))
/* -------- SMC_DELAY2 : (SMC Offset: 0xC4) SMC Delay on I/O -------- */
/* -------- SMC_DELAY3 : (SMC Offset: 0xC8) SMC Delay on I/O -------- */
/* -------- SMC_DELAY4 : (SMC Offset: 0xCC) SMC Delay on I/O -------- */
/* -------- SMC_DELAY5 : (SMC Offset: 0xD0) SMC Delay on I/O -------- */
/* -------- SMC_DELAY6 : (SMC Offset: 0xD4) SMC Delay on I/O -------- */
/* -------- SMC_DELAY7 : (SMC Offset: 0xD8) SMC Delay on I/O -------- */
/* -------- SMC_DELAY8 : (SMC Offset: 0xDC) SMC Delay on I/O -------- */
/* -------- SMC_WPMR : (SMC Offset: 0xE4) SMC Write Protect Mode Register -------- */
#define SMC_WPMR_WPEN (0x1u << 0) /**< \brief (SMC_WPMR) Write Protect Enable */
#define SMC_WPMR_WPKEY_Pos 8
#define SMC_WPMR_WPKEY_Msk (0xffffffu << SMC_WPMR_WPKEY_Pos) /**< \brief (SMC_WPMR) Write Protect KEY */
#define SMC_WPMR_WPKEY(value) ((SMC_WPMR_WPKEY_Msk & ((value) << SMC_WPMR_WPKEY_Pos)))
/* -------- SMC_WPSR : (SMC Offset: 0xE8) SMC Write Protect Status Register -------- */
#define SMC_WPSR_WPVS (0x1u << 0) /**< \brief (SMC_WPSR) Write Protect Enable */
#define SMC_WPSR_WPVSRC_Pos 8
#define SMC_WPSR_WPVSRC_Msk (0xffffu << SMC_WPSR_WPVSRC_Pos) /**< \brief (SMC_WPSR) Write Protect Violation Source */

/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
/** Frequency of the board main oscillator */
#define BOARD_MAINOSC           12000000

/** Master clock frequency (when using board_lowlevel.c) */
#define BOARD_MCK                ((unsigned long)((BOARD_MAINOSC / 3 / 2 / 3) * 200 ))
void CSP_Delay (volatile CPU_INT32U num )
{
  volatile CPU_INT32U us;
  
  for(; num > 0; num--) {
    for( us = ( BOARD_MCK/100000000 ); us > 0; us--) {
      asm("nop");
    }
  }
}

/**
 * \brief Changes the mapping of the chip so that the remap area mirrors the
 * internal ROM or the EBI CS0.
 */
void CSP_RemapRom( void )
{
    CSP_MATRIX_REG->MATRIX_MRCR = 0;
}

/**
 * \brief Changes the mapping of the chip so that the remap area mirrors the
 * internal RAM.
 */
void CSP_RemapRam( void )
{
    CSP_MATRIX_REG->MATRIX_MRCR = CSP_MATRIX_MRCR_RCB0 | CSP_MATRIX_MRCR_RCB1;
}

/**
 * \brief Initialize Vdd EBI drive
 * \param 0: 1.8V 1: 3.3V
 */
void CSP_VddMemSel_Cfg( CPU_INT08U VddMemSel )
{

    if (VddMemSel == 1) {
         *CSP_CCFG_EBICSA_ADDR |=  (1u << 16);
         *CSP_CCFG_EBICSA_ADDR &= ~(1u << 17);
    }
    else {
         *CSP_CCFG_EBICSA_ADDR &= ~(1u << 16);
         *CSP_CCFG_EBICSA_ADDR &= ~(1u << 17);
    }
}

void CSP_NandFlashEn(void)
{
  CPU_REG32 regcsa;
  regcsa = *CSP_CCFG_EBICSA_ADDR;

  regcsa |= (1 << 3)   /* EBI Chip Select 3 is assigned to the Static Memory Controller and the NAND Flash Logic is activated */
         | (1 << 24);  /* NAND Flash I/O are connected to D16-D31 in case VDDIOM do not equals VDDNF */
         // | (1 << 25);  /* DDR Multi-port is enabled, performances are increased when using DDR2 (or LP-DDR) and 8-bit NAND Flash */
  regcsa &= (~(1<<8));/* 0 = EBI D0 - D15 Data Bus bits are internally pulled-up to the VDDIOM power supply. */
  regcsa |= (1<<9);/* EBI D0 - D15 Data Bus bits are not internally pulled-down */
  *CSP_CCFG_EBICSA_ADDR = regcsa;
}

void CSP_NandFlashDis(void)
{
  CPU_REG32 regcsa;
  regcsa = *CSP_CCFG_EBICSA_ADDR;

  regcsa |= (1 << 3);/* EBI Chip Select 3 is assigned to the Static Memory Controller and the NAND Flash Logic is activated */
  /* NAND Flash I/O are connected to D16-D0 in case VDDIOM do not equals VDDNF */
  regcsa &= (~(1 << 24))
         | (1 << 25);  /* DDR Multi-port is enabled, performances are increased when using DDR2 (or LP-DDR) and 8-bit NAND Flash */
  regcsa &= (~(1<<8));/* 0 = EBI D0 - D15 Data Bus bits are internally pulled-up to the VDDIOM power supply. */
  regcsa |= (1<<9);/* EBI D0 - D15 Data Bus bits are not internally pulled-down */
  *CSP_CCFG_EBICSA_ADDR = regcsa;
}

void CSP_Ddram_Cfg( CPU_INT08U busWidth )
{
}

void CSP_NandFlash_Cfg( CPU_INT08U busWidth )
{
  CSP_NandFlashEn();
  CSP_SMC_REG->SMC_CS_NUMBER[3].SMC_SETUP = 0
                    | SMC_SETUP_NWE_SETUP(1)
                    | SMC_SETUP_NCS_WR_SETUP(0)
                    | SMC_SETUP_NRD_SETUP(2)
                    | SMC_SETUP_NCS_RD_SETUP(0);

  CSP_SMC_REG->SMC_CS_NUMBER[3].SMC_PULSE = 0
                    | SMC_PULSE_NWE_PULSE(3)
                    | SMC_PULSE_NCS_WR_PULSE(5)
                    | SMC_PULSE_NRD_PULSE(4)
                    | SMC_PULSE_NCS_RD_PULSE(6);

  CSP_SMC_REG->SMC_CS_NUMBER[3].SMC_CYCLE = 0
                    | SMC_CYCLE_NWE_CYCLE(5)
                    | SMC_CYCLE_NRD_CYCLE(7);
  CSP_SMC_REG->SMC_CS_NUMBER[3].SMC_MODE = SMC_MODE_READ_MODE
                    | SMC_MODE_WRITE_MODE | SMC_MODE_DBW(busWidth/16) | SMC_MODE_TDF_CYCLES(1);    
}

void CSP_NorFlash_Cfg( CPU_INT08U busWidth )
{
 
  CSP_NandFlashDis();
  CSP_SMC_REG->SMC_CS_NUMBER[0].SMC_SETUP = 0 /* MCLK=133MHz=7.5ns */
                    | SMC_SETUP_NWE_SETUP(0) /* , min 0ns */
                    | SMC_SETUP_NCS_WR_SETUP(0) /* 22.5ns */
                    | SMC_SETUP_NRD_SETUP(0)
                    | SMC_SETUP_NCS_RD_SETUP(0);
  CSP_SMC_REG->SMC_CS_NUMBER[0].SMC_PULSE = 0
                    | SMC_PULSE_NWE_PULSE(14) /* 82.5ns */
                    | SMC_PULSE_NCS_WR_PULSE(14) /* 105ns */
                    | SMC_PULSE_NRD_PULSE(14) /* 20ns */
                    | SMC_PULSE_NCS_RD_PULSE(14); /* 65ns */
  CSP_SMC_REG->SMC_CS_NUMBER[0].SMC_CYCLE = 0
                    | SMC_CYCLE_NWE_CYCLE(20) /* 12*7.5ns , min 90 ns*/
                    | SMC_CYCLE_NRD_CYCLE(20);/* min 90ns */
  CSP_SMC_REG->SMC_CS_NUMBER[0].SMC_MODE = SMC_MODE_READ_MODE
                    | SMC_MODE_WRITE_MODE 
                    | SMC_MODE_DBW(busWidth/16)
                    | SMC_MODE_EXNW_MODE(0)
                    | SMC_MODE_TDF_CYCLES(3);                                          								
}

void CSP_SMCCSx_Cfg( CPU_INT08U smccs )
{
  if( smccs >= CSP_SMCCS_NBR_MAX) {
    return;
  }
  CSP_NandFlashDis();
  CSP_SMC_REG->SMC_CS_NUMBER[smccs].SMC_SETUP = 0 /* MCLK=133MHz=7.5ns */
                    | SMC_SETUP_NWE_SETUP(5) /* , min 0ns */
                    | SMC_SETUP_NCS_WR_SETUP(2) /* 10ns */
                    | SMC_SETUP_NRD_SETUP(5)
                    | SMC_SETUP_NCS_RD_SETUP(2);
  CSP_SMC_REG->SMC_CS_NUMBER[smccs].SMC_PULSE = 0
                    | SMC_PULSE_NWE_PULSE(10) /* 30ns */
                    | SMC_PULSE_NCS_WR_PULSE(10) /* 30ns */
                    | SMC_PULSE_NRD_PULSE(10) /* 30ns */
                    | SMC_PULSE_NCS_RD_PULSE(10); /* 30ns */
  CSP_SMC_REG->SMC_CS_NUMBER[smccs].SMC_CYCLE = 0
                    | SMC_CYCLE_NWE_CYCLE(17) /* 12*7.5ns , min 90 ns*/
                    | SMC_CYCLE_NRD_CYCLE(17);/* min 90ns */
  CSP_SMC_REG->SMC_CS_NUMBER[smccs].SMC_MODE = SMC_MODE_READ_MODE
                    | SMC_MODE_WRITE_MODE 
                    | SMC_MODE_DBW(1)
                    | SMC_MODE_EXNW_MODE(0)
                    | SMC_MODE_TDF_CYCLES(3);                  
  
}

   
#define AT91C_DM9000_NWE_SETUP          (1  << 0)                     /* Note: these timings are based on MCK, which is assumed   */   
#define AT91C_DM9000_NWE_PULSE          (3  << 0)                     /* to be 96MHz                                              */   
#define AT91C_DM9000_NWE_CYCLE          (4  << 0)        
   
#define AT91C_DM9000_NRD_SETUP          (1  << 16)               
#define AT91C_DM9000_NRD_PULSE          (3  << 16)           
#define AT91C_DM9000_NRD_CYCLE          (4  << 16)           
       
#define AT91C_DM9000_NCS_WR_SETUP       (0  << 8)        
#define AT91C_DM9000_NCS_WR_PULSE       (4  << 8)        
       
#define AT91C_DM9000_NCS_RD_SETUP       (0  << 24)           
#define AT91C_DM9000_NCS_RD_PULSE       (4  << 24)             
     
#define AT91C_DM9000_TDF                (1  << 16)     

void CSP_SMC_DM9000EP_Cfg( CPU_INT08U smccs )
{
  if( smccs >= CSP_SMCCS_NBR_MAX) {
    return;
  }
  CSP_NandFlashDis();
  CSP_SMC_REG->SMC_CS_NUMBER[smccs].SMC_SETUP = 0 /* MCLK=133MHz=7.5ns */
                    | AT91C_DM9000_NWE_SETUP /* , min 0ns */
                    | AT91C_DM9000_NCS_WR_SETUP /* 10ns */
                    | AT91C_DM9000_NRD_SETUP
                    | AT91C_DM9000_NCS_RD_SETUP;
  CSP_SMC_REG->SMC_CS_NUMBER[smccs].SMC_PULSE = 0
                    | AT91C_DM9000_NWE_PULSE /* 30ns */
                    | AT91C_DM9000_NCS_WR_PULSE /* 30ns */
                    | AT91C_DM9000_NRD_PULSE /* 30ns */
                    | AT91C_DM9000_NCS_RD_PULSE; /* 30ns */
  CSP_SMC_REG->SMC_CS_NUMBER[smccs].SMC_CYCLE = 0
                    | AT91C_DM9000_NWE_CYCLE /* 12*7.5ns , min 90 ns*/
                    | AT91C_DM9000_NRD_CYCLE;/* min 90ns */
  CSP_SMC_REG->SMC_CS_NUMBER[smccs].SMC_MODE = SMC_MODE_READ_MODE
                    | SMC_MODE_WRITE_MODE 
                    | SMC_MODE_DBW(1)
                    | SMC_MODE_EXNW_MODE(0)
                    | AT91C_DM9000_TDF;                  
  
}

/*
*********************************************************************************************************
*                                             CSP_LowLevelInit()
*
* Description : System Low Level Init (PLLs, External Memories, Boot loaders, etc).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Startup Code.
* 
* Note(s)     : none.
*********************************************************************************************************
*/

void  CSP_LowLevelInit (void)
{
  CSP_PMC_Init();
  /* Remap */
  CSP_RemapRam();
}


