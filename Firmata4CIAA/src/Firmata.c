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

/*Brief:
 * This module's purpose is to answer, through the Uart peripheral, the questions asked
 * by an external Application which uses the Firmata Protocol.
 * Because of this, this module only knows the messages and responses of the protocol in order
 * to establish a communication, while peripheral management is delegated to another module,
 * the HAL module, to make this one portable across different applications.
 */

/*==================[inclusions]=============================================*/
#include "stdint.h"
#include "Firmata.h"
#include "HAL.h"

/*==================[macros and definitions]=================================*/

/* Define Boolean Data Type */
typedef uint8_t bool_t;

#ifndef TRUE
   #define TRUE   1
#endif
#ifndef FALSE
   #define FALSE  0
#endif


/*-------------------Firmata command messages--------------------*/
/* Source: http://www.firmata.org/wiki/V2.3ProtocolDetails
 * Version numbers for the protocol.  The protocol is still changing, so these
 * version numbers are important.  This number can be queried so that host
 * software can test whether it will be compatible with the currently
 * installed firmware. */
#define FIRMATA_MAJOR_VERSION   2 /* for non-compatible changes */
#define FIRMATA_MINOR_VERSION   3 /* for backwards compatible changes */

#define MAX_DATA_BYTES   32 /* max number of data bytes in non-Sysex messages */

/* Message Types (128-255/0x80-0xFF) */
/* Data Messages */
#define DIGITAL_MESSAGE   0x90 /* send data for a digital pin */
#define ANALOG_MESSAGE   0xE0 /* send data for an analog pin (or PWM). Max pin=15 */
/* Control Messages */
#define REPORT_ANALOG   0xC0 /* enable analog input by pin # */
#define REPORT_DIGITAL   0xD0 /* enable digital input by port pair */
#define SET_PIN_MODE   0xF4 /* set a pin to INPUT/OUTPUT/PWM/etc */
/* Protocol Version */
#define REPORT_VERSION   0xF9 /* report protocol version */
/* System Reset */
#define SYSTEM_RESET   0xFF /* reset from MIDI */
/* Sysex Messages */
#define START_SYSEX   0xF0 /* start a MIDI Sysex message */
#define END_SYSEX   0xF7 /* end a MIDI Sysex message */

/* Sysex Command Messages (0-127/0x00-0x7F) */
/* 0x00-0x0F reserved for user-defined commands */
#define ANALOG_MAPPING_QUERY   0x69 /* ask for mapping of analog to pin numbers */
#define ANALOG_MAPPING_RESPONSE   0x6A /* reply with mapping info */
#define CAPABILITY_QUERY   0x6B /* ask for supported modes and resolution of all pins */
#define CAPABILITY_RESPONSE   0x6C /* reply with supported modes and resolution */
#define PIN_STATE_QUERY   0x6D /* ask for a pin's current mode and value */
#define PIN_STATE_RESPONSE   0x6E /* reply with pin's current mode and value */
#define EXTENDED_ANALOG   0x6F /* analog write (PWM, Servo, etc) to any pin */
#define SERVO_CONFIG   0x70 /* set max angle, minPulse, maxPulse, freq */
#define STRING_DATA   0x71 /* a string message with 14-bits per char */
#define SHIFT_DATA   0x75 /* a bitstream to/from a shift register */
#define I2C_REQUEST   0x76 /* send an I2C read/write request */
#define I2C_REPLY   0x77 /* a reply to an I2C read request */
#define I2C_CONFIG   0x78 /* config I2C settings such as delay times and power pins */
#define REPORT_FIRMWARE   0x79 /* report name and version of the firmware */
#define SAMPLING_INTERVAL   0x7A /* set the poll rate of the main loop */
#define SYSEX_NON_REALTIME   0x7E /* MIDI Reserved for non-realtime messages */
#define SYSEX_REALTIME   0x7F /* MIDI Reserved for realtime messages */


/*==================[internal data declaration]==============================*/
/* Firmware name: Firmata.c */
const uint8_t REPORT_FIRMWARE_MSG[] = {0x46,0x00,0x69,0x00,0x72,0x00,0x6D,0x00,0x61,0x00,0x74,0x00,0x61,0x00,0x2E,0x00,0x63,0x00};

static bool_t gFirstTime_flag = TRUE;
static bool_t gReportDigital_flag = FALSE;
static bool_t gReportAnalog_flag = FALSE;

/*==================[internal functions declaration]=========================*/
/*---- Protocol related functions ----*/
static void startSysex(void);
static void endSysex(void);

static void printFirmwareVersion(void);
static void printVersion(void);
static void printAnalogMappingResponse(void);
static void printCapabilityResponse(void);
static void printPinStateResponse(void);

/*---- Data handling functions ----*/
static void sendUint16AsTwo7bitBytes(uint16_t);
static uint8_t dataMessagesTo8bitsByte(uint8_t , uint8_t);

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
/*---- Protocol related functions ----*/
/* Prints the message 'Start Sysex' (0xF0) */
static void startSysex(void)
{
   uartWrite(START_SYSEX);
}

/* Prints the message 'End Sysex' (0xF7) */
static void endSysex(void)
{
   uartWrite(END_SYSEX);
}

/* Prints the name of the file (Firmata.c) and the protocol version */
static void printFirmwareVersion(void)
{
   startSysex();
   uartWrite(REPORT_FIRMWARE);
   uartWrite(FIRMATA_MAJOR_VERSION);
   uartWrite(FIRMATA_MINOR_VERSION);
   uartWriteString(REPORT_FIRMWARE_MSG, sizeof(REPORT_FIRMWARE_MSG));
   endSysex();

   /* Reset global variables */
   gFirstTime_flag = TRUE;
   gReportDigital_flag = FALSE;
   gReportAnalog_flag = TRUE;
}

/* Prints the protocol version */
static void printVersion(void)
{
   uartWrite(REPORT_VERSION);
   uartWrite(FIRMATA_MAJOR_VERSION);
   uartWrite(FIRMATA_MINOR_VERSION);
}

/* Analog Mapping Response (0x6A)
 * The analog mapping query provides the information about which pins
 * correspond to the analog channels
 * Message structure:
 * First Byte - START_SYSEX (0xF0)
 * Second Byte - analog mapping response (0x6A)
 * For each pin (one byte for each pin):
 *      127 = 0x7F if the pin does not support analog
 *      or the analog channel corresponding to pin (which go from 00 to 0F)
 * Last Byte - END_SYSEX (0xF7)
 */
static void printAnalogMappingResponse(void)
{
   uint8_t pinNumber=0,analogChannel=0;
   startSysex();
   uartWrite(ANALOG_MAPPING_RESPONSE);

   for(pinNumber=FIRST_PIN; pinNumber<LAST_PIN;pinNumber++)
   {
      if(HAL_pinSupportsMode(pinNumber,ANALOG_MODE))
      {
		 /* Analog channels can only be 0-15, so chop higher bits */
         uartWrite(analogChannel & 0x0F);
         analogChannel++;
      }
      else
      {
         uartWrite(0x7F);
      }
   }
   endSysex();
}

/* Capability Response (0x6C)
 * The capabilities query provides a list of all modes supported by all pins,
 * and the resolution used by each mode.
 * Supported modes: 00 = Input; 01 = Output; 02= Analog; 03= Pwm; 04=Servo; 06=I2C
 * Message structure:
 * First Byte - START_SYSEX (0xF0)
 * Second Byte - capability response (0x6C)
 * For each pin:
 *    - first mode supported of the pin
 *    - resolution of the first mode
 *    - Second mode supported of the pin
 *    - resolution of the second mode
 *    - .... etc
 *    - 0x7F to mark the end of the pin's modes.
 * Last Byte - END_SYSEX (0xF7)
 */
static void printCapabilityResponse(void)
{
   uint8_t pinNumber=0,mode=0;
   startSysex();
   uartWrite(CAPABILITY_RESPONSE);

   for(pinNumber=FIRST_PIN; pinNumber<LAST_PIN;pinNumber++)
   {
      for(mode=0;mode<MODES_TOTALNUMBER;mode++)
      {
         if(HAL_pinSupportsMode(pinNumber,mode))
         {
            uartWrite(mode);
            uartWrite(HAL_ModeResolution(mode));
         }
      }
      uartWrite(0x7F);
   }
   endSysex();
}

/* Pin State Response (0x6E)
 * The pin state query allows the GUI to read the current configuration of any pin.
 * Message structure:
 * For each pin:
 * First Byte - START_SYSEX (0xF0)
 * Second Byte - Pin State Response (0x6E)
 * Third Byte - Pin number (0 to 127 = 0x7F)
 * Fourth Byte - default pin mode
 * Fifth Byte - pin state
 * Last Byte - END_SYSEX (0xF7)
 * NOTE: despite the fact that the sender asks the pin state query for each pin
 * (ie: F0 6D 00 F7 ... F0 6D n F7), each message can't be answer individually because
 * while answering the first query, all others will be lost. That's why this message
 * is answered 2-3 times with all the pins and Firmata Test seems to load the values several times.
 * To solve this a flag (gFirstTime_flag) is set when the pin state response has already been received
 */
static void printPinStateResponse(void)
{
   uint8_t pinNumber=0;
   if(gFirstTime_flag)
   {
      for(pinNumber=FIRST_PIN; pinNumber<LAST_PIN;pinNumber++)
      {
         startSysex();
         uartWrite(PIN_STATE_RESPONSE);
         uartWrite(pinNumber);
         uartWrite(HAL_CurrentMode(pinNumber));
         uartWrite(HAL_GetPinValue(pinNumber));
         endSysex();
      }
      gFirstTime_flag = FALSE;
   }
}

/*---- Data handling functions ----*/
/* Sends the 16 bit value to the UART by dividing it into 2 MIDI formated bytes (MSB = 0)*/
static void sendUint16AsTwo7bitBytes(uint16_t valueToSend)
{
   uartWrite(valueToSend & 0b01111111);	/* LSB */
   uartWrite(valueToSend>>7 & 0b01111111); /* MSB */
}

/* Converts the first and second data message bytes, received after an analog (E0~EF) or
 * digital (90~9F) message, into a single byte. MIDI protocol uses them this way:
 *   	 1st Byte (LSB)			|		 2nd Byte(MSB)				|		Address Byte
 *   0 x6 x5 x4 x3 x2 x1 x0		|	  0 y6 y5 y4 y3 y2 y1 y0		|	y0 x6 x5 x4 x3 x2 x1 x0
 */
static uint8_t dataMessagesTo8bitsByte(uint8_t byte1, uint8_t byte2)
{
   uint8_t portValue;
   portValue = ((byte2 << 7) & 0b10000000) | (byte1 & 0b01111111);
   return (portValue);
}


/*==================[external functions definition]==========================*/

/*
 * @brief   Sends the updated digital and analog inputs values to the client
 *   Updated because if the values are the same as before, they are not sended
 * @param   none
 * @return   nothing
 * @note   This function should be called periodically (e.g. 100ms)
 */
void Firmata_InputsUpdateTask( void  )
{
   uint8_t address = 0;
   int16_t value=0;

   /* Send digital ports data if digital data reporting was enabled */
   if(gReportDigital_flag)
   {
      for (address=0;address < DIGITALPORT_TOTALNUMBER;address++)
      {
         value = HAL_GetDIPortValue(address);	/* Get digital port value */
         if(value!=-1)
         {
            uartWrite(DIGITAL_MESSAGE | (address & 0x0F));
            sendUint16AsTwo7bitBytes((uint16_t)value);
         }
      }
   }

   /* Send analog channels data if analog data reporting was enabled */
   if(gReportAnalog_flag)
      {
      for (address=0;address < ANALOGCHANNEL_TOTALNUMBER;address++)
      {
         value=HAL_GetAIChannelValue(address);	/* Get analog value */
         if(value!=-1)
         {
            uartWrite(ANALOG_MESSAGE | (address & 0x0F));
            sendUint16AsTwo7bitBytes((uint16_t)value);
         }
      }
   }
}


/*
 * @brief   Decodes the messages received from the client and
 *   actuates accordingly
 * @param   none
 * @return   nothing
 * @note   This function should be called periodically (e.g. 10ms)
 */
void Firmata_UpdateTask( void )
{
   uint8_t receivedByte=0, receivedByteTemp=0 ,portBinanyValue=0, dataMessageAddress = 0,  dataMessageByte1 = 0,  dataMessageByte2 = 0;

   receivedByte = uartRead();
   receivedByteTemp = receivedByte;
   /* Because non-sysex messages are 90, C0, D0 and E0, and they can go from 0 to F
    * (90~9F ; C0~CF ; D0~DF ; E0~EF) the 4 LSB must be removed in order to check if
    *  the message is correct with the switch case  */
   if(receivedByteTemp < 0xF0)
   {
      receivedByteTemp &= 0b11110000;
   }

   switch(receivedByteTemp)
   {
      /* SySex Message handling */
      case (START_SYSEX):
         receivedByte = uartRead();	/* get the SySex command */
         switch (receivedByte)
         {
            case (REPORT_FIRMWARE):
               printFirmwareVersion();
               break;

            case (ANALOG_MAPPING_QUERY):
               printAnalogMappingResponse();
               break;

            case (CAPABILITY_QUERY):
               printCapabilityResponse();
               break;

            case (PIN_STATE_QUERY):
               printPinStateResponse();
               break;

            case(EXTENDED_ANALOG):
            /* This message has variable length. Its made by F0 6F 'pin' 'message' 7F
             * "pin" can go from 0x10 (16) to 0x7F(127)
             * "message" can go from 0x00 - 0x7F (only 1 byte), to 0x00 0x01 - 0x7F 0x01 (2 bytes) */
               dataMessageAddress = uartRead();	/* Pin number. From 0x10(16) to 0xFF(255) */
               dataMessageByte1 = uartRead();
               dataMessageByte2 = uartRead();
               /* There is a problem in the sender. When firstByte <= 127,
			    * the second byte is 0xF7 (END_SYSEX) and the message has goes from 0 to 127.
                * But when firstByte = 127+1, the sender sends firstByte = 0
				* (because the MSB in MIDI is always 0) and secondByte = 0xF7,
			    * which is the same as if the real received byte was 0.
                * In other words, 0 and 128 are treated the same way because the SENDER does not distinguish them */
               if(dataMessageByte2 == END_SYSEX)
               {
                  dataMessageByte2=0x00;
               }
               portBinanyValue = dataMessagesTo8bitsByte(dataMessageByte1,dataMessageByte2);
               HAL_SetPinValue(dataMessageAddress,portBinanyValue);
               break;
         }
         break;

      /* Protocol Version request handling  */
      case (REPORT_VERSION):
         printVersion();
         break;

      /* Data Message handling */
      case (DIGITAL_MESSAGE):
         /* Get the 4 LSB, which contains information about the port that has to be changed */
         dataMessageAddress = (receivedByte & 0b00001111); /* Port number, from 0x00 (0) to 0x0F (15) */
         dataMessageByte1 = uartRead(); /* digital pins 0-6 bitmask */
         dataMessageByte2 = uartRead(); /* digital pin 7 bitmask */
         portBinanyValue = dataMessagesTo8bitsByte(dataMessageByte1,dataMessageByte2);
         /* Till this point we have 0x9X (dataMessageAddress, where X is the port number),
          * and 0xY (portBinanyValue), which is an 8 bit byte containing ones where the pin
          * should be set.
          * eg: 0x91 0x05 (0b00000101) = port 1, bit 1 and 3 to ON
          *(PIN equivalent for HAL = port*8 + bit) */
         HAL_SetDOsPortValue(dataMessageAddress,portBinanyValue);
         break;

      case (ANALOG_MESSAGE):
         /* For pin number >15 see the EXTENDED_ANALOG message */

         dataMessageAddress = (receivedByte & 0b00001111);	/* pin number, from 0x00(0) to 0x0F(15) */
         dataMessageByte1 = uartRead();
         dataMessageByte2 = uartRead();

         portBinanyValue = dataMessagesTo8bitsByte(dataMessageByte1,dataMessageByte2);

         HAL_SetPinValue(dataMessageAddress,portBinanyValue);
         break;


      /* Control Message handling */
      case(SET_PIN_MODE):
         receivedByte = uartRead();	/* pin number */
         receivedByteTemp = uartRead();  /* Pin mode */
         HAL_ChangePinMode(receivedByte,receivedByteTemp);
         break;
	  
      case(REPORT_DIGITAL):
	     gReportDigital_flag = TRUE;
	     break;
		 
      case(REPORT_ANALOG):
	     gReportAnalog_flag = TRUE;
	     break;

   }
}

/*==================[end of file]============================================*/


