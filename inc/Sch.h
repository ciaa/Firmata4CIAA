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

#ifndef _SCH_H_
#define _SCH_H_
/** @brief Brief for this header file.
 **
 ** Full description for this header file.
 **
 **/

/** \addtogroup groupName Group Name
 ** @{ */

/*
 * Initials    Name
 * ---------------------------
 * FN          Full Name
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 FN Initial release.
 */

/*==================[inclusions]=============================================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

// The maximum number of tasks required at any one time during the execution
// of the program
// MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCH_MAX_TASKS (2)

/*==================[typedef]================================================*/

// Store in DATA area, if possible, for rapid access
// Total memory per task is 7 bytes
typedef struct
{
   // Pointer to the task (must be a 'void (void)' function)
   void (* pTask)(void);
   // Delay (ticks) until the function will (next) be run
   // - see SCH_Add_Task() for further details
   int Delay;
   // Interval (ticks) between subsequent runs.
   // - see SCH_Add_Task() for further details
   int Period;
   // Incremented (by scheduler) when task is due to execute
   int RunMe;
} sTask;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

void SCH_Dispatch_Tasks(void);
char SCH_Add_Task(void (*) (void), const int, const int);
char SCH_Delete_Task(const int);
void SCH_Report_Status(void);


/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _SCH_H_ */
