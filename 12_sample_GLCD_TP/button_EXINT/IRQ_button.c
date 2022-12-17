#include <stdint.h>
#include <stdlib.h>
#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"


char morseVector[MAX_LEN] = {0,0,0,0,2,1,1,1,2,0,1,0,0,2,0,1,3,1,1,2,0,0,1,2,1,0,2,1,0,0,2,1,1,1,3,0,1,1,1,1,2,0,0,1,1,1,4};
	
volatile char transMorse[MAX_LEN] = {0};

void EINT0_IRQHandler (void)	  	/* INT0														 */
{
	enable_debouncing(INT0);
	
	LED_OffAll();
	
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	enable_debouncing(KEY1);
	LED_OffAll();
	
	convertArray(morseVector);
	
	LED_OnAll();
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	static volatile char translation[MAX_LEN] = {0};
	volatile int numTrans;
	
	enable_debouncing(KEY2);
	
	NVIC_DisableIRQ(EINT0_IRQn);		// disable the switches inside the key2 handler
	NVIC_DisableIRQ(EINT1_IRQn);
	
	numTrans = translate_morse(morseVector, MAX_LEN, (char *)translation, MAX_LEN, 2, 3, 4);
	
	LED_OnNum(numTrans);
	
	
	NVIC_EnableIRQ(EINT0_IRQn);		// reanable the switches
	NVIC_EnableIRQ(EINT1_IRQn);
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


