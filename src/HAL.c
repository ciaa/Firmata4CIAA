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


/* Brief:
 * This module connects the 'Pin Map' and several 'Peripheral Maps' so higher layers
 * don't need to know about their configurations
 *
 * Notes:
 * A Pin Map is a list of the available pins, with their possible functions and capabilities.
 * A Peripheral Map, of a certain peripheral, enumerates the peripherals instances and
 * has the information to configure and use them.
 * The difference between is that the Pin Map "re-maps" a set of peripheral maps
 * in order to concentrate the information about several peripherals in 1 single map,
 * whereas a single peripheral map uses microcontroller libraries or registers to
 * actually use the peripherals.
 */


/*==================[inclusions]=============================================*/
#include "sAPI.h"

#include "HAL.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/


/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
/* This map connects the pin names defined in this module with the peripheral
 * names defined in the peripheral modules and tells which modes are not supported */
static const unsigned char pinMap[PIN_TOTALNUMBER][MODES_TOTALNUMBER] =
{
/*Pin name { Input  , Output  , Analog  , PWM  , Servo    } Name in the board*/
/* PIN0 */ { NO_MODE , LEDR , NO_MODE , NO_MODE , NO_MODE }, /* LED R */
/* PIN1 */ { NO_MODE , LEDG , NO_MODE , NO_MODE , NO_MODE }, /* LED G */
/* PIN2 */ { NO_MODE , LEDB , NO_MODE , NO_MODE , NO_MODE }, /* LED B */
/* PIN3 */ { NO_MODE , LED1 , NO_MODE , PWM7 , NO_MODE }, /* LED 1 */
/* PIN4 */ { NO_MODE , LED2 , NO_MODE , PWM8 , NO_MODE }, /* LED 2 */
/* PIN5 */ { NO_MODE , LED3 , NO_MODE , PWM9 , NO_MODE }, /* LED 3 */
/* PIN6 */ { TEC1 , NO_MODE , NO_MODE , NO_MODE , NO_MODE }, /* TEC 1 */
/* PIN7 */ { TEC2 , NO_MODE , NO_MODE , NO_MODE , NO_MODE }, /* TEC 2 */
/* PIN8 */ { TEC3 , NO_MODE , NO_MODE , NO_MODE , NO_MODE }, /* TEC 3 */
/* PIN9 */ { TEC4 , NO_MODE , NO_MODE , NO_MODE , NO_MODE }, /* TEC 4 */
/* PIN10 */ { DIO34 , DIO34 , NO_MODE , NO_MODE , NO_MODE }, /* SPI_MOSI */
/* PIN11 */ { DIO33 , DIO33 , NO_MODE , NO_MODE , NO_MODE }, /* LCD_EN */
/* PIN12 */ { DIO32 , DIO32 , NO_MODE , NO_MODE , NO_MODE }, /* GPIO0 */
/* PIN13 */ { DIO31 , DIO31 , NO_MODE , PWM10 , SERVO8 }, /* GPIO2 */
/* PIN14 */ { DIO30 , DIO30 , NO_MODE , NO_MODE , NO_MODE }, /* GPIO4 */
/* PIN15 */ { DIO29 , DIO29 , NO_MODE , NO_MODE , NO_MODE }, /* GPIO6 */
/* PIN16 */ { DIO11 , DIO11 , NO_MODE , PWM6 , SERVO4 }, /* GPIO8 */
/* PIN17 */ { DIO12 , DIO12 , NO_MODE , NO_MODE , NO_MODE }, /* GPIO7 */
/* PIN18 */ { DIO13 , DIO13 , NO_MODE , NO_MODE , NO_MODE }, /* GPIO5 */
/* PIN19 */ { DIO14 , DIO14 , NO_MODE , NO_MODE , NO_MODE }, /* GPIO3 */
/* PIN20 */ { DIO15 , DIO15 , NO_MODE , NO_MODE , NO_MODE }, /* GPIO1 */
/* PIN21 */ { DIO16 , DIO16 , NO_MODE , NO_MODE , SERVO5 }, /* LCD1 */
/* PIN22 */ { DIO17 , DIO17 , NO_MODE , NO_MODE , SERVO6 }, /* LCD2 */
/* PIN23 */ { DIO18 , DIO18 , NO_MODE , NO_MODE , SERVO7 }, /* LCD3 */
/* PIN24 */ { DIO19 , DIO19 , NO_MODE , NO_MODE , NO_MODE }, /* LCD_RS */
/* PIN25 */ { DIO20 , DIO20 , NO_MODE , NO_MODE , NO_MODE }, /* LCD4 */
/* PIN26 */ { DIO6 , DIO6 , NO_MODE , PWM5 , NO_MODE }, /* T_COL1 */
/* PIN27 */ { DIO5 , DIO5 , NO_MODE , NO_MODE , NO_MODE }, /* T_FIL0 */
/* PIN28 */ { DIO4 , DIO4 , NO_MODE , PWM4 , SERVO3 }, /* T_FIL3 */
/* PIN29 */ { DIO3 , DIO3 , NO_MODE , PWM3 , SERVO2 }, /* T_FIL2 */
/* PIN30 */ { DIO2 , DIO2 , NO_MODE , PWM2 , SERVO1 }, /* T_COL0 */
/* PIN31 */ { DIO0 , DIO0 , NO_MODE , PWM0 , SERVO0 }, /* T_FIL1 */
/* PIN32 */ { DIO1 , DIO1 , NO_MODE , PWM1 , NO_MODE }, /* T_COL2 */
/* PIN33 */ { NO_MODE , NO_MODE , ACH1 , NO_MODE , NO_MODE }, /* CH1 */
/* PIN34 */ { NO_MODE , NO_MODE , ACH2 , NO_MODE , NO_MODE }, /* CH2 */
/* PIN35 */ { NO_MODE , NO_MODE , ACH3 , NO_MODE , NO_MODE }, /* CH3 */
};

static const unsigned char defaultPinModes[PIN_TOTALNUMBER] =
{
/* PIN0 */   OUTPUT_MODE,
/* PIN1 */   OUTPUT_MODE,
/* PIN2 */   OUTPUT_MODE,
/* PIN3 */   OUTPUT_MODE,
/* PIN4 */   OUTPUT_MODE,
/* PIN5 */   OUTPUT_MODE,
/* PIN6 */   INPUT_MODE,
/* PIN7 */   INPUT_MODE,
/* PIN8 */   INPUT_MODE,
/* PIN9 */   INPUT_MODE,
/* PIN10 */   OUTPUT_MODE,
/* PIN11 */   OUTPUT_MODE,
/* PIN12 */   OUTPUT_MODE,
/* PIN13 */   OUTPUT_MODE,
/* PIN14 */   OUTPUT_MODE,
/* PIN15 */   OUTPUT_MODE,
/* PIN16 */   OUTPUT_MODE,
/* PIN17 */   OUTPUT_MODE,
/* PIN18 */   OUTPUT_MODE,
/* PIN19 */   OUTPUT_MODE,
/* PIN20 */   OUTPUT_MODE,
/* PIN21 */   OUTPUT_MODE,
/* PIN22 */   OUTPUT_MODE,
/* PIN23 */   OUTPUT_MODE,
/* PIN24 */   OUTPUT_MODE,
/* PIN25 */   OUTPUT_MODE,
/* PIN26 */   OUTPUT_MODE,
/* PIN27 */   OUTPUT_MODE,
/* PIN28 */   OUTPUT_MODE,
/* PIN29 */   OUTPUT_MODE,
/* PIN30 */   OUTPUT_MODE,
/* PIN31 */   OUTPUT_MODE,
/* PIN32 */   OUTPUT_MODE,
/* PIN33 */   ANALOG_MODE,
/* PIN34 */   ANALOG_MODE,
/* PIN35 */   ANALOG_MODE
};

/* Save the current mode of the available pins */
static unsigned char currentPinModes[PIN_TOTALNUMBER] =
{
/* PIN0 */   NO_MODE,
/* PIN1 */   NO_MODE,
/* PIN2 */   NO_MODE,
/* PIN3 */   NO_MODE,
/* PIN4 */   NO_MODE,
/* PIN5 */   NO_MODE,
/* PIN6 */   NO_MODE,
/* PIN7 */   NO_MODE,
/* PIN8 */   NO_MODE,
/* PIN9 */   NO_MODE,
/* PIN10 */   NO_MODE,
/* PIN11 */   NO_MODE,
/* PIN12 */   NO_MODE,
/* PIN13 */   NO_MODE,
/* PIN14 */   NO_MODE,
/* PIN15 */   NO_MODE,
/* PIN16 */   NO_MODE,
/* PIN17 */   NO_MODE,
/* PIN18 */   NO_MODE,
/* PIN19 */   NO_MODE,
/* PIN20 */   NO_MODE,
/* PIN21 */   NO_MODE,
/* PIN22 */   NO_MODE,
/* PIN23 */   NO_MODE,
/* PIN24 */   NO_MODE,
/* PIN25 */   NO_MODE,
/* PIN26 */   NO_MODE,
/* PIN27 */   NO_MODE,
/* PIN28 */   NO_MODE,
/* PIN29 */   NO_MODE,
/* PIN30 */   NO_MODE,
/* PIN31 */   NO_MODE,
/* PIN32 */   NO_MODE,
/* PIN33 */   NO_MODE,
/* PIN34 */   NO_MODE,
/* PIN35 */   NO_MODE
};


/*==================[external data definition]===============================*/
/* Mode resolutions. These are:
 * 0 = Input Mode resolution
 * 1 = Output Mode resolution
 * 2 = Analog Mode resolution
 * 3 = pwm Mode resolution
 * 4 = Servo Mode resolution
 */
const unsigned char modeResolutions[MODES_TOTALNUMBER]=
{
   0x01,0x01,0x0A,0x08,0x08
};
/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*
 * @brief   Initialize all pins with their default mode and enables peripherals
 * @param   none
 * @return   nothing
 */
void HAL_Init(void)
{
   unsigned char pinNumber=0;
   boardInit(); /* From sAPI_Board */

   for(pinNumber = FIRST_PIN;pinNumber<LAST_PIN;pinNumber++)
   {
      HAL_ChangePinMode(pinNumber,defaultPinModes[pinNumber]);
   }
   /* Initialize servo peripheral */
   servoConfig();
   /* Initialize pwm peripheral */
   pwmConfig();
   /* Initialize ADC peripheral */
   analogConfig(ON);
}

/*
 * @brief   Get the resolution of a given mode
 * @param   mode:   mode to get the resolution from
 * @return   mode's resolution
 */
unsigned char HAL_ModeResolution (unsigned char mode)
{
   return (modeResolutions[mode]);
}

/*
 * @brief   Checks if the pin can be configured with a certain mode
 * @param   pinNumber:   number of the pin
 * @param   mode:   pin's mode
 * @return    1 if the pin supports the mode, 0 if not
 */
unsigned char HAL_pinSupportsMode (unsigned char pinNumber, unsigned char mode)
{
   return (pinMap[pinNumber][mode]!=NO_MODE);
}

 /*
 * @brief   Returns the current mode of a pin
 * @param   pinNumber:   number of the pin.
 * @return   pin's current mode
 * @PRECONDITION   the system must be initialized with HAL_Init
 */
unsigned char HAL_CurrentMode (unsigned char pinNumber)
{
   return (currentPinModes[pinNumber]);
}

/*
 * @brief   Changes a pin's mode
 * @param   pinNumber:   number of the pin
 * @param   mode:   pin's mode
 * @return   nothing
 */
void HAL_ChangePinMode (unsigned char pinNumber, unsigned char mode)
{
   if(currentPinModes[pinNumber]!=mode)
   {
      switch(mode)
      {
         case INPUT_MODE:
            digitalConfig(pinMap[pinNumber][INPUT_MODE],INPUT_MODE);
            break;
         case OUTPUT_MODE:
            if(servoIsAttached(pinMap[pinNumber][SERVO_MODE]))
               {servoDetach(pinMap[pinNumber][SERVO_MODE]);}
            if(pwmIsAttached(pinMap[pinNumber][PWM_MODE]))
               {pwmDetach(pinMap[pinNumber][PWM_MODE]);}
            digitalConfig(pinMap[pinNumber][OUTPUT_MODE],OUTPUT_MODE);
            break;
         /* case ANALOG_MODE:
            There is no need to change to analog mode since the analog pins
            only support that mode, and they are always enabled that way
            break; */
         case PWM_MODE:
            pwmAttach(pinMap[pinNumber][PWM_MODE]);
            break;
         case SERVO_MODE:
            if(pwmIsAttached(pinMap[pinNumber][PWM_MODE]))
            {
               pwmDetach(pinMap[pinNumber][PWM_MODE]);
               /* This is a necessary step since the transition from pwm to servo fails */
               digitalConfig(pinMap[pinNumber][OUTPUT_MODE],OUTPUT_MODE);
            }
            servoAttach(pinMap[pinNumber][SERVO_MODE]);
            break;
         default:
            /* Error: The given mode is incorrect. Do nothing */
            break;
      }
      /* Update mode in the current pin mode list */
      currentPinModes[pinNumber] = mode;
   }
}

/*
 * @brief   Sets the state of a pin if its configured as output
 * @param   pinNumber:   number of the pin
 * @param   value:   value to be set in the pin
 * @return   nothing
 * @note   If pin's mode is INPUT or ANALOG, or the pin number is out of range, returns 0
 */
void HAL_SetPinValue(unsigned char pinNumber, unsigned char value)
{
   switch(currentPinModes[pinNumber])
   {
   case OUTPUT_MODE:
      digitalWrite(pinMap[pinNumber][OUTPUT_MODE],value);
      break;

   case PWM_MODE:
      pwmWrite(pinMap[pinNumber][PWM_MODE],value);
      break;

   case SERVO_MODE:
   servoWrite(pinMap[pinNumber][SERVO_MODE],value);
      break;

   /* case ANALOG_MODE:
      TODO: This should write the value to the DAC
      break; */

   default:
      /* Error: The given mode is incorrect. Do nothing */
      break;
   }
}

/*
 * @brief   Gets the state of a pin
 * @param   pinNumber:   number of the pin
 * @return   pin's value.
 * @note   If pin's mode is OUTPUT or the pin number is out of range, return = 0
 * @note   for analog channel values use HAL_GetAIChannelValue
 */
unsigned char HAL_GetPinValue(unsigned char pinNumber)
{
   unsigned char pinValue = 0;
   switch(currentPinModes[pinNumber])
   {
   case INPUT_MODE:
      pinValue = digitalRead(pinMap[pinNumber][INPUT_MODE]);
      break;

   case ANALOG_MODE:
      pinValue = 0x00;
      break;

   case SERVO_MODE:
      servoRead(pinMap[pinNumber][SERVO_MODE]);
      break;


   case PWM_MODE:
      /* TODO: to be tested */
      pwmRead(pinMap[pinNumber][PWM_MODE]);
      break;

   default:
      /* Error: The given mode is incorrect. Do nothing */
      break;
   }
   return (pinValue);
}

/*
 * @brief   Sets the value of a theoretical 8 bit port
 * @param   portNumber:   number of the port
 * @param   portValue:   port's value.
 * @return   nothing
 */
void HAL_SetDOsPortValue(unsigned char portNumber, unsigned char portValue)
{
   unsigned char i=0,portNumx8=portNumber*8, pinNumber = 0;
   for(i=0;i<8;i++)
   {
      pinNumber = i+portNumx8;
      if(pinNumber < PIN_TOTALNUMBER)
      {
         /* using HAL_SetPinValue here will make things slower */
         digitalWrite(pinMap[pinNumber][OUTPUT_MODE],(portValue>>i)&0x1);
      }
   }
}

/*
 * @brief   Gets the value of a theoretical 8 bit port
 * @param   portNumber:   number of the port
 * @return  port's value, or -1 if there was no change since the last function call
 * @PRECONDITION   the system must be initialized with HAL_Init
 */
signed short HAL_GetDIPortValue(unsigned char portNumber)
{
   static signed short portValAnt[16]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
   signed short portVal=0;
   unsigned char i=0, portNumx8=portNumber*8, pinState=0, pinNumber = 0;

   for(i=0;i<8;i++)
   {
      pinNumber = i+portNumx8;
      /* Because PIN_TOTALNUMBER is not necessarily multiple of 8, the pin number
      * must be checked to avoid problems.
      * i.e: HAL_GetPinState(PIN_TOTALNUMBER+1) should not return a value
      * because you cannot get the state of a non existent PIN */
      if(pinNumber<PIN_TOTALNUMBER)
      {
         pinState = HAL_GetPinValue(pinNumber);
      }
	  /* else, pinState = 0, the initialized value */
      if(pinState)
      {
         portVal |= 1<<i;
      }
      else
      {
         portVal &= ~(1<<i);
      }
   }
   if(portVal == portValAnt[portNumber])
   {
      portVal=-1;
   }
   else
   {
      portValAnt[portNumber] = portVal;
   }
   return (portVal);
}

/*
 * @brief   Gets the value of an analog input channel
 * @param   channelNumber:   analog channel number
 * @return   channel's value, or -1 if there was no change since the last function call
 * @PRECONDITION   the system must be initialized with HAL_Init
 */
signed short HAL_GetAIChannelValue(unsigned char channelNumber)
{
   static signed short channelValAnt[16]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
   signed short channelVal=0;
   unsigned char pinNumber = channelNumber + LAST_DIGITAL_PIN + 1;
   /* fixme: this is not automated. It only works if the analog pins come before the digital pins
   NOT if they are in the middle of the pin list */

   if((pinNumber<PIN_TOTALNUMBER) && (currentPinModes[pinNumber] == ANALOG_MODE))
   {
      channelVal = analogRead(pinMap[pinNumber][ANALOG_MODE]);
   }
   /* else, pinState = 0, the initialized value */
   if(channelVal == channelValAnt[channelNumber])
   {
      channelVal=-1;
   }
   else
   {
      channelValAnt[channelNumber] = channelVal;
   }

   return (channelVal);
}
/*==================[end of file]============================================*/
