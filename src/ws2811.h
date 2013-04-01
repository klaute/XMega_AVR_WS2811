/*
 * This code is based on the git://github.com/jamuraa/xmega-ws2811-bitbang.git project.
 *
 */

#include "globals.h"

#ifndef __WS2811_H__
#define __WS2811_H__

#include <util/delay.h>

/* ------------------------------------------------------------------------- */

#define NUM_LED 120

/* ------------------------------------------------------------------------- */

uint8_t r[NUM_LED];
uint8_t g[NUM_LED];
uint8_t b[NUM_LED];

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

#define NOP_SHORT NOP5 /* < NOT4 does not work */
#define NOP_LONG NOP13 /* < NOP12 does not work */

#define WS2811_RESET_DELAY_US 51

/* ------------------------------------------------------------------------- */

#define WS2811_PORT PORTA
#define WS2811_PIN  PIN1_bm

/* ------------------------------------------------------------------------- */

#define WS2811_BIT_SET(X, N) \
    /*printf("%d %d\r\n", X, N);*/ \
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

#define WS2811_SEND_PIXEL(R, G, B) \
    WS2811_BIT_ALL(G); \
    WS2811_BIT_ALL(R); \
    WS2811_BIT_ALL(B);

#define WS2811_UPDATE_COLORS() \
    /* Reset */ \
    WS2811_PORT.OUT &= ~WS2811_PIN; \
    _delay_us(WS2811_RESET_DELAY_US); \
    /* Send all color channels */ \
    for (uint8_t i = 0; i < NUM_LED; i++) \
    { \
        WS2811_BIT_ALL(gbuff[i] & 0xff); \
        WS2811_BIT_ALL(rbuff[i] & 0xff); \
        WS2811_BIT_ALL(bbuff[i] & 0xff); \
    }\
    WS2811_PORT.OUT |= WS2811_PIN;

#define WS2811_SET_BUFFER_ALL(R, G, B) \
    /* set the no signal color */ \
    for (uint8_t i = 0; i < NUM_LED; i++) \
    { \
        rbuff[i] = R; \
        gbuff[i] = G; \
        bbuff[i] = B; \
    }


/* ------------------------------------------------------------------------- */

#endif

