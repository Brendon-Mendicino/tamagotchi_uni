#ifndef TAMAGOTCHI_H
#define TAMAGOTCHI_H

#include <stdint.h>

#define SPRITE_NUM      (3)
#define SPRITE_WIDTH    (17)
#define SPRITE_HEIGHT   (13)
#define SPRITE_SCALE    (5)

#define SCREEN_WIDTH    (SPRITE_WIDTH * SPRITE_SCALE)
#define SCREEN_HEIGHT   (SPRITE_HEIGHT * SPRITE_SCALE)


typedef uint8_t sprite_t[SCREEN_HEIGHT][SCREEN_WIDTH];

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
} rect_t;

typedef struct {
    rect_t rect;
    sprite_t *sprite;
    uint16_t colour;
    uint8_t curr_sprite;
} tamagotchi_t;



void TAM_init(void);

void TAM_render(void);



#endif
