/* Copyright 2015~2016, Ian Olivieri.
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * For more information about the UART peripheral, refer to the Chapter 40 of
 * the LPC43xx user manual
 */


/*==================[inclusions]=============================================*/

#include "chip.h"
/* Specific modules used:
   #include "scu_18xx_43xx.h" for Chip_SCU funtions
   #include "uart_18xx_43xx.h" for Chip_UART funtions
*/

#include "ring_buffer.h"
#include "sAPI_DataTypes.h"

#include "sAPI_Uart.h"

/*==================[macros and definitions]=================================*/
/* Transmit and receive ring buffer sizes */
/* NOTE: if you are sending/receiving a lot of bytes in a short period of time,
 * you should increase the size of the buffers to avoid data loss */
#define SRB_SIZE 512   /* Send */
#define RRB_SIZE 128   /* Receive */

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/* Transmit and receive buffers */
static uint8_t rxbuff[RRB_SIZE], txbuff[SRB_SIZE];

/* Transmit and receive ring buffers */
static RINGBUFF_T txring, rxring;
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/*
 * @brief   indicates if there data available in the reception buffer
 * @param   none
 * @return   1 if there is a byte in the reception buffer, 0 if not
 * @note   this function should be used before uartRead() to avoid receiving
 *   invalid bytes
 */
uint8_t uartCanRead (void)
{
   return (!RingBuffer_IsEmpty(&rxring));
}

/*
 * @brief   Data consumer in the Rx side of the communication
 * @param    none
 * @return   the oldest byte in the reception buffer. 0 if there is
 *   no new data.
 * @note   if there is no new data, the return will be zero
 */
uint8_t uartRead( void)
{
   uint8_t ch=0;
   RingBuffer_Pop(&rxring, &ch);
   return ch;
}

/*
 * @brief   Data producer in the Tx side of the communication
 * @param   byte:   data to be writen in the transmission buffer
 * @return   nothing
 */
void uartWrite( uint8_t byte )
{
   RingBuffer_Insert(&txring, &byte);
}

/*
 * @brief   write a string to the transmission buffer
 * @param   strPtr:   pointer to the string
 * @param   strLengt:   length of the string
 * @return   nothing
 * @note   Max string length = SRB_SIZE
 */
void uartWriteString(uint8_t *strPtr,uint8_t strLength)
{
   uint8_t i=0;
   for(i=0; i<strLength;i++)
   {
      uartWrite(strPtr[i]);
   }
}

/*
 * @brief   Data consumer in the Tx side of the communication
 * @param   none
 * @return   nothing
 * @note   This function should be updated continously
 */
void uartTxGatekeeperTask( void )
{
   uint8_t ch=0;
   /* Fill FIFO until full or until TX ring buffer is empty */
   while ((Chip_UART_ReadLineStatus(LPC_USART2) & UART_LSR_THRE) != 0 &&  RingBuffer_Pop(&txring, &ch))
   {
      Chip_UART_SendByte(LPC_USART2, ch);
   }
}

/*
 * @brief   Data producer in the Rx side of the communication
 * @param   none
 * @return   nothing
 * @note   This function should be updated continously
 */
void uartRxGatekeeperTask( void )
{
   uint8_t ch=0;
   /* New data will be ignored if data not popped in time */
   while (Chip_UART_ReadLineStatus(LPC_USART2) & UART_LSR_RDR)
   {
      ch = Chip_UART_ReadByte(LPC_USART2);
      RingBuffer_Insert(&rxring, &ch);
   }
}

/*
 * @brief   Enables UART2 with a given baud rate
 * @param   baudRate:   rate of the uart.
 *   Value examples: 9600, 57600
 * @return   nothing
 */
void uartConfig( uint32_t baudRate )
{
   /*Initialize the Buffers used to hold the data*/
   RingBuffer_Init(&rxring, rxbuff, 1, RRB_SIZE);
   RingBuffer_Init(&txring, txbuff, 1, SRB_SIZE);

   /* Configure the necessary parameters to use the peripheral and enables UART transmission*/
   /* Initialize peripheral */
   Chip_UART_Init(LPC_USART2);
   /* Set Baud rate */
   Chip_UART_SetBaud(LPC_USART2, baudRate);
   /* Configure the serial port to 8N1 (8 data bits, no parity, 1 stop bit) */
   Chip_UART_ConfigData(LPC_USART2, (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT));
   /* Modify FCR (FIFO Control Register). Enable FIFO, reset Rx and Tx FIFOs and trigger level
    *(number of bytes needed in the FIFO for the interrupt to activate) to 8 bytes */
   Chip_UART_SetupFIFOS(LPC_USART2, UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS | UART_FCR_TRG_LEV2);


   /* Configure the corresponding pins for Tx and Rx */
   Chip_SCU_PinMux(7, 1, MD_PDN, FUNC6);              /* P7_1: UART2_TXD */
   Chip_SCU_PinMux(7, 2, MD_PLN|MD_EZI|MD_ZI, FUNC6); /* P7_2: UART2_RXD */

   /* Enable UART Transmission */
   Chip_UART_TXEnable(LPC_USART2);

   /* Enable UART Rx Interrupt. For more information: LPC43xx User manual page 111 * /
   /* Enable Rx interrupt with the RBRINT (Receiver Buffer Register Interrupt)) * /
   Chip_UART_IntEnable(CIAA_BOARD_UART,UART_IER_RBRINT );
   /* Enable UART line status interrupt. Priority must be greater than 5 * /
   NVIC_SetPriority(USART2_IRQn, 5+1);
   /* Enable Interrupt for UART channel * /
   NVIC_EnableIRQ(USART2_IRQn);
   */
}

/*==================[ISR external functions definition]======================*/
//void UART2_IRQHandler(void){}


/*==================[end of file]============================================*/
