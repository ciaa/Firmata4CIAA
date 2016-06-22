/* Copyright Year, Author
 *
 * This file is part of a project.
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
 * FN           Full Name
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1   FN first version
 */

/*==================[inclusions]=============================================*/

#include "Isr.h"
#include "Sch.h"
#include "sAPI.h"       /* <= sAPI */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

static unsigned char schRun = 0;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

// The array of tasks (see Sch.C)

extern sTask SCH_tasks[SCH_MAX_TASKS];

// The error code variable
//
// See Port.H for port on which error codes are displayed
// and for details of error codes
extern char Error_code;

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*------------------------------------------------------------------*-
tickHook() <-- Firmware/modules/sapi_bm/sAPI_Tick.c
-*------------------------------------------------------------------*/
void tickHook(void)
{
   if(schRun){
      SCH_Update();
   }
}

/*------------------------------------------------------------------*-
SCH_Init()
Scheduler initialization function. Prepares scheduler
data structures.
Must call this function before using the scheduler.
-*------------------------------------------------------------------*/
void SCH_Init(void)
{
   char i;
   for (i = 0; i < SCH_MAX_TASKS; i++)
   {
      SCH_Delete_Task(i);
   }
   // Reset the global error variable
   // - SCH_Delete_Task() will generate an error code,
   // (because the task array is empty)
   Error_code = 0;

}

/*------------------------------------------------------------------*-
SCH_Start()
Starts the scheduler, by enabling timer interrupts.
NOTE: Usually called after all regular tasks are added,
to keep the tasks synchronized.
NOTE: ONLY THE SCHEDULER INTERRUPT SHOULD BE ENABLED!!!
-*------------------------------------------------------------------*/
void SCH_Start(void)
{
   schRun = 1;
}


/*------------------------------------------------------------------*-
SCH_Update()
This is the scheduler ISR. It is called at a rate
determined by the timer settings in the 'init' function.
This version is triggered by Timer 2 interrupts:
timer is automatically reloaded.
-*------------------------------------------------------------------*/
void SCH_Update(void)
{
   int Index;

   // NOTE: calculations are in *TICKS* (not milliseconds)
   for (Index = 0; Index < SCH_MAX_TASKS; Index++)
   {
      // Check if there is a task at this location
      if (SCH_tasks[Index].pTask)
      {
         if (SCH_tasks[Index].Delay == 0)
         {
            // The task is due to run
            SCH_tasks[Index].RunMe += 1; // Inc. the 'RunMe' flag
            if (SCH_tasks[Index].Period)
            {
               // Schedule regular tasks to run again
               SCH_tasks[Index].Delay = SCH_tasks[Index].Period;
            }
         }
         else
         {
            // Not yet ready to run: just decrement the delay
            SCH_tasks[Index].Delay -= 1;
         }
      }
   }
}



/** @} doxygen end group definition */
/*==================[end of file]============================================*/
