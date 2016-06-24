/* Copyright 2016, Ian Olivieri <ianolivieri93@gmail.com>
 * All rights reserved.
 *
 * This file is part of Firmata4CIAA program.
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

/*==================[inclusions]=============================================*/

#include "stdint.h"

#include "Isr.h"
#include "Sch.h"
#include "Firmata.h"
#include "HAL.h"

#include "sAPI_Uart.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
void uartUpdateTask(void);
void uartEchoTask(void);
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
int main(void)
{
   // Inicializacion del hardware
   HAL_Init();

   //Inicializacion de la UART
   uartConfig(57600);

   // Se inicia al planificador
   SCH_Init();

   // inicializacion de traeas
   // Para agregar mas tareas cambiar #define SCH_MAX_TASKS en Sch.h
   SCH_Add_Task(Firmata_UpdateTask, 0, 10);
   SCH_Add_Task(Firmata_InputsUpdateTask, 1, 100);
   //SCH_Add_Task(uartEchoTask, 1, 10);


   // Inicio el planificador
   SCH_Start();

   // Background tasks
   while(1) {
      //TODO: habria q buscar una manera de que esto no se ejecute SIEMPRE. poner un goto_sleep si hace falta hacer update de la uart o algo asi
      uartUpdateTask();

      // Despacho las tareas
      SCH_Dispatch_Tasks();
   }

   return 0 ;
}

/*The background task is responsible for the uart update*/
void uartUpdateTask(void)
{
   uartRxGatekeeperTask();
   uartTxGatekeeperTask();
}

void uartEchoTask(void)
{
   if (uartCanRead()) //FIXME esto lo debería hacer solo el "uartRead()"
   {
      uartWrite(uartRead());
   }
}

/*==================[external functions definition]==========================*/

/*==================[end of file]============================================*/

