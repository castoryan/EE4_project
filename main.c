/*********************************************************************
 *
 *                  EE 4 Project - Code Template
 *
 *********************************************************************
 * FileName:        main.c
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
 * Jeroen Van Aken		14/03/11	Updated for use of bac3 board
 * Jeroen Van Aken		18/02/14	Added stepper process
 ********************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "config.h"
#include "adc_process.h"
#include "pwm_process.h"
#include "stepper_process.h"
#include "led.h"
#include "speaker.h"


#define Button2 PORTBbits.RB7
#define Button1 PORTCbits.RC6  	

#define LED2 LATCbits.LATC1 	

#define SPEAKER LATAbits.LATA2
//** V A R I A B L E S ********************************************************/


unsigned char State;
unsigned char Winner;
int flag1;
int flag2;

//Button
long int ButtonCount;



//HEARTBEAT
long int HRcount1;
long int HRcount2;
short int ScorePlayer1;
short int ScorePlayer2;
short int RealScorePlayer1;
short int RealScorePlayer2;
short int Player1HR;
short int Player2HR;

//EEG

int P1a;
int P2a;
int P1b;
int P2b;
int P1c;
int P2c;
unsigned char P1peak; // value of peak.
unsigned char P2peak; // value op peak. 
signed char eegdiff; // difference between eeg1b and eeg2b.
unsigned char eegpointsP1;
unsigned char eegpointsP2;


/** P R I V A T E  P R O T O T Y P E S ***************************************/
void Init(void);

//Button
void ButtonCheck(void);


//HeartRate
void HeartBeatGame(void);

//EEG
void EEG_Game(void);


//Others
void Delayms(int);

/** D E C L A R A T I O N S **************************************************/
/******************************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Main program entry point.
 *****************************************************************************/
void main(void) {

Init();						//initialise the system
	while(1) {

		ButtonCheck();
			

		if(Button1 == 1)
		{
		
		ButtonCount = 0;
		switch(State%6)
		{ 
			case 0:	
				Init();	
				LED_Number(15);	
				break;
			
			case 1:
				//Stepmotor_Right();
				LED2 = 1;
				Speaker_Song2();
				LED_AllLedsBlink();

				break;
			case 2:		
				LED_AllLedsBlinkSpeedUp();				
				//LED2 = 0;
				//LED_leftFourLedsBlink();
				Speaker_Song3();
				//LED_allLedsGoReverseFast();
				//Stepmotor_Left();
							//Wait();
				break;
			case 3:					
				if(Winner  == 0 ){
					LED2 = 1;
					HeartBeatGame();
				};
				if(Winner  == 1 ){LED2 = 0;LED_rightFourLedsBlink();};
				if(Winner  == 2 ){LED2 = 0;LED_leftFourLedsBlink();};	

				break;
			case 4:
				LED_allLedsGoFast();
				Speaker_Song1();
//				if(Winner  == 0 ){
//					LED2 = 1;
//					EEG_Game();
//				}
			//	if(Winner  == 1 ){LED_rightFourLedsBlink();}
			//	if(Winner  == 2 ){LED_leftFourLedsBlink();}
				break;
			case 5:
				LED_allLedsGo();
				break;
		}
//
//			if(State%4 == 0)
//			{
//				
//				
//			}
//			if(State%4 == 1)
//			{
//				
//			}
//			if(State%4 == 2)
//			{		
//				
//			}
//			if(State%4 == 3)
//			{		
//
//			}
////			if(State%5 == 4)
//			{	
//				
//			}
//			

		}

		ADC_Process();		//execute one step in the ADC prosess
		Player1HR = analogInput_0;
		Player2HR = analogInput_1;
//		PWM_Process();		//execute one step in the PWM prosess
		//Stepper_Step(0, 1);	//Asks the Stepper_Process to turn the motor 1 step CW	
		//Stepper_Process();
		Wait();				//wait until one 1m has elapesed
	}
}

/******************************************************************************
 * Function:        void Init(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Init is a centralize initialization routine.
 *                  
 *                  User application initialization routine should also be
 *                  called from here.                  
 *****************************************************************************/
void Init(void) {
	//configure I/O
	TRISCbits.TRISC1 = 0;
	LATCbits.LATC1 = 0;

	//Button
	TRISCbits.TRISC6 = 1;
	TRISBbits.TRISB7 = 1;	


   //Variables
	State = 0;
	Winner = 0;
	flag1 = 0;
	flag2 = 0;
	PreLEDpos = 7;

	//Button
	ButtonCount = 0;


  	//HeartRate
	Player1HR = 0;
	Player2HR = 0;
	RealScorePlayer1 = 0;
	RealScorePlayer2 = 0;
	ScorePlayer1 = 0;
	ScorePlayer2 = 0;
	HRcount1 = 0;
	HRcount2 = 0;


    Init_LED();
	Init_Speaker();

	Init_Timer_Loop();			
//	Init_PWM_Process();		//initialise the PWM module
	Init_ADC_Process();		//initialise the A/D module
	Init_Stepper_Process();	//initialise the Stepper module
}

//===================== Button =====================//
void ButtonCheck(void){
		
		if(Button1 == 0)						//
		{
	    	ButtonCount++;
			if(ButtonCount == 30)
			{
				State++;					// increment the amount of button pushing
			}
		}
}


//===================== HeartBeat =====================//
void HeartBeatGame(void){
    

	if(Player1HR >500)
	{	HRcount1++;   }
	else
	{	HRcount1 = 0; }

	if(Player2HR >530)
	{	HRcount2++;   }
	else
	{   HRcount2 = 0; }



	if(HRcount1 == 100){ 	//count for 100 ms
		HRcount1 = 0;
		RealScorePlayer1++;
	}
	if(HRcount2 == 100){    //count for 100 ms
		HRcount2 = 0;
		RealScorePlayer2++;
	}

	if(RealScorePlayer1 == 5){ 	//count for 5 times
		RealScorePlayer1 = 0;
		ScorePlayer1++;
	}
	if(RealScorePlayer2 == 5){ 	//count for 5 times
		RealScorePlayer2 = 0;
		ScorePlayer2++;
	}
				
	if(LEDpos > 0 && LEDpos < 14)
	{
		LEDpos = ScorePlayer2 - ScorePlayer1 + 7;
		LED_Number(LEDpos);
		if(PreLEDpos < LEDpos){flag1 = 1;flag2 = 0;}
		if(PreLEDpos > LEDpos){flag2 = 1;flag1 = 0;}
		
		if(flag1 == 1&&flag2 == 0){Stepper_Step(0, 0);}
		if(flag2 == 1&&flag1 == 0){Stepper_Step(0, 1);}
			
		PreLEDpos = LEDpos;
	}
	else
	{
		if(LEDpos == 14){LED_Number(14);Winner = 1; }
		if(LEDpos == 0 ){LED_Number(0 );Winner = 2; }
	}

}

//=========================EEG=======================================

void EEG_Game(void){

/**** Player 1 EEG code****/

// P1a newest value n
// P1b old value n-1
// P1c oldest value n-2


P1a = analogInput_3;

if (P1c < P1b && P1a < P1b)
{
P1peak = P1b;
}
P1c = P1b;
P1b = P1a;



/**** Player 2 EEG code****/

P2a = analogInput_4;

if (P2c < P2b && P2a < P2b)
{
P2peak = P2b;
}
P2c = P2b;
P2b = P2a;

/**** Comparison between P1 and P2 peakvalues code****/

eegdiff = P1peak - P2peak;
if (eegdiff > 0) // if P1 has a higher peak voltage then P2

{
/***check to see how much higher te peakvoltage is and assign points accordingly***/

/**** game highest alpha waves score points*****/

 if (eegdiff > 5)
 {
   eegpointsP1 += 5;
 }
 else if (eegdiff >4)
 {
   eegpointsP1 += 4;
 }
 else if (eegdiff >3)
 {
    eegpointsP1 += 3;
 }
 else if (eegdiff >2)
 { 
    eegpointsP1 += 2;
 }
 else if (eegdiff >1)
 {
    eegpointsP1 += 1;
 }
 else
 {}
}
else  // if P2 has a higher peak voltage then P1

{
eegdiff = -eegdiff;

/***check to see how much higher te peakvoltage is and assign points accordingly***/

 if (eegdiff > 5)
 {
   eegpointsP2 += 5;
 }
 else if (eegdiff >4)
 {
   eegpointsP2 += 4;
 }
 else if (eegdiff >3)
 {
    eegpointsP2 += 3;
 }
 else if (eegdiff >2)
 { 
    eegpointsP2 += 2;
 }
 else if (eegdiff >1)
 {
    eegpointsP2 += 1;
 }
 else
 {}
}

/******Points*******/
if (eegpointsP1 >= 10)
{
eegpointsP1 -= 10;
// score a game point , led steps , stepper steps.
}
if (eegpointsP2 >= 10)
{
eegpointsP2 -= 10;
// score a game point , led steps , stepper steps.


}
}

//



//========================Others=====================================
void Delayms(int ms){	
	int tt;
	for(tt = 0; tt<ms;tt++)
	{
		Wait();
		}
}



////EOF-------------------------------------------------------------------------
