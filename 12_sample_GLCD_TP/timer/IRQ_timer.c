/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "../led/led.h"


/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

/*
static inline void set_timer_mcr(uint8_t timer, uint8_t match, uint8_t value)
{
	switch (timer) {
	case TIMER0:
		// Clear all bits
		LPC_TIM0->MCR &= ~((CONTROL_INTERRUPT | CONTROL_RESET | CONTROL_STOP) << 3 * match); 
		LPC_TIM0->MCR |= (value << 3 * match);
		break;
	case TIMER1:
		// Clear all bits
		LPC_TIM1->MCR &= ~((CONTROL_INTERRUPT | CONTROL_RESET | CONTROL_STOP) << 3 * match); 
		LPC_TIM1->MCR |= (value << 3 * match);
		break;
	case TIMER2:
		// Clear all bits
		LPC_TIM2->MCR &= ~((CONTROL_INTERRUPT | CONTROL_RESET | CONTROL_STOP) << 3 * match); 
		LPC_TIM2->MCR |= (value << 3 * match);
		break;
	case TIMER3:
		// Clear all bits
		LPC_TIM3->MCR &= ~((CONTROL_INTERRUPT | CONTROL_RESET | CONTROL_STOP) << 3 * match); 
		LPC_TIM3->MCR |= (value << 3 * match);
		break;
	}
}


static inline void check_register(uint32_t *MR, uint8_t timer, uint8_t match)
{
	*MR += get_matchRegInitialValue(timer, match);
	
	callback_t callback = get_callback(timer, match);
	
	if (callback != NULL && callback()) {
		set_timer_mcr(timer, match, CONTROL_NULL);
	}
}
*/


void TIMER0_IRQHandler (void)
{
	callable_t callable;
	
	/* Match register 0 interrupt service routine */
	if (LPC_TIM0->IR & 01)
	{
		LPC_TIM0->MR0 += get_matchRegInitialValue(TIMER0, MATCH0);

		if  ((callable = get_callable(TIMER0, MATCH0)) != NULL) {
			callable();
		}

		// In case the callback exceded the time
		LPC_TIM0->MR0 = (LPC_TIM0->MR0 < LPC_TIM0->TC - 20) ? LPC_TIM0->TC + 20 : LPC_TIM0->MR0;
		
		LPC_TIM0->IR = 1;			/* clear interrupt flag */
	}
		/* Match register 1 interrupt service routine */
	else if(LPC_TIM0->IR & 02)
  {
		LPC_TIM0->MR1 += get_matchRegInitialValue(TIMER0, MATCH1);

		if ((callable = get_callable(TIMER0, MATCH1)) != NULL) {
			callable();
		}

		// In case the callback exceded the time
		LPC_TIM0->MR1 = (LPC_TIM0->MR1 < LPC_TIM0->TC - 20) ? LPC_TIM0->TC + 20 : LPC_TIM0->MR1;
		
		LPC_TIM0->IR =  2 ;			/* clear interrupt flag */	
	}
	/* Match register 2 interrupt service routine */
	else if(LPC_TIM0->IR & 4)
  {
		LPC_TIM0->MR2 += get_matchRegInitialValue(TIMER0, MATCH2);

		if ((callable = get_callable(TIMER0, MATCH2)) != NULL) {
			callable();
		}
		
		// In case the callback exceded the time
		LPC_TIM0->MR2 = (LPC_TIM0->MR2 < LPC_TIM0->TC - 20) ? LPC_TIM0->TC + 20 : LPC_TIM0->MR2;
		
		LPC_TIM0->IR =  4 ;			/* clear interrupt flag */	
	}
		/* Match register 3 interrupt service routine */
	else if(LPC_TIM0->IR & 8)
  {
		// Update the value of MR2
		LPC_TIM0->MR3 += get_matchRegInitialValue(TIMER0, MATCH3);
		
	 
		LPC_TIM0->IR =  8 ;			/* clear interrupt flag */	
	}
	
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	
  return;
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 2 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER2_IRQHandler (void)
{
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}





/******************************************************************************
**                            End Of File
******************************************************************************/
