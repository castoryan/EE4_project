/*********************************************************************
 *
 *                  EE 4 Project - Code Template
 *
 *********************************************************************
 * FileName:        adc_process.c
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
 * Jeroen Van Aken		14/03/11	Updated for use of bac3 board
 ********************************************************************/
 
/** I N C L U D E S *************************************************/
#include "adc_process.h"

/** V A R I A B L E S ***********************************************/
char ADCState;
int analogInput_0;
int analogInput_1;
int analogInput_2;
int analogInput_3;
int analogInput_4;

/** D E C L A R A T I O N S *****************************************/
/********************************************************************
 * Function:        void Init_ADC_Process(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Initializes A/D module and input channels
 ********************************************************************/
void Init_ADC_Process() {
	
	TRISAbits.TRISA0 = 1;	//configure AN0 I/O direction
	TRISAbits.TRISA1 = 0;	//configure AN1 I/O direction
	TRISAbits.TRISA2 = 0;	//configure AN2 I/O direction
	TRISAbits.TRISA3 = 0;	//configure AN3 I/O direction
	TRISAbits.TRISA5 = 0;	//configure AN4 I/O direction
	
	OpenADC( ADC_FOSC_64  &		//use internal RC for timing conversion
		 ADC_RIGHT_JUST   &		//right justify the 10bit in a 16bit int
		 ADC_8_TAD,				//wait 8 ADC_OSC before starting conversion
		 ADC_CH0          &		//initially select AD channel 0
		 ADC_INT_OFF      &		//disable interrupts for A/D module
		 ADC_REF_VDD_VSS,		//select Vdd and GND as upper and lower reference
		 ADC_1ANA);				//select number of active ADC channels
								/*
								 * ADC_0ANA    All digital
								 * ADC_1ANA    analog:AN0
								 * ADC_2ANA    analog:AN0-AN1
								 * ADC_3ANA    analog:AN0-AN2
								 * ADC_4ANA    analog:AN0-AN3
								 * ADC_5ANA    analog:AN0-AN4
								 */
}	

/********************************************************************
 * Function:        void ADC_Process(void)
 *
 * PreCondition:    Init_ADC_Process(void)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Selects the A/D channel and starts the conversion,
 *					readouts will be stored in analogInput
 ********************************************************************/
void ADC_Process() {
	switch(ADCState) {
		case 0 :
			SetChanADC(ADC_CH0);
			ADCState++;
			break;
		case 1 :
			ConvertADC();
			ADCState++;
			break;
		case 2 :
			if (!BusyADC()) {
				analogInput_0 = ReadADC();
				SetChanADC(ADC_CH1);
				ADCState++;
			}
			break;
		case 3 :
			ConvertADC();
			ADCState++;
			break;
		case 4 :
			if (!BusyADC()) {
				analogInput_1 = ReadADC();
				SetChanADC(ADC_CH2);
				ADCState++;
			}
			break;
		case 5 :
			ConvertADC();
			ADCState++;
			break;
		case 6 :
			if (!BusyADC()) {
				analogInput_2 = ReadADC();
				SetChanADC(ADC_CH3);
				ADCState++;
			}
			break;
		case 7 :
			ConvertADC();
			ADCState++;
			break;
		case 8 :
			if (!BusyADC()) {
				analogInput_3 = ReadADC();
				SetChanADC(ADC_CH4);
				ADCState++;
			}
			break;
		case 9 :
			ConvertADC();
			ADCState++;
			break;
		case 10 :
			if (!BusyADC()) {
				analogInput_4 = ReadADC();
				SetChanADC(ADC_CH0);
				ADCState = 0;
			}
			break;
		default :
			break;
	}
} 

//EOF-----------------------------------------------------------------
