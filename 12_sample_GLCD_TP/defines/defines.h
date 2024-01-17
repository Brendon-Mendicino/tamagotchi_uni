#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>
#include <stdbool.h>

#ifdef EMUL
#define DIV_SCALE (25)
#else
#define DIV_SCALE (1)
#endif

typedef void (*callable_t)(void);

typedef void (*consumer_t)(void *);


#endif
