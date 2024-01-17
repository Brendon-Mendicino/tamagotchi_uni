#include <stdint.h>
#include <stdlib.h>
#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"
#include "../timer/timer.h"


void EINT0_IRQHandler (void)	  	/* INT0														 */
{
	BUTTON_enable_debouncing(TIMER1, INT0);
	
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


