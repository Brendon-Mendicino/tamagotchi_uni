
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "controller.h"
#include "tamagotchi.h"
#include "../GLCD/GLCD.h"
#include "../GLCD/AsciiLib.h"
#include "../TouchPanel/TouchPanel.h"
#include "../sound/sound.h"




uint8_t battery[NUM_BATTERY][BATTERY_HEIGHT][BATTERY_WIDTH] = {
{
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,0},
{1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,0},
{1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,0},
{1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1},
{1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1},
{1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,0},
{1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,0},
{1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
},

{
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,1,1,0},
{1,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,1,1,0},
{1,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,1,1,0},
{1,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,1,1,1},
{1,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,1,1,1},
{1,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,1,1,0},
{1,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,1,1,0},
{1,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,1,1,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
},

{
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
{1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
{1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
},

{
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
},
};
uint8_t snack[FOOD_LEN][FOOD_LEN]={
{0,0,1,0,0,0,0,0,0,0,0},
{0,1,1,0,0,0,0,0,0,0,0},
{1,1,1,0,0,0,0,0,0,0,0},
{0,0,0,1,1,1,0,0,0,0,0},
{0,0,0,1,1,1,1,0,0,0,0},
{0,0,0,1,1,1,1,1,0,0,0},
{0,0,0,0,1,1,1,1,0,0,0},
{0,0,0,0,0,1,1,1,0,0,0},
{0,0,0,0,0,0,0,0,1,1,1},
{0,0,0,0,0,0,0,0,1,1,0},
{0,0,0,0,0,0,0,0,1,0,0},
};
uint8_t meal[FOOD_LEN][FOOD_LEN]={
{1,1,1,1,0,0,0,0,0,0,0},
{1,1,1,1,1,1,0,0,0,0,0},
{1,1,1,1,1,1,1,0,0,0,0},
{1,1,1,1,1,1,1,1,0,0,0},
{0,1,1,1,1,1,1,1,0,0,0},
{0,0,1,1,1,1,1,1,0,0,0},
{0,0,0,0,0,1,0,1,1,0,0},
{0,0,0,0,0,0,1,0,1,1,1},
{0,0,0,0,0,0,0,1,0,0,1},
{0,0,0,0,0,0,0,1,0,0,1},
{0,0,0,0,0,0,0,1,1,1,0},
};


const uint8_t sound_icon[SOUND_ICON_LEN][SOUND_ICON_LEN] = {
{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
};

const uint8_t sound_volume_icon[MAX_VOLUME][SOUND_LEVEL_ICON_LEN][SOUND_LEVEL_ICON_LEN] = {
{
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,1,1,0,0,0,0,0,0,0,0,0},
{0,1,1,1,0,0,0,0,0,0,0,0,0},
{0,1,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,0,0,0,0},
{0,0,0,0,0,0,1,1,1,0,0,0,0},
{0,1,1,1,0,0,1,1,1,0,0,0,0},
{0,1,1,1,0,0,1,1,1,0,0,0,0},
{0,1,1,1,0,0,1,1,1,0,0,0,0},
{0,0,0,0,0,0,1,1,1,0,0,0,0},
{0,0,0,0,0,0,1,1,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0},
},
{
{0,0,0,0,0,0,0,0,0,0,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1},
{0,0,0,0,0,0,1,1,1,0,1,1,1},
{0,0,0,0,0,0,1,1,1,0,1,1,1},
{0,1,1,1,0,0,1,1,1,0,1,1,1},
{0,1,1,1,0,0,1,1,1,0,1,1,1},
{0,1,1,1,0,0,1,1,1,0,1,1,1},
{0,0,0,0,0,0,1,1,1,0,1,1,1},
{0,0,0,0,0,0,1,1,1,0,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1},
{0,0,0,0,0,0,0,0,0,0,1,1,1},
},
};


static char text[100];

controller_t controller;

extern tamagotchi_t entity;


static void draw_battery(uint32_t level, bool left_battery)
{
	uint16_t row, col;
	uint16_t shift_amt = (left_battery) ? 0 : MAX_X / 2;

	for (row = 0; row < BATTERY_HEIGHT; row++) {
		for (col = 0; col < BATTERY_WIDTH; col++) {
			
			// Draw the battery
			if (battery[level][row][col] == 1) {
				LCD_SetPoint(30 + col + shift_amt, DATA_HEIGHT - BATTERY_HEIGHT - 10 + row, (level > 1) ? Red : Green);
			}
			else {
				LCD_SetPoint(30 + col + shift_amt, DATA_HEIGHT - BATTERY_HEIGHT - 10 + row, controller.background_colour);
			}
		}
	}
}

static void draw_speaker(bool fast_draw)
{
	int row, col;
	volatile uint32_t volume = SOUND_get_volume();

	if (!fast_draw) {
		for (row = 0; row < SOUND_ICON_LEN; row++) {
			for (col = 0; col < SOUND_ICON_LEN; col++) {
				if (sound_icon[row][col]) {
					LCD_SetPoint(col + MAX_X - SOUND_ICON_LEN - SOUND_LEVEL_ICON_LEN - 5, row + 5, controller.text_colour);
				}
			}
		}
	}
	
	for (row = 0; row < SOUND_LEVEL_ICON_LEN; row++) {
		for (col = 0; col < SOUND_LEVEL_ICON_LEN; col++) {
			if (sound_volume_icon[volume][row][col]) {
				LCD_SetPoint(col + MAX_X - SOUND_LEVEL_ICON_LEN - 5, row + 5, controller.text_colour);
			}
			else {
				LCD_SetPoint(col + MAX_X - SOUND_LEVEL_ICON_LEN - 5, row + 5, controller.background_colour);
			}
		}
	}
}

static void update_age(void)
{
	controller.age.sec = (controller.age.sec + 1) % 60;
	controller.age.min = (controller.age.min + ((controller.age.sec == 0) ? 1 : 0)) % 60;
	controller.age.hh  = (controller.age.hh  + ((controller.age.min == 0 && controller.age.sec == 0) ? 1 : 0));
}

void render_food(void)
{
	int row, col;
	uint16_t colour;

	if (controller.chasing_food == false && controller.clear_food == false) {
		return;
	}

	if (controller.clear_food) {
		controller.clear_food = false;
		colour = Black;
	}
	else {
		colour = Green;
	}

	for (row = 0; row < controller.active_food->rect.width; row++) {
		for (col = 0; col < controller.active_food->rect.height; col++) {
			if ((*controller.active_food->sprite)[row][col]) {
				LCD_SetPoint(controller.active_food->rect.x + col, controller.active_food->rect.y + row, colour);
			}
		}
	}
}

/**
 * @brief move the entity towards the food
 * 
 * @param e entity rect
 * @param f food rect
 */
void move_to_food(rect_t *e, rect_t *f)
{

	volatile int32_t modulo;
	volatile int32_t len;
	
	modulo = 10;
	// calc the length between the food and the entity.
	len = (int32_t)(sqrtl((int32_t)(e->x - f->x) * (int32_t)(e->x - f->x) + (int32_t)(e->y - f->y) * (int32_t)(e->y - f->y) ));

	TAM_move(
		(int16_t)(div((f->x - e->x) * modulo, len).quot),
		(int16_t)(div((f->y - e->y) * modulo, len).quot)
	);
}

void CON_init(void)
{
	controller.age.sec = 0;
	controller.age.min = 0;
	controller.age.hh = 0;

	controller.happiness = MAX_HAPPINESS;
	controller.satiety = MAX_SATIETY;
	controller.dead = false;
	controller.chasing_food = false;
	controller.update_to_reset = false;
	controller.death_text_wrote = false;


	controller.happiness_count = 0;
	controller.satiety_count = 0;

	controller.background_colour = Grey;
	controller.text_colour = Green;

	controller.meal.active = false;
	controller.meal.rect.height = FOOD_LEN;
	controller.meal.rect.width = FOOD_LEN;
	controller.meal.sprite = &(meal);
	
	controller.snack.active = false;
	controller.snack.rect.height = FOOD_LEN;
	controller.snack.rect.width = FOOD_LEN;
	controller.snack.sprite = &(snack);

	controller.active_food = NULL;
	
	TAM_init();
}


void CON_update(void)
{
	if (!controller.dead) {
		update_age();

		// Happiness and statiety only decrease after 5 update cycles.
		controller.happiness -= (controller.happiness_count == HAPPINESS_UPDATE - 1 && controller.happiness != 0) ? 1 : 0;
		controller.satiety   -= (controller.satiety_count == SATIETY_UPDATE - 1     && controller.satiety != 0)   ? 1 : 0;

		controller.happiness_count = (controller.happiness_count + 1) % HAPPINESS_UPDATE;
		controller.satiety_count   = (controller.satiety_count + 1) % SATIETY_UPDATE;
	}

	// Check if the tamagotchi died
	if (controller.dead != true && controller.happiness == 0 && controller.satiety == 0) {
		controller.update_to_reset = true;
		controller.dead = true;

		// Tamagotchi's death sound
		SOUND_death();
	}

	TAM_update();
}


#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a < b) ? b : a)

bool collision_detection(rect_t *a, rect_t *b) 
{
	// x check
	if (a->x < b->x) {
		if (a->x + a->width < b->x) {
			return false;
		}
	}
	else {
		if (b->x + b->width < a->x) {
			return false;
		}
	}

	// y check
	if (a->y < b->y) {
		if (a->y + a->height < b->y) {
			return false;
		}
	}
	else {
		if (b->y + b->height < a->y) {
			return false;
		}
	}

	return true;
}


void CON_init_food(food_t *food)
{
	food->active = true;
	food->rect.x = rand() % (MAX_X - food->rect.width);
	food->rect.y = DATA_HEIGHT + (rand() % (MAX_Y - food->rect.height - DATA_HEIGHT - BUTTON_HEIGHT));

	controller.active_food = food;
	controller.chasing_food = true;

}

bool CON_no_food_active(void)
{
	return (controller.snack.active == false && controller.meal.active == false);
}


void CON_on_click_listener(void)
{
	// If there is no touch return
	if (!getDisplayPoint(&display, Read_Ads7846(), &matrix)) {
		return;
	}

	// If the touch is outside the screen return
	if (display.x > MAX_X || display.y > MAX_Y) {
		return;
	}

	// If the touch is not inside the button return
	if (display.y < MAX_Y - BUTTON_HEIGHT) {
		return;
	}

	if (controller.dead) {
		// Reset the game
		CON_init();
		CON_render();
	}
	else {
		if (display.x > MAX_X/2 && CON_no_food_active()) {
			CON_init_food(&controller.snack);
		}
		else if (display.x < MAX_X/2 && CON_no_food_active()) {
			CON_init_food(&controller.meal);
		}
	}
}


void reset_cuddling(void)
{
	entity.is_cuddling = false;
	TIMER_match_reg(TIMER2, MATCH0, CONTROL_NULL, 0, false);
}

void reset_eating(void)
{
	entity.is_eating = false;
	TIMER_match_reg(TIMER2, MATCH3, CONTROL_NULL, 0, false);
}

/**
 * @brief Checks if the tamagotchi can be cuddled, if it can it refilles the happinyess level.
 * 
 * @param x x coordinate
 * @param y y coordinate
 */
void CON_click_listener(uint16_t x, uint16_t y)
{
	if (entity.is_cuddling) {
		return;
	}

	if (controller.dead || entity.is_eating) {
		return;
	}

	if ((x >= entity.rect.x && x <= entity.rect.x + entity.rect.width) &&
		(y >= entity.rect.y && y <= entity.rect.y + entity.rect.height)) {
		
		entity.is_cuddling = true;
		controller.happiness = MAX_HAPPINESS;
		controller.happiness_count = 0;

		SOUND_cuddles();
		TIMER_match_reg(TIMER2, MATCH0, CONTROL_INTERRUPT, TIMER_CLK * 2 / DIV_SCALE, true);  /* 2 sec */
		TIMER_set_callable(TIMER2, MATCH0, reset_cuddling);
	}
}






void CON_render(void)
{
	uint16_t row;

	// Draw data context
	for (row = 0; row < DATA_HEIGHT; row++) {
		LCD_DrawLine(0, row, MAX_X, row, controller.background_colour);
	}

	sprintf(text, "AGE => %02d:%02d:%02d", controller.age.hh, controller.age.min, controller.age.sec);
	GUI_Text(40, 0, (uint8_t *)text, controller.text_colour, controller.background_colour);
	GUI_Text(25, 20, (uint8_t *)"HAPPINESS", controller.text_colour, controller.background_colour);
	GUI_Text(25 + MAX_X/2, 20, (uint8_t *)"SATIETY", controller.text_colour, controller.background_colour);

	draw_battery(NUM_BATTERY - controller.happiness - 1, true);
	draw_battery(NUM_BATTERY - controller.satiety - 1, false);

	draw_speaker(false);


	// Draw button context
	for (row = MAX_Y-1; row >= MAX_Y - BUTTON_HEIGHT; row--) {
		LCD_DrawLine(0, row, MAX_X, row, controller.background_colour);
	}

	if (controller.dead) {
		controller.update_to_reset = false;
		GUI_Text(80, MAX_Y - BUTTON_HEIGHT + 10, (uint8_t *)"RESET", controller.text_colour, controller.background_colour);
	}
	else {
		LCD_DrawLine(MAX_X / 2, MAX_Y - BUTTON_HEIGHT, MAX_X / 2, MAX_Y, Black);
		GUI_Text(25, MAX_Y - BUTTON_HEIGHT + 10, (uint8_t *)"MEAL", controller.text_colour, controller.background_colour);
		GUI_Text(25 + MAX_X/2, MAX_Y - BUTTON_HEIGHT + 10, (uint8_t *)"SNACK", controller.text_colour, controller.background_colour);
	}

	TAM_render();
}

/**
 * @brief fast render
 * 
 */
void CON_render_data(void)
{
	int row;

	sprintf(text, "AGE => %02d:%02d:%02d", controller.age.hh, controller.age.min, controller.age.sec);
	GUI_Text(40, 0, (uint8_t *)text, controller.text_colour, controller.background_colour);

	draw_battery(NUM_BATTERY - controller.happiness - 1, true);
	draw_battery(NUM_BATTERY - controller.satiety - 1, false);

	draw_speaker(true);

	// If the reset flag is active, redraw the bottons
	if (controller.update_to_reset) {
		controller.update_to_reset = false;

		// Clear previous text to redraw the RESET text
		for (row = MAX_Y-1; row >= MAX_Y - BUTTON_HEIGHT; row--) {
			LCD_DrawLine(0, row, MAX_X, row, controller.background_colour);
		}
		GUI_Text(80, MAX_Y - BUTTON_HEIGHT + 10, (uint8_t *)"RESET", controller.text_colour, controller.background_colour);
	}


	// Tamagotchi logic
	if (controller.dead) {
		if (entity.rect.x > MAX_X) {

			// If the text has already been wrote, just exit to avoid uneccessary overhead
			if (controller.death_text_wrote) {
				return;
			}

			GUI_Text(0, MAX_Y/2, (uint8_t *)"YOU CAN'T EVEN PLAY THIS GAME", White, Red);
			GUI_Text(0, MAX_Y/2 + 20, (uint8_t *)"YOU ARE SO TERRIBLE...", White, Red);
			GUI_Text(0, MAX_Y/2 + 40, (uint8_t *)"GO BACK AND PLAY WITH MINECRAFT", White, Red);

			controller.death_text_wrote = true;
		}

		TAM_move((entity.rect.x <= MAX_X) ? 5 : 0, 0);
	}
	else if (entity.is_cuddling) {
		// Don't do anything
	}
	else if (entity.is_eating) {
		// Don't do anything
	}
	// If the enity is chasing the food
	else if (controller.chasing_food) {
		move_to_food(&(entity.rect), &(controller.active_food->rect));

		// If collided with the food it starts eating it
		if (collision_detection(&entity.rect, &controller.active_food->rect)) {

			if (controller.meal.active) {
				entity.is_eating = true;
			}
			else if (controller.snack.active) {
				entity.is_eating = true;
			}

			// Start the eating sound
			SOUND_eating();
			TIMER_match_reg(TIMER2, MATCH3, CONTROL_INTERRUPT, TIMER_CLK / DIV_SCALE, true);  /* 2 sec */
			TIMER_set_callable(TIMER2, MATCH3, reset_eating);


			// Increase happiness/satiety levels
			if (controller.snack.active) {
				controller.happiness_count = HAPPINESS_UPDATE;
				controller.happiness += (controller.happiness != MAX_HAPPINESS) ? 1 : 0;
			}
			if (controller.meal.active) {
				controller.satiety_count = HAPPINESS_UPDATE;
				controller.satiety	 += (controller.satiety != MAX_SATIETY) ? 1 : 0;
			}

			controller.active_food->active = false;
			controller.chasing_food = false;
			controller.clear_food = true;
		}
	}

	render_food();

	TAM_clear_render();
	TAM_render();
}
