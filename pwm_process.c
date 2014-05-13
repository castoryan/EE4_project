/*********************************************************************
 *
 *                  EE 4 Project - Code Template
 *
 *********************************************************************
 * FileName:        pwm_process.c
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
 
/** I N C L U D E S *************************************************/
#include <p18cxxx.h>
#include "pwm_process.h"

/** V A R I A B L E S ***********************************************/
unsigned char PWM_counter;
unsigned char PWM_Duty_1;

/** D E C L A R A T I O N S *****************************************/
/********************************************************************
 * Function:        void Init_PWM_Process(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Initializes all output channels for the PWM process
 ********************************************************************/
void Init_PWM_Process() {
	PWM_counter = 0;
	PWM_Duty_1 = 2;
	
	LATBbits.LATB7 = 0;
	TRISBbits.TRISB7 = 0;	
}

/********************************************************************
 * Function:        void PWM_Process(void)
 *
 * PreCondition:    Init_PWM_Process(void)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Process's the PWM information and sets or unsets the
 *					outputs 
 ********************************************************************/
void PWM_Process() {
	if (PWM_counter++ > 10) {
		PWM_counter = 0;
	}

	if (PWM_Duty_1 > PWM_counter) LATBbits.LATB7 = 1;
		else LATBbits.LATB7 = 0;

	//LATBbits.LATB7 = (PWM_Duty_1 > PWM_counter);	
}

//EOF-----------------------------------------------------------------
