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


//Button
long int ButtonCount;


unsigned char buttonCounter;
unsigned char prevState;
//unsigned char b;
int counterBlink1;
int counterBlink2;


//SPEAKER
unsigned char counterSpeaker;
int i;
int m;


////LED
unsigned char far rom data[16][8] = {{0,0,0,1,0,0,0,1},{0,0,0,1,0,0,1,0},{0,0,0,1,0,1,0,0},{0,0,0,1,1,0,0,0},{0,0,1,0,0,0,0,1},{0,0,1,0,0,0,1,0},{0,0,1,0,0,1,0,0},
{0,0,1,0,1,0,0,0},
{0,1,0,0,0,0,1,0},{0,1,0,0,0,1,0,0},{0,1,0,0,1,0,0,0},{1,0,0,0,0,0,0,1},{1,0,0,0,0,0,1,0},{1,0,0,0,0,1,0,0},{1,0,0,0,1,0,0,0},
{0,1,0,0,0,0,0,1}};
unsigned char j;
unsigned char t;
unsigned char f; 
unsigned char LEDpos;

////HEARTBEAT
unsigned int peakBoolean1;
unsigned int peakBoolean2;
long int HRcount1;
long int HRcount2;
short int ScorePlayer1;
short int ScorePlayer2;
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
void LED_Blink(void);


//HeartRate
void HR_Detect(unsigned char);

//Speaker
void Speaker(void);


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
				
				LED_Init();
				
			}
			if(State%4 == 1)
			{
				LED2 = 0;
				LED_Number(15);	
				LED_Number(5);
			}
			if(State%4 == 2)
			{	
				LED2 = 0;
				LED_Blink();
			}
			if(State%4 == 3)
			{	
				LED2 = 1;
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
					ScorePlayer1++;
				}
				if(HRcount2 == 100){    //count for 100 ms
					HRcount2 = 0;
					ScorePlayer2++;
				}
				
				
				if(LEDpos > 0 && LEDpos < 14)
				{
					LEDpos = ScorePlayer2 - ScorePlayer1 + 7;
					LED_Number(LEDpos);	
				}
				else
				{
					if(LEDpos == 14){LED_Number(14);}
					if(LEDpos == 0 ){LED_Number(0 );}
				}	
				


			}

		}




		ADC_Process();		//execute one step in the ADC prosess
		Player1HR = analogInput_0;
		Player2HR = analogInput_1;
		Wait();				//wait until one 1m has elapesed
//		PWM_Process();		//execute one step in the PWM prosess
//		Stepper_Step(0, 1);	//Asks the Stepper_Process to turn the motor 1 step CW
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

	TRISCbits.TRISC0 = 1;
	TRISBbits.TRISB0 = 1;	


	//LED
	TRISBbits.TRISB4 = 0;
	LATBbits.LATB4 = 0;

   	TRISBbits.TRISB5 = 0;		
	LATBbits.LATB5 = 0;
    
	TRISBbits.TRISB6 = 0;
	LATBbits.LATB6 = 0;
	


///////Variables
	State = 0;


	
	//Button
	ButtonCount = 0;

	//LED
    t = 7;
	j = 0;
	f = 0;
	counterBlink1 = 0;
	LEDpos = 7;

  	//HeartRate
	peakBoolean1 = 0;
	peakBoolean2 = 0;
	Player1HR = 0;
	Player2HR = 0;
	ScorePlayer1 = 0;
	ScorePlayer2 = 0;


	//Speaker
    buttonCounter = 0;
	counterSpeaker = 0;
	i=0; 



	
	Init_Timer_Loop();			
//	Init_PWM_Process();		//initialise the PWM module
	Init_ADC_Process();		//initialise the A/D module
//	Init_Stepper_Process();	//initialise the Stepper module
}



//===================== Button =====================//


void ButtonCheck(void)
{
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
  LATBbits.LATB6 = 0;
  Wait();		
  for(j=0;j<8;j++){
			LATBbits.LATB4 = 0;
	     	LATBbits.LATB5 = 0;
			LATBbits.LATB4 = 1; 
	}	
	LATBbits.LATB6 = 1;	
}

void LED_Number(unsigned char d){

	LATBbits.LATB6 = 0;
	Wait();
	for(j=0;j<8;j++){
		LATBbits.LATB4 = 0;
		LATBbits.LATB5 = data[d][j];
		LATBbits.LATB4 = 1; 
	}	
	LATBbits.LATB6 = 1;        
}



void LED_HRGame(void){
  unsigned char firstFour[8] = {0,0,0,1,1,1,1,1};
  LATBbits.LATB6 = 0;     
  Wait();
		for(j=0;j<8;j++)
		{
			LATBbits.LATB4 = 0;
	     	LATBbits.LATB5 = firstFour[j];
			LATBbits.LATB4 = 1; 
		}	
			LATBbits.LATB6 = 1;	
}

void LED_Blink(void)
{
		// the first four leds blink to show it's HR game and sLed Off
		if(counterBlink1 == 0) {			
			if(f == 0){			
			    LED_HRGame();   //four Leds on
			}
			if(f == 1){
		    	LED_Init();  //four Leds off
			}
		}

		if (counterBlink1 == 1000) {				//game status
			counterBlink1 = 0;
			f++;
            if(f > 1){f = 0;}
		} 
		else {
			counterBlink1++;
		}
}

//===================== HeartBeat =====================//
unsigned int HeartDetect(unsigned int x){
    int peak = 0;

	  ADC_Process();	
	  if(x==1) {

		peak = analogInput_1; 
		if(peak > 0x01ff)
		{
			peakBoolean1 = 1;
		}
		else
		{
			peakBoolean1 = 0;
		}
     		return 	peakBoolean1;
		}

		if(x==2)
		{
		peak = analogInput_2;
		
		if(peak > 0x01ff)
		{
			peakBoolean2 = 1;
		}
		else
		{
			peakBoolean2 = 0;
		}
     
			return 	peakBoolean2;
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
//EOF-------------------------------------------------------------------------
