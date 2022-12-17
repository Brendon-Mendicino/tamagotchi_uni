
#include "button.h"
#include "lpc17xx.h"
#include "../led/led.h"
#include "../timer/timer.h"


char tt1[] = {'E', 'T'};
char tt2[] = {'I', 'A', 'N', 'M'};
char tt3[] = {'S', 'U', 'R', 'W', 'D', 'K', 'G', 'O'};
char tt4[] = {'H', 'V', 'F', '?', 'L', '?', 'P', 'J', 'B', 'X', 'C', 'Y', 'Z', 'Q', '?', '?'};
char tt5[] = {'5', '4', '?', '3', '?', '?', '?', '2', '?', '?', '?', '?', '?', '?', '?', '1', '6', '?', '?', '?', '?', '?', '?', '?', '7', '?', '?', '?', '8', '?', '9', '0'};

char *transTable[5] = {
	tt1,
	tt2,
	tt3,
	tt4,
	tt5
};



/**
 * @brief  Function that initializes Buttons
 */
void BUTTON_init(void) {

  LPC_PINCON->PINSEL4    |= (1 << 20);		 /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 10);    /* PORT2.10 defined as input          */

  LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 11);    /* PORT2.11 defined as input          */
  
  LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 12);    /* PORT2.12 defined as input          */

  LPC_SC->EXTMODE = 0x7;

  NVIC_EnableIRQ(EINT2_IRQn);              /* enable irq in nvic                 */
	NVIC_SetPriority(EINT2_IRQn, 1);				 /* priority, the lower the better     */
  NVIC_EnableIRQ(EINT1_IRQn);              /* enable irq in nvic                 */
	NVIC_SetPriority(EINT1_IRQn, 2);				 
  NVIC_EnableIRQ(EINT0_IRQn);              /* enable irq in nvic                 */
	NVIC_SetPriority(EINT0_IRQn, 3);				 /* decreasing priority	from EINT2->0	 */
}


bool int0_callback(void) 
{
	if ((LPC_GPIO2->FIOPIN & (1 << 10)) != 0) { /* checks if p2.10 is released					*/
		LPC_PINCON->PINSEL4 |= (0x01 << 20);			/* enable p2.10 EINT0 									*/
		return true;
	}
	return false;
}

bool key1_callback(void) 
{
	if ((LPC_GPIO2->FIOPIN & (1 << 11)) != 0) { /* checks if p2.11 is released					*/
		LPC_PINCON->PINSEL4 |= (0x01 << 22);			/* enable p2.11 EINT1 									*/
		return true;
	}
	return false;
}

bool key2_callback(void) 
{
	if ((LPC_GPIO2->FIOPIN & (1 << 12)) != 0) { /* checks if p2.12 is released					*/
		LPC_PINCON->PINSEL4 |= (0x01 << 24);			/* enable p2.10 EINT2 									*/
		return true;
	}
	return false;
}

void enable_debouncing(uint8_t button)
{
	uint8_t match;
	callback_t callback;
	uint32_t milliseconds = 50;
	uint32_t time_interval = milliseconds * TIMER_CLK / 1000;

	switch (button) {
		case INT0:
			LPC_PINCON->PINSEL4 &= ~(0x03 << 20);		/* reset p2.10 */
			callback = int0_callback;
			match = MATCH0;
			break;
		case KEY1:
			LPC_PINCON->PINSEL4 &= ~(0x03 << 22); 	/* reset p2.11 */
			callback = key1_callback;
			match = MATCH1;
			break;
		case KEY2:
			LPC_PINCON->PINSEL4 &= ~(0x03 << 24); 	/* reset p2.12 */
			callback = key2_callback;
			match = MATCH2;
			break;
		default:
			// Throw an error
			return;
	}
	
	init_match_reg(TIMER0, match, CONTROL_INTERRUPT, time_interval, true);
	set_callback(TIMER0, match, callback);
}


void disable_debouncing(uint8_t button)
{
	
}


/**
 *
 */
char getCharFromMorse(char num, char len) {
	return transTable[len-1][num];
}

void convertArray(char *array)
{
	volatile char result[MAX_LEN];
	int i;
	int resLen;
	char len = 0;
	char num = 0;
	int readSymb = 0;
	for (i = 0, resLen = 0; i < MAX_LEN; i++, len++) {
		if (array[i] == 2) {
			result[resLen++] = getCharFromMorse(num, len-1);
			LED_OnNum(++readSymb);
			
			len = 0;
			num = 0;
			continue;
		}
		
		if (array[i] == 3) {
			result[resLen++] = getCharFromMorse(num, len-1);
			LED_OnNum(++readSymb);
			result[resLen++] = ' ';
			
			len = 0;
			num = 0;
			continue;
		}
		
		if (array[i] == 4) {
			result[resLen++] = getCharFromMorse(num, len-1);
			LED_OnNum(++readSymb);
			break;
		}

		num = (num << 1);
		num |= array[i];
	}
}
