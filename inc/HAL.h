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
 */

#ifndef HAL_H_
#define HAL_H_


/*==================[inclusions]=============================================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros and definitions]=================================*/
#if !defined(OFF)
#define OFF   0
#endif

#if !defined(ON)
#define ON   1
#endif

/* ------------------ Available modes ------------------ */
#define INPUT_MODE   0x00 /* digital pin in analogInput mode */
#define OUTPUT_MODE   0x01 /* digital pin in analogOutput mode */
#define ANALOG_MODE   0x02 /* analog pin in analogInput mode */
#define PWM_MODE   0x03 /* digital pin in PWM output mode */
#define SERVO_MODE   0x04 /* digital pin in Servo output mode */
#define NO_MODE   255 /* no mode supported or no mode available */
#define MODES_TOTALNUMBER   5 /* Input, Output, Analog, Pwm and Servo */


/* Pin Map shorcuts */
#define FIRST_PIN   PIN0
#define LAST_PIN  PIN_TOTALNUMBER

/* from the pin map */
#define FIRST_DIGITAL_PIN   PIN0
#define LAST_DIGITAL_PIN   PIN32

/* theorical port equivalent from the number of pins */
#define DIGITALPORT_TOTALNUMBER   ceil(((double)LAST_DIGITAL_PIN)/8)+1

#define ANALOGCHANNEL_TOTALNUMBER   3


/*==================[typedef]================================================*/
/*	------------------ Mapeo de pines ------------------ */
typedef enum{
   PIN0,   /* LED R */
   PIN1,   /* LED G */
   PIN2,   /* LED B */
   PIN3,   /* LED 1 */
   PIN4,   /* LED 2 */
   PIN5,   /* LED 3 */
   PIN6,   /* TEC 1 */
   PIN7,   /* TEC 2 */
   PIN8,   /* TEC 3 */
   PIN9,   /* TEC 4 */
   PIN10,   /* SPI_MOSI */
   PIN11,   /* LCD_EN */
   PIN12,   /* GPIO0 */
   PIN13,   /* GPIO2 */
   PIN14,   /* GPIO4 */
   PIN15,   /* GPIO6 */
   PIN16,   /* GPIO8 */
   PIN17,   /* GPIO7 */
   PIN18,   /* GPIO5 */
   PIN19,   /* GPIO3 */
   PIN20,   /* GPIO1 */
   PIN21,   /* LCD1 */
   PIN22,   /* LCD2 */
   PIN23,   /* LCD3 */
   PIN24,   /* LCD_RS */
   PIN25,   /* LCD4 */
   PIN26,   /* T_COL1 */
   PIN27,   /* T_FIL0 */
   PIN28,   /* T_FIL3 */
   PIN29,   /* T_FIL2 */
   PIN30,   /* T_COL0 */
   PIN31,   /* T_FIL1 */
   PIN32,   /* T_COL2 */
   PIN33,   /* CH1 */
   PIN34,   /* CH2 */
   PIN35,   /* CH3 */
   PIN_TOTALNUMBER /* = 36*/
} PinMap_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
/*
 * @brief   Initialize all pins with their default mode and enables peripherals
 * @param   none
 * @return   nothing
 */
void HAL_Init(void);

/*
 * @brief   Get the resolution of a given mode
 * @param   mode:   mode to get the resolution from
 * @return   mode's resolution
 */
unsigned char HAL_ModeResolution (unsigned char mode);

/*
 * @brief   Checks if the pin can be configured with a certain mode
 * @param   pinNumber:   number of the pin
 * @param   mode:   pin's mode
 * @return    1 if the pin supports the mode, 0 if not
 */
unsigned char HAL_PinSupportsMode (unsigned char pinNumber, unsigned char mode);

 /*
 * @brief   Returns the current mode of a pin
 * @param   pinNumber:   number of the pin.
 * @return   pin's current mode
 * @PRECONDITION   the system must be initialized with HAL_Init
 */
unsigned char HAL_CurrentMode (unsigned char pinNumber);

/*
 * @brief   Changes a pin's mode
 * @param   pinNumber:   number of the pin
 * @param   mode:   pin's mode
 * @return   nothing
 */
void HAL_ChangePinMode (unsigned char pinNumber, unsigned char mode);

/*
 * @brief   Sets the state of a pin if its configured as output
 * @param   pinNumber:   number of the pin
 * @param   value:   value to be set in the pin
 * @return   nothing
 * @note   If pin's mode is INPUT or ANALOG, or the pin number is out of range, returns 0
 */
void HAL_SetPinValue(unsigned char pinNumber, unsigned char value);

/*
 * @brief   Gets the state of a pin
 * @param   pinNumber:   number of the pin
 * @return   pin's value.
 * @note   If pin's mode is OUTPUT or the pin number is out of range, return = 0
 * @note   for analog channel values use HAL_GetAIChannelValue
 */
unsigned char HAL_GetPinValue(unsigned char pinNumber);

/*
 * @brief   Sets the value of a theoretical 8 bit port
 * @param   portNumber:   number of the port
 * @param   portValue:   port's value.
 * @return   nothing
 */
void HAL_SetDOsPortValue(unsigned char portNumber, unsigned char portValue);

/*
 * @brief   Gets the value of a theoretical 8 bit port
 * @param   portNumber:   number of the port
 * @return  port's value, or -1 if there was no change since the last function call
 * @PRECONDITION   the system must be initialized with HAL_Init
 */
signed short HAL_GetDIPortValue(unsigned char portNumber);

/*
 * @brief   Gets the value of an analog input channel
 * @param   channelNumber:   analog channel number
 * @return   channel's value, or -1 if there was no change since the last function call
 * @PRECONDITION   the system must be initialized with HAL_Init
 */
signed short HAL_GetAIChannelValue(unsigned char channelNumber);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/


#endif /* HAL_H_ */
