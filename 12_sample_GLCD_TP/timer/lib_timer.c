/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        atomic functions to be used by higher sw levels
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <stdlib.h>

#include "lpc17xx.h"
#include "timer.h"




// Defines a structure to hold the callback for every combination of (timer, matchReg).
callback_t callbackTable[TIMER_TOT][MATCH_TOT] = {
	{NULL}
};

// Defines a structure to hold the callable for every
// combination of (timer, matchReg)
callable_t callableTable[TIMER_TOT][MATCH_TOT] = {
	{NULL}
};

// Defines the mathReg initial values, in case of an interrupt and there are no plans on
// resetting the timer, the values can be updated
uint32_t matchRegInitialValues[TIMER_TOT][MATCH_TOT] = {
	{0}
};

bool enabled_timers[TIMER_TOT] = {false};


/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void enable_timer( uint8_t timer_num )
{
	enabled_timers[timer_num] = true;
	
  if ( timer_num == 0 )
  {
		LPC_TIM0->TCR = 1;
		NVIC_EnableIRQ(TIMER0_IRQn);
  }
  else if(timer_num == 1)
  {
		LPC_TIM1->TCR = 1;
		NVIC_EnableIRQ(TIMER1_IRQn);
  }
	else if(timer_num == 2)
	{
		LPC_TIM2->TCR = 1;
		NVIC_EnableIRQ(TIMER2_IRQn);
	}	
	else if (timer_num == TIMER3)
	{
		LPC_TIM3->TCR = 1;
		NVIC_EnableIRQ(TIMER3_IRQn);
	}
  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void disable_timer( uint8_t timer_num )
{
	enabled_timers[timer_num] = false;
	
  if ( timer_num == 0 )
  {
		LPC_TIM0->TCR = 0;
		NVIC_DisableIRQ(TIMER0_IRQn);
  }
  else if(timer_num == 1)
  {
		LPC_TIM1->TCR = 0;
		NVIC_DisableIRQ(TIMER1_IRQn);
  }
	else if(timer_num == 2)
	{
		LPC_TIM2->TCR = 0;
		NVIC_DisableIRQ(TIMER2_IRQn);
	}
	else if (timer_num == TIMER3)
	{
		LPC_TIM3->TCR = 0;
		NVIC_DisableIRQ(TIMER3_IRQn);
	}
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void reset_timer( uint8_t timer_num )
{
  uint32_t regVal;

  if ( timer_num == 0 )
  {
		regVal = LPC_TIM0->TCR;
		regVal |= 0x02;
		LPC_TIM0->TCR = regVal;
  }
  else if (timer_num == 1)
  {
		regVal = LPC_TIM1->TCR;
		regVal |= 0x02;
		LPC_TIM1->TCR = regVal;
  }
  else if (timer_num == 2)
  {
		regVal = LPC_TIM2->TCR;
		regVal |= 0x02;
		LPC_TIM2->TCR = regVal;
  }
  else if (timer_num == 3)
  {
		regVal = LPC_TIM3->TCR;
		regVal |= 0x02;
		LPC_TIM3->TCR = regVal;
  }
  return;
}

uint32_t init_timer ( uint8_t timer_num, uint32_t Prescaler, uint8_t MatchReg, uint8_t SRImatchReg, uint32_t TimerInterval )
{
	matchRegInitialValues[timer_num][MatchReg] = TimerInterval; 
	
  if ( timer_num == 0 )
  {
		LPC_TIM0->PR = Prescaler;
		
		if(MatchReg == 0)
		{
			LPC_TIM0->MR0 = TimerInterval;
			LPC_TIM0->MCR |= SRImatchReg << 3*MatchReg ;
		}
		else if(MatchReg == 1)
		{
			LPC_TIM0->MR1 = TimerInterval;
			LPC_TIM0->MCR |= SRImatchReg << 3*MatchReg ;
		}	
		else if(MatchReg == 2)
		{
			LPC_TIM0->MR2 = TimerInterval;
			LPC_TIM0->MCR |= SRImatchReg << 3*MatchReg ;
		}		
		else if(MatchReg == 3)
		{
			LPC_TIM0->MR3 = TimerInterval;
			LPC_TIM0->MCR |= SRImatchReg << 3*MatchReg ;
		}			

	NVIC_EnableIRQ(TIMER0_IRQn);
	//NVIC_SetPriority(TIMER0_IRQn, 4);		/* less priority than buttons */
	NVIC_SetPriority(TIMER0_IRQn, 0);		/* more priority than buttons */
	return (0);
  }
  else if ( timer_num == 1 )
  {
		LPC_TIM1->PR = Prescaler;
		
		if(MatchReg == 0)
		{
			LPC_TIM1->MR0 = TimerInterval;
			LPC_TIM1->MCR |= SRImatchReg << 3*MatchReg ;
		}
		else if(MatchReg == 1)
		{
			LPC_TIM1->MR1 = TimerInterval;
			LPC_TIM1->MCR |= SRImatchReg << 3*MatchReg ;
		}	
		else if(MatchReg == 2)
		{
			LPC_TIM1->MR2 = TimerInterval;
			LPC_TIM1->MCR |= SRImatchReg << 3*MatchReg ;
		}		
		else if(MatchReg == 3)
		{
			LPC_TIM1->MR3 = TimerInterval;
			LPC_TIM1->MCR |= SRImatchReg << 3*MatchReg ;
		}	
		NVIC_EnableIRQ(TIMER1_IRQn);
	//NVIC_SetPriority(TIMER1_IRQn, 4);		/* less priority than buttons */
		NVIC_SetPriority(TIMER1_IRQn, 0);		/* more priority than buttons */
		return (0);
	}
  else if ( timer_num == 2 )
  {
		LPC_TIM2->PR = Prescaler;
		
		if(MatchReg == 0)
		{
			LPC_TIM2->MR0 = TimerInterval;
			LPC_TIM2->MCR |= SRImatchReg << 3*MatchReg ;
		}
		else if(MatchReg == 1)
		{
			LPC_TIM2->MR1 = TimerInterval;
			LPC_TIM2->MCR |= SRImatchReg << 3*MatchReg ;
		}	
		else if(MatchReg == 2)
		{
			LPC_TIM2->MR2 = TimerInterval;
			LPC_TIM2->MCR |= SRImatchReg << 3*MatchReg ;
		}		
		else if(MatchReg == 3)
		{
			LPC_TIM2->MR3 = TimerInterval;
			LPC_TIM2->MCR |= SRImatchReg << 3*MatchReg ;
		}	
		NVIC_EnableIRQ(TIMER2_IRQn);
	//NVIC_SetPriority(TIMER1_IRQn, 4);		/* less priority than buttons */
		NVIC_SetPriority(TIMER2_IRQn, 0);		/* more priority than buttons */
		return (0);
  }
	  else if ( timer_num == 3 )
  {
		LPC_TIM3->PR = Prescaler;
		
		if(MatchReg == 0)
		{
			LPC_TIM3->MR0 = TimerInterval;
			LPC_TIM3->MCR |= SRImatchReg << 3*MatchReg ;
		}
		else if(MatchReg == 1)
		{
			LPC_TIM3->MR1 = TimerInterval;
			LPC_TIM3->MCR |= SRImatchReg << 3*MatchReg ;
		}	
		else if(MatchReg == 2)
		{
			LPC_TIM3->MR2 = TimerInterval;
			LPC_TIM3->MCR |= SRImatchReg << 3*MatchReg ;
		}		
		else if(MatchReg == 3)
		{
			LPC_TIM3->MR3 = TimerInterval;
			LPC_TIM3->MCR |= SRImatchReg << 3*MatchReg ;
		}	
		NVIC_EnableIRQ(TIMER3_IRQn);
	//NVIC_SetPriority(TIMER3_IRQn, 4);		/* less priority than buttons */
		NVIC_SetPriority(TIMER3_IRQn, 0);		/* more priority than buttons */
		return (0);
	}
  return (1);
}

void init_match_reg( uint8_t timer_num, uint8_t MatchReg, uint8_t SRImatchReg, uint32_t TimerInterval, bool add_TC)
{
	LPC_TIM_TypeDef *TIM;
	volatile uint32_t *MR;
	uint32_t shift_val;
	
	switch (timer_num) {
	case TIMER0:
		TIM = LPC_TIM0;
		break;
	case TIMER1:
		TIM = LPC_TIM1;
		break;
	case TIMER2:
		TIM = LPC_TIM2;
		break;
	case TIMER3:
		TIM = LPC_TIM3;
		break;
	default:
		return;
	}
	
	switch (MatchReg) {
	case MATCH0:
		MR = &(TIM->MR0);
		shift_val = 3 * 0;
		break;
	case MATCH1:
		MR = &TIM->MR1;
		shift_val = 3 * 1;
		break;
	case MATCH2:
		MR = &TIM->MR2;
		shift_val = 3 * 2;
		break;
	case MATCH3:
		MR = &TIM->MR3;
		shift_val = 3 * 3;
		break;
	default:
		return;
	}
	
	matchRegInitialValues[timer_num][MatchReg] = TimerInterval;
	*MR = ((add_TC) ? TIM->TC : 0) + TimerInterval;					/* set the timeInterval summed to the current TimerCounter 	*/
	TIM->MCR |= SRImatchReg << shift_val;		/* set the SRI flags of the current match register					*/
}

void init_match_reg_millis(uint8_t timer, uint8_t match_reg, uint8_t SRI_match_reg, uint32_t millis, bool add_TC)
{
	uint32_t time_interval = millis * TIMER_CLK / 1000;
	init_match_reg(timer, match_reg, SRI_match_reg, time_interval, add_TC);
}



void set_callback(uint8_t timer, uint8_t matchReg, callback_t callback)
{
	callbackTable[timer][matchReg] = callback;
}

void set_callable(uint8_t timer, uint8_t matchReg, callable_t callable)
{
	callableTable[timer][matchReg] = callable;
}

callback_t get_callback(uint8_t timer, uint8_t matchReg)
{
	return callbackTable[timer][matchReg];
}

callable_t get_callable(uint8_t timer, uint8_t matchReg)
{
	return callableTable[timer][matchReg];
}

uint32_t get_matchRegInitialValue(uint8_t timer, uint8_t matchReg)
{
	return matchRegInitialValues[timer][matchReg];
}


/******************************************************************************
**                            End Of File
******************************************************************************/
