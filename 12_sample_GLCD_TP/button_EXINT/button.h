#ifndef BUTTON_H
#define BUTTON_H


#include <stdlib.h>
#include <stdint.h>


#define INT0		(0)				/* p2.10 */
#define KEY1		(1)   		/* p2.11 */
#define KEY2		(2)				/* p2.12 */


#define MAX_LEN (100)


void BUTTON_init(void);

void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);
void EINT3_IRQHandler(void);


/* lib_button.c */
void enable_debouncing(uint8_t button);
void disable_debouncing(uint8_t button);


char getCharFromMorse(char num, char len);
void convertArray(char *array);

extern int translate_morse(char* vett_input, 
		int vet_input_lenght, 
		char* vett_output, 
		int vet_output_lenght,
		char change_symbol, 
		char space, 
		char sentence_end);
		
		
#endif
