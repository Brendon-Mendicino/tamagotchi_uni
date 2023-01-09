
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>

#include "tamagotchi.h"


#define BUTTON_HEIGHT   (40)
#define DATA_HEIGHT     (60)

#define BATTERY_WIDTH   (21)
#define BATTERY_HEIGHT  (14)
#define NUM_BATTERY     (4)


#define MAX_HAPPINESS   (3)
#define HAPPINESS_UPDATE (5)

#define MAX_SATIETY     (3)
#define SATIETY_UPDATE  (5)

#define FOOD_LEN       (11)

typedef uint8_t food_sprite_t[FOOD_LEN][FOOD_LEN];

typedef struct {
    uint8_t sec;
    uint8_t min;
    uint8_t hh;
} age_t;

typedef struct {
    rect_t rect;
    bool active;
    food_sprite_t *sprite;
} food_t;

typedef struct {
    age_t age;
    uint8_t happiness;
    uint8_t satiety;
    uint8_t happiness_count;
    uint8_t satiety_count;
    bool update_to_reset;
    bool dead;
    bool chasing_food;
    bool clear_food;
    uint16_t background_colour;
    uint16_t text_colour;

    food_t snack;
    food_t meal;
    food_t *active_food;
} controller_t;



void CON_init(void);

void CON_render(void);

void CON_render_data(void);

bool CON_no_food_active(void);

void CON_init_food(food_t *food);

void CON_update(void);

void CON_on_click_listener(void);


#endif
