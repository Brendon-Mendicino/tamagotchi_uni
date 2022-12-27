
#include "tamagotchi.h"
#include "../GLCD/GLCD.h"

uint8_t sprite[SPRITE_NUM][SPRITE_HEIGHT][SPRITE_WIDTH] = {
{
{0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,0,0},
{0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0},
{0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0},
{0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,1,0},
{0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0},
{1,0,0,0,1,0,0,0,1,0,0,1,0,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0},
{0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0},
{0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
{0,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
},

{
{0,1,1,0,1,0,0,1,0,1,1,0,0,0,1,0,0},
{0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0},
{0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0},
{0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,1,0},
{0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0},
{1,0,0,0,1,0,0,0,1,0,0,1,0,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0},
{0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0},
{0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
{0,0,1,1,0,0,1,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
},

{
{0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
{0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,0,0},
{0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0},
{0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,1,0},
{0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0},
{1,0,0,1,0,0,0,1,0,0,0,1,0,0,1,1,0},
{1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0},
{0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0},
{0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0},
{0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
},

};

uint8_t sprite_scale[SPRITE_NUM][SPRITE_HEIGHT * SPRITE_SCALE][SPRITE_WIDTH * SPRITE_SCALE];


tamagotchi_t entity;



void TAM_init(void)
{
	int num, row, col, scale;

	for (num = 0; num < SPRITE_NUM; num++) {
		for (row = 0; row < SPRITE_HEIGHT; row++) {
			for (col = 0; col < SPRITE_WIDTH; col++) {
				for (scale = 0; scale < SPRITE_SCALE * SPRITE_SCALE; scale++) {
					sprite_scale[num][row * SPRITE_SCALE + (scale / SPRITE_SCALE)][col * SPRITE_SCALE + (scale % SPRITE_SCALE)] = sprite[num][row][col];
				}
			}
		}
	}

	entity.curr_sprite = 0;
	entity.sprite = &(sprite_scale[0]);
	entity.colour = White;


	entity.rect.x = MAX_X/3;
	entity.rect.y = MAX_Y/2;
	entity.rect.height = SCREEN_HEIGHT;
	entity.rect.width = SCREEN_WIDTH;

	entity.old_rect = entity.rect;

	entity.is_eating = false;
}



void TAM_render(void)
{
	int row, col;
	sprite_t *sprite = entity.sprite;

	if (entity.is_eating != 1) {
		for (row = 0; row < entity.rect.height; row++) {
			for (col = 0; col < entity.rect.width; col++) {

				// Print the sprite to the screen
				if ((*sprite)[row][col] == 1) {
					LCD_SetPoint(entity.rect.x + col, entity.rect.y + row, entity.colour);
				}
			}
		}
	}
	else {
		for (row = 0; row < entity.rect.height; row++) {
			for (col = 0; col < entity.rect.width; col++) {

				// Print the sprite to the screen
				if ((*sprite)[entity.rect.height - row - 1][col] == 1) {
					LCD_SetPoint(entity.rect.x + col, entity.rect.y + row, entity.colour);
				}
			}
		}
	}
}

void TAM_clear_render(void)
{
	int row;
	for (row = 0; row < entity.old_rect.height; row++) {
		LCD_DrawLine(entity.old_rect.x, entity.old_rect.y + row, entity.old_rect.x + entity.old_rect.width, entity.old_rect.y + row, Black);
	}

	entity.old_rect = entity.rect;
}

void TAM_move(int16_t dx, int16_t dy)
{
	entity.rect.x += dx;
	entity.rect.y += dy;
}

void TAM_update(void) 
{
	if (entity.is_eating != 0) {
		entity.is_eating = (entity.is_eating == 2) ? 1 : 0;
	}

	entity.curr_sprite = (entity.curr_sprite + 1) % SPRITE_NUM;
	entity.sprite = &(sprite_scale[entity.curr_sprite]);
}

