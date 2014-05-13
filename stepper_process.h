/*********************************************************************
 *
 *                  EE 4 Project - Code Template
 *
 *********************************************************************
 * FileName:        stepper_process.h
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
 * Jeroen Van Aken      18/02/14    Original.
 ********************************************************************/ 
#ifndef _STEPPER_PROCESS_H
#define _STEPPER_PROCESS_H

/** D E F I N E S ***************************************************/
#define ENABLED_CHANNELS 1
#define CHAN_0_TRIS1	TRISBbits.TRISB0
#define CHAN_0_TRIS2	TRISBbits.TRISB1
#define CHAN_0_TRIS3	TRISBbits.TRISB2
#define CHAN_0_TRIS4	TRISBbits.TRISB3
//#define CHAN_1_TRIS1	TRISBbits.TRISB4
//#define CHAN_1_TRIS2	TRISBbits.TRISB5
//#define CHAN_1_TRIS3	TRISBbits.TRISB6
//#define CHAN_1_TRIS4	TRISBbits.TRISB7

#define CHAN_0_A		LATBbits.LATB0
#define CHAN_0_B		LATBbits.LATB1
#define CHAN_0_C		LATBbits.LATB2
#define CHAN_0_D		LATBbits.LATB3
//#define CHAN_1_A		LATBbits.LATB4
//#define CHAN_1_B		LATBbits.LATB5
//#define CHAN_1_C		LATBbits.LATB6
//#define CHAN_1_D		LATBbits.LATB7

/** I N C L U D E S *************************************************/

/** V A R I A B L E S ***********************************************/


/** P R O T O T Y P E S *********************************************/
void Init_Stepper_Process(void);
void Stepper_Process(void);
void Stepper_Step(char chan,char CW);

#endif
//EOF----------------------------------------------------------------
