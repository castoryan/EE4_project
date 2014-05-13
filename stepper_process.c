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
/** I N C L U D E S *************************************************/
#include "stepper_process.h"
#include <timers.h>
#include <p18cxxx.h>

/** V A R I A B L E S ***********************************************/
struct stepper_status {
	enum {STOP, GO_CW, GO_CCW} status;
	unsigned char sequence;
};

static struct stepper_status stepper[ENABLED_CHANNELS];

/** D E C L A R A T I O N S *****************************************/
/********************************************************************
 * Function:        void Init_Stepper_Process(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Initializes all output channels for the stepper process
 ********************************************************************/
void Init_Stepper_Process() {
	int i;
	for (i=0;i<=ENABLED_CHANNELS-1;i++) {
		stepper[i].status = STOP;
		stepper[i].sequence = 0x00;
	}
	CHAN_0_TRIS1 = 0;
	CHAN_0_TRIS2 = 0;
	CHAN_0_TRIS3 = 0;
	CHAN_0_TRIS4 = 0;
//	CHAN_1_TRIS1 = 0;
//	CHAN_1_TRIS2 = 0;
//	CHAN_1_TRIS3 = 0;
//	CHAN_1_TRIS4 = 0;
	OpenTimer1( TIMER_INT_ON 	&
            	T1_16BIT_RW 	&
				T1_SOURCE_INT 	&
				T1_PS_1_1		&
				T1_OSC1EN_OFF	&
				T1_SYNC_EXT_OFF );
	INTCONbits.GIE = 1;
	INTCONbits.PEIE = 1;
}

/********************************************************************
 * Function:        void Stepper_Process(void)
 *
 * PreCondition:    Init_Stepper_Process(void)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Process's the stepper information and sets or unsets the
 *					outputs 
 ********************************************************************/
void Stepper_Process() {
	int i;
	for (i=0;i<ENABLED_CHANNELS;i++) {
		if (stepper[i].status == GO_CW) {
			if (stepper[i].sequence == 0x00) {
				stepper[i].sequence	= 0x06;
			} else if (stepper[i].sequence == 0x60) {
				stepper[i].sequence	= 0x00;
				stepper[i].status == STOP;
			} else {
				stepper[i].sequence <<= 1;	
			}
		} else if (stepper[i].status == GO_CCW) {
			if (stepper[i].sequence == 0x00) {
				stepper[i].sequence	= 0x60;
			} else if (stepper[i].sequence == 0x06) {
				stepper[i].sequence	= 0x00;
				stepper[i].status == STOP;
			} else {
				stepper[i].sequence >>= 1;
			}
		}
	}

	CHAN_0_A = (stepper[0].sequence & 0x04) > 0;
	CHAN_0_B = (stepper[0].sequence & 0x08) > 0;
	CHAN_0_C = (stepper[0].sequence & 0x10) > 0;
	CHAN_0_D = (stepper[0].sequence & 0x20) > 0;	
//	CHAN_1_A = (stepper[1].sequence & 0x04) > 0;
//	CHAN_1_B = (stepper[1].sequence & 0x08) > 0;
//	CHAN_1_C = (stepper[1].sequence & 0x10) > 0;
//	CHAN_1_D = (stepper[1].sequence & 0x20) > 0;
	WriteTimer1(0x4000);
}

/********************************************************************
 * Function:        void Stepper_Step(char channel, char CW)
 *
 * PreCondition:    Init_Stepper_Process(void)
 *
 * Input:           char channel :	number indicating the output channel
 *					char CW :		1 for turning clock wise, 0 for turning counter clock wise
 *
 * Output:          None
 *
 * Overview:        Process's the stepper information and sets or unsets the
 *					outputs 
 ********************************************************************/
void Stepper_Step(char chan, char CW) {
	if (chan >= 0 && chan <= ENABLED_CHANNELS ) {
		if (stepper[chan].status == STOP) {
			if(CW == 1) {
				stepper[chan].status = GO_CW;
			} else {
				stepper[chan].status = GO_CCW;
			}
		}
	}
}

//EOF-----------------------------------------------------------------
