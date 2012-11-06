/*
*********************************************************************************************************
*        CSP
* Chip Support Package
* Filename      : csp_usart.h
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

#ifndef  CSP_USART_PRESENT
#define  CSP_USART_PRESENT
/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

//#include  <csp.h>

/*
*********************************************************************************************************
*                                    REGISTER & BIT-FIELD DEFINITION
*********************************************************************************************************
*/

/*
*********************************************************************************************************
* Register definition for USART peripheral
*********************************************************************************************************
*/

#define CSP_REG_BASE_ADDR_USART_00                (CPU_INT32U)(0xF801C000U) /* (USART0  ) Base Address */
#define CSP_REG_BASE_ADDR_USART_01                (CPU_INT32U)(0xF8020000U) /* (USART1  ) Base Address */
#define CSP_REG_BASE_ADDR_USART_02                (CPU_INT32U)(0xF8024000U) /* (USART2  ) Base Address */
#define CSP_REG_BASE_ADDR_USART_03                (CPU_INT32U)(0xF8028000U) /* (USART3  ) Base Address */
#define CSP_REG_BASE_ADDR_USART                   (CPU_INT32U)(0xF801C000U) /* (USARTxx  ) Base Address */

#define CSP_REG_USART_00                          ((CSP_USART_REG_TAG_PTR)(CSP_REG_BASE_ADDR_USART_00))
#define CSP_REG_USART_01                          ((CSP_USART_REG_TAG_PTR)(CSP_REG_BASE_ADDR_USART_01))
#define CSP_REG_USART_02                          ((CSP_USART_REG_TAG_PTR)(CSP_REG_BASE_ADDR_USART_02))
#define CSP_REG_USART_03                          ((CSP_USART_REG_TAG_PTR)(CSP_REG_BASE_ADDR_USART_03))
#define CSP_REG_USART(nbr)                        ((CSP_USART_REG_TAG_PTR)(CSP_REG_BASE_ADDR_USART + ((nbr) * 0x4000)))

/*
*********************************************************************************************************
* SOFTWARE API DEFINITION FOR Universal Synchronous Asynchronous Receiver Transmitter
* AT91SAM9X25_USART Universal Synchronous Asynchronous Receiver Transmitter
*********************************************************************************************************
*/

typedef struct {
  CPU_REG32 US_CR;         /**< \brief (Usart Offset: 0x0000) Control Register */
  CPU_REG32 US_MR;         /**< \brief (Usart Offset: 0x0004) Mode Register */
  CPU_REG32 US_IER;        /**< \brief (Usart Offset: 0x0008) Interrupt Enable Register */
  CPU_REG32 US_IDR;        /**< \brief (Usart Offset: 0x000C) Interrupt Disable Register */
  CPU_REG32 US_IMR;        /**< \brief (Usart Offset: 0x0010) Interrupt Mask Register */
  CPU_REG32 US_CSR;        /**< \brief (Usart Offset: 0x0014) Channel Status Register */
  CPU_REG32 US_RHR;        /**< \brief (Usart Offset: 0x0018) Receiver Holding Register */
  CPU_REG32 US_THR;        /**< \brief (Usart Offset: 0x001C) Transmitter Holding Register */
  CPU_REG32 US_BRGR;       /**< \brief (Usart Offset: 0x0020) Baud Rate Generator Register */
  CPU_REG32 US_RTOR;       /**< \brief (Usart Offset: 0x0024) Receiver Time-out Register */
  CPU_REG32 US_TTGR;       /**< \brief (Usart Offset: 0x0028) Transmitter Timeguard Register */
  CPU_REG32 Reserved1[5];
  CPU_REG32 US_FIDI;       /**< \brief (Usart Offset: 0x0040) FI DI Ratio Register */
  CPU_REG32 US_NER;        /**< \brief (Usart Offset: 0x0044) Number of Errors Register */
  CPU_REG32 Reserved2[1];
  CPU_REG32 US_IF;         /**< \brief (Usart Offset: 0x004C) IrDA Filter Register */
  CPU_REG32 US_MAN;        /**< \brief (Usart Offset: 0x0050) Manchester Encoder Decoder Register */
  CPU_REG32 US_LINMR;      /**< \brief (Usart Offset: 0x0054) LIN Mode Register */
  CPU_REG32 US_LINIR;      /**< \brief (Usart Offset: 0x0058) LIN Identifier Register */
  CPU_REG32 Reserved3[34];
  CPU_REG32 US_WPMR;       /**< \brief (Usart Offset: 0xE4) Write Protect Mode Register */
  CPU_REG32 US_WPSR;       /**< \brief (Usart Offset: 0xE8) Write Protect Status Register */
} CSP_USART_REG_TAG, *CSP_USART_REG_TAG_PTR;

/* -------- CSP_US_CR : (USART Offset: 0x0000) Control Register -------- */
#define CSP_US_CR_RSTRX (0x1u << 2) /**< \brief (US_CR) Reset Receiver */
#define CSP_US_CR_RSTTX (0x1u << 3) /**< \brief (US_CR) Reset Transmitter */
#define CSP_US_CR_RXEN (0x1u << 4) /**< \brief (US_CR) Receiver Enable */
#define CSP_US_CR_RXDIS (0x1u << 5) /**< \brief (US_CR) Receiver Disable */
#define CSP_US_CR_TXEN (0x1u << 6) /**< \brief (US_CR) Transmitter Enable */
#define CSP_US_CR_TXDIS (0x1u << 7) /**< \brief (US_CR) Transmitter Disable */
#define CSP_US_CR_RSTSTA (0x1u << 8) /**< \brief (US_CR) Reset Status Bits */
#define CSP_US_CR_STTBRK (0x1u << 9) /**< \brief (US_CR) Start Break */
#define CSP_US_CR_STPBRK (0x1u << 10) /**< \brief (US_CR) Stop Break */
#define CSP_US_CR_STTTO (0x1u << 11) /**< \brief (US_CR) Start Time-out */
#define CSP_US_CR_SENDA (0x1u << 12) /**< \brief (US_CR) Send Address */
#define CSP_US_CR_RSTIT (0x1u << 13) /**< \brief (US_CR) Reset Iterations */
#define CSP_US_CR_RSTNACK (0x1u << 14) /**< \brief (US_CR) Reset Non Acknowledge */
#define CSP_US_CR_RETTO (0x1u << 15) /**< \brief (US_CR) Rearm Time-out */
#define CSP_US_CR_RTSEN (0x1u << 18) /**< \brief (US_CR) Request to Send Enable */
#define CSP_US_CR_FCS (0x1u << 18) /**< \brief (US_CR) Force SPI Chip Select */
#define CSP_US_CR_RTSDIS (0x1u << 19) /**< \brief (US_CR) Request to Send Disable */
#define CSP_US_CR_RCS (0x1u << 19) /**< \brief (US_CR) Release SPI Chip Select */
#define CSP_US_CR_LINABT (0x1u << 20) /**< \brief (US_CR) Abort LIN Transmission */
#define CSP_US_CR_LINWKUP (0x1u << 21) /**< \brief (US_CR) Send LIN Wakeup Signal */
/* -------- CSP_US_MR : (USART Offset: 0x0004) Mode Register -------- */
#define CSP_US_MR_USART_MODE_Pos 0
#define CSP_US_MR_USART_MODE_Msk (0xfu << CSP_US_MR_USART_MODE_Pos) /**< \brief (US_MR)  */
#define CSP_US_MR_USART_MODE_NORMAL (0x0u << 0) /**< \brief (US_MR) Normal mode */
#define CSP_US_MR_USART_MODE_RS485 (0x1u << 0) /**< \brief (US_MR) RS485 */
#define CSP_US_MR_USART_MODE_HW_HANDSHAKING (0x2u << 0) /**< \brief (US_MR) Hardware Handshaking */
#define CSP_US_MR_USART_MODE_IS07816_T_0 (0x4u << 0) /**< \brief (US_MR) IS07816 Protocol: T = 0 */
#define CSP_US_MR_USART_MODE_IS07816_T_1 (0x6u << 0) /**< \brief (US_MR) IS07816 Protocol: T = 1 */
#define CSP_US_MR_USART_MODE_IRDA (0x8u << 0) /**< \brief (US_MR) IrDA */
#define CSP_US_MR_USART_MODE_LIN_MASTER (0xAu << 0) /**< \brief (US_MR) LIN Master */
#define CSP_US_MR_USART_MODE_LIN_SLAVE (0xBu << 0) /**< \brief (US_MR) LIN Slave */
#define CSP_US_MR_USART_MODE_SPI_MASTER (0xEu << 0) /**< \brief (US_MR) SPI Master */
#define CSP_US_MR_USART_MODE_SPI_SLAVE (0xFu << 0) /**< \brief (US_MR) SPI Slave */
#define CSP_US_MR_USCLKS_Pos 4
#define CSP_US_MR_USCLKS_Msk (0x3u << CSP_US_MR_USCLKS_Pos) /**< \brief (US_MR) Clock Selection */
#define CSP_US_MR_USCLKS_MCK (0x0u << 4) /**< \brief (US_MR) Master Clock MCK is selected */
#define CSP_US_MR_USCLKS_DIV (0x1u << 4) /**< \brief (US_MR) Internal Clock Divided MCK/DIV (DIV=8) is selected */
#define CSP_US_MR_USCLKS_SCK (0x3u << 4) /**< \brief (US_MR) Serial Clock SLK is selected */
#define CSP_US_MR_CHRL_Pos 6
#define CSP_US_MR_CHRL_Msk (0x3u << CSP_US_MR_CHRL_Pos) /**< \brief (US_MR) Character Length. */
#define CSP_US_MR_CHRL_5_BIT (0x0u << 6) /**< \brief (US_MR) Character length is 5 bits */
#define CSP_US_MR_CHRL_6_BIT (0x1u << 6) /**< \brief (US_MR) Character length is 6 bits */
#define CSP_US_MR_CHRL_7_BIT (0x2u << 6) /**< \brief (US_MR) Character length is 7 bits */
#define CSP_US_MR_CHRL_8_BIT (0x3u << 6) /**< \brief (US_MR) Character length is 8 bits */
#define CSP_US_MR_SYNC (0x1u << 8) /**< \brief (US_MR) Synchronous Mode Select */
#define CSP_US_MR_CPHA (0x1u << 8) /**< \brief (US_MR) SPI Clock Phase */
#define CSP_US_MR_PAR_Pos 9
#define CSP_US_MR_PAR_Msk (0x7u << CSP_US_MR_PAR_Pos) /**< \brief (US_MR) Parity Type */
#define CSP_US_MR_PAR_EVEN (0x0u << 9) /**< \brief (US_MR) Even parity */
#define CSP_US_MR_PAR_ODD (0x1u << 9) /**< \brief (US_MR) Odd parity */
#define CSP_US_MR_PAR_SPACE (0x2u << 9) /**< \brief (US_MR) Parity forced to 0 (Space) */
#define CSP_US_MR_PAR_MARK (0x3u << 9) /**< \brief (US_MR) Parity forced to 1 (Mark) */
#define CSP_US_MR_PAR_NO (0x4u << 9) /**< \brief (US_MR) No parity */
#define CSP_US_MR_PAR_MULTIDROP (0x6u << 9) /**< \brief (US_MR) Multidrop mode */
#define CSP_US_MR_NBSTOP_Pos 12
#define CSP_US_MR_NBSTOP_Msk (0x3u << CSP_US_MR_NBSTOP_Pos) /**< \brief (US_MR) Number of Stop Bits */
#define CSP_US_MR_NBSTOP_1_BIT (0x0u << 12) /**< \brief (US_MR) 1 stop bit */
#define CSP_US_MR_NBSTOP_1_5_BIT (0x1u << 12) /**< \brief (US_MR) 1.5 stop bit (SYNC = 0) or reserved (SYNC = 1) */
#define CSP_US_MR_NBSTOP_2_BIT (0x2u << 12) /**< \brief (US_MR) 2 stop bits */
#define CSP_US_MR_CHMODE_Pos 14
#define CSP_US_MR_CHMODE_Msk (0x3u << CSP_US_MR_CHMODE_Pos) /**< \brief (US_MR) Channel Mode */
#define CSP_US_MR_CHMODE_NORMAL (0x0u << 14) /**< \brief (US_MR) Normal Mode */
#define CSP_US_MR_CHMODE_AUTOMATIC (0x1u << 14) /**< \brief (US_MR) Automatic Echo. Receiver input is connected to the TXD pin. */
#define CSP_US_MR_CHMODE_LOCAL_LOOPBACK (0x2u << 14) /**< \brief (US_MR) Local Loopback. Transmitter output is connected to the Receiver Input. */
#define CSP_US_MR_CHMODE_REMOTE_LOOPBACK (0x3u << 14) /**< \brief (US_MR) Remote Loopback. RXD pin is internally connected to the TXD pin. */
#define CSP_US_MR_MSBF (0x1u << 16) /**< \brief (US_MR) Bit Order */
#define CSP_US_MR_CPOL (0x1u << 16) /**< \brief (US_MR) SPI Clock Polarity */
#define CSP_US_MR_MODE9 (0x1u << 17) /**< \brief (US_MR) 9-bit Character Length */
#define CSP_US_MR_CLKO (0x1u << 18) /**< \brief (US_MR) Clock Output Select */
#define CSP_US_MR_OVER (0x1u << 19) /**< \brief (US_MR) Oversampling Mode */
#define CSP_US_MR_INACK (0x1u << 20) /**< \brief (US_MR) Inhibit Non Acknowledge */
#define CSP_US_MR_DSNACK (0x1u << 21) /**< \brief (US_MR) Disable Successive NACK */
#define CSP_US_MR_VAR_SYNC (0x1u << 22) /**< \brief (US_MR) Variable Synchronization of Command/Data Sync Start Frame Delimiter */
#define CSP_US_MR_MAX_ITERATION_Pos 24
#define CSP_US_MR_MAX_ITERATION_Msk (0x7u << CSP_US_MR_MAX_ITERATION_Pos) /**< \brief (US_MR)  */
#define CSP_US_MR_MAX_ITERATION(value) ((CSP_US_MR_MAX_ITERATION_Msk & ((value) << CSP_US_MR_MAX_ITERATION_Pos)))
#define CSP_US_MR_FILTER (0x1u << 28) /**< \brief (US_MR) Infrared Receive Line Filter */
#define CSP_US_MR_MAN (0x1u << 29) /**< \brief (US_MR) Manchester Encoder/Decoder Enable */
#define CSP_US_MR_MODSYNC (0x1u << 30) /**< \brief (US_MR) Manchester Synchronization Mode */
#define CSP_US_MR_ONEBIT (0x1u << 31) /**< \brief (US_MR) Start Frame Delimiter Selector */
/* -------- CSP_US_IER : (USART Offset: 0x0008) Interrupt Enable Register -------- */
#define CSP_US_IER_RXRDY (0x1u << 0) /**< \brief (US_IER) RXRDY Interrupt Enable */
#define CSP_US_IER_TXRDY (0x1u << 1) /**< \brief (US_IER) TXRDY Interrupt Enable */
#define CSP_US_IER_RXBRK (0x1u << 2) /**< \brief (US_IER) Receiver Break Interrupt Enable */
#define CSP_US_IER_OVRE (0x1u << 5) /**< \brief (US_IER) Overrun Error Interrupt Enable */
#define CSP_US_IER_FRAME (0x1u << 6) /**< \brief (US_IER) Framing Error Interrupt Enable */
#define CSP_US_IER_PARE (0x1u << 7) /**< \brief (US_IER) Parity Error Interrupt Enable */
#define CSP_US_IER_TIMEOUT (0x1u << 8) /**< \brief (US_IER) Time-out Interrupt Enable */
#define CSP_US_IER_TXEMPTY (0x1u << 9) /**< \brief (US_IER) TXEMPTY Interrupt Enable */
#define CSP_US_IER_ITER (0x1u << 10) /**< \brief (US_IER) Max number of Repetitions Reached */
#define CSP_US_IER_UNRE (0x1u << 10) /**< \brief (US_IER) SPI Underrun Error */
#define CSP_US_IER_NACK (0x1u << 13) /**< \brief (US_IER) Non Acknowledge Interrupt Enable */
#define CSP_US_IER_LINBK (0x1u << 13) /**< \brief (US_IER) LIN Break Sent or LIN Break Received Interrupt Enable */
#define CSP_US_IER_LINID (0x1u << 14) /**< \brief (US_IER) LIN Identifier Sent or LIN Identifier Received Interrupt Enable */
#define CSP_US_IER_LINTC (0x1u << 15) /**< \brief (US_IER) LIN Transfer Completed Interrupt Enable */
#define CSP_US_IER_CTSIC (0x1u << 19) /**< \brief (US_IER) Clear to Send Input Change Interrupt Enable */
#define CSP_US_IER_MANE (0x1u << 24) /**< \brief (US_IER) Manchester Error Interrupt Enable */
#define CSP_US_IER_LINBE (0x1u << 25) /**< \brief (US_IER) LIN Bus Error Interrupt Enable */
#define CSP_US_IER_LINISFE (0x1u << 26) /**< \brief (US_IER) LIN Inconsistent Synch Field Error Interrupt Enable */
#define CSP_US_IER_LINIPE (0x1u << 27) /**< \brief (US_IER) LIN Identifier Parity Interrupt Enable */
#define CSP_US_IER_LINCE (0x1u << 28) /**< \brief (US_IER) LIN Checksum Error Interrupt Enable */
#define CSP_US_IER_LINSNRE (0x1u << 29) /**< \brief (US_IER) LIN Slave Not Responding Error Interrupt Enable */
/* -------- CSP_US_IDR : (USART Offset: 0x000C) Interrupt Disable Register -------- */
#define CSP_US_IDR_RXRDY (0x1u << 0) /**< \brief (US_IDR) RXRDY Interrupt Disable */
#define CSP_US_IDR_TXRDY (0x1u << 1) /**< \brief (US_IDR) TXRDY Interrupt Disable */
#define CSP_US_IDR_RXBRK (0x1u << 2) /**< \brief (US_IDR) Receiver Break Interrupt Disable */
#define CSP_US_IDR_OVRE (0x1u << 5) /**< \brief (US_IDR) Overrun Error Interrupt Disable */
#define CSP_US_IDR_FRAME (0x1u << 6) /**< \brief (US_IDR) Framing Error Interrupt Disable */
#define CSP_US_IDR_PARE (0x1u << 7) /**< \brief (US_IDR) Parity Error Interrupt Disable */
#define CSP_US_IDR_TIMEOUT (0x1u << 8) /**< \brief (US_IDR) Time-out Interrupt Disable */
#define CSP_US_IDR_TXEMPTY (0x1u << 9) /**< \brief (US_IDR) TXEMPTY Interrupt Disable */
#define CSP_US_IDR_ITER (0x1u << 10) /**< \brief (US_IDR) Max number of Repetitions Reached Disable */
#define CSP_US_IDR_UNRE (0x1u << 10) /**< \brief (US_IDR) SPI Underrun Error Disable */
#define CSP_US_IDR_NACK (0x1u << 13) /**< \brief (US_IDR) Non Acknowledge Interrupt Disable */
#define CSP_US_IDR_LINBK (0x1u << 13) /**< \brief (US_IDR) LIN Break Sent or LIN Break Received Interrupt Disable */
#define CSP_US_IDR_LINID (0x1u << 14) /**< \brief (US_IDR) LIN Identifier Sent or LIN Identifier Received Interrupt Disable */
#define CSP_US_IDR_LINTC (0x1u << 15) /**< \brief (US_IDR) LIN Transfer Completed Interrupt Disable */
#define CSP_US_IDR_CTSIC (0x1u << 19) /**< \brief (US_IDR) Clear to Send Input Change Interrupt Disable */
#define CSP_US_IDR_MANE (0x1u << 24) /**< \brief (US_IDR) Manchester Error Interrupt Disable */
#define CSP_US_IDR_LINBE (0x1u << 25) /**< \brief (US_IDR) LIN Bus Error Interrupt Disable */
#define CSP_US_IDR_LINISFE (0x1u << 26) /**< \brief (US_IDR) LIN Inconsistent Synch Field Error Interrupt Disable */
#define CSP_US_IDR_LINIPE (0x1u << 27) /**< \brief (US_IDR) LIN Identifier Parity Interrupt Disable */
#define CSP_US_IDR_LINCE (0x1u << 28) /**< \brief (US_IDR) LIN Checksum Error Interrupt Disable */
#define CSP_US_IDR_LINSNRE (0x1u << 29) /**< \brief (US_IDR) LIN Slave Not Responding Error Interrupt Disable */
/* -------- CSP_US_IMR : (USART Offset: 0x0010) Interrupt Mask Register -------- */
#define CSP_US_IMR_RXRDY (0x1u << 0) /**< \brief (US_IMR) RXRDY Interrupt Mask */
#define CSP_US_IMR_TXRDY (0x1u << 1) /**< \brief (US_IMR) TXRDY Interrupt Mask */
#define CSP_US_IMR_RXBRK (0x1u << 2) /**< \brief (US_IMR) Receiver Break Interrupt Mask */
#define CSP_US_IMR_OVRE (0x1u << 5) /**< \brief (US_IMR) Overrun Error Interrupt Mask */
#define CSP_US_IMR_FRAME (0x1u << 6) /**< \brief (US_IMR) Framing Error Interrupt Mask */
#define CSP_US_IMR_PARE (0x1u << 7) /**< \brief (US_IMR) Parity Error Interrupt Mask */
#define CSP_US_IMR_TIMEOUT (0x1u << 8) /**< \brief (US_IMR) Time-out Interrupt Mask */
#define CSP_US_IMR_TXEMPTY (0x1u << 9) /**< \brief (US_IMR) TXEMPTY Interrupt Mask */
#define CSP_US_IMR_ITER (0x1u << 10) /**< \brief (US_IMR) Max number of Repetitions Reached Mask */
#define CSP_US_IMR_UNRE (0x1u << 10) /**< \brief (US_IMR) SPI Underrun Error Mask */
#define CSP_US_IMR_NACK (0x1u << 13) /**< \brief (US_IMR) Non Acknowledge Interrupt Mask */
#define CSP_US_IMR_LINBK (0x1u << 13) /**< \brief (US_IMR) LIN Break Sent or LIN Break Received Interrupt Mask */
#define CSP_US_IMR_LINID (0x1u << 14) /**< \brief (US_IMR) LIN Identifier Sent or LIN Identifier Received Interrupt Mask */
#define CSP_US_IMR_LINTC (0x1u << 15) /**< \brief (US_IMR) LIN Transfer Completed Interrupt Mask */
#define CSP_US_IMR_CTSIC (0x1u << 19) /**< \brief (US_IMR) Clear to Send Input Change Interrupt Mask */
#define CSP_US_IMR_MANE (0x1u << 24) /**< \brief (US_IMR) Manchester Error Interrupt Mask */
#define CSP_US_IMR_LINBE (0x1u << 25) /**< \brief (US_IMR) LIN Bus Error Interrupt Mask */
#define CSP_US_IMR_LINISFE (0x1u << 26) /**< \brief (US_IMR) LIN Inconsistent Synch Field Error Interrupt Mask */
#define CSP_US_IMR_LINIPE (0x1u << 27) /**< \brief (US_IMR) LIN Identifier Parity Interrupt Mask */
#define CSP_US_IMR_LINCE (0x1u << 28) /**< \brief (US_IMR) LIN Checksum Error Interrupt Mask */
#define CSP_US_IMR_LINSNRE (0x1u << 29) /**< \brief (US_IMR) LIN Slave Not Responding Error Interrupt Mask */
/* -------- CSP_US_CSR : (USART Offset: 0x0014) Channel Status Register -------- */
#define CSP_US_CSR_RXRDY (0x1u << 0) /**< \brief (US_CSR) Receiver Ready */
#define CSP_US_CSR_TXRDY (0x1u << 1) /**< \brief (US_CSR) Transmitter Ready */
#define CSP_US_CSR_RXBRK (0x1u << 2) /**< \brief (US_CSR) Break Received/End of Break */
#define CSP_US_CSR_OVRE (0x1u << 5) /**< \brief (US_CSR) Overrun Error */
#define CSP_US_CSR_FRAME (0x1u << 6) /**< \brief (US_CSR) Framing Error */
#define CSP_US_CSR_PARE (0x1u << 7) /**< \brief (US_CSR) Parity Error */
#define CSP_US_CSR_TIMEOUT (0x1u << 8) /**< \brief (US_CSR) Receiver Time-out */
#define CSP_US_CSR_TXEMPTY (0x1u << 9) /**< \brief (US_CSR) Transmitter Empty */
#define CSP_US_CSR_ITER (0x1u << 10) /**< \brief (US_CSR) Max number of Repetitions Reached */
#define CSP_US_CSR_UNRE (0x1u << 10) /**< \brief (US_CSR) SPI Underrun Error */
#define CSP_US_CSR_NACK (0x1u << 13) /**< \brief (US_CSR) Non Acknowledge Interrupt */
#define CSP_US_CSR_LINBK (0x1u << 13) /**< \brief (US_CSR) LIN Break Sent or LIN Break Received */
#define CSP_US_CSR_LINID (0x1u << 14) /**< \brief (US_CSR) LIN Identifier Sent or LIN Identifier Received */
#define CSP_US_CSR_LINTC (0x1u << 15) /**< \brief (US_CSR) LIN Transfer Completed */
#define CSP_US_CSR_CTSIC (0x1u << 19) /**< \brief (US_CSR) Clear to Send Input Change Flag */
#define CSP_US_CSR_CTS (0x1u << 23) /**< \brief (US_CSR) Image of CTS Input */
#define CSP_US_CSR_LINBLS (0x1u << 23) /**< \brief (US_CSR) LIN Bus Line Status */
#define CSP_US_CSR_MANERR (0x1u << 24) /**< \brief (US_CSR) Manchester Error */
#define CSP_US_CSR_LINBE (0x1u << 25) /**< \brief (US_CSR) LIN Bit Error */
#define CSP_US_CSR_LINISFE (0x1u << 26) /**< \brief (US_CSR) LIN Inconsistent Synch Field Error */
#define CSP_US_CSR_LINIPE (0x1u << 27) /**< \brief (US_CSR) LIN Identifier Parity Error */
#define CSP_US_CSR_LINCE (0x1u << 28) /**< \brief (US_CSR) LIN Checksum Error */
#define CSP_US_CSR_LINSNRE (0x1u << 29) /**< \brief (US_CSR) LIN Slave Not Responding Error */
/* -------- CSP_US_RHR : (USART Offset: 0x0018) Receiver Holding Register -------- */
#define CSP_US_RHR_RXCHR_Pos 0
#define CSP_US_RHR_RXCHR_Msk (0x1ffu << CSP_US_RHR_RXCHR_Pos) /**< \brief (US_RHR) Received Character */
#define CSP_US_RHR_RXSYNH (0x1u << 15) /**< \brief (US_RHR) Received Sync */
/* -------- CSP_US_THR : (USART Offset: 0x001C) Transmitter Holding Register -------- */
#define CSP_US_THR_TXCHR_Pos 0
#define CSP_US_THR_TXCHR_Msk (0x1ffu << CSP_US_THR_TXCHR_Pos) /**< \brief (US_THR) Character to be Transmitted */
#define CSP_US_THR_TXCHR(value) ((CSP_US_THR_TXCHR_Msk & ((value) << CSP_US_THR_TXCHR_Pos)))
#define CSP_US_THR_TXSYNH (0x1u << 15) /**< \brief (US_THR) Sync Field to be transmitted */
/* -------- CSP_US_BRGR : (USART Offset: 0x0020) Baud Rate Generator Register -------- */
#define CSP_US_BRGR_CD_Pos 0
#define CSP_US_BRGR_CD_Msk (0xffffu << CSP_US_BRGR_CD_Pos) /**< \brief (US_BRGR) Clock Divider */
#define CSP_US_BRGR_CD(value) ((CSP_US_BRGR_CD_Msk & ((value) << CSP_US_BRGR_CD_Pos)))
#define CSP_US_BRGR_FP_Pos 16
#define CSP_US_BRGR_FP_Msk (0x7u << CSP_US_BRGR_FP_Pos) /**< \brief (US_BRGR) Fractional Part */
#define CSP_US_BRGR_FP(value) ((CSP_US_BRGR_FP_Msk & ((value) << CSP_US_BRGR_FP_Pos)))
/* -------- CSP_US_RTOR : (USART Offset: 0x0024) Receiver Time-out Register -------- */
#define CSP_US_RTOR_TO_Pos 0
#define CSP_US_RTOR_TO_Msk (0x1ffffu << CSP_US_RTOR_TO_Pos) /**< \brief (US_RTOR) Time-out Value */
#define CSP_US_RTOR_TO(value) ((CSP_US_RTOR_TO_Msk & ((value) << CSP_US_RTOR_TO_Pos)))
/* -------- CSP_US_TTGR : (USART Offset: 0x0028) Transmitter Timeguard Register -------- */
#define CSP_US_TTGR_TG_Pos 0
#define CSP_US_TTGR_TG_Msk (0xffu << CSP_US_TTGR_TG_Pos) /**< \brief (US_TTGR) Timeguard Value */
#define CSP_US_TTGR_TG(value) ((CSP_US_TTGR_TG_Msk & ((value) << CSP_US_TTGR_TG_Pos)))
/* -------- CSP_US_FIDI : (USART Offset: 0x0040) FI DI Ratio Register -------- */
#define CSP_US_FIDI_FI_DI_RATIO_Pos 0
#define CSP_US_FIDI_FI_DI_RATIO_Msk (0x7ffu << CSP_US_FIDI_FI_DI_RATIO_Pos) /**< \brief (US_FIDI) FI Over DI Ratio Value */
#define CSP_US_FIDI_FI_DI_RATIO(value) ((CSP_US_FIDI_FI_DI_RATIO_Msk & ((value) << CSP_US_FIDI_FI_DI_RATIO_Pos)))
/* -------- CSP_US_NER : (USART Offset: 0x0044) Number of Errors Register -------- */
#define CSP_US_NER_NB_ERRORS_Pos 0
#define CSP_US_NER_NB_ERRORS_Msk (0xffu << CSP_US_NER_NB_ERRORS_Pos) /**< \brief (US_NER) Number of Errors */
/* -------- CSP_US_IF : (USART Offset: 0x004C) IrDA Filter Register -------- */
#define CSP_US_IF_IRDA_FILTER_Pos 0
#define CSP_US_IF_IRDA_FILTER_Msk (0xffu << CSP_US_IF_IRDA_FILTER_Pos) /**< \brief (US_IF) IrDA Filter */
#define CSP_US_IF_IRDA_FILTER(value) ((CSP_US_IF_IRDA_FILTER_Msk & ((value) << CSP_US_IF_IRDA_FILTER_Pos)))
/* -------- CSP_US_MAN : (USART Offset: 0x0050) Manchester Encoder Decoder Register -------- */
#define CSP_US_MAN_TX_PL_Pos 0
#define CSP_US_MAN_TX_PL_Msk (0xfu << CSP_US_MAN_TX_PL_Pos) /**< \brief (US_MAN) Transmitter Preamble Length */
#define CSP_US_MAN_TX_PL(value) ((CSP_US_MAN_TX_PL_Msk & ((value) << CSP_US_MAN_TX_PL_Pos)))
#define CSP_US_MAN_TX_PP_Pos 8
#define CSP_US_MAN_TX_PP_Msk (0x3u << CSP_US_MAN_TX_PP_Pos) /**< \brief (US_MAN) Transmitter Preamble Pattern */
#define CSP_US_MAN_TX_PP_ALL_ONE (0x0u << 8) /**< \brief (US_MAN) The preamble is composed of '1's */
#define CSP_US_MAN_TX_PP_ALL_ZERO (0x1u << 8) /**< \brief (US_MAN) The preamble is composed of '0's */
#define CSP_US_MAN_TX_PP_ZERO_ONE (0x2u << 8) /**< \brief (US_MAN) The preamble is composed of '01's */
#define CSP_US_MAN_TX_PP_ONE_ZERO (0x3u << 8) /**< \brief (US_MAN) The preamble is composed of '10's */
#define CSP_US_MAN_TX_MPOL (0x1u << 12) /**< \brief (US_MAN) Transmitter Manchester Polarity */
#define CSP_US_MAN_RX_PL_Pos 16
#define CSP_US_MAN_RX_PL_Msk (0xfu << CSP_US_MAN_RX_PL_Pos) /**< \brief (US_MAN) Receiver Preamble Length */
#define CSP_US_MAN_RX_PL(value) ((CSP_US_MAN_RX_PL_Msk & ((value) << CSP_US_MAN_RX_PL_Pos)))
#define CSP_US_MAN_RX_PP_Pos 24
#define CSP_US_MAN_RX_PP_Msk (0x3u << CSP_US_MAN_RX_PP_Pos) /**< \brief (US_MAN) Receiver Preamble Pattern detected */
#define CSP_US_MAN_RX_PP_ALL_ONE (0x0u << 24) /**< \brief (US_MAN) The preamble is composed of '1's */
#define CSP_US_MAN_RX_PP_ALL_ZERO (0x1u << 24) /**< \brief (US_MAN) The preamble is composed of '0's */
#define CSP_US_MAN_RX_PP_ZERO_ONE (0x2u << 24) /**< \brief (US_MAN) The preamble is composed of '01's */
#define CSP_US_MAN_RX_PP_ONE_ZERO (0x3u << 24) /**< \brief (US_MAN) The preamble is composed of '10's */
#define CSP_US_MAN_RX_MPOL (0x1u << 28) /**< \brief (US_MAN) Receiver Manchester Polarity */
#define CSP_US_MAN_STUCKTO1 (0x1u << 29) /**< \brief (US_MAN)  */
#define CSP_US_MAN_DRIFT (0x1u << 30) /**< \brief (US_MAN) Drift compensation */
/* -------- CSP_US_LINMR : (USART Offset: 0x0054) LIN Mode Register -------- */
#define CSP_US_LINMR_NACT_Pos 0
#define CSP_US_LINMR_NACT_Msk (0x3u << CSP_US_LINMR_NACT_Pos) /**< \brief (US_LINMR) LIN Node Action */
#define CSP_US_LINMR_NACT_PUBLISH (0x0u << 0) /**< \brief (US_LINMR) The USART transmits the response. */
#define CSP_US_LINMR_NACT_SUBSCRIBE (0x1u << 0) /**< \brief (US_LINMR) The USART receives the response. */
#define CSP_US_LINMR_NACT_IGNORE (0x2u << 0) /**< \brief (US_LINMR) The USART does not transmit and does not receive the response. */
#define CSP_US_LINMR_PARDIS (0x1u << 2) /**< \brief (US_LINMR) Parity Disable */
#define CSP_US_LINMR_CHKDIS (0x1u << 3) /**< \brief (US_LINMR) Checksum Disable */
#define CSP_US_LINMR_CHKTYP (0x1u << 4) /**< \brief (US_LINMR) Checksum Type */
#define CSP_US_LINMR_DLM (0x1u << 5) /**< \brief (US_LINMR) Data Length Mode */
#define CSP_US_LINMR_FSDIS (0x1u << 6) /**< \brief (US_LINMR) Frame Slot Mode Disable */
#define CSP_US_LINMR_WKUPTYP (0x1u << 7) /**< \brief (US_LINMR) Wakeup Signal Type */
#define CSP_US_LINMR_DLC_Pos 8
#define CSP_US_LINMR_DLC_Msk (0xffu << CSP_US_LINMR_DLC_Pos) /**< \brief (US_LINMR) Data Length Control */
#define CSP_US_LINMR_DLC(value) ((CSP_US_LINMR_DLC_Msk & ((value) << CSP_US_LINMR_DLC_Pos)))
#define CSP_US_LINMR_PDCM (0x1u << 16) /**< \brief (US_LINMR) DMAC Mode */
/* -------- CSP_US_LINIR : (USART Offset: 0x0058) LIN Identifier Register -------- */
#define CSP_US_LINIR_IDCHR_Pos 0
#define CSP_US_LINIR_IDCHR_Msk (0xffu << CSP_US_LINIR_IDCHR_Pos) /**< \brief (US_LINIR) Identifier Character */
#define CSP_US_LINIR_IDCHR(value) ((CSP_US_LINIR_IDCHR_Msk & ((value) << CSP_US_LINIR_IDCHR_Pos)))
/* -------- CSP_US_WPMR : (USART Offset: 0xE4) Write Protect Mode Register -------- */
#define CSP_US_WPMR_WPEN (0x1u << 0) /**< \brief (US_WPMR) Write Protect Enable */
#define CSP_US_WPMR_WPKEY_Pos 8
#define CSP_US_WPMR_WPKEY_Msk (0xffffffu << CSP_US_WPMR_WPKEY_Pos) /**< \brief (US_WPMR) Write Protect KEY */
#define CSP_US_WPMR_WPKEY(value) ((CSP_US_WPMR_WPKEY_Msk & ((value) << CSP_US_WPMR_WPKEY_Pos)))
/* -------- CSP_US_WPSR : (USART Offset: 0xE8) Write Protect Status Register -------- */
#define CSP_US_WPSR_WPVS (0x1u << 0) /**< \brief (US_WPSR) Write Protect Violation Status */
#define CSP_US_WPSR_WPVSRC_Pos 8
#define CSP_US_WPSR_WPVSRC_Msk (0xffffu << CSP_US_WPSR_WPVSRC_Pos) /**< \brief (US_WPSR) Write Protect Violation Source */

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of CSP_USART module include.                      */

