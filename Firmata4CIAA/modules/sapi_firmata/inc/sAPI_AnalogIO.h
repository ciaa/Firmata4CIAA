/* Copyright 2016, Ian Olivieri <ianolivieri93@gmail.com>
 * All rights reserved.
 *
 * This file is part of the Firmata4CIAA program.
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


#ifndef SAPI_ANALOGIO_H_
#define SAPI_ANALOGIO_H_

/*==================[inclusions]=============================================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros and definitions]=================================*/

/*==================[typedef]================================================*/

/*  Analog Channel names are defined in sAPI_PeripheralMap.h:
typedef enum{
   ACH1=1, ACH2, ACH3
} ACMap_t;
*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/*
 * @brief:   enable/disable the ADC and DAC peripheral
 * @param:   enable: 1 to enable, 0 to disable.
 * @return:   none
*/
void analogConfig(bool_t enable);


/*
 * @brief   Write a value in the DAC.
 * @param   value: value to be writen in the DAC, from 0 to 1024
 * @return   none
 */
void analogWrite(uint32_t value);

/* 
 * @brief   Get the value of one ADC channel. Mode: BLOCKING
 * @param   channel: number of channel, from ACH1 to ACH3 (1 to 3)
 * @return   value of the channel
 */
uint16_t analogRead(uint8_t channel);
/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/


#endif /* #ifndef _SAPI_ANALOGIO_H_ */
