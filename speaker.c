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

#define SPEAKER LATAbits.LATA2
/** V A R I A B L E S ***********************************************/
unsigned char speaker1Counter;
int i;
int m;


int speaker2Counter;
unsigned char Song2FCounter;
unsigned char Song2FCounter2;
unsigned char Song2FCounter3;
unsigned char Song2FCounter4;
unsigned char Song2FCounter5;

int speaker3Counter;
unsigned char Song3FCounter1;
unsigned char Song3FCounter2;
unsigned char Song3FCounter3;
unsigned char Song3FCounter4;
unsigned char Song3FCounter5;
unsigned char Song3FCounter7;
unsigned char Song3FCounter8;


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

void Init_Speaker(void){

	TRISAbits.TRISA2 = 0;
	LATAbits.LATA2 = 0;

	//Speaker
	speaker1Counter = 0;
	i=0; 
//Song2
	Song2FCounter = 0;
	Song2FCounter2 = 0;
	Song2FCounter3 = 0;
	Song2FCounter4 = 0;	
	Song2FCounter5 = 0;
	speaker2Counter = 0;

//Song3
	Song3FCounter1 = 0;
	Song3FCounter2 = 0;
	Song3FCounter3 = 0;
	Song3FCounter4 = 0;	
	Song3FCounter5 = 0;
	Song3FCounter7 = 0;
	Song3FCounter8 = 0;	
	speaker3Counter = 0;
	
}


//===================== Speaker =====================//
void Speaker_Song1(void){	
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
					
								
			if (speaker1Counter == 0 ) {
				SPEAKER = !SPEAKER;
				i++; 
			}
			
			if (speaker1Counter == m) {
				speaker1Counter = 0;
			} else {
				speaker1Counter++;
			}
}


void Speaker_Song2(void){
	if (speaker2Counter < 500) {
		if( Song2FCounter2 == 0) {
			SPEAKER = !SPEAKER;
		}
	}

	if (speaker2Counter > 700 && speaker2Counter <1000) {
		if(Song2FCounter3 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
	if (speaker2Counter > 1000 && speaker2Counter <2000) {
		if(Song2FCounter4 == 0) {
			SPEAKER = !SPEAKER;
		}
	}	
	if (speaker2Counter > 3000) {
		if(Song2FCounter5 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
	

	if (speaker2Counter > 500 && speaker2Counter <600) {
		if(Song2FCounter == 0) {
			SPEAKER = !SPEAKER;
		}
	}


			
	if (speaker2Counter == 4000) {
		speaker2Counter = 0;
	} else {
		speaker2Counter++;
	}

	if (Song2FCounter == 5) {
		Song2FCounter = 0;
	} else {
		Song2FCounter++;
	}
	if (Song2FCounter2 == 7) {
		Song2FCounter2 = 0;
	} else {
		Song2FCounter2++;
	}
	if (Song2FCounter3 == 10) {
		Song2FCounter3 = 0;
	} else {
		Song2FCounter3++;
	}
	if (Song2FCounter4 == 13) {
		Song2FCounter4 = 0;
	} else {
		Song2FCounter4++;
	}
	if (Song2FCounter5 == 13) {
		Song2FCounter5 = 0;
	} else {
		Song2FCounter5++;
	}
}


void Speaker_Song3(void){

	if (speaker3Counter < 1000) {
		if( Song3FCounter5 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
	if (speaker3Counter > 1000 && speaker3Counter < 2000) {
		if(Song3FCounter4 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
	if (speaker3Counter > 2000 && speaker3Counter <3000) {
		if(Song3FCounter3 == 0) {
			SPEAKER = !SPEAKER;
		}
	}	
	if (speaker3Counter > 3000 && speaker3Counter <4000) {				//first 4 notes
		if(Song3FCounter5 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
	if (speaker3Counter > 4000 && speaker3Counter <5000) {
		if(Song3FCounter3 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
	if (speaker3Counter > 5000 && speaker3Counter <6000) {
		if(Song3FCounter2 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
	if (speaker3Counter > 6000 && speaker3Counter <7000) {				//first 7 notes
		if(Song3FCounter1 == 0) {
			SPEAKER = !SPEAKER;
		}
	}

	if (speaker3Counter > 8000 && speaker3Counter <8500) {
		if(Song3FCounter1 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
	if (speaker3Counter > 8500 && speaker3Counter <9000) {
		if(Song3FCounter7 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
	if (speaker3Counter > 9000 && speaker3Counter <9500) {
		if(Song3FCounter1 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
	if (speaker3Counter > 9500 && speaker3Counter <10000) {
		if(Song3FCounter2 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
	if (speaker3Counter > 10000 && speaker3Counter <11000) {
		if(Song3FCounter3 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
	if (speaker3Counter > 11000 && speaker3Counter < 12000) {				//first 13 notes
		if( Song3FCounter5 == 0) {
			SPEAKER = !SPEAKER;
		}
	}

	if (speaker3Counter > 12500 && speaker3Counter < 13500) {				
		if( Song3FCounter5 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
	if (speaker3Counter > 13500 && speaker3Counter < 14500) {				
		if( Song3FCounter8 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
	if (speaker3Counter > 14500 && speaker3Counter < 16000) {				
		if( Song3FCounter5 == 0) {
			SPEAKER = !SPEAKER;
		}
	}
// Time 			
	if (speaker3Counter == 20000) {
		speaker3Counter = 0;
	} else {
		speaker3Counter++;
	}

//Frequenties
	if (Song3FCounter1 == 3) {
		Song3FCounter1 = 0;
	} else {
		Song3FCounter1++;
	}
	if (Song3FCounter2 == 5) {
		Song3FCounter2 = 0;
	} else {
		Song3FCounter2++;
	}
	if (Song3FCounter3 == 7) {
		Song3FCounter3 = 0;
	} else {
		Song3FCounter3++;
	}
	if (Song3FCounter4 == 10) {
		Song3FCounter4 = 0;
	} else {
		Song3FCounter4++;
	}
	if (Song3FCounter5 == 13) {
		Song3FCounter5 = 0;
	} else {
		Song3FCounter5++;
	}
	if (Song3FCounter7 == 1) {
		Song3FCounter7 = 0;
	} else {
		Song3FCounter7++;
	}
	if (Song3FCounter8 == 17) {
		Song3FCounter8 = 0;
	} else {
		Song3FCounter8++;
	}
}