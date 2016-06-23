/* Copyright 2015~2016, Ian Olivieri <ianolivieri93@gmail.com>
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

#ifndef PWM_DRIVER_H_
#define PWM_DRIVER_H_

/*==================[inclusions]=============================================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros and definitions]=================================*/

/*==================[typedef]================================================*/

/*  PWM names are defined in sAPI_PeripheralMap.h:

typedef enum{
   PWM0, PWM1, PWM2, PWM3, PWM4, PWM5, PWM6, PWM7, PWM8, PWM9, PWM10
} PwmMap_t;
*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/*
 * @Brief:   Initializes the pwm peripheral.
 * @param   none
 * @return   nothing
 */
void pwmConfig(void);

/*
 * @brief:   adds pwm to the the list of working pwms
 * @param:   pwmNumber:   ID of the pwm, from 0 to 10
 * @return:   True if pwm was successfully attached, False if not.
 */
bool_t pwmAttach( uint8_t pwmNumber);

/*
 * @brief:   removes pwm (attached to pwmNumber) from the list
 * @param:   pwmNumber:   ID of the pwm, from 0 to 10
 * @return:    True if pwm was successfully detached, False if not.
 */
bool_t pwmDetach( uint8_t pwmNumber );

/*
 * @brief:   change the value of the pwm at the selected pin
 * @param:   pwmNumber:   ID of the pwm, from 0 to 10
 * @param:   value:   8bit value, from 0 to 255
 * @return:   True if the value was successfully changed, False if not.
 */
bool_t pwmWrite( uint8_t pwmNumber, uint8_t percent );

/*
 * @brief:   read the value of the pwm in the pin
 * @param:   pwmNumber:   ID of the pwm, from 0 to 10
 * @return:   value of the pwm in the pin (0 ~ 255).
 *   If an error ocurred, return = EMPTY_POSITION = 255
 */
uint8_t pwmRead( uint8_t pwmNumber );

/*
 * @brief:   Tells if the pwm is currently active, and its position
 * @param:   pwmNumber:   ID of the pwm, from 0 to 10
 * @return:   position (1 ~ PWM_TOTALNUMBER), 0 if the element was not found.
 */
uint8_t pwmIsAttached( uint8_t pwmNumber );



/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/


#endif /* PWM_DRIVER_H_ */
