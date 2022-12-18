
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>


#define BUTTON_HEIGHT   (40)
#define DATA_HEIGHT     (60)

#define BATTERY_WIDTH   (21)
#define BATTERY_HEIGHT  (14)
#define NUM_BATTERY     (4)

#define MAX_HAPPINESS   (3)
#define MAX_SATIETY     (3)


typedef struct {
    uint8_t sec;
    uint8_t min;
    uint8_t hh;
} age_t;

typedef struct {
    age_t age;
    uint8_t happiness;
    uint8_t satiety;
    bool dead;
    uint16_t background_colour;
    uint16_t text_colour;
} controller_t;



void CON_init(void);

void CON_render(void);





#endif
