/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_timer, funct_timer, IRQ_timer .c files
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef __TIMER_H
#define __TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define TIMER_TOT						(4)
#define MATCH_TOT						(4)

#define TIMER0							(0)
#define TIMER1							(1)
#define TIMER2							(2)
#define TIMER3							(3)

#define MATCH0							(0)
#define MATCH1							(1)
#define MATCH2							(2)
#define MATCH3							(3)

#define CONTROL_NULL				(0)
#define CONTROL_INTERRUPT 	(1 << 0)
#define CONTROL_RESET 			(1 << 1)
#define CONTROL_STOP				(1 << 2)


#define CURRCLK 						(0x05F5E100)  	/* 100MHz */
#define TIMER_CLK						(CURRCLK >> 2)  /* CURRCLK / 4 */


typedef bool (*callback_t)(void);

typedef void (*callable_t)(void);

/* init_timer.c */
/**
 * @brief intializes the timer and enables the interrupt
 * 
 * @param timer_num timer id
 * @param Prescaler timer prescaler
 * @return uint32_t return 0 if the timer was intialized, 1 if failed
 */
extern uint32_t init_timer( uint8_t timer_num, uint32_t Prescaler );

extern void init_match_reg( uint8_t timer_num, uint8_t MatchReg, uint8_t SRImatchReg, uint32_t TimerInterval, bool add_TC);
extern void init_match_reg_millis(uint8_t timer, uint8_t match_reg, uint8_t SRI_match_reg, uint32_t millis, bool add_TC);


extern void enable_timer( uint8_t timer_num );
extern void disable_timer( uint8_t timer_num );
extern void reset_timer( uint8_t timer_num );

extern void set_callback(uint8_t timer, uint8_t matchReg, callback_t callback);
extern void set_callable(uint8_t timer, uint8_t matchReg, callable_t callable);
extern callback_t get_callback(uint8_t timer, uint8_t matchReg);
extern callable_t get_callable(uint8_t timer, uint8_t matchReg);

extern uint32_t get_matchRegInitialValue(uint8_t timer, uint8_t matchReg);

/* IRQ_timer.c */
extern void TIMER0_IRQHandler (void);
extern void TIMER1_IRQHandler (void);

#endif /* end __TIMER_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
