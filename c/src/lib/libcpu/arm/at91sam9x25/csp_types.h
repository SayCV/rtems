/*
*********************************************************************************************************
*        CSP
* Chip Support Package
* Filename      : csp_types.h
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

#ifndef  CSP_TYPES_MODULE_PRESENT
#define  CSP_TYPES_MODULE_PRESENT


/*
*********************************************************************************************************
*                                           INCLUDE FILES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   CSP_TYPES_MODULE
#define  CSP_TYPES_EXT
#else
#define  CSP_TYPES_EXT  extern
#endif



/*
*********************************************************************************************************
*                                    CONFIGURE STANDARD DATA TYPES
*
* Note(s) : (1) Configure standard data types according to CPU-/compiler-specifications.
*
*           (2) (a) (1) 'CPU_FNCT_VOID' data type defined to replace the commonly-used function pointer
*                       data type of a pointer to a function which returns void & has no arguments.
*
*                   (2) Example function pointer usage :
*
*                           CPU_FNCT_VOID  FnctName;
*
*                           FnctName();
*
*               (b) (1) 'CPU_FNCT_PTR'  data type defined to replace the commonly-used function pointer
*                       data type of a pointer to a function which returns void & has a single void
*                       pointer argument.
*
*                   (2) Example function pointer usage :
*
*                           CPU_FNCT_PTR   FnctName;
*                           void          *p_obj
*
*                           FnctName(p_obj);
*********************************************************************************************************
*/

typedef            void        CPU_VOID;
typedef            char        CPU_CHAR;                        /*  8-bit character                                     */
typedef  unsigned  char        CPU_BOOLEAN;                     /*  8-bit boolean or logical                            */
typedef  unsigned  char        CPU_INT08U;                      /*  8-bit unsigned integer                              */
typedef    signed  char        CPU_INT08S;                      /*  8-bit   signed integer                              */
typedef  unsigned  short       CPU_INT16U;                      /* 16-bit unsigned integer                              */
typedef    signed  short       CPU_INT16S;                      /* 16-bit   signed integer                              */
typedef  unsigned  int         CPU_INT32U;                      /* 32-bit unsigned integer                              */
typedef    signed  int         CPU_INT32S;                      /* 32-bit   signed integer                              */
typedef  unsigned  long  long  CPU_INT64U;                      /* 64-bit unsigned integer                              */
typedef    signed  long  long  CPU_INT64S;                      /* 64-bit   signed integer                              */

typedef            float       CPU_FP32;                        /* 32-bit floating point                                */
typedef            double      CPU_FP64;                        /* 64-bit floating point                                */


typedef  volatile  CPU_INT08U  CPU_REG08;                       /*  8-bit register                                      */
typedef  volatile  CPU_INT16U  CPU_REG16;                       /* 16-bit register                                      */
typedef  volatile  CPU_INT32U  CPU_REG32;                       /* 32-bit register                                      */
typedef  volatile  CPU_INT64U  CPU_REG64;                       /* 64-bit register                                      */


typedef            void      (*CPU_FNCT_VOID)(void);            /* See Note #2a.                                        */
typedef            void      (*CPU_FNCT_PTR )(void *p_obj);     /* See Note #2b.                                        */


/*
*********************************************************************************************************
*                                        DEVICE NUMBER IDENTIFIERS
*
* Note(s) : (1) The 'CSP_DEV_NBR' data type is used to reference port numbers, clk identifiers and peripherals 
*               IDs.
*********************************************************************************************************
*/

typedef  CPU_INT16U  CSP_DEV_NBR;                               /* Device number.                                       */


/*
*********************************************************************************************************
*                                        OPTIONS  AND OPTIONS FLAGS
*********************************************************************************************************
*/

typedef  CPU_INT16U  CSP_OPT_FLAGS;                             /* Option flags.                                        */
typedef  CPU_INT16U  CSP_OPT;                                   /* Options.                                             */


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/
	
																	/* ------------------- BIT DEFINES -------------------- */
#define  DEF_BIT_NONE                                   0x00u
	
#define  DEF_BIT_00                                     0x01u
#define  DEF_BIT_01                                     0x02u
#define  DEF_BIT_02                                     0x04u
#define  DEF_BIT_03                                     0x08u
#define  DEF_BIT_04                                     0x10u
#define  DEF_BIT_05                                     0x20u
#define  DEF_BIT_06                                     0x40u
#define  DEF_BIT_07                                     0x80u
	
#define  DEF_BIT_08                                   0x0100u
#define  DEF_BIT_09                                   0x0200u
#define  DEF_BIT_10                                   0x0400u
#define  DEF_BIT_11                                   0x0800u
#define  DEF_BIT_12                                   0x1000u
#define  DEF_BIT_13                                   0x2000u
#define  DEF_BIT_14                                   0x4000u
#define  DEF_BIT_15                                   0x8000u
	
#define  DEF_BIT_16                               0x00010000u
#define  DEF_BIT_17                               0x00020000u
#define  DEF_BIT_18                               0x00040000u
#define  DEF_BIT_19                               0x00080000u
#define  DEF_BIT_20                               0x00100000u
#define  DEF_BIT_21                               0x00200000u
#define  DEF_BIT_22                               0x00400000u
#define  DEF_BIT_23                               0x00800000u
	
#define  DEF_BIT_24                               0x01000000u
#define  DEF_BIT_25                               0x02000000u
#define  DEF_BIT_26                               0x04000000u
#define  DEF_BIT_27                               0x08000000u
#define  DEF_BIT_28                               0x10000000u
#define  DEF_BIT_29                               0x20000000u
#define  DEF_BIT_30                               0x40000000u
#define  DEF_BIT_31                               0x80000000u


/*
*********************************************************************************************************
*                                              MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of CSP_TYPES module include.                     */
