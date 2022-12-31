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
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "tamagotchi/tamagotchi.h"
#include "tamagotchi/controller.h"
#include "RIT/RIT.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int main(void)
 {
	SystemInit();  												/* System Initialization (i.e., PLL)  */
	
	LCD_Initialization();
	
  
	TP_Init();
	TouchPanel_Calibrate();

	LCD_Clear(Black);
	 
	TAM_init();
	CON_init();
	CON_render();

	/* random number init */
	srand(0x9d42efec);

	
	//init_timer(0, 0x1312D0 ); 						/* 50ms * 25MHz = 1.25*10^6 = 0x1312D0 */
	//init_timer(0, 0x6108 ); 						  /* 1ms * 25MHz = 25*10^3 = 0x6108 */
	//init_timer(0, 0x4E2 ); 						    /* 500us * 25MHz = 1.25*10^3 = 0x4E2 */
	init_timer(TIMER0, 0); 						    	

	// TOUCH MATCHING
	//init_match_reg(TIMER0, MATCH0, CONTROL_INTERRUPT, 0xC8, true); /* 8us * 25MHz = 200 ~= 0xC8 */
	init_match_reg(TIMER0, MATCH0, CONTROL_INTERRUPT, TIMER_CLK / 20, true);
	set_callable(TIMER0, MATCH0, CON_on_click_listener);


	// CONTROLLER UPDATE RATE (1 sec)
	init_match_reg(TIMER0, MATCH1, CONTROL_INTERRUPT, TIMER_CLK / 10, true);
	set_callable(TIMER0, MATCH1, CON_render_data);

	// SCREEN UPDATE FPS (30)
	init_match_reg(TIMER0, MATCH2, CONTROL_INTERRUPT, TIMER_CLK / 5, true);
	set_callable(TIMER0, MATCH2, CON_update);

	
	enable_timer(TIMER0);

	/* RIT initialization */
	init_RIT(CURRCLK / 30);
	enable_RIT();
	
	

	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
	while (1) {
		__ASM("wfi");
	}
}

/*********************************************************************************************************
	END FILE
*********************************************************************************************************/
