/*********************************************************************
 *
 *                  EE 4 Project - Code Template
 *
 *********************************************************************
 * FileName:        pwm_process.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30+
 * Company:         KULeuven - GROUPT
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Jeroen Van Aken      11/03/08    Original.
 ********************************************************************/
#ifndef _PWM_PROCESS_H
#define _PWM_PROCESS_H

/** V A R I A B L E S ***********************************************/
extern unsigned char PWM_Duty_1;

/** P R O T O T Y P E S *********************************************/
void Init_PWM_Process(void);
void PWM_Process(void);

#endif
//EOF-----------------------------------------------------------------
