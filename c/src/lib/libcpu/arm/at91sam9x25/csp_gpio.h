/*
*********************************************************************************************************
*        CSP
* Chip Support Package
* Filename      : csp_gpio.h
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

#ifndef  CSP_GPIO_PRESENT
#define  CSP_GPIO_PRESENT

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
#define  CSP_GPIO_PORT_NBR_MAX          (CSP_DEV_NBR)( 4u)		/* AT91SAM9X25 maximum number of ports                    */



#define CSP_GPIO_LISTSIZE(pPins)    (sizeof(pPins) / sizeof(CSP_GPIO_TAG))

                                                                /* ------------ GPIO DRIVE MODE DEFINES ------------- */
/*  The pin is controlled by the associated signal of peripheral A. */
/*  The pin is controlled by the associated signal of peripheral B. */
/*  The pin is controlled by the associated signal of peripheral C. */
/*  The pin is controlled by the associated signal of peripheral D. */
/*  The pin is an input. */
/*  The pin is an output and has a default level of 0. */
/*  The pin is an output and has a default level of 1. */
#define  CSP_GPIO_TYPE_PERIPH_A                    (CSP_OPT_FLAGS)(DEF_BIT_00)
#define  CSP_GPIO_TYPE_PERIPH_B                    (CSP_OPT_FLAGS)(DEF_BIT_01)
#define  CSP_GPIO_TYPE_PERIPH_C                    (CSP_OPT_FLAGS)(DEF_BIT_02)
#define  CSP_GPIO_TYPE_PERIPH_D                    (CSP_OPT_FLAGS)(DEF_BIT_03)
#define  CSP_GPIO_TYPE_INPUT                       (CSP_OPT_FLAGS)(DEF_BIT_04)
#define  CSP_GPIO_TYPE_OUTPUT_0                    (CSP_OPT_FLAGS)(DEF_BIT_05)
#define  CSP_GPIO_TYPE_OUTPUT_1                    (CSP_OPT_FLAGS)(DEF_BIT_06)

/*  The internal debouncing filter is active. */
/*  Default pin configuration (no attribute). */
/*  The internal pin pull-up is active. */
/*  The internal glitch filter is active. */
/*  The pin is open-drain. */
/*  The internal debouncing filter is active. */
/*  Enable additional interrupt modes. */
#define  CSP_GPIO_MODE_DEFAULT                     (0 << 0)
#define  CSP_GPIO_MODE_PULLUP                      (1 << 0)
#define  CSP_GPIO_MODE_DEGLITCH                    (1 << 1)
#define  CSP_GPIO_MODE_OPENDRAIN                   (1 << 2)
#define  CSP_GPIO_MODE_DEBOUNCE                    (1 << 3)

#define  CSP_GPIO_MODE_INT_AIME                 (1 << 4)

/*  Interrupt High Level/Rising Edge detection is active. */
#define CSP_GPIO_INT_RE_OR_HL             (1 << 5)
/*  Interrupt Edge detection is active. */
#define CSP_GPIO_INT_EDGE                 (1 << 6)

/*  Low level interrupt is active */
#define CSP_GPIO_INT_LOW_LEVEL            (0               | 0 | CSP_GPIO_MODE_INT_AIME)
/*  High level interrupt is active */
#define CSP_GPIO_INT_HIGH_LEVEL           (CSP_GPIO_INT_RE_OR_HL | 0 | CSP_GPIO_MODE_INT_AIME)
/*  Falling edge interrupt is active */
#define CSP_GPIO_INT_FALL_EDGE            (0               | CSP_GPIO_INT_EDGE | CSP_GPIO_MODE_INT_AIME)
/*  Rising edge interrupt is active */
#define CSP_GPIO_INT_RISE_EDGE            (CSP_GPIO_INT_RE_OR_HL | CSP_GPIO_INT_EDGE | CSP_GPIO_MODE_INT_AIME)

#define CSP_GPIO_WPMR_WPEN_EN            ( 0x01     << 0 )

#define CSP_GPIO_WPMR_WPEN_DIS           ( 0x00     << 0 )

#define CSP_GPIO_WPMR_WPKEY_VALID        ( 0x50494F << 8 )

typedef struct {
    /*  Bitmask indicating which pin(s) to configure. */
    //CPU_INT32U          mask;
  CPU_INT32U          port_nbr;
    /*  Pointer to the PIO controller which has the pin(s). */
    //CSP_GPIO_REG_TAG    *pio;
  CPU_INT32U          pins;
    /*  Peripheral ID of the PIO controller which has the pin(s). */
  //CPU_INT08U          id;
    /*  Pin type. */
  CPU_INT08U          type;
    /*  Pin attribute. */
  CPU_INT08U          attribute;
} CSP_GPIO_TAG;


                                                                /* ------------- GPIO PORT NUMBER DEFINES ------------- */
#define  CSP_GPIO_PORT_NBR_00                   (CSP_DEV_NBR)( 0u)
#define  CSP_GPIO_PORT_NBR_01                   (CSP_DEV_NBR)( 1u)
#define  CSP_GPIO_PORT_NBR_02                   (CSP_DEV_NBR)( 2u)
#define  CSP_GPIO_PORT_NBR_03                   (CSP_DEV_NBR)( 3u)
#define  CSP_GPIO_PORT_NBR_04                   (CSP_DEV_NBR)( 4u)
#define  CSP_GPIO_PORT_NBR_05                   (CSP_DEV_NBR)( 5u)
#define  CSP_GPIO_PORT_NBR_06                   (CSP_DEV_NBR)( 6u)
#define  CSP_GPIO_PORT_NBR_07                   (CSP_DEV_NBR)( 7u)
#define  CSP_GPIO_PORT_NBR_08                   (CSP_DEV_NBR)( 8u)
#define  CSP_GPIO_PORT_NBR_09                   (CSP_DEV_NBR)( 9u)
#define  CSP_GPIO_PORT_NBR_10                   (CSP_DEV_NBR)(10u)
#define  CSP_GPIO_PORT_NBR_11                   (CSP_DEV_NBR)(11u)
#define  CSP_GPIO_PORT_NBR_12                   (CSP_DEV_NBR)(12u)
#define  CSP_GPIO_PORT_NBR_13                   (CSP_DEV_NBR)(13u)
#define  CSP_GPIO_PORT_NBR_14                   (CSP_DEV_NBR)(14u)
#define  CSP_GPIO_PORT_NBR_15                   (CSP_DEV_NBR)(15u)

#define  CSP_GPIO_PORT_NBR_A                    (CSP_DEV_NBR)( 0u)
#define  CSP_GPIO_PORT_NBR_B                    (CSP_DEV_NBR)( 1u)
#define  CSP_GPIO_PORT_NBR_C                    (CSP_DEV_NBR)( 2u)
#define  CSP_GPIO_PORT_NBR_D                    (CSP_DEV_NBR)( 3u)
#define  CSP_GPIO_PORT_NBR_E                    (CSP_DEV_NBR)( 4u)
#define  CSP_GPIO_PORT_NBR_F                    (CSP_DEV_NBR)( 5u)
#define  CSP_GPIO_PORT_NBR_G                    (CSP_DEV_NBR)( 6u)
#define  CSP_GPIO_PORT_NBR_H                    (CSP_DEV_NBR)( 7u)
#define  CSP_GPIO_PORT_NBR_I                    (CSP_DEV_NBR)( 8u)
#define  CSP_GPIO_PORT_NBR_J                    (CSP_DEV_NBR)( 9u)
#define  CSP_GPIO_PORT_NBR_K                    (CSP_DEV_NBR)(10u)
#define  CSP_GPIO_PORT_NBR_L                    (CSP_DEV_NBR)(11u)
#define  CSP_GPIO_PORT_NBR_M                    (CSP_DEV_NBR)(12u)
#define  CSP_GPIO_PORT_NBR_N                    (CSP_DEV_NBR)(13u)
#define  CSP_GPIO_PORT_NBR_P                    (CSP_DEV_NBR)(14u)
#define  CSP_GPIO_PORT_NBR_O                    (CSP_DEV_NBR)(15u)

#define  CSP_GPIO_PIN_00                        DEF_BIT_00
#define  CSP_GPIO_PIN_01                        DEF_BIT_01
#define  CSP_GPIO_PIN_02                        DEF_BIT_02
#define  CSP_GPIO_PIN_03                        DEF_BIT_03
#define  CSP_GPIO_PIN_04                        DEF_BIT_04
#define  CSP_GPIO_PIN_05                        DEF_BIT_05
#define  CSP_GPIO_PIN_06                        DEF_BIT_06
#define  CSP_GPIO_PIN_07                        DEF_BIT_07
#define  CSP_GPIO_PIN_08                        DEF_BIT_08
#define  CSP_GPIO_PIN_09                        DEF_BIT_09
#define  CSP_GPIO_PIN_10                        DEF_BIT_10
#define  CSP_GPIO_PIN_11                        DEF_BIT_11
#define  CSP_GPIO_PIN_12                        DEF_BIT_12
#define  CSP_GPIO_PIN_13                        DEF_BIT_13
#define  CSP_GPIO_PIN_14                        DEF_BIT_14
#define  CSP_GPIO_PIN_15                        DEF_BIT_15
#define  CSP_GPIO_PIN_16                        DEF_BIT_16
#define  CSP_GPIO_PIN_17                        DEF_BIT_17
#define  CSP_GPIO_PIN_18                        DEF_BIT_18
#define  CSP_GPIO_PIN_19                        DEF_BIT_19
#define  CSP_GPIO_PIN_20                        DEF_BIT_20
#define  CSP_GPIO_PIN_21                        DEF_BIT_21
#define  CSP_GPIO_PIN_22                        DEF_BIT_22
#define  CSP_GPIO_PIN_23                        DEF_BIT_23
#define  CSP_GPIO_PIN_24                        DEF_BIT_24
#define  CSP_GPIO_PIN_25                        DEF_BIT_25
#define  CSP_GPIO_PIN_26                        DEF_BIT_26
#define  CSP_GPIO_PIN_27                        DEF_BIT_27
#define  CSP_GPIO_PIN_28                        DEF_BIT_28
#define  CSP_GPIO_PIN_29                        DEF_BIT_29
#define  CSP_GPIO_PIN_30                        DEF_BIT_30
#define  CSP_GPIO_PIN_31                        DEF_BIT_31


#define  CSP_GPIOA_REG_BASE_ADDR        0xFFFFF400U
#define  CSP_GPIOB_REG_BASE_ADDR        0xFFFFF600U
#define  CSP_GPIOC_REG_BASE_ADDR        0xFFFFF800U
#define  CSP_GPIOD_REG_BASE_ADDR        0xFFFFFA00U

#define  CSP_GPIOA_REG                  ((CSP_GPIO_REG_TAG_PTR)(CSP_GPIOA_REG_BASE_ADDR))
#define  CSP_GPIOB_REG                  ((CSP_GPIO_REG_TAG_PTR)(CSP_GPIOB_REG_BASE_ADDR))
#define  CSP_GPIOC_REG                  ((CSP_GPIO_REG_TAG_PTR)(CSP_GPIOC_REG_BASE_ADDR))
#define  CSP_GPIOD_REG                  ((CSP_GPIO_REG_TAG_PTR)(CSP_GPIOD_REG_BASE_ADDR))

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
  CPU_REG32 PIO_PER;       /**< \brief (Pio Offset: 0x0000) PIO Enable Register */
  CPU_REG32 PIO_PDR;       /**< \brief (Pio Offset: 0x0004) PIO Disable Register */
  CPU_REG32 PIO_PSR;       /**< \brief (Pio Offset: 0x0008) PIO Status Register */
  CPU_REG32 Reserved1[1];
  CPU_REG32 PIO_OER;       /**< \brief (Pio Offset: 0x0010) Output Enable Register */
  CPU_REG32 PIO_ODR;       /**< \brief (Pio Offset: 0x0014) Output Disable Register */
  CPU_REG32 PIO_OSR;       /**< \brief (Pio Offset: 0x0018) Output Status Register */
  CPU_REG32 Reserved2[1];
  CPU_REG32 PIO_IFER;      /**< \brief (Pio Offset: 0x0020) Glitch Input Filter Enable Register */
  CPU_REG32 PIO_IFDR;      /**< \brief (Pio Offset: 0x0024) Glitch Input Filter Disable Register */
  CPU_REG32 PIO_IFSR;      /**< \brief (Pio Offset: 0x0028) Glitch Input Filter Status Register */
  CPU_REG32 Reserved3[1];
  CPU_REG32 PIO_SODR;      /**< \brief (Pio Offset: 0x0030) Set Output Data Register */
  CPU_REG32 PIO_CODR;      /**< \brief (Pio Offset: 0x0034) Clear Output Data Register */
  CPU_REG32 PIO_ODSR;      /**< \brief (Pio Offset: 0x0038) Output Data Status Register */
  CPU_REG32 PIO_PDSR;      /**< \brief (Pio Offset: 0x003C) Pin Data Status Register */
  CPU_REG32 PIO_IER;       /**< \brief (Pio Offset: 0x0040) Interrupt Enable Register */
  CPU_REG32 PIO_IDR;       /**< \brief (Pio Offset: 0x0044) Interrupt Disable Register */
  CPU_REG32 PIO_IMR;       /**< \brief (Pio Offset: 0x0048) Interrupt Mask Register */
  CPU_REG32 PIO_ISR;       /**< \brief (Pio Offset: 0x004C) Interrupt Status Register */
  CPU_REG32 PIO_MDER;      /**< \brief (Pio Offset: 0x0050) Multi-driver Enable Register */
  CPU_REG32 PIO_MDDR;      /**< \brief (Pio Offset: 0x0054) Multi-driver Disable Register */
  CPU_REG32 PIO_MDSR;      /**< \brief (Pio Offset: 0x0058) Multi-driver Status Register */
  CPU_REG32 Reserved4[1];
  CPU_REG32 PIO_PUDR;      /**< \brief (Pio Offset: 0x0060) Pull-up Disable Register */
  CPU_REG32 PIO_PUER;      /**< \brief (Pio Offset: 0x0064) Pull-up Enable Register */
  CPU_REG32 PIO_PUSR;      /**< \brief (Pio Offset: 0x0068) Pad Pull-up Status Register */
  CPU_REG32 Reserved5[1];
  CPU_REG32 PIO_ABCDSR[2]; /**< \brief (Pio Offset: 0x0070) Peripheral Select Register */
  CPU_REG32 Reserved6[2];
  CPU_REG32 PIO_IFSCDR;    /**< \brief (Pio Offset: 0x0080) Input Filter Slow Clock Disable Register */
  CPU_REG32 PIO_IFSCER;    /**< \brief (Pio Offset: 0x0084) Input Filter Slow Clock Enable Register */
  CPU_REG32 PIO_IFSCSR;    /**< \brief (Pio Offset: 0x0088) Input Filter Slow Clock Status Register */
  CPU_REG32 PIO_SCDR;      /**< \brief (Pio Offset: 0x008C) Slow Clock Divider Debouncing Register */
  CPU_REG32 PIO_PPDDR;     /**< \brief (Pio Offset: 0x0090) Pad Pull-down Disable Register */
  CPU_REG32 PIO_PPDER;     /**< \brief (Pio Offset: 0x0094) Pad Pull-down Enable Register */
  CPU_REG32 PIO_PPDSR;     /**< \brief (Pio Offset: 0x0098) Pad Pull-down Status Register */
  CPU_REG32 Reserved7[1];
  CPU_REG32 PIO_OWER;      /**< \brief (Pio Offset: 0x00A0) Output Write Enable */
  CPU_REG32 PIO_OWDR;      /**< \brief (Pio Offset: 0x00A4) Output Write Disable */
  CPU_REG32 PIO_OWSR;      /**< \brief (Pio Offset: 0x00A8) Output Write Status Register */
  CPU_REG32 Reserved8[1];
  CPU_REG32 PIO_AIMER;     /**< \brief (Pio Offset: 0x00B0) Additional Interrupt Modes Enable Register */
  CPU_REG32 PIO_AIMDR;     /**< \brief (Pio Offset: 0x00B4) Additional Interrupt Modes Disables Register */
  CPU_REG32 PIO_AIMMR;     /**< \brief (Pio Offset: 0x00B8) Additional Interrupt Modes Mask Register */
  CPU_REG32 Reserved9[1];
  CPU_REG32 PIO_ESR;       /**< \brief (Pio Offset: 0x00C0) Edge Select Register */
  CPU_REG32 PIO_LSR;       /**< \brief (Pio Offset: 0x00C4) Level Select Register */
  CPU_REG32 PIO_ELSR;      /**< \brief (Pio Offset: 0x00C8) Edge/Level Status Register */
  CPU_REG32 Reserved10[1];
  CPU_REG32 PIO_FELLSR;    /**< \brief (Pio Offset: 0x00D0) Falling Edge/Low Level Select Register */
  CPU_REG32 PIO_REHLSR;    /**< \brief (Pio Offset: 0x00D4) Rising Edge/ High Level Select Register */
  CPU_REG32 PIO_FRLHSR;    /**< \brief (Pio Offset: 0x00D8) Fall/Rise - Low/High Status Register */
  CPU_REG32 Reserved11[1];
  CPU_REG32 PIO_LOCKSR;    /**< \brief (Pio Offset: 0x00E0) Lock Status */
  CPU_REG32 PIO_WPMR;      /**< \brief (Pio Offset: 0x00E4) Write Protect Mode Register */
  CPU_REG32 PIO_WPSR;      /**< \brief (Pio Offset: 0x00E8) Write Protect Status Register */
  CPU_REG32 Reserved12[5];
  CPU_REG32 PIO_SCHMITT;   /**< \brief (Pio Offset: 0x0100) Schmitt Trigger Register */
  CPU_REG32 Reserved13[3];
  CPU_REG32 PIO_DELAYR;    /**< \brief (Pio Offset: 0x0110) IO Delay Register */
  CPU_REG32 PIO_DRIVER1;   /**< \brief (Pio Offset: 0x0114) I/O Drive Register 1 */
  CPU_REG32 PIO_DRIVER2;   /**< \brief (Pio Offset: 0x0118) I/O Drive Register 2 */
}  CSP_GPIO_REG_TAG, *CSP_GPIO_REG_TAG_PTR;



/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of CSP_GPIO module include.                      */

