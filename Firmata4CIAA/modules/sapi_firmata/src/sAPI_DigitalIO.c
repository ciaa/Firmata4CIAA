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

/** @brief Brief for this file.
 **
 **/

/** \addtogroup groupName Group Name
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * ENP          Eric Pernia
 *
 *  */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20150923   v0.0.1   First version
 */

/*==================[inclusions]=============================================*/

#include "chip.h"
/* Specific modules used:
   #include "scu_18xx_43xx.h" for Chip_SCU funtions
   #include "gpio_18xx_43xx.h" for Chip_GPIO functions
*/

#include "sAPI_DataTypes.h"
#include "sAPI_PeripheralMap.h"

#include "sAPI_DigitalIO.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/* ---------- Begin Digital Pin Map EDU-CIAA-NXP ---------- */

const pinConfigDigitalLpc4337_t digitalPinsConfig[] = {
   /*{ {PinNamePortN ,PinNamePinN}, PinFUNC, {GpioPortN, GpioPinN} }*/

   { {4, 1}, FUNC0, {2, 1} },   /*   0   CON1_36   T_FIL1           */
   { {7, 5}, FUNC0, {3,13} },   /*   1   CON1_34   T_COL2           */

   { {1, 5}, FUNC0, {1, 8} },   /*   2   CON1_39   T_COL0           */
   { {4, 2}, FUNC0, {2, 2} },   /*   3   CON1_37   T_FIL2           */
   { {4, 3}, FUNC0, {2, 3} },   /*   4   CON1_35   T_FIL3           */
   { {4, 0}, FUNC0, {2, 0} },   /*   5   CON1_33   T_FIL0           */
   { {7, 4}, FUNC0, {3,12} },   /*   6   CON1_31   T_COL1           */

   { {3, 2}, FUNC4, {5, 9} },   /*   7   CON1_29   CAN_TD           */
   { {3, 1}, FUNC4, {5, 8} },   /*   8   CON1_27   CAN_RD           */

   { {2, 3}, FUNC4, {5, 3} },   /*   9   CON1_25   RS232_TXD        */
   { {2, 4}, FUNC4, {5, 4} },   /*  10   CON1_23   RS232_RXD        */

   { {6,12}, FUNC0, {2, 8} },   /*  11   CON2_40   GPIO8            */
   { {6,11}, FUNC0, {3, 7} },   /*  12   CON2_38   GPIO7            */
   { {6, 9}, FUNC0, {3, 5} },   /*  13   CON2_36   GPIO5            */
   { {6, 7}, FUNC4, {5,15} },   /*  14   CON2_34   GPIO3            */
   { {6, 4}, FUNC0, {3, 3} },   /*  15   CON2_32   GPIO1            */

   { {4, 4}, FUNC0, {2, 4} },   /*  16   CON2_30   LCD1             */
   { {4, 5}, FUNC0, {2, 5} },   /*  17   CON2_28   LCD2             */
   { {4, 6}, FUNC0, {2, 6} },   /*  18   CON2_26   LCD3             */
   { {4, 8}, FUNC4, {5,12} },   /*  19   CON2_24   LCDRS            */
   { {4,10}, FUNC4, {5,14} },   /*  20   CON2_22   LCD4             */

   { {1, 3}, FUNC0, {0,10} },   /*  21   CON2_18   SPI_MISO         */

   { {1,20}, FUNC0, {0,15} },   /*  22   CON2_16   ENET_TXD1        */
   { {1,18}, FUNC0, {0,13} },   /*  23   CON2_14   ENET_TXD0        */
   { {1,17}, FUNC0, {0,12} },   /*  24   CON2_12   ENET_MDIO        */
   { {1,16}, FUNC0, {0, 3} },   /*  25   CON2_10   ENET_CRS_DV      */
   { {7, 7}, FUNC0, {3,15} },   /*  26   CON2_08   ENET_MDC         */
   { {0, 1}, FUNC0, {0, 1} },   /*  27   CON2_06   ENET_TXEN        */
   { {0, 0}, FUNC0, {0, 0} },   /*  28   CON2_04   ENET_RXD1        */

   { {6,10}, FUNC0, {3, 6} },   /*  29   CON2_35   GPIO6            */
   { {6, 8}, FUNC4, {5,16} },   /*  30   CON2_33   GPIO4            */
   { {6, 5}, FUNC0, {3, 4} },   /*  31   CON2_31   GPIO2            */
   { {6, 1}, FUNC0, {3, 0} },   /*  32   CON2_29   GPIO0            */

   { {4, 9}, FUNC4, {5,13} },   /*  33   CON2_23   LCDEN            */

   { {1, 4}, FUNC0, {0,11} },   /*  34   CON2_21   SPI_MOSI         */

   { {1,15}, FUNC0, {0, 2} },   /*  35   CON2_09   ENET_RXD0        */

   { {1, 0}, FUNC0, {0, 4} },   /*  36   TECS_1    TEC1             */
   { {1, 1}, FUNC0, {0, 8} },   /*  37   TECS_2    TEC2             */
   { {1, 2}, FUNC0, {0, 9} },   /*  38   TECS_3    TEC3             */
   { {1, 6}, FUNC0, {1, 9} },   /*  39   TECS_4    TEC4             */

   { {2,10}, FUNC0, {0,14} },   /*  40   LEDS_1    LED1             */
   { {2,11}, FUNC0, {1,11} },   /*  41   LEDS_2    LED2             */
   { {2,12}, FUNC0, {1,12} },   /*  42   LEDS_3    LED3             */
   { {2, 0}, FUNC4, {5, 0} },   /*  43   LEDS_4    LEDR             */
   { {2, 1}, FUNC4, {5, 1} },   /*  44   LEDS_5    LEDG             */
   { {2, 2}, FUNC4, {5, 2} }    /*  45   LEDS_6    LEDB             */
};

/* ----------- End Pin Map EDU-CIAA-NXP ----------- */

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void digitalObtainPinConfig( int8_t pin, int8_t mode, 
                      int8_t *pinNamePort, int8_t *pinNamePin, int8_t *func, 
                      int8_t *gpioPort, int8_t *gpioPin ){

   *pinNamePort = digitalPinsConfig[pin].pinName.port;
   *pinNamePin  = digitalPinsConfig[pin].pinName.pin;
   *func        = digitalPinsConfig[pin].func;
   *gpioPort    = digitalPinsConfig[pin].gpio.port;
   *gpioPin     = digitalPinsConfig[pin].gpio.pin;

}

/*==================[external functions definition]==========================*/

bool_t digitalConfig( int8_t pin, int8_t mode ){

   bool_t ret_val     = 1;

   int8_t pinNamePort = 0;
   int8_t pinNamePin  = 0;

   int8_t func        = 0;

   int8_t gpioPort    = 0;
   int8_t gpioPin     = 0;

   digitalObtainPinConfig( pin, mode, &pinNamePort, &pinNamePin, &func, 
                           &gpioPort, &gpioPin );

   switch(mode){

      case INPUT:
         Chip_SCU_PinMux(
            pinNamePort,
            pinNamePin,
            SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
            func
         );
         Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), INPUT );
      break;

      case INPUT_PULLUP:
         Chip_SCU_PinMux(
            pinNamePort,
            pinNamePin,
            SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
            func
         );
         Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), INPUT );
      break;

      case INPUT_PULLDOWN:
         Chip_SCU_PinMux(
            pinNamePort,
            pinNamePin,
            SCU_MODE_PULLDOWN | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
            func
         );
         Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), INPUT );
      break;
      case INPUT_REPEATER:
         Chip_SCU_PinMux(
            pinNamePort,
            pinNamePin,
            SCU_MODE_REPEATER | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
            func
         );
         Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), INPUT );
      break;

      case OUTPUT:
         Chip_SCU_PinMux(
            pinNamePort,
            pinNamePin,
            SCU_MODE_INACT | SCU_MODE_ZIF_DIS,
            func
         );
         Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), OUTPUT );
      break;

      default:
         ret_val = 0;
      break;
   }

   return ret_val;

}


bool_t digitalWrite( int8_t pin, bool_t value ){

   bool_t ret_val     = 1;

   int8_t pinNamePort = 0;
   int8_t pinNamePin  = 0;

   int8_t func        = 0;

   int8_t gpioPort    = 0;
   int8_t gpioPin     = 0;

   digitalObtainPinConfig( pin, OUTPUT, &pinNamePort, &pinNamePin, &func, 
                           &gpioPort, &gpioPin );

   Chip_GPIO_SetPinState( LPC_GPIO_PORT, gpioPort, gpioPin, value);

   return ret_val;
}

bool_t digitalRead( int8_t pin ){

   bool_t ret_val     = OFF;

   int8_t pinNamePort = 0;
   int8_t pinNamePin  = 0;

   int8_t func        = 0;

   int8_t gpioPort    = 0;
   int8_t gpioPin     = 0;

   digitalObtainPinConfig( pin, INPUT, &pinNamePort, &pinNamePin, &func, 
                           &gpioPort, &gpioPin );

   ret_val = (bool_t) Chip_GPIO_ReadPortBit( LPC_GPIO_PORT, gpioPort, gpioPin );

   return ret_val;
}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
