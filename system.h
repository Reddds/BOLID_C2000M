#ifndef SYSTEM_H
#define	SYSTEM_H
/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/
#include <xc.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        9216000L
#define FCY             SYS_FREQ/4
#define _XTAL_FREQ      SYS_FREQ
#define TIMER_TICKS_IN_1_MS 0x10000 - FCY / 1000




// 1 min = FCY * 60 = 150000000
// 1/10 min = FCY * 6 = 15 000 000
#define WATCH_TIMER_PRESCALER 256
#define WATCH_TIMER_CORRECTION_ZERO 127
#define WATCH_TIMER_CORRECTION -1

#define WATCH_TIMER_TICKS_IN_1_SEC (FCY / WATCH_TIMER_PRESCALER + WATCH_TIMER_CORRECTION)
#define WATCH_TIMER_TICKS_TO_END_6S 0x10000 - WATCH_TIMER_TICKS_IN_1_SEC * 6
/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/
#define word(hb, lb) (((uint16_t)hb<<8)|lb)
#define byteFrom2(hb, lb) (((hb << 4) & 0xf0) | (lb & 0x0f))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= ((unsigned short)1 << (bit))) // (1UL << (bit))
#define bitClear(value, bit) ((value) &= ~((unsigned short)1 << (bit))) // (1UL << (bit))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit)) 
/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
#endif