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


#define Button2 PORTBbits.RB7
#define Button1 PORTCbits.RC6  	

#define LED2 LATCbits.LATC1 	

#define SPEAKER LATAbits.LATA0

///** V A R I A B L E S ********************************************************/
unsigned char State;
unsigned char Winner;


//Button
long int ButtonCount;


int counterBlink1;
int counterBlink2;


//SPEAKER
unsigned char counterSpeaker;
int i;
int m;


////LED
unsigned char far rom data[16][8] = 
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

unsigned char FlagBlink1; 
unsigned char FlagBlink2; 
int counterBlink1;
int counterBlink2;
unsigned char LEDpos;

////HEARTBEAT
unsigned int peakBoolean1;
unsigned int peakBoolean2;
long int HRcount1;
long int HRcount2;
short int ScorePlayer1;
short int ScorePlayer2;
short int RealScorePlayer1;
short int RealScorePlayer2;
short int Player1HR;
short int Player2HR;

///** P R I V A T E  P R O T O T Y P E S ***************************************/
void Init(void);

//Button
void ButtonCheck(void);

//LED
void LED_Init(void);
void LED_Number(unsigned char);
void LED_HRGame(void);
void LED_Blink_Left(void);
void LED_Blink_Right(void);


//HeartRate
void HeartBeatGame(void);

//Speaker
void Speaker(void);


//Others
void Delay(void);

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
//		switch(State%4)
//		{ 
//			case 0:		break;
//			case 1:		break;
//			case 2:		break;
//			case 3:		break;
//		}

			if(State%4 == 0)
			{
				Init();	
				LED_Init();
				
			}
			if(State%4 == 1)
			{
				LED2 = 1;
				LED_Number(15);
				LED_Blink_Left();
			}
			if(State%4 == 2)
			{	
				LED2 = 0;
				LED_Blink_Right();
			}
			if(State%4 == 3)
			{	
				LED2 = 1;
				HeartBeatGame();


			}

		}




		ADC_Process();		//execute one step in the ADC prosess
		Player1HR = analogInput_0;
		Player2HR = analogInput_1;
		Wait();				//wait until one 1m has elapesed
//		PWM_Process();		//execute one step in the PWM prosess
//		Stepper_Step(0, 1);	//Asks the Stepper_Process to turn the motor 1 step CW
//		Wait();				//wait until one 1m has elapesed
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


	//LED
	TRISBbits.TRISB4 = 0;
	LATBbits.LATB4 = 0;

   	TRISBbits.TRISB5 = 0;		
	LATBbits.LATB5 = 0;
    
	TRISBbits.TRISB6 = 0;
	LATBbits.LATB6 = 0;
	


///////Variables
	State = 0;
	Winner = 0;

	
	//Button
	ButtonCount = 0;

	//LED
	FlagBlink1 = 0;
	FlagBlink2 = 0;
	counterBlink1 = 0;
	counterBlink2 = 0;
	LEDpos = 7;

  	//HeartRate
	peakBoolean1 = 0;
	peakBoolean2 = 0;
	Player1HR = 0;
	Player2HR = 0;
	RealScorePlayer1 = 0;
	RealScorePlayer2 = 0;
	ScorePlayer1 = 0;
	ScorePlayer2 = 0;


	//Speaker
	counterSpeaker = 0;
	i=0; 



	
	Init_Timer_Loop();			
//	Init_PWM_Process();		//initialise the PWM module
	Init_ADC_Process();		//initialise the A/D module
//	Init_Stepper_Process();	//initialise the Stepper module
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




//======================== LED =========================//

void LED_Init(void){

	unsigned char j;
	LATBbits.LATB6 = 0;
	Delay();		
  	for(j=0;j<8;j++){
		LATBbits.LATB4 = 0;
	    LATBbits.LATB5 = 0;
		LATBbits.LATB4 = 1; 
	}	
	LATBbits.LATB6 = 1;	
}

void LED_Number(unsigned char d){
	unsigned char j;
	LATBbits.LATB6 = 0;
	Delay();
	for(j=0;j<8;j++){
		LATBbits.LATB4 = 0;
		LATBbits.LATB5 = data[d][j];
		LATBbits.LATB4 = 1; 
	}	
	LATBbits.LATB6 = 1;        
}


void LED_Left_Four(void){
  unsigned char firstFour[8] = {0,0,0,1,1,1,1,1};
  unsigned char j;
  LATBbits.LATB6 = 0;     
  Delay();
		for(j=0;j<8;j++)
		{
			LATBbits.LATB4 = 0;
	     	LATBbits.LATB5 = firstFour[j];
			LATBbits.LATB4 = 1; 
		}	
			LATBbits.LATB6 = 1;	
}

void LED_Right_Four(void){
  unsigned char firstFour[8] = {0,1,0,1,1,0,0,1};
  unsigned char j;
  LATBbits.LATB6 = 0;     
  Delay();
		for(j=0;j<8;j++)
		{
			LATBbits.LATB4 = 0;
	     	LATBbits.LATB5 = firstFour[j];
			LATBbits.LATB4 = 1; 
		}	
			LATBbits.LATB6 = 1;	
}

void LED_Blink_Left(void){
		
// the first four leds blink to show it's HR game and sLed Off
		if(counterBlink1 == 0) {			
			if(FlagBlink1 == 0){			
			    LED_Left_Four();   //four Leds on
			}
			if(FlagBlink1 == 1){
		    	LED_Init();  //four Leds off
			}
		}

		if (counterBlink1 == 1000) {				//blink for 1s
			counterBlink1 = 0;
			FlagBlink1++;
            if(FlagBlink1 > 1){FlagBlink1 = 0;}
		} 
		else {
			counterBlink1++;
		}
}

void LED_Blink_Right(void){
		
// the first four leds blink to show it's HR game and sLed Off
		if(counterBlink2 == 0) {			
			if(FlagBlink2 == 0){			
			    LED_Right_Four();   //four Leds on
			}
			if(FlagBlink2 == 1){
		    	LED_Init();  //four Leds off
			}
		}

		if (counterBlink2 == 1000) {				//blink for 1s
			counterBlink2 = 0;
			FlagBlink2++;
            if(FlagBlink2 > 1){FlagBlink2 = 0;}
		} 
		else {
			counterBlink2++;
		}
}

//===================== HeartBeat =====================//
void HeartBeatGame(void){
    

	if(Player1HR >500)
	{	HRcount1++;   }
	else
	{	HRcount1 = 0; }

	if(Player2HR >500)
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
	}
	else
	{
		if(LEDpos == 14){LED_Number(14);Winner = 1; }
		if(LEDpos == 0 ){LED_Number(0 );Winner = 2; }
	}

}


//===================== Speaker =====================//
void Speaker(void){	
					if(i < 75) {
						m =5;	
					} else {
						if( i < 125) {
							m = 10;
						} else {
							if( i < 200) {
								m = 15;
							} else {
								if(i < 250) {
									m = 3;
								} else {
									if( i < 125) {
										m = 5;
									} else {
										if( i < 200) {
											m = 7;
										} else {
											if(i < 250) {
												m = 10;
											} else {
												i = 0;
											}
										}
									}
								}
							}
						}
					}
					
								
				if (counterSpeaker == 0 ) {
					SPEAKER = !SPEAKER;
					i++; 
				}
			
			if (counterSpeaker == m) {
				counterSpeaker = 0;
			} else {
				counterSpeaker++;
			}
}

//========================Others=====================================
void Delay(void){	
	int tt;
	for(tt = 0; tt<200;tt++);
}



//EOF-------------------------------------------------------------------------
