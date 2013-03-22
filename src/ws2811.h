/*
 * This code is based on the git://github.com/jamuraa/xmega-ws2811-bitbang.git project.
 *
 */

#include "globals.h"

#ifndef __WS2811_H__
#define __WS2811_H__

#include <util/delay.h>

/* ------------------------------------------------------------------------- */

#define CHANNELS 120

/* ------------------------------------------------------------------------- */

uint8_t r[CHANNELS];
uint8_t g[CHANNELS];
uint8_t b[CHANNELS];

/* ------------------------------------------------------------------------- */

#define NOP __asm__ __volatile__ ("cp r0,r0\n");

#define NOP2 NOP NOP
#define NOP1 NOP
#define NOP3 NOP NOP2
#define NOP4 NOP NOP3
#define NOP5 NOP NOP4
#define NOP6 NOP NOP5
#define NOP7 NOP NOP6
#define NOP8 NOP NOP7
#define NOP9 NOP NOP8
#define NOP10 NOP NOP9
#define NOP11 NOP NOP10
#define NOP12 NOP NOP11
#define NOP13 NOP NOP12
#define NOP14 NOP NOP13
#define NOP15 NOP NOP14

#define NOP_SHORT NOP4
#define NOP_LONG NOP12

/* ------------------------------------------------------------------------- */

#define WS2811_PORT PORTA
#define WS2811_PIN PIN1_bm

/* ------------------------------------------------------------------------- */

#define WS2811_BIT_SET(X, N) \
    if ( X & (1<<N)) { \
        WS2811_PORT.OUT |=  WS2811_PIN; \
        NOP_LONG; \
        WS2811_PORT.OUT &= ~WS2811_PIN; \
        NOP_SHORT; \
    } else \
        { \
        WS2811_PORT.OUT |=  WS2811_PIN; \
        NOP_SHORT; \
        WS2811_PORT.OUT &= ~WS2811_PIN; \
        NOP_LONG; \
    }

#define WS2811_BIT_ALL(cur_byte) \
    WS2811_BIT_SET(cur_byte, 7); \
    WS2811_BIT_SET(cur_byte, 6); \
    WS2811_BIT_SET(cur_byte, 5); \
    WS2811_BIT_SET(cur_byte, 4); \
    WS2811_BIT_SET(cur_byte, 3); \
    WS2811_BIT_SET(cur_byte, 2); \
    WS2811_BIT_SET(cur_byte, 1); \
    WS2811_BIT_SET(cur_byte, 0);

#define WS2811_ALL() \
    uint8_t i = 0; \
    for (i = 0; i < CHANNELS; i++) \
    { \
        WS2811_BIT_ALL(g[i] & 0xff); \
        WS2811_BIT_ALL(r[i] & 0xff); \
        WS2811_BIT_ALL(b[i] & 0xff); \
    }

#define WS2811_UPDATE_COLORS() \
    /* Reset */ \
    WS2811_PORT.OUT |= WS2811_PIN; \
    _delay_us(50); \
    /* Send all color channels */ \
    WS2811_ALL(); \
    WS2811_PORT.OUT &= ~WS2811_PIN;

/* ------------------------------------------------------------------------- */

#endif

