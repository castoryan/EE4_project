/*********************************************************************
 *
 *                  EE 4 Project - Code Template
 *
 *********************************************************************
 * FileName:        config.c
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
 * Jeroen Van Aken		21/02/10	Removed Timer from interrupt
 ********************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "config.h"
#include "stepper_process.h"

/** V A R I A B L E S ********************************************************/


/** V E C T O R  R E M A P P I N G *******************************************/
   /****** Remapped Vectors ********************
    *   _____________________
    *   |       RESET       |   0x000000
    *   |      LOW_INT      |   0x000008
    *   |      HIGH_INT     |   0x000018
    *   |       TRAP        |   0x000028
    *   |     Bootloader    |   0x00002E
    *   .                   .
    *   .                   .
    *   |     USER_RESET    |   0x000800
    *   |    USER_LOW_INT   |   0x000808
    *   |    USER_HIGH_INT  |   0x000818
    *   |      USER_TRAP    |   0x000828
    *   |                   |
    *   |   Program Memory  |
    *   .                   .
    *   |___________________|   0x0005FFF
    */

extern void _startup (void);
#pragma code _RESET_INTERRUPT_VECTOR = 0x000800
void _reset (void) {
_asm goto _startup _endasm
}

#pragma code InterruptVectorHigh = 0x0808
void InterruptVectorHigh (void) {
  _asm goto Interrupt_Handler _endasm //jump to interrupt routine
}

#pragma code InterruptVectorLow = 0x0818
void InterruptVectorLow (void) {
  _asm goto Interrupt_Handler _endasm //jump to interrupt routine
}

#pragma interrupt Interrupt_Handler

#pragma code

/** D E C L A R A T I O N S **************************************************/
/******************************************************************************
 * Function:        void Init_Timer_Loop(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Initializes Timer0, tuned to 1 ms, for the sleep loop
 *****************************************************************************/
void Init_Timer_Loop(void) {
	//configure Timer0
	OpenTimer0( TIMER_INT_OFF &			//disable interrupt on Timer0 overflow
				T0_8BIT &				//set Timer0 to 16bit counter
				T0_SOURCE_INT &			//use internal clock source
				T0_PS_1_16 );			//set prescaler to 1:1
}

/******************************************************************************
 * Function:        void Wait(void)
 *
 * PreCondition:    Init_Timer_Loop(void)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Stays in a while loop, doing NOP until Timer0 generates
 *					an overflow
 *****************************************************************************/
void Wait(void) {
	while(!INTCONbits.TMR0IF){Nop()};
	INTCONbits.TMR0IF = 0;
}	

/******************************************************************************
 * Function:        void Interrupt_Handler(void)
 *
 * PreCondition:    GIE need to be set
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        This routine is called whenever an interrupt condition is 
 *					reached
 *****************************************************************************/	
void Interrupt_Handler(void) {
	if(PIR1bits.TMR1IF == 1) {
		Stepper_Process();
		PIR1bits.TMR1IF = 0;
	}
}
 
//EOF-------------------------------------------------------------------------
