/*
*********************************************************************************************************
*        CSP
* Chip Support Package
* Filename      : csp_grp.h
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

#ifndef  CSP_GRP_MODULE_PRESENT
#define  CSP_GRP_MODULE_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/


#include <csp_types.h>

/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/

#ifdef   CSP_GRP_MODULE
#define  CSP_GRP_EXT
#else
#define  CSP_GRP_EXT  extern
#endif


/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/




/*
*********************************************************************************************************
*                                           FAMILY DEFINITION
*********************************************************************************************************
*/

#define  CSP_GRP_SAM9X25
#define  CSP_GRP_NAME                           "SAM9X25"



/*
*********************************************************************************************************
*                                  SAM9X25 INTERRUPT CONTROLLER DEVICE NUMBERS
*
* Note(s): (1) The SAM9X25 uses the Nested Vectored Interrupt Controller (NVIC)that is an integral part of 
*              the ARM9 architecture.
* 
*              (a) Interrupts 0  to 15  are internals and common for all the ARM9 processors.
*              (b) Interurpts 16 to 256 are externals and varies among CPU's implementation.
* 
*
*          (2) Some interrupts lines are ORed together to a single channel of the vectored interrupt controller. 
*              To reduce the complexity of the interrupt handler for ORed interrupt lines a shared interupt handler
*              is implemented to allow the application to install a ISR for every interrupt line form the ORed channnel.
*              In the case of the of the SAM9X25 a virtual interrupt controller is used for the USB shared interrupt handler.
*
*                         
*                                +-------------+                                       +-------------+
*                                |             |                        src16 -------->|             |
*                 src16 -------->|  Interrupt  |                        src17 -------->|  Interrupt  |
*                 src17 -------->|  Controller |                        src18 -------->|  Controller |
*                 src18 -------->|             |                                   .   |             |
*                 src19 -------->|    NVIC     |                                   .   |    NVIC     |
*                            .   |             |  ====                             .   |             |  
*                            .   |             |  ====                  srcn --------->|             |  
*                            .   |             |                                       |             |
*                 srcn --------->|             |                                       |             |
*                                |             |                                       +-------------+
*                   +-----+  --->|             |                    +------------+
*      usb_src0 --->|     |  |   +-------------|       usb_src0 --->|            |
*      usb_src1 --->|     |  |                         usb_src1 --->|    USB     |
*      usb_src2 --->|     |  |                         usb_src2 --->| Software   |
*          .        |  OR |--|                              .       | Interrupt  |
*          .        |     |                                 .       | controller |
*          .        |     |                                 .       |            |
*      usb_srcn --->|     |                            usb_srcn --->|            |
*                   +-----+                                         +------------+
*   
*           
*                For example two independent ISR can be installed for the USB Host and the OTG interrupt                
*
*                CSP_IntVectReg((CSP_DEV_NBR   )CSP_INT_CTRL_NBR_USB,
*                               (CSP_DEV_NBR   )CSP_INT_USB_SRC_NBR_OTG,
*                               (CPU_FNCT_PTR  )OTG_Handler,
*                               (CPU_VOID     *)0);
*
*                CSP_IntVectReg((CSP_DEV_NBR   )CSP_INT_CTRL_NBR_USB,
*                               (CSP_DEV_NBR   )CSP_INT_USB_SRC_NBR_HOST,
*                               (CPU_FNCT_PTR  )HOST_Handler,
*                               (CPU_VOID     *)0);
*
*                (a) The 'USB shared interrupt handler" is available for the following processors:
*                        LPC1754
*                        LPC1756
*                        LPC1758
*                        LPC1765
*                        LPC1766
*                        LPC1768
*********************************************************************************************************
*/

#define  CSP_INT_CTRL_NBR_MAIN                  (CSP_DEV_NBR)(0u)   /* NVIC    External Interrupt Controller.           */
#define  CSP_INT_CTRL_NBR_SYS                   (CSP_DEV_NBR)(1u)   /* Virtual USB      Interrupt Controller.           */
#define  CSP_INT_CTRL_NBR_USB                   (CSP_DEV_NBR)(2u)   /* Virtual USB      Interrupt Controller.           */


/*
*********************************************************************************************************
*                                          INTERRUPT SOURCES
*
* Note(s) : (1) Interrupt controller sources #define's use the following standard:
*
*               #define  CSP_INT_SRC_NBR_<PER>_<EVENT>_<PER_NBR>
*
*               where 
*
*                   <PER>      Peripheral name (UART, ETHER, DMA, USB, etc)
*                   <EVENT>    Interrupt event (RX, TX, MATCH, ALERT, TO, etc)
*                              Empty for multiple events interrupts.
*                   <PER_NBR>  Peripheral number. (00, 01, 02, etc)
*
*              #define  CSP_INT_SRC_NBR_UART_RX_00    UART 00 receive interrupt.
*              #define  CSP_INT_SRC_NBR_UART_TX_01    UART 01 receive interrupt. 
*
*            (2) 'CSP_INT_SRC_NBR_MAX' defines maximum number of interrupts in the interrupt controller.
*********************************************************************************************************
*/
#define	CSP_INT_SRC_NBR_FIQ						(CSP_DEV_NBR)( 0u) 	/**<	\brief	Advanced	Interrupt	Controller	(FIQ)	*/              
#define	CSP_INT_SRC_NBR_SYS						(CSP_DEV_NBR)( 1u) 	/**<	\brief	System	Controller	Interrupt	(SYS)	*/                
#define	CSP_INT_SRC_NBR_PIOA					(CSP_DEV_NBR)( 2u) 	/**<	\brief	Parallel	I/O	Controller	A	and	B	(PIOA)	*/          
#define	CSP_INT_SRC_NBR_PIOB					(CSP_DEV_NBR)( 2u) 	/**<	\brief	Parallel	I/O	Controller	A	and	B	(PIOB)	*/          
#define	CSP_INT_SRC_NBR_PIOC					(CSP_DEV_NBR)( 3u) 	/**<	\brief	Parallel	I/O	Controller	C	and	D	(PIOC)	*/          
#define	CSP_INT_SRC_NBR_PIOD					(CSP_DEV_NBR)( 3u) 	/**<	\brief	Parallel	I/O	Controller	C	and	D	(PIOD)	*/          
#define	CSP_INT_SRC_NBR_SMD						(CSP_DEV_NBR)( 4u) 	/**<	\brief	SMD	Soft	Modem	(SMD)	*/                              
#define	CSP_INT_SRC_NBR_USART_00			(CSP_DEV_NBR)( 5u) 	/**<	\brief	USART	0	(USART0)	*/                                  
#define	CSP_INT_SRC_NBR_USART_01			(CSP_DEV_NBR)( 6u) 	/**<	\brief	USART	1	(USART1)	*/                                  
#define	CSP_INT_SRC_NBR_USART_02			(CSP_DEV_NBR)( 7u)	/**<	\brief	USART	2	(USART2)	*/                                  
#define	CSP_INT_SRC_NBR_USART_03			(CSP_DEV_NBR)( 8u)	/**<	\brief	USART	3	(USART3)	*/                                  
#define	CSP_INT_SRC_NBR_TWI_00				(CSP_DEV_NBR)( 9u)	/**<	\brief	Two-Wire	Interface	0	(TWI0)	*/                      
#define	CSP_INT_SRC_NBR_TWI_01				(CSP_DEV_NBR)(10u)	/**<	\brief	Two-Wire	Interface	1	(TWI1)	*/                      
#define	CSP_INT_SRC_NBR_TWI_02				(CSP_DEV_NBR)(11u)	/**<	\brief	Two-Wire	Interface	2	(TWI2)	*/                      
#define	CSP_INT_SRC_NBR_HSMCI_00			(CSP_DEV_NBR)(12u)	/**<	\brief	High	Speed	Multimedia	Card	Interface	0	(HSMCI0)	*/
#define	CSP_INT_SRC_NBR_SPI_00				(CSP_DEV_NBR)(13u)	/**<	\brief	Serial	Peripheral	Interface	0	(SPI0)	*/            
#define	CSP_INT_SRC_NBR_SPI_01				(CSP_DEV_NBR)(14u)	/**<	\brief	Serial	Peripheral	Interface	1	(SPI1)	*/            
#define	CSP_INT_SRC_NBR_UART_00				(CSP_DEV_NBR)(15u)	/**<	\brief	UART	0	(UART0)	*/                                    
#define	CSP_INT_SRC_NBR_UART_01				(CSP_DEV_NBR)(16u)	/**<	\brief	UART	1	(UART1)	*/                                    
#define	CSP_INT_SRC_NBR_TC_00					(CSP_DEV_NBR)(17u)	/**<	\brief	Timer	Counter	0	(TC0)	*/                              
#define	CSP_INT_SRC_NBR_TC_01					(CSP_DEV_NBR)(18u)	/**<	\brief	1	(TC1)	*/                                            
#define	CSP_INT_SRC_NBR_PWM						(CSP_DEV_NBR)(19u)	/**<	\brief	Pulse	Width	Modulation	Controller	(PWM)	*/          
#define	CSP_INT_SRC_NBR_ADC						(CSP_DEV_NBR)(20u)	/**<	\brief	ADC	Controller	(ADC)	*/                              
#define	CSP_INT_SRC_NBR_DMAC_00				(CSP_DEV_NBR)(21u)	/**<	\brief	DMA	Controller	0	(DMAC0)	*/                          
#define	CSP_INT_SRC_NBR_DMAC_01				(CSP_DEV_NBR)(22u)	/**<	\brief	DMA	Controller	1	(DMAC1)	*/				                  
#define	CSP_INT_SRC_NBR_UHPHS					(CSP_DEV_NBR)(23u)	/**<	\brief	USB	Host	High	Speed	(UHPHS)	*/                      
#define	CSP_INT_SRC_NBR_UDPHS					(CSP_DEV_NBR)(24u)	/**<	\brief	USB	Device	High	Speed	(UDPHS)	*/                    
#define	CSP_INT_SRC_NBR_EMAC_00				(CSP_DEV_NBR)(25u)	/**<	\brief	Ethernet	MAC	0	(EMAC0)	*/                            
#define	CSP_INT_SRC_NBR_HSMCI_01			(CSP_DEV_NBR)(26u)	/**<	\brief	High	Speed	Multimedia	Card	Interface	1	(HSMCI1)	*/
#define	CSP_INT_SRC_NBR_EMAC_01				(CSP_DEV_NBR)(27u)	/**<	\brief	Ethernet	MAC	1	(EMAC1)	*/                            
#define	CSP_INT_SRC_NBR_SSC						(CSP_DEV_NBR)(28u)	/**<	\brief	Synchronous	Serial	Controller	(SSC)	*/              
#define	CSP_INT_SRC_NBR_CAN_00				(CSP_DEV_NBR)(29u)	/**<	\brief	CAN	controller	0	(CAN0)	*/                          
#define	CSP_INT_SRC_NBR_CAN_01				(CSP_DEV_NBR)(30u)	/**<	\brief	CAN	controller	1	(CAN1)	*/                          
#define	CSP_INT_SRC_NBR_IRQ						(CSP_DEV_NBR)(31u)	/**<	\brief	Advanced	Interrupt	Controller	(IRQ)	*/              

#define  CSP_INT_SRC_NBR_MAX                    (CSP_DEV_NBR)(32u)    /* Total number of external sources                 */


/*
*********************************************************************************************************
*                                    SAM9X25 SOFT USB INTERRUPT CONTROLLER SOURCES
*********************************************************************************************************
*/

#define  CSP_INT_USB_SRC_NBR_DEV                (CSP_DEV_NBR)0u
#define  CSP_INT_USB_SRC_NBR_HOST               (CSP_DEV_NBR)1u
#define  CSP_INT_USB_SRC_NBR_ATX                (CSP_DEV_NBR)2u
#define  CSP_INT_USB_SRC_NBR_OTG                (CSP_DEV_NBR)3u
#define  CSP_INT_USB_SRC_NBR_I2C                (CSP_DEV_NBR)4u

#define  CSP_INT_USB_SRC_MAX_NBR                (CSP_DEV_NBR)5u

#define  CSP_PMC_SYS_CLK_NBR_PCLKSEL_SLOW        (CSP_DEV_NBR)0u    /* Slow  clock                                        */
#define  CSP_PMC_SYS_CLK_NBR_PCLKSEL_MAIN        (CSP_DEV_NBR)1u    /* Main  clock                                        */
#define  CSP_PMC_SYS_CLK_NBR_PCLKSEL_PLLA        (CSP_DEV_NBR)2u    /* PLL   clock                                        */ 
#define  CSP_PMC_SYS_CLK_NBR_PCLKSEL_PLLB        (CSP_DEV_NBR)3u    /* PLL   clock                                        */ 

#define  CSP_PMC_SYS_CLK_PCLKSEL_NBR_MAX         (CSP_DEV_NBR)(4u)

#define  CSP_PMC_SYS_CLK_NBR_PCK                 (CSP_DEV_NBR)0u
#define  CSP_PMC_SYS_CLK_NBR_DDRCK               (CSP_DEV_NBR)2u
#define  CSP_PMC_SYS_CLK_NBR_SMDCK               (CSP_DEV_NBR)4u
#define  CSP_PMC_SYS_CLK_NBR_UHP                 (CSP_DEV_NBR)6u
#define  CSP_PMC_SYS_CLK_NBR_UDP                 (CSP_DEV_NBR)7u
#define  CSP_PMC_SYS_CLK_NBR_PCK0                (CSP_DEV_NBR)8u
#define  CSP_PMC_SYS_CLK_NBR_PCK1                (CSP_DEV_NBR)9u
#define  CSP_PMC_SYS_CLK_NBR_HCK0                (CSP_DEV_NBR)16u
#define  CSP_PMC_SYS_CLK_NBR_HCK1                (CSP_DEV_NBR)17u

#define  CSP_PMC_SYS_CLK_NBR_MAX                 (CSP_DEV_NBR)(32u)

/* ************************************************************************** */
/*   PERIPHERAL ID DEFINITIONS FOR AT91SAM9X25 */
/* ************************************************************************** */
/** \addtogroup AT91SAM9X25_id Peripheral Ids Definitions */
/*@{*/
#define	CSP_PER_ID_NBR_FIQ						(CSP_DEV_NBR)( 0u) 	/**<	\brief	Advanced	Interrupt	Controller	(FIQ)	*/              
#define	CSP_PER_ID_NBR_SYS						(CSP_DEV_NBR)( 1u) 	/**<	\brief	System	Controller	Interrupt	(SYS)	*/                
#define	CSP_PER_ID_NBR_PIOA						(CSP_DEV_NBR)( 2u) 	/**<	\brief	Parallel	I/O	Controller	A	and	B	(PIOA)	*/          
#define	CSP_PER_ID_NBR_PIOB						(CSP_DEV_NBR)( 2u) 	/**<	\brief	Parallel	I/O	Controller	A	and	B	(PIOB)	*/          
#define	CSP_PER_ID_NBR_PIOC						(CSP_DEV_NBR)( 3u) 	/**<	\brief	Parallel	I/O	Controller	C	and	D	(PIOC)	*/          
#define	CSP_PER_ID_NBR_PIOD						(CSP_DEV_NBR)( 3u) 	/**<	\brief	Parallel	I/O	Controller	C	and	D	(PIOD)	*/          
#define	CSP_PER_ID_NBR_SMD						(CSP_DEV_NBR)( 4u) 	/**<	\brief	SMD	Soft	Modem	(SMD)	*/                              
#define	CSP_PER_ID_NBR_USART_00				(CSP_DEV_NBR)( 5u) 	/**<	\brief	USART	0	(USART0)	*/                                  
#define	CSP_PER_ID_NBR_USART_01				(CSP_DEV_NBR)( 6u) 	/**<	\brief	USART	1	(USART1)	*/                                  
#define	CSP_PER_ID_NBR_USART_02				(CSP_DEV_NBR)( 7u)	/**<	\brief	USART	2	(USART2)	*/                                  
#define	CSP_PER_ID_NBR_USART_03				(CSP_DEV_NBR)( 8u)	/**<	\brief	USART	3	(USART3)	*/                                  
#define	CSP_PER_ID_NBR_TWI_00					(CSP_DEV_NBR)( 9u)	/**<	\brief	Two-Wire	Interface	0	(TWI0)	*/                      
#define	CSP_PER_ID_NBR_TWI_01					(CSP_DEV_NBR)(10u)	/**<	\brief	Two-Wire	Interface	1	(TWI1)	*/                      
#define	CSP_PER_ID_NBR_TWI_02					(CSP_DEV_NBR)(11u)	/**<	\brief	Two-Wire	Interface	2	(TWI2)	*/                      
#define	CSP_PER_ID_NBR_HSMCI_00				(CSP_DEV_NBR)(12u)	/**<	\brief	High	Speed	Multimedia	Card	Interface	0	(HSMCI0)	*/
#define	CSP_PER_ID_NBR_SPI_00					(CSP_DEV_NBR)(13u)	/**<	\brief	Serial	Peripheral	Interface	0	(SPI0)	*/            
#define	CSP_PER_ID_NBR_SPI_01					(CSP_DEV_NBR)(14u)	/**<	\brief	Serial	Peripheral	Interface	1	(SPI1)	*/            
#define	CSP_PER_ID_NBR_UART_00				(CSP_DEV_NBR)(15u)	/**<	\brief	UART	0	(UART0)	*/                                    
#define	CSP_PER_ID_NBR_UART_01				(CSP_DEV_NBR)(16u)	/**<	\brief	UART	1	(UART1)	*/                                    
#define	CSP_PER_ID_NBR_TC_00					(CSP_DEV_NBR)(17u)	/**<	\brief	Timer	Counter	0	(TC0)	*/                              
#define	CSP_PER_ID_NBR_TC_01					(CSP_DEV_NBR)(18u)	/**<	\brief	1	(TC1)	*/                                            
#define	CSP_PER_ID_NBR_PWM						(CSP_DEV_NBR)(19u)	/**<	\brief	Pulse	Width	Modulation	Controller	(PWM)	*/          
#define	CSP_PER_ID_NBR_ADC						(CSP_DEV_NBR)(20u)	/**<	\brief	ADC	Controller	(ADC)	*/                              
#define	CSP_PER_ID_NBR_DMAC_00				(CSP_DEV_NBR)(21u)	/**<	\brief	DMA	Controller	0	(DMAC0)	*/                          
#define	CSP_PER_ID_NBR_DMAC_01				(CSP_DEV_NBR)(22u)	/**<	\brief	DMA	Controller	1	(DMAC1)	*/				                  
#define	CSP_PER_ID_NBR_UHPHS					(CSP_DEV_NBR)(23u)	/**<	\brief	USB	Host	High	Speed	(UHPHS)	*/                      
#define	CSP_PER_ID_NBR_UDPHS					(CSP_DEV_NBR)(24u)	/**<	\brief	USB	Device	High	Speed	(UDPHS)	*/                    
#define	CSP_PER_ID_NBR_EMAC_00				(CSP_DEV_NBR)(25u)	/**<	\brief	Ethernet	MAC	0	(EMAC0)	*/                            
#define	CSP_PER_ID_NBR_HSMCI_01				(CSP_DEV_NBR)(26u)	/**<	\brief	High	Speed	Multimedia	Card	Interface	1	(HSMCI1)	*/
#define	CSP_PER_ID_NBR_EMAC_01				(CSP_DEV_NBR)(27u)	/**<	\brief	Ethernet	MAC	1	(EMAC1)	*/                            
#define	CSP_PER_ID_NBR_SSC						(CSP_DEV_NBR)(28u)	/**<	\brief	Synchronous	Serial	Controller	(SSC)	*/              
#define	CSP_PER_ID_NBR_CAN_00					(CSP_DEV_NBR)(29u)	/**<	\brief	CAN	controller	0	(CAN0)	*/                          
#define	CSP_PER_ID_NBR_CAN_01					(CSP_DEV_NBR)(30u)	/**<	\brief	CAN	controller	1	(CAN1)	*/                          
#define	CSP_PER_ID_NBR_IRQ						(CSP_DEV_NBR)(31u)	/**<	\brief	Advanced	Interrupt	Controller	(IRQ)	*/              

/*
*********************************************************************************************************
*                                     PERIPHERALS CLOCKS DEFINES
*
* Note(s) : (1) The peripheral's clock #define's use the following standard.
*        
*                   #define  CSP_PMC_PER_CLK_NBR_<PER>_<PER_NBR>
*
*                   where,
*
*                   <PER>      Peripheral clock name.
*                   <PER_NBR>  Peripheral clock number identifier.
*********************************************************************************************************
*/
#define	CSP_PMC_PER_CLK_NBR_FIQ						(CSP_DEV_NBR)( 0u) 	/**<	\brief	Advanced	Interrupt	Controller	(FIQ)	*/              
#define	CSP_PMC_PER_CLK_NBR_SYS						(CSP_DEV_NBR)( 1u) 	/**<	\brief	System	Controller	Interrupt	(SYS)	*/                
#define	CSP_PMC_PER_CLK_NBR_PIOA					(CSP_DEV_NBR)( 2u) 	/**<	\brief	Parallel	I/O	Controller	A	and	B	(PIOA)	*/          
#define	CSP_PMC_PER_CLK_NBR_PIOB					(CSP_DEV_NBR)( 2u) 	/**<	\brief	Parallel	I/O	Controller	A	and	B	(PIOB)	*/          
#define	CSP_PMC_PER_CLK_NBR_PIOC					(CSP_DEV_NBR)( 3u) 	/**<	\brief	Parallel	I/O	Controller	C	and	D	(PIOC)	*/          
#define	CSP_PMC_PER_CLK_NBR_PIOD					(CSP_DEV_NBR)( 3u) 	/**<	\brief	Parallel	I/O	Controller	C	and	D	(PIOD)	*/          
#define	CSP_PMC_PER_CLK_NBR_SMD						(CSP_DEV_NBR)( 4u) 	/**<	\brief	SMD	Soft	Modem	(SMD)	*/                              
#define	CSP_PMC_PER_CLK_NBR_USART_00			(CSP_DEV_NBR)( 5u) 	/**<	\brief	USART	0	(USART0)	*/                                  
#define	CSP_PMC_PER_CLK_NBR_USART_01			(CSP_DEV_NBR)( 6u) 	/**<	\brief	USART	1	(USART1)	*/                                  
#define	CSP_PMC_PER_CLK_NBR_USART_02			(CSP_DEV_NBR)( 7u)	/**<	\brief	USART	2	(USART2)	*/                                  
#define	CSP_PMC_PER_CLK_NBR_USART_03			(CSP_DEV_NBR)( 8u)	/**<	\brief	USART	3	(USART3)	*/                                  
#define	CSP_PMC_PER_CLK_NBR_TWI_00				(CSP_DEV_NBR)( 9u)	/**<	\brief	Two-Wire	Interface	0	(TWI0)	*/                      
#define	CSP_PMC_PER_CLK_NBR_TWI_01				(CSP_DEV_NBR)(10u)	/**<	\brief	Two-Wire	Interface	1	(TWI1)	*/                      
#define	CSP_PMC_PER_CLK_NBR_TWI_02				(CSP_DEV_NBR)(11u)	/**<	\brief	Two-Wire	Interface	2	(TWI2)	*/                      
#define	CSP_PMC_PER_CLK_NBR_HSMCI_00			(CSP_DEV_NBR)(12u)	/**<	\brief	High	Speed	Multimedia	Card	Interface	0	(HSMCI0)	*/
#define	CSP_PMC_PER_CLK_NBR_SPI_00				(CSP_DEV_NBR)(13u)	/**<	\brief	Serial	Peripheral	Interface	0	(SPI0)	*/            
#define	CSP_PMC_PER_CLK_NBR_SPI_01				(CSP_DEV_NBR)(14u)	/**<	\brief	Serial	Peripheral	Interface	1	(SPI1)	*/            
#define	CSP_PMC_PER_CLK_NBR_UART_00				(CSP_DEV_NBR)(15u)	/**<	\brief	UART	0	(UART0)	*/                                    
#define	CSP_PMC_PER_CLK_NBR_UART_01				(CSP_DEV_NBR)(16u)	/**<	\brief	UART	1	(UART1)	*/                                    
#define	CSP_PMC_PER_CLK_NBR_TC_00					(CSP_DEV_NBR)(17u)	/**<	\brief	Timer	Counter	0	(TC0)	*/                              
#define	CSP_PMC_PER_CLK_NBR_TC_01					(CSP_DEV_NBR)(18u)	/**<	\brief	1	(TC1)	*/                                            
#define	CSP_PMC_PER_CLK_NBR_PWM						(CSP_DEV_NBR)(19u)	/**<	\brief	Pulse	Width	Modulation	Controller	(PWM)	*/          
#define	CSP_PMC_PER_CLK_NBR_ADC						(CSP_DEV_NBR)(20u)	/**<	\brief	ADC	Controller	(ADC)	*/                              
#define	CSP_PMC_PER_CLK_NBR_DMAC_00				(CSP_DEV_NBR)(21u)	/**<	\brief	DMA	Controller	0	(DMAC0)	*/                          
#define	CSP_PMC_PER_CLK_NBR_DMAC_01				(CSP_DEV_NBR)(22u)	/**<	\brief	DMA	Controller	1	(DMAC1)	*/				                  
#define	CSP_PMC_PER_CLK_NBR_UHPHS					(CSP_DEV_NBR)(23u)	/**<	\brief	USB	Host	High	Speed	(UHPHS)	*/                      
#define	CSP_PMC_PER_CLK_NBR_UDPHS					(CSP_DEV_NBR)(24u)	/**<	\brief	USB	Device	High	Speed	(UDPHS)	*/                    
#define	CSP_PMC_PER_CLK_NBR_EMAC_00				(CSP_DEV_NBR)(25u)	/**<	\brief	Ethernet	MAC	0	(EMAC0)	*/                            
#define	CSP_PMC_PER_CLK_NBR_HSMCI_01			(CSP_DEV_NBR)(26u)	/**<	\brief	High	Speed	Multimedia	Card	Interface	1	(HSMCI1)	*/
#define	CSP_PMC_PER_CLK_NBR_EMAC_01				(CSP_DEV_NBR)(27u)	/**<	\brief	Ethernet	MAC	1	(EMAC1)	*/                            
#define	CSP_PMC_PER_CLK_NBR_SSC						(CSP_DEV_NBR)(28u)	/**<	\brief	Synchronous	Serial	Controller	(SSC)	*/              
#define	CSP_PMC_PER_CLK_NBR_CAN_00				(CSP_DEV_NBR)(29u)	/**<	\brief	CAN	controller	0	(CAN0)	*/                          
#define	CSP_PMC_PER_CLK_NBR_CAN_01				(CSP_DEV_NBR)(30u)	/**<	\brief	CAN	controller	1	(CAN1)	*/                          
#define	CSP_PMC_PER_CLK_NBR_IRQ						(CSP_DEV_NBR)(31u)	/**<	\brief	Advanced	Interrupt	Controller	(IRQ)	*/              

#if 0
#define	CSP_PER_ID_NBR_FIQ			CSP_PER_ID_NBR_FIQ	    
#define	CSP_PER_ID_NBR_SYS			CSP_PER_ID_NBR_SYS	    
#define	CSP_PER_ID_NBR_PIOA			CSP_PER_ID_NBR_PIOA	    
#define	CSP_PER_ID_NBR_PIOB			CSP_PER_ID_NBR_PIOB	    
#define	CSP_PER_ID_NBR_PIOC			CSP_PER_ID_NBR_PIOC	    
#define	CSP_PER_ID_NBR_PIOD			CSP_PER_ID_NBR_PIOD	    
#define	CSP_PER_ID_NBR_SMD			CSP_PER_ID_NBR_SMD	    
#define	CSP_PER_ID_NBR_USART_00	                CSP_PER_ID_NBR_USART_00 
#define	CSP_PER_ID_NBR_USART_01	                CSP_PER_ID_NBR_USART_01 
#define	CSP_PER_ID_NBR_USART_02	                CSP_PER_ID_NBR_USART_02 
#define	CSP_PER_ID_NBR_USART_03	                CSP_PER_ID_NBR_USART_03 
#define	CSP_PER_ID_NBR_TWI_00		        CSP_PER_ID_NBR_TWI_00		
#define	CSP_PER_ID_NBR_TWI_01		        CSP_PER_ID_NBR_TWI_01		
#define	CSP_PER_ID_NBR_TWI_02		        CSP_PER_ID_NBR_TWI_02		
#define	CSP_PER_ID_NBR_HSMCI_00	                CSP_PER_ID_NBR_HSMCI_00 
#define	CSP_PER_ID_NBR_SPI_00		        CSP_PER_ID_NBR_SPI_00		
#define	CSP_PER_ID_NBR_SPI_01		        CSP_PER_ID_NBR_SPI_01		
#define	CSP_PER_ID_NBR_UART_00	                CSP_PER_ID_NBR_UART_00	
#define	CSP_PER_ID_NBR_UART_01	                CSP_PER_ID_NBR_UART_01	
#define	CSP_PER_ID_NBR_TC_00		        CSP_PER_ID_NBR_TC_00		
#define	CSP_PER_ID_NBR_TC_01		        CSP_PER_ID_NBR_TC_01		
#define	CSP_PER_ID_NBR_PWM			CSP_PER_ID_NBR_PWM		  
#define	CSP_PER_ID_NBR_ADC			CSP_PER_ID_NBR_ADC		  
#define	CSP_PER_ID_NBR_DMAC_00	                CSP_PER_ID_NBR_DMAC_00	
#define	CSP_PER_ID_NBR_DMAC_01	                CSP_PER_ID_NBR_DMAC_01	
#define	CSP_PER_ID_NBR_UHPHS		        CSP_PER_ID_NBR_UHPHS		
#define	CSP_PER_ID_NBR_UDPHS		        CSP_PER_ID_NBR_UDPHS    
#define	CSP_PER_ID_NBR_EMAC_00	                CSP_PER_ID_NBR_EMAC_00	
#define	CSP_PER_ID_NBR_HSMCI_01	                CSP_PER_ID_NBR_HSMCI_01 
#define	CSP_PER_ID_NBR_EMAC_01	                CSP_PER_ID_NBR_EMAC_01  
#define	CSP_PER_ID_NBR_SSC			CSP_PER_ID_NBR_SSC      
#define	CSP_PER_ID_NBR_CAN_00		        CSP_PER_ID_NBR_CAN_00   
#define	CSP_PER_ID_NBR_CAN_01		        CSP_PER_ID_NBR_CAN_01	  
#define	CSP_PER_ID_NBR_IRQ			CSP_PER_ID_NBR_IRQ      

#endif
#define  CSP_PMC_PER_CLK_NBR_MAX               (CSP_DEV_NBR)(32u)


/*
*********************************************************************************************************
*                                          DMA TRANSFER TYPES
*********************************************************************************************************
*/

#define  CSP_DMA_XFER_TYPE_MEM_TO_MEM         (CSP_OPT    )(0u)      /* Memory     to memory     transfer                    */
#define  CSP_DMA_XFER_TYPE_PER_TO_MEM         (CSP_OPT    )(1u)      /* Peripheral to memory     transfer.                   */
#define  CSP_DMA_XFER_TYPE_MEM_TO_PER         (CSP_OPT    )(2u)      /* Memory     to peripheral transfer.                   */
#define  CSP_DMA_XFER_TYPE_PER_TO_PER         (CSP_OPT    )(3u)      /* Peripheral to peripheral transfer.                   */


/*
*********************************************************************************************************
*                                             DMA PRIORITIES
*********************************************************************************************************
*/

#define  CSP_DMA_CH_PRIO_LOWEST               (CSP_OPT    )(0u)
#define  CSP_DMA_CH_PRIO_HIGHEST              (CSP_OPT    )(7u)
#define  CSP_DMA_CH_PRIO_ANY_LOW              (CSP_OPT    )(8u)
#define  CSP_DMA_CH_PRIO_ANY_HIGH             (CSP_OPT    )(9u)


/*
*********************************************************************************************************
*                                              DMA OPTIONS FLAGS
*********************************************************************************************************
*/

#define  CSP_DMA_OPT_FLAG_XFER_SRC_INC          DEF_BIT_00
#define  CSP_DMA_OPT_FLAG_XFER_DEST_INC         DEF_BIT_01


/*
*********************************************************************************************************
*                                      DMA PERIPHERAL REQUEST SIGNALS
*********************************************************************************************************
*/

#define  CSP_DMA_XFER_PER_REQ_SSP_00_TX         (CSP_DEV_NBR)(0u)
#define  CSP_DMA_XFER_PER_REQ_SSP_00_RX         (CSP_DEV_NBR)(1u)
#define  CSP_DMA_XFER_PER_REQ_SSP_01_TX         (CSP_DEV_NBR)(2u)
#define  CSP_DMA_XFER_PER_REQ_SSP_01_RX         (CSP_DEV_NBR)(3u)
#define  CSP_DMA_XFER_PER_REQ_ADC               (CSP_DEV_NBR)(4u)
#define  CSP_DMA_XFER_PER_REQ_I2S_00            (CSP_DEV_NBR)(5u)
#define  CSP_DMA_XFER_PER_REQ_I2S_01            (CSP_DEV_NBR)(6u)
#define  CSP_DMA_XFER_PER_REQ_DAC               (CSP_DEV_NBR)(7u)
#define  CSP_DMA_XFER_PER_REQ_UART_00_TX        (CSP_DEV_NBR)(8u)
#define  CSP_DMA_XFER_PER_REQ_UART_00_RX        (CSP_DEV_NBR)(9u)
#define  CSP_DMA_XFER_PER_REQ_UART_01_TX        (CSP_DEV_NBR)(10u)
#define  CSP_DMA_XFER_PER_REQ_UART_01_RX        (CSP_DEV_NBR)(11u)
#define  CSP_DMA_XFER_PER_REQ_UART_02_TX        (CSP_DEV_NBR)(12u)
#define  CSP_DMA_XFER_PER_REQ_UART_02_RX        (CSP_DEV_NBR)(13u)
#define  CSP_DMA_XFER_PER_REQ_UART_03_TX        (CSP_DEV_NBR)(14u)
#define  CSP_DMA_XFER_PER_REQ_UART_03_RX        (CSP_DEV_NBR)(15u)
#define  CSP_DMA_XFER_PER_REQ_TMR_00_MATCH_0    (CSP_DEV_NBR)(16u)
#define  CSP_DMA_XFER_PER_REQ_TMR_00_MATCH_1    (CSP_DEV_NBR)(17u)
#define  CSP_DMA_XFER_PER_REQ_TMR_01_MATCH_0    (CSP_DEV_NBR)(18u)
#define  CSP_DMA_XFER_PER_REQ_TMR_01_MATCH_1    (CSP_DEV_NBR)(19u)
#define  CSP_DMA_XFER_PER_REQ_TMR_02_MATCH_0    (CSP_DEV_NBR)(20u)
#define  CSP_DMA_XFER_PER_REQ_TMR_02_MATCH_1    (CSP_DEV_NBR)(21u)
#define  CSP_DMA_XFER_PER_REQ_TMR_03_MATCH_0    (CSP_DEV_NBR)(22u)
#define  CSP_DMA_XFER_PER_REQ_TMR_03_MATCH_1    (CSP_DEV_NBR)(23u)


/*
*********************************************************************************************************
*                                           TIMER MATCH DEFINES
*********************************************************************************************************
*/

#define  CSP_TMR_MATCH_NBR_00                 (CSP_DEV_NBR)(0u)
#define  CSP_TMR_MATCH_NBR_01                 (CSP_DEV_NBR)(1u)
#define  CSP_TMR_MATCH_NBR_02                 (CSP_DEV_NBR)(2u)
#define  CSP_TMR_MATCH_NBR_03                 (CSP_DEV_NBR)(3u)

#define  CSP_TMR_EXT_MATCH_OPT_NONE           (CSP_OPT    )(0u)
#define  CSP_TMR_EXT_MATCH_OPT_CLR            (CSP_OPT    )(1u)
#define  CSP_TMR_EXT_MATCH_OPT_SET            (CSP_OPT    )(2u)
#define  CSP_TMR_EXT_MATCH_OPT_TOGGLE         (CSP_OPT    )(3u)


/*
*********************************************************************************************************
*                                              SPI DEFINES
*********************************************************************************************************
*/

#define  CSP_SPI_NBR_MAX                      (CSP_DEV_NBR)(1u)


/*
*********************************************************************************************************
*                                              I2C DEFINES
*********************************************************************************************************
*/

#define  CSP_I2C_NBR_MAX                      (CSP_DEV_NBR)(3u)


/*
*********************************************************************************************************
*                                              SPI DEFINES
*********************************************************************************************************
*/

#define  CSP_SSP_NBR_00                         (CSP_DEV_NBR)( 0u)
#define  CSP_SSP_NBR_01                         (CSP_DEV_NBR)( 1u)
#define  CSP_SSP_NBR_02                         (CSP_DEV_NBR)( 2u)
#define  CSP_SSP_NBR_03                         (CSP_DEV_NBR)( 3u)
#define  CSP_SSP_NBR_04                         (CSP_DEV_NBR)( 4u)
#define  CSP_SSP_NBR_05                         (CSP_DEV_NBR)( 5u)
#define  CSP_SSP_NBR_06                         (CSP_DEV_NBR)( 6u)
#define  CSP_SSP_NBR_07                         (CSP_DEV_NBR)( 7u)
#define  CSP_SSP_NBR_08                         (CSP_DEV_NBR)( 8u)
#define  CSP_SSP_NBR_09                         (CSP_DEV_NBR)( 9u)
#define  CSP_SSP_NBR_10                         (CSP_DEV_NBR)(10u)
#define  CSP_SSP_NBR_11                         (CSP_DEV_NBR)(11u)
#define  CSP_SSP_NBR_12                         (CSP_DEV_NBR)(12u)
#define  CSP_SSP_NBR_13                         (CSP_DEV_NBR)(13u)
#define  CSP_SSP_NBR_14                         (CSP_DEV_NBR)(14u)
#define  CSP_SSP_NBR_15                         (CSP_DEV_NBR)(15u)

#define  CSP_SSP_NBR_MAX                        (CSP_DEV_NBR)(2u)
#define  CSP_SSP_FRAME_FMT_SPI                  (CSP_OPT    )(0u) 
#define  CSP_SSP_FRAME_FMT_TI                   (CSP_OPT    )(1u) 
#define  CSP_SSP_FRAME_FMT_MICROWIRE            (CSP_OPT    )(2u) 


/*
*********************************************************************************************************
*                                            DATA TYPES
*********************************************************************************************************
*/

typedef  CPU_INT32U  CSP_GPIO_MSK;                              /* GPIO port size.                                      */
typedef  CPU_INT32U  CSP_TMR_VAL;                               /* Timer value size.                                    */


/*
*********************************************************************************************************
*                                      INTERRUPT VECTOR DATA TYPE
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      DMA CALL BACK FUNCTION
*********************************************************************************************************
*/


typedef  void  (*CSP_DMA_CALLBACK_PTR)(CSP_DEV_NBR  ch_nbr,                                                            
                                       CPU_INT16U   xfer_size_rem, 
                                       void        *p_arg,                           
                                       CPU_BOOLEAN  status);


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                               MCU's FAMILY DEPENDENT API (EXTENDED API)
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         DMA FUNCTIONS
*********************************************************************************************************
*/

CPU_BOOLEAN  CSP_DMA_InitExt            (void);

CPU_BOOLEAN  CSP_DMA_CH_AllocExt        (CSP_OPT                prio,
                                         CSP_DEV_NBR           *p_ch_nbr);

CPU_BOOLEAN  CSP_DMA_CH_FreeExt         (CSP_DEV_NBR            ch_nbr);
                                
CPU_BOOLEAN  CSP_DMA_CH_CfgExt          (CSP_DEV_NBR            ch_nbr,
                                         CSP_OPT                xfer_type,                                       
                                         CSP_OPT                src_burst_size,
                                         CSP_OPT                src_width,
                                         CSP_OPT                dest_burst_size,
                                         CSP_OPT                dest_width,
                                         CSP_DEV_NBR            src_req,
                                         CSP_DEV_NBR            dest_req);

CPU_BOOLEAN  CSP_DMA_XferStartExt       (CSP_DEV_NBR            ch_nbr,
                                         void                   *p_src,
                                         void                   *p_dest,
                                         CPU_SIZE_T             xfer_size,
                                         CSP_OPT_FLAGS          opt);

#if 0
CPU_BOOLEAN  CSP_DMA_XferSyncStart      (CSP_DEV_NBR            ch_nbr,
                                         void                  *p_src,
                                         void                  *p_dest,
                                         CPU_INT16U             timeout,
                                         CPU_INT16U            *p_xfer_size_rem,
                                         CSP_OPT_FLAGS          opt);
#endif

CPU_BOOLEAN  CSP_DMA_XferAsyncStartExt  (CSP_DEV_NBR            ch_nbr,
                                         void                  *p_src,
                                         void                  *p_dest,
                                         CPU_SIZE_T             xfer_size,
                                         CSP_DMA_CALLBACK_PTR   callback,
                                         void                  *p_arg,
                                         CSP_OPT_FLAGS          opt);

CPU_INT32U   CSP_DMA_XferSizeMaxGetExt  (CSP_DEV_NBR            ch_nbr);


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of CSP_GRP module include.                      */

