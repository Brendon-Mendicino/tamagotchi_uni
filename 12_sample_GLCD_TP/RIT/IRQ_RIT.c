/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <stdbool.h>
#include <stdint.h>

#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../joystick/joystick.h"




/**
 * @brief check if the button of the joystick is pressed
 * and also act as a debouncer.
 * 
 * @param joystick_enab 
 */
void check_for_joystick_pressed(joystick_enab_t *joystick_enab) 
{
	uint32_t FIOPIN = LPC_GPIO1->FIOPIN;
	
	/* joystick pressed */
	joystick_enab->sel_enab   = (FIOPIN & (1 << 25)) == 0 ? true : false; 
	joystick_enab->down_enab  = (FIOPIN & (1 << 26)) == 0 ? true : false;
	joystick_enab->left_eban  = (FIOPIN & (1 << 27)) == 0 ? true : false;
	joystick_enab->right_enab = (FIOPIN & (1 << 28)) == 0 ? true : false;
	joystick_enab->up_enab    = (FIOPIN & (1 << 29)) == 0 ? true : false;

	/* debounce control */
	joystick_enab->sel_int   = (joystick_enab->sel_enab   == false && joystick_enab->sel_int   == true) ? false : joystick_enab->sel_int   ; 
	joystick_enab->down_int  = (joystick_enab->down_enab  == false && joystick_enab->down_int  == true) ? false : joystick_enab->down_int  ;
	joystick_enab->left_int  = (joystick_enab->left_eban  == false && joystick_enab->left_int  == true) ? false : joystick_enab->left_int  ;
	joystick_enab->right_int = (joystick_enab->right_enab == false && joystick_enab->right_int == true) ? false : joystick_enab->right_int ;
	joystick_enab->up_int    = (joystick_enab->up_enab    == false && joystick_enab->up_int    == true) ? false : joystick_enab->up_int    ;
}


/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int down=0;
extern char led_value;

#define BRIGHT_INCREMENT  (1000)

void RIT_IRQHandler (void)
{
	joystick_enab_t joystick_enab = {
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false
	};

	led_bright_t *brightness;

	check_for_joystick_pressed(&joystick_enab);

	if (joystick_enab.sel_enab && !joystick_enab.sel_int) {
		joystick_enab.sel_int = true;

	}

	if (joystick_enab.down_enab && !joystick_enab.down_int) {
		joystick_enab.down_int = true;
		
		brightness = get_led_brighness(0);
		brightness->match0 -= BRIGHT_INCREMENT;
		set_led_brightness(0, brightness->match0, brightness->match1);
	}

	if (joystick_enab.left_eban && !joystick_enab.left_int) {
		joystick_enab.left_int = true;

		brightness = get_led_brighness(0);
		brightness->match1 += BRIGHT_INCREMENT;
		set_led_brightness(0, brightness->match0, brightness->match1);
	}

	if (joystick_enab.right_enab && !joystick_enab.right_int) {
		joystick_enab.right_int = true;

		brightness = get_led_brighness(0);
		brightness->match1 -= BRIGHT_INCREMENT;
		set_led_brightness(0, brightness->match0, brightness->match1);
	}

	if (joystick_enab.up_enab && !joystick_enab.up_int) {
		joystick_enab.up_int = true;

		brightness = get_led_brighness(0);
		brightness->match0 += BRIGHT_INCREMENT;
		set_led_brightness(0, brightness->match0, brightness->match1);
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
