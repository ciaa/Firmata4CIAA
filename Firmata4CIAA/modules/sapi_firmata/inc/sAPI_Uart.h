/* Copyright 2015, Eric Pernia.
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

#ifndef SAPI_UART_H_
#define SAPI_UART_H_


/*==================[inclusions]=============================================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/


/*==================[external data declaration]==============================*/

/*==================[ISR external functions definition]======================*/

//void UART0_IRQHandler(void);
//void UART1_IRQHandler(void);
//void UART2_IRQHandler(void);

/*==================[external functions declaration]=========================*/

/*
 * @brief   Data consumer in the Rx side of the communication
 * @param    none
 * @return   the oldest byte in the reception buffer. 0 if there is 
 *   no new data.
 * @note   if there is no new data, the return will be zero
 */
uint8_t uartCanRead (void);

/*
 * @brief   indicates if there data available in the reception buffer
 * @param   none
 * @return   1 if there is a byte in the reception buffer, 0 if not
 * @note   this function should be used before uartRead() to avoid receiving 
 *   invalid bytes
 */
uint8_t uartRead( void );

/*
 * @brief   Data producer in the Tx side of the communication
 * @param   byte:   data to be writen in the transmission buffer
 * @return   nothing
 */
void uartWrite( uint8_t byte);

/*
 * @brief   write a string to the transmission buffer
 * @param   strPtr:   pointer to the string
 * @param   strLengt:   length of the string (sizeof)
 * @return   nothing
 * @note   Max string length = SRB_SIZE
 */
void uartWriteString( uint8_t *strPtr,uint8_t strLength); 

/*
 * @brief   Data consumer in the Tx side of the communication
 * @param   none
 * @return   nothing
 * @note   This function should be updated continously
 */
void uartTxGatekeeperTask( void );

/*
 * @brief   Data producer in the Rx side of the communication
 * @param   none
 * @return   nothing
 * @note   This function should be updated continously
 */
void uartRxGatekeeperTask( void );

/*
 * @brief   Enables UART2 with a given baud rate
 * @param   baudRate:   rate of the uart.
 *   Values examples: 9600, 57600
 * @return   nothing
 */
void uartConfig(uint32_t baudRate);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* SAPI_UART_H_ */
