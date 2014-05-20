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
#ifndef _LED_H
#define _LED_H
/** I N C L U D E S *************************************************/


/** V A R I A B L E S ***********************************************/
extern const unsigned char far rom data[16][8] = 
{
{0,0,0,1,0,0,0,1},		//  Light0
{0,0,0,1,0,0,1,0},		//  Light1
{0,0,0,1,0,1,0,0},		//  Light2
{0,0,0,1,1,0,0,0},		//  Light3
{0,0,1,0,0,0,0,1},		//  Light4
{0,0,1,0,0,0,1,0},		//  Light5
{0,0,1,0,0,1,0,0},		//  Light6
{0,0,1,0,1,0,0,0},		//  Light7
{0,1,0,0,0,0,1,0},		//  Light8
{0,1,0,0,0,1,0,0},		//  Light9
{0,1,0,0,1,0,0,0},		//  Light10
{1,0,0,0,0,0,0,1},		//  Light11
{1,0,0,0,0,0,1,0},		//  Light12
{1,0,0,0,0,1,0,0},		//  Light13
{1,0,0,0,1,0,0,0},		//  Light14
{0,1,0,0,0,0,0,1}		//  Light15
};
//unsigned char far rom data[1][1];
extern unsigned char FlagBlink1; 
extern unsigned char FlagBlink2; 
extern unsigned char FlagBlink3;
extern unsigned char FlagBlink4;
extern unsigned int counterBlink1;
extern unsigned int counterBlink2;
extern unsigned int counterBlink3;
extern unsigned int counterBlink4;

extern unsigned int SpeedUpCounter1;
extern unsigned int counterBlinkV1;

extern unsigned char LEDpos;
extern unsigned char PreLEDpos;

extern unsigned char ledsUp;
extern unsigned char ledsDown;
extern int counterAll;


/** P R O T O T Y P E S *********************************************/
void Init_LED(void); 
void LED_All_Off(void);
void LED_Number(unsigned char);
void LED_rightFourLeds(void);
void LED_rightFourLedsBlink(void);
void LED_leftFourLeds(void);
void LED_leftFourLedsBlink(void);

void LED_allLedsGo(void);
void LED_allLedsGoReverse(void);
void LED_allLedsblink(void);
void LED_allLedsOn(void);
void LED_allLedsGoReverseFast(void);
void LED_allLedsGoFast(void);

void LED_AllLedsBlink(void);
void LED_AllLedsBlinkSpeedUp(void);

#endif
//EOF----------------------------------------------------------------
