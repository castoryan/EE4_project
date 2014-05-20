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
 ********************************************************************/
 
/** I N C L U D E S *************************************************/
#include <p18cxxx.h>

/** V A R I A B L E S ***********************************************/
//LED
const unsigned char far rom data[16][8] = 
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
unsigned char FlagBlink1; 
unsigned char FlagBlink2; 
unsigned char FlagBlink3;
unsigned char FlagBlink4;
unsigned int counterBlink1;
unsigned int counterBlink2;
unsigned int counterBlink3;
unsigned int counterBlink4;

unsigned int SpeedUpCounter1;
unsigned int counterBlinkV1;

unsigned char LEDpos;
unsigned char PreLEDpos;

unsigned char ledsUp;
unsigned char ledsDown;
int counterAll;

void Delay(void);
void LED_All_Off(void);

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

void Init_LED(void)
{
	//LED
	TRISBbits.TRISB4 = 0;
	LATBbits.LATB4 = 0;

   	TRISBbits.TRISB5 = 0;		
	LATBbits.LATB5 = 0;
    
	TRISBbits.TRISB6 = 0;
	LATBbits.LATB6 = 0;


	//LED
	FlagBlink1 = 0;
	FlagBlink2 = 0;
	FlagBlink3 = 0;
	FlagBlink4 = 0;
	counterBlink1 = 0;
	counterBlink2 = 0;
	counterBlink3 = 0;
	counterBlink4 = 0;

	SpeedUpCounter1 = 0;
	counterBlinkV1 = 1000;

	LEDpos = 7;

	ledsUp = 0;
	ledsDown = 14;
	counterAll = 0;
}


void LED_All_Off(void){

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


void LED_rightFourLeds(void){
  unsigned char firstFour[8] = {1,0,0,0,1,1,1,1};
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



void LED_rightFourLedsBlink(void){
		
// the first four leds blink to show it's HR game and sLed Off
		if(counterBlink1 == 0) {			
			if(FlagBlink1 == 0){			
			    LED_rightFourLeds();   //four Leds on
			}
			if(FlagBlink1 == 1){
		    	LED_All_Off();  //four Leds off
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



void LED_leftFourLeds(void){
 	unsigned char leftFour[8] = {0,0,0,1,1,1,1,1};
	unsigned char j;
  	LATBbits.LATB6 = 0;
	Delay();
		for(j=0;j<8;j++)
		{
			LATBbits.LATB4 = 0;
	     	LATBbits.LATB5 = leftFour[j];
			LATBbits.LATB4 = 1; 
		}	
			LATBbits.LATB6 = 1;	
}

void LED_leftFourLedsBlink(void){
	unsigned char j;
		if(counterBlink2 == 0) {			
			if(FlagBlink2 == 0){			
			    LED_leftFourLeds();   //four Leds on
			}
			if(FlagBlink2 == 1){
		    	LED_All_Off();  //four Leds off
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

void LED_allLedsGo(void){
  unsigned char j;
  if(counterAll==0){
  LATBbits.LATB6 = 0;     
		for(j=0;j<8;j++)
		{
			LATBbits.LATB4 = 0;
	     	LATBbits.LATB5 = data[ledsUp][j];
			LATBbits.LATB4 = 1; 
		}	
			LATBbits.LATB6 = 1;	
		ledsUp++;
}

if(counterAll==600){
counterAll=0;
}
else{counterAll++;}

if(ledsUp>14) {ledsUp=0;}
}

void LED_allLedsGoFast(void){
unsigned char j;
if(counterAll==0){
 LATBbits.LATB6 = 0;     
		for(j=0;j<8;j++)
		{
			LATBbits.LATB4 = 0;
	     	LATBbits.LATB5 = data[ledsUp][j];
			LATBbits.LATB4 = 1; 
		}	
			LATBbits.LATB6 = 1;	
		ledsUp++;
}

if(counterAll>50){
counterAll=0;
}
else{counterAll++;}

if(ledsUp>14) {ledsUp=0;
}
}

void LED_allLedsGoReverse(void){
unsigned char j;
if(counterAll==0){
 LATBbits.LATB6 = 0;     
		for(j=0;j<8;j++)
		{
			LATBbits.LATB4 = 0;
	     	LATBbits.LATB5 = data[ledsDown][j];
			LATBbits.LATB4 = 1; 
		}	
			LATBbits.LATB6 = 1;	
		ledsDown--;
}

if(counterAll==600){
counterAll=0;
}
else{counterAll++;}

if(ledsDown==0){ledsDown=14;
}
}

void LED_allLedsGoReverseFast(void){
unsigned char j;
if(counterAll==0){
 LATBbits.LATB6 = 0;     
		for(j=0;j<8;j++)
		{
			LATBbits.LATB4 = 0;
	     	LATBbits.LATB5 = data[ledsDown][j];
			LATBbits.LATB4 = 1; 
		}	
			LATBbits.LATB6 = 1;	
		ledsDown--;
}

if(counterAll>50){
counterAll=0;
}
else{counterAll++;}

if(ledsDown==0){ledsDown=14;
}
}


void LED_allLedsOn(void){
unsigned char j;
 LATBbits.LATB6 = 0;     
		for(j=0;j<8;j++)
		{
			LATBbits.LATB4 = 0;
	     	LATBbits.LATB5 = 1;
			LATBbits.LATB4 = 1; 
		}	
			LATBbits.LATB6 = 1;	

}

void LED_AllLedsBlink(void){
	unsigned char j;
		if(counterBlink3 == 0) {			
			if(FlagBlink3 == 0){			
			    LED_allLedsOn();   //four Leds on
			}
			if(FlagBlink3 == 1){
		    	LED_All_Off();  //four Leds off
			}
		}

		if (counterBlink3 == 1000) {				//blink for 1s
			counterBlink3 = 0;
			FlagBlink3++;
            if(FlagBlink3 > 1){FlagBlink3 = 0;}
		} 
		else {
			counterBlink3++;
		}
}

void LED_AllLedsBlinkSpeedUp(void){
	unsigned char j;
		if(counterBlink4 == 0) {			
			if(FlagBlink4 == 0){			
			    LED_allLedsOn();   //four Leds on
			}
			if(FlagBlink4 == 1){
		    	LED_All_Off();  //four Leds off
			}
		}

		if (counterBlink4 == counterBlinkV1) {				//blink for 1s
			counterBlink4 = 0;
			FlagBlink4++;
            if(FlagBlink4 > 1){
				FlagBlink4 = 0;
				if(counterBlinkV1 > 500){counterBlinkV1 = counterBlinkV1 - 30;}
				if(counterBlinkV1 > 300&&counterBlinkV1 < 500){counterBlinkV1 = counterBlinkV1 - 20;}
				if(counterBlinkV1 > 100&&counterBlinkV1 < 300){counterBlinkV1 = counterBlinkV1 - 10;}
				if(counterBlinkV1 > 8&&counterBlinkV1 < 100){counterBlinkV1 = counterBlinkV1 - 3;}
				}
			}
		else {
			counterBlink4++;
		}
	
}

//======================Others======================

void Delay(void){	
	int ttt;
	for(ttt = 0; ttt<200;ttt++);
}


//EOF-----------------------------------------------------------------
