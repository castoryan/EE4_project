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
#define Button PORTCbits.RC0  //still need to decide which pin we can use here
#define GameButton PORTBbits.RB1  //still need to decide which pin we can use here

/** V A R I A B L E S ********************************************************/
unsigned char buttonCounter;
unsigned char prevState;
//unsigned char b;
unsigned char counterBlink1;
unsigned char counterBlink2;
//unsigned char timeDelayBefore;				// this is the timedelay before the game starts so that the players have time to prepare. 
//unsigned char timeDelayAfter;
//unsigned char gameOver;

//SPEAKER
unsigned char counterSpeaker;
int i;
int m;
//int u;  //?is used??

//LED
unsigned char data[16][8] = {{0,0,0,1,0,0,0,1},{0,0,0,1,0,0,1,0},{0,0,0,1,0,1,0,0},{0,0,0,1,1,0,0,0},{0,0,1,0,0,0,0,1},{0,0,1,0,0,0,1,0},{0,0,1,0,0,1,0,0},
{0,0,1,0,1,0,0,0},
{0,1,0,0,0,0,1,0},{0,1,0,0,0,1,0,0},{0,1,0,0,1,0,0,0},{1,0,0,0,0,0,0,1},{1,0,0,0,0,0,1,0},{1,0,0,0,0,1,0,0},{1,0,0,0,1,0,0,0},
{0,1,0,0,0,0,0,1}};
unsigned char j;
unsigned char t;

//HEARTBEAT
unsigned char prevPeak;
unsigned char heartBeatPiek1;					// the number 1 and 2 indicate players 1 and 2
unsigned char heartBeatCounter1;				//counts the amount of pieks during an amount of time determend by the heartBeatTimer
unsigned char heartBeatPiek2;
unsigned char heartBeatCounter2;
unsigned char heartBeatTimer;
unsigned int peakBoolean;
unsigned char counterHR;



/** P R I V A T E  P R O T O T Y P E S ***************************************/
void Init(void);
void LedInit(void);
void ledNumber(unsigned char);
void HRGameLight(void);
void Speaker(void);
unsigned int HeartDetect(unsigned int);
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
	unsigned char f = 0; 
	Init();					
	while(1) { 
// pushing button times
	if(Button != prevState)//Firstly Button=1,prevState =1;
	{
		Wait();
		Wait();
		if(Button != prevState)
		{
			prevState = Button;
			if (Button == 0) {							// only use rising edge
				buttonCounter++;					// increment the amount of button pushing
			}
		}
	}
//select different modes
 	    if(buttonCounter%3 == 0){
       LedInit();
       }
// stand by
	    if(buttonCounter%3 == 1){
	//sLed on
       ledNumber(15);
       }

 //HeartBeat
	if(buttonCounter%3 == 2){
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
		if (counterBlink1 == 500) {				//game status
			counterBlink1 = 0;
			f++;
            if(f > 1) { f = 0;}
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
		//	ledNumber(7);	
           // speaker on (maybe later off)
            Speaker(); // made it in process file
            delayms(2000);
		   // compare two persons' heartbeat
          if(t == 13 || t == 0){
			    	if(t == 13) {									//data[][] = ... 4 leds will burn at the winners side
						  ledNumber(13);
							delayms(500);
					      }	
					else {	
						  ledNumber(0);
							delayms(500);	
					 }
			        // some congradulations
					
				    // initialize all the things

			}
          else{
			heartBeatCounter1 = HeartDetect(1);
			heartBeatCounter2 = HeartDetect(2);
		//	if(heartBeatCounter1 > heartBeatCounter2){ // we define "1"is right side; "2"is left side;
			if( heartBeatCounter1 == 1 ){			
	//stepper motor moves one step right
                

				//led moves one step right
						t--;
                        ledNumber(t);
						
               }
		//	else if (heartBeatCounter1 < heartBeatCounter2){

			if(heartBeatCounter2 == 1 ){
		//stepper motor moves one step left


				//led moves one step left
						t++;                        
						ledNumber(t);							
			    }
			delayms(500);

            }
		}

   }
 //EEG   
   if(buttonCounter%4 == 3){

   }
 
//		ADC_Process();		//execute one step in the ADC prosess
//		PWM_Process();		//execute one step in the PWM prosess
//		Stepper_Step(0, 1);	//Asks the Stepper_Process to turn the motor 1 step CW
		Wait();				//wait until one 1ms has elapese
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
	TRISCbits.TRISC0 = 1;
	prevState=1;
	
	PORTCbits.RC0 = 1;
	TRISBbits.TRISB1 = 1;
	PORTBbits.RB1 = 0;
  //speaker
	TRISAbits.TRISA0 = 0;
	LATAbits.LATA0 = 0;
  //led
   	TRISBbits.TRISB5 = 0;
	LATBbits.LATB5 = 0;
    TRISBbits.TRISB4 = 0;
	LATBbits.LATB4 = 0;
	TRISBbits.TRISB6 = 0;
	LATBbits.LATB6 = 0;
  //HR
	peakBoolean = 0;
  //stepper motor
   // TRISCbits.TRISC0 = 1;

//other variables
	//speaker
    buttonCounter = 0;
	counterSpeaker = 0;
	i=0; 
    counterBlink1 = 0;
	//led
     t = 7;
	 j = 0;
     


	Init_Timer_Loop();			
//	Init_PWM_Process();		//initialise the PWM module
	Init_ADC_Process();		//initialise the A/D module
//	Init_Stepper_Process();	//initialise the Stepper module
}

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

void ledNumber(unsigned char d){

	LATBbits.LATB6 = 0;
			Wait();
		for(j=0;j<8;j++)
		{
			LATBbits.LATB4 = 0;
			LATBbits.LATB5 = data[d][j];
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


unsigned int HeartDetect(unsigned int x){
    int peak = 0;
    int count = 0;
    //int ii = 0;
    //unsigned char prevPeak = peakBoolean;
	  ADC_Process();	
	  if(x==1) {peak = analogInput_1;} 
      if(x==2) {peak = analogInput_2;} 
//		if(peakBoolean != prevPeak) {
//			prevPeak = peakBoolean;
//			if(peakBoolean == 1) {
//				count++;
//			} 
//		}

		if(peak > 0x01ff)
		{
			peakBoolean = 1;
		}
		else
		{
			peakBoolean = 0;
		}
     
	return 	peakBoolean;	
}

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

void delayms(int ms)
{	
	int i;
    long int j;
	for(i=0;i<ms;i++)
	{
		Wait();
		//for(j=0;j<200000;j++);
	}
}
//EOF-------------------------------------------------------------------------
