// UARTTestMain.c
// Runs on LM4F120/TM4C123
// Used to test the UART.c driver
// Daniel Valvano
// September 12, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013

 Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// U0Rx (VCP receive) connected to PA0
// U0Tx (VCP transmit) connected to PA1

#include "PLL.h"
#include "UART.h"
#include "ADCSWTrigger.h"
#include "../tm4c123gh6pm.h"


void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
volatile unsigned long ADCvalue;

//---------------------OutCRLF---------------------
// Output a CR,LF to UART to go to a new line
// Input: none
// Output: none
void OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}
//debug code
int main(void){
  unsigned long n;
	unsigned long volatile delay;
  PLL_Init();                           // 80 MHz
  UART_Init();              // initialize UART
  OutCRLF();
	ADC0_InitSWTriggerSeq3_Ch1();         // ADC initialization PE2/AIN1
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF; // activate port F
  delay = SYSCTL_RCGC2_R;
  GPIO_PORTF_DIR_R |= 0x04;             // make PF2 out (built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x04;          // disable alt funct on PF2
  GPIO_PORTF_DEN_R |= 0x04;             // enable digital I/O on PF2
                                        // configure PF2 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF0FF)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;               // disable analog functionality on PF
  while(1){
    GPIO_PORTF_DATA_R |= 0x04;          // profile
    ADCvalue = ADC0_InSeq3();
    GPIO_PORTF_DATA_R &= ~0x04;
    for(delay=0; delay<100000; delay++){};
		ADCvalue = n;
		UART_OutString(" ADC converted value="); UART_OutUDec(n); OutCRLF();
  }
	///////////////////////////////////////////////////////////////////////////
	 
  

  
  


  
}
