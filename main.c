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


/** D E F I N E S ********************************************************/
//SPEAKER
#define SPEAKER LATAbits.LATA0
#define Button PORTBbits.RB0  //still need to decide which pin we can use here
#define GameButton PORTBbits.RB1  //still need to decide which pin we can use here

/** V A R I A B L E S ********************************************************/
unsigned char buttonCounter;
//unsigned char b;
unsigned char counterBlink1;
unsigned char counterBlink2;
//unsigned char timeDelayBefore;				// this is the timedelay before the game starts so that the players have time to prepare. 
//unsigned char timeDelayAfter;
//unsigned char gameOver;

//SPEAKER
unsigned char speaker;//??  I don't understand.
unsigned char counterSpeaker;
int i;
int m;
//int u;  //?is used??

//LED
unsigned char data[16][8] = {{0,1,0,0,0,0,1,0},{0,1,0,0,0,1,0,0},{0,1,0,0,1,0,0,0},{1,0,0,0,0,0,0,1},{1,0,0,0,0,0,1,0},{1,0,0,0,0,1,0,0},{1,0,0,0,1,0,0,0},
{0,0,1,0,0,1,0,0}, {0,0,1,0,0,0,1,0},{0,0,1,0,0,0,0,1},{0,0,0,1,1,0,0,0},{0,0,0,1,0,1,0,0},{0,0,0,1,0,0,1,0},{0,0,0,1,0,0,0,1},{1,0,0,0,1,1,1,1},{0,0,0,1,1,1,1,1}
};
unsigned char j;
unsigned char t;
unsigned char s;

//HEARTBEAT
unsigned char prevPeak;
unsigned char heartBeatPiek1;					// the number 1 and 2 indicate players 1 and 2
unsigned char heartBeatCounter1;				//counts the amount of pieks during an amount of time determend by the heartBeatTimer
unsigned char heartBeatPiek2;
unsigned char heartBeatCounter2;
unsigned char heartBeatTimer;
unsigned char peakBoolean1;
unsigned char peakBoolean2;
unsigned char prevPeak1;
unsigned char prevPeak2;
unsigned char counterHR;



/** P R I V A T E  P R O T O T Y P E S ***************************************/
void Init(void);
void LedInit(void);
void sLedOn(void);
void centerLed(void);
void HRGameLight(void);
void Speaker(void);
unsigned char HeartDetect1(void);
unsigned char HeartDetect2(void);
void delayms(int);
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
    unsigned char prevState = Button;	
	unsigned char f = 0; 
	Init();					
	while(1) { 
// pushing button times
		if (Button != prevState) {						// detect rising edge
			prevState = Button;
			if (Button == 0) {							// only use rising edge
				buttonCounter++;					// increment the amount of button pushing
			}
		}
}
//select different modes
 // stand by
	    if(buttonCounter%3 == 0){
	//sLed on
       sLedOn();
}

//HeartBeat
	if(buttonCounter%3 == 1){
	//
	   if( GameButton == 0){	   // not that good, maybe need to detect rising edge
        // the first four leds blink to show it's HR game and sLed Off
		if(counterBlink1 == 0) {			
			if(f == 0){			
			    HRGameLight();   //four Leds on
			}
			if(f == 1){
		    	LedInit();  //four Leds off
			}
		}
		if (counterBlink1 == 100) {				//game status
			counterBlink1 = 0;
			f++;
            if(f >= 1) { f = 0;}
		} 
		else {
			counterBlink1++;
		}
        Wait();	
      }
	//push GameButton to start HR game
       if(GameButton == 1){    // not that good
		   // all Leds off
			LedInit();
		   // the led in board center needs to be on
			centerLed();	
           // speaker on (maybe later off)
            Speaker(); // made it in process file
		   // compare two persons' heartbeat
          if(t == 14 || t == 0){
			    	if(t == 14) {									//data[][] = ... 4 leds will burn at the winners side
						  LATBbits.LATB6 = 0;
    					  Wait();		
  						  for(j=0;j<8;j++)
	                    	{LATBbits.LATB4 = 0;
	                    	LATBbits.LATB5 = data[14][j];
			                LATBbits.LATB4 = 1; 
	                     	}	
		                    LATBbits.LATB6 = 1;	
					      }	
					else {	
						LATBbits.LATB6 = 0;
    					  Wait();		
  						  for(j=0;j<8;j++)
	                    	{LATBbits.LATB4 = 0;
	                    	LATBbits.LATB5 = data[0][j];
			                LATBbits.LATB4 = 1; 
	                     	}	
		                    LATBbits.LATB6 = 1;		
					 }
			        // some congradulations
			}
          else{
			if( HeartDetect1() == 1 )
			{heartBeatCounter1++;}

			if( HeartDetect2() == 1 )
			{heartBeatCounter2++;}

//			if(heartBeatCounter1 > heartBeatCounter2){ // we define "1"is right side; "2"is left side;
//				//stepper motor moves one step right
//                
//
//				//led moves one step right
//			           	LATBbits.LATB6 = 0;
//    					Wait();		
//  						  for(j=0;j<8;j++)
//	                    	{LATBbits.LATB4 = 0;
//	                    	LATBbits.LATB5 = data[t][j];
//			                LATBbits.LATB4 = 1; 
//	                     	}	
//		                    LATBbits.LATB6 = 1;	
//						t--;
//               }
//			else if (heartBeatCounter1 < heartBeatCounter2){
//				//stepper motor moves one step left
//
//
//				//led moves one step left
//                        LATBbits.LATB6 = 0;
//    			    	Wait();		
//  						  for(j=0;j<8;j++)
//	                    	{LATBbits.LATB4 = 0;
//	                    	LATBbits.LATB5 = data[s][j];
//			                LATBbits.LATB4 = 1; 
//	                     	}	
//		                    LATBbits.LATB6 = 1;
//						s++;
//			    }
//			else{
//                //just keep state, nothing needs to write here
//                }
            }
		}

   }
 //EEG   
   if(buttonCounter%3 == 2){

   }
 
//		ADC_Process();		//execute one step in the ADC prosess
//		PWM_Process();		//execute one step in the PWM prosess
//		Stepper_Step(0, 1);	//Asks the Stepper_Process to turn the motor 1 step CW
		Wait();				//wait until one 1ms has elapesed

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
  //speaker
    TRISCbits.TRISC0 = 1;
	TRISAbits.TRISA0 = 0;
	LATAbits.LATA0 = 0;
  //led
   	TRISBbits.TRISB5 = 0;
	LATBbits.LATB5 = 0;
    TRISBbits.TRISB4 = 0;
	LATBbits.LATB4 = 0;
	TRISBbits.TRISB6 = 0;
	LATBbits.LATB6 = 0;
  //HeartBeat
	peakBoolean1 = 0;
	peakBoolean2 = 0;
	prevPeak1 = 0;
	prevPeak2 = 0;
	heartBeatCounter1 = 0;
	heartBeatCounter2 = 0;
  //stepper motor
    

//other variables
	//speaker
    buttonCounter = 0;
	counterSpeaker = 0;
	i=0; 

	//led
     t = 6;
     s = 7;
	 j = 0;



	Init_Timer_Loop();			
//	Init_PWM_Process();		//initialise the PWM module
	Init_ADC_Process();		//initialise the A/D module
//	Init_Stepper_Process();	//initialise the Stepper module
}



//============================LED===============================//

void LedInit(void){
  LATBbits.LATB6 = 0;
  Wait();		
  for(j=0;j<8;j++)
		{
			LATBbits.LATB4 = 0;
	     	LATBbits.LATB5 = 0;
			LATBbits.LATB4 = 1; 
		}	
		LATBbits.LATB6 = 1;	
}

void sLedOn(void){
  unsigned char sLed[8] = {0,1,0,0,0,0,0,1};
  LATBbits.LATB6 = 0;    
  Wait();
	for(j=0;j<8;j++)
		{
			LATBbits.LATB4 = 0;
	     	LATBbits.LATB5 = sLed[j];
			LATBbits.LATB4 = 1; 
		}	
			LATBbits.LATB6 = 1;	
}

void HRGameLight(void){
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

void centerLed(void){
  unsigned char middle[8] = {0,0,1,0,1,0,0,0};
  LATBbits.LATB6 = 0;     
  Wait();
		for(j=0;j<8;j++)
		{
			LATBbits.LATB4 = 0;
	     	LATBbits.LATB5 = middle[j];
			LATBbits.LATB4 = 1; 
		}	
			LATBbits.LATB6 = 1;	
}




//================================HeartBeat=====================================//
unsigned char HeartDetect1(void){			// x is the number of Heartbeat sensor
    int peak = 0;
	ADC_Process();  		//not aware how long will it consume 
	peak = analogInput_1;

	if(peak > 0x01ff)		//0x01ff is 512, just 2.5V, 0 is 0V, 1024 is 5V
	{   delayms(2);
		if(peak > 0x01ff)	//avoid noise
		{peakBoolean1 = 1;}
	}
	else
	{
		peakBoolean1 = 0;
	}
	

	if(prevPeak1==0&&peakBoolean1==1)
	{prevPeak1 = peakBoolean1;return 1;}
	else
	{prevPeak1 = peakBoolean1;return 0;}
}

unsigned char HeartDetect2(void){			// x is the number of Heartbeat sensor
    int peak = 0;
	ADC_Process();  		//not aware how long will it consume 
	peak = analogInput_2;

	if(peak > 0x01ff)		//0x01ff is 512, just 2.5V, 0 is 0V, 1024 is 5V
	{   delayms(2);
		if(peak > 0x01ff)	//avoid noise
		{peakBoolean2 = 1;}
	}
	else
	{
		peakBoolean2 = 0;
	}
	

	if(prevPeak2==0&&peakBoolean2==1)
	{prevPeak2 = peakBoolean2;return 1;}
	else
	{prevPeak2 = peakBoolean2;return 0;}
}



//===============================Speaker=================================//
void Speaker(void){
	  if (speaker == 0) {	
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
			} else {
				SPEAKER = 0;
			}
			
			if (counterSpeaker == m) {
				counterSpeaker = 0;
			} else {
				counterSpeaker++;
			}
}

void delayms(int ms)
{	
	int i;
	for(i=0;i<ms;i++)
	{
		Wait();
	}
}


//EOF-------------------------------------------------------------------------
