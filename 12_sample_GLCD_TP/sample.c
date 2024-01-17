/****************************************Copyright (c)****************************************************
**
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <time.h>

#include "LPC17xx.h"
#include "defines/defines.h"
#include "GLCD/GLCD.h"
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "button_EXINT/button.h"
#include "joystick/joystick.h"
#include "led/led.h"
#include "adc/adc.h"
#include "tamagotchi/controller.h"
#include "sound/sound.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

extern controller_t controller;


void sel_callable(void)
{
	if (controller.dead) {
		SOUND_click();
		CON_init();
		LCD_Clear(Black);
		CON_render();
	}
}

void left_callable(void)
{
	if (CON_no_food_active()) {
		SOUND_click();
		CON_init_food(&(controller.meal));
	}
}

void right_callable(void){
	if (CON_no_food_active()) {
		SOUND_click();
		CON_init_food(&(controller.snack));
	}
}


/**
 * @brief periodically read the POTENTIOMETER values.
 * 
 * @param value 
 */
void adc_potentiometer_consumer(uint16_t *value)
{
	uint32_t volume = div(*value * MAX_VOLUME, MAX_ADGDR_VALUE + 1).quot;

	if (SOUND_get_volume() == volume) {
		return;
	}

	SOUND_set_volume(volume);
}


/**
 * @brief listens to click on the touchpanel
 * 
 */
void click_listener(void)
{
	if (getDisplayPoint(&display, Read_Ads7846(), &matrix)) {
		CON_click_listener(display.x, display.y);
	}
}


int main(void)
{
	SystemInit(); /* System Initialization (i.e., PLL)  */
	
	LCD_Initialization();
  
	TP_Init();
	TouchPanel_Calibrate();

	LCD_Clear(Black);
	 
	CON_init();
	CON_render();

	/* random number init */
	srand(0x12bac123);

	TIMER_init(TIMER0, 2, 0);
	
	// CONTROLLER UPDATE RATE (1 sec)
	TIMER_match_reg(TIMER0, MATCH1, CONTROL_INTERRUPT, TIMER_CLK / DIV_SCALE, true);
	TIMER_set_callable(TIMER0, MATCH1, CON_update);
	
	// SCREEN UPDATE FPS (1/15 sec)
	TIMER_match_reg(TIMER0, MATCH2, CONTROL_INTERRUPT, TIMER_CLK / 15, true);
	TIMER_set_callable(TIMER0, MATCH2, CON_render_data);
	
	TIMER_enable(TIMER0);

	/* JOYSTICK initalization */
	JOY_init(true);
	JOY_set_callable(J_SEL, sel_callable);
	JOY_set_callable(J_LEFT, left_callable);
	JOY_set_callable(J_RIGHT, right_callable);
	
	/* RIT initialization */
	// JOYSTICK READ FPS (1/30 sec)
	RIT_init(CURRCLK / 30, 1);
	RIT_set_callable(JOY_run_directions);
	RIT_enable();

	/* CONVERTER INIT */
	DAC_init();
	ADC_init(10);
	ADC_set_consumer((consumer_t) adc_potentiometer_consumer);
	TIMER_init(TIMER1, 0, 0);

	/* SET UP TIMER FOR CONVERSION every 20 FPS */
	TIMER_init(TIMER2, 10, 0);
	TIMER_match_reg(TIMER2, MATCH1, CONTROL_INTERRUPT, TIMER_CLK / 20, true); /* 50 ms */
	TIMER_set_callable(TIMER2, MATCH1, ADC_start_conversion);
	TIMER_enable(TIMER2);

	/* SET UP TIMER FOR TOUCH */
	TIMER_match_reg(TIMER2, MATCH2, CONTROL_INTERRUPT, TIMER_CLK / 20, true); /* 50 ms */
	TIMER_set_callable(TIMER2, MATCH2, click_listener);


	LPC_SC->PCON |= 0x1; /* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);

	while (1)
	{
		__ASM("wfi");
	}
}

/*********************************************************************************************************
	END FILE
*********************************************************************************************************/
