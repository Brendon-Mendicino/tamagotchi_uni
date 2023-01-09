																			 /*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_joystick, funct_joystick .c files
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#ifndef JOYSTICK_H
#define JOYSTICK_H


#include <stdint.h>
#include <stdbool.h>


typedef struct {
	bool sel_enab   :1;
	bool sel_int    :1;
	bool down_enab  :1;
	bool down_int   :1;
	bool left_eban  :1;
	bool left_int   :1;
	bool right_enab :1;
	bool right_int  :1;
	bool up_enab    :1;
	bool up_int     :1;
} joystick_enab_t;



void joystick_init(void);



#endif
