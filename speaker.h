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
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS?CONDITION. NO WARRANTIES,
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
#ifndef _SPEAKER_H
#define _SPEAKER_H
/** I N C L U D E S *************************************************/


/** V A R I A B L E S ***********************************************/
extern unsigned char speaker1Counter;
extern int i;
extern int m;

extern int speaker2Counter;
extern unsigned char Song2FCounter;
extern unsigned char Song2FCounter2;
extern unsigned char Song2FCounter3;
extern unsigned char Song2FCounter4;
extern unsigned char Song2FCounter5;


extern int speaker3Counter;
extern unsigned char Song3FCounter1;
extern unsigned char Song3FCounter2;
extern unsigned char Song3FCounter3;
extern unsigned char Song3FCounter4;
extern unsigned char Song3FCounter5;
extern unsigned char Song3FCounter7;
extern unsigned char Song3FCounter8;

/** P R O T O T Y P E S *********************************************/
void Init_Speaker(void);
void Speaker_Song1(void);
void Speaker_Song2(void);
void Speaker_Song3(void);

#endif
//EOF----------------------------------------------------------------
