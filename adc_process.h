/*********************************************************************
 *
 *                  EE 4 Project - Code Template
 *
 *********************************************************************
 * FileName:        adc_process.h
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
#ifndef _ADC_PROCESS_H
#define _ADC_PROCESS_H
/** I N C L U D E S *************************************************/
#include <adc.h>

/** V A R I A B L E S ***********************************************/
extern int analogInput_0;
extern int analogInput_1;
extern int analogInput_2;
extern int analogInput_3;
extern int analogInput_4;

/** P R O T O T Y P E S *********************************************/
void Init_ADC_Process(void);
void ADC_Process(void);

#endif
//EOF----------------------------------------------------------------
