/* 
 * File:   buttons.h
 * Author: denis
 *
 * Created on 29 ?????? 2017 ?., 20:01
 */

#ifndef BUTTONS_H
#define	BUTTONS_H

#include <stdint.h>        /* For uint8_t definition */

#ifdef	__cplusplus
extern "C" {
#endif

    
enum 
{
    BTN_ARM,
    BTN_DISARM,
    BTN_BPS,
    BTN_TRBL,
    BTN_MEM,
    BTN_LEFT,
    BTN_1,
    BTN_4,
    BTN_7,
    BTN_CLR,
    BTN_PRG,
    BTN_2,
    BTN_5,
    BTN_8,
    BTN_0,                
    BTN_RIGHT,
    BTN_3,
    BTN_6,
    BTN_9,
    BTN_ENT,
    BTN_NONE = 0xff
};

#define BUTTONS_COUNT 20
#define BUTTONS_ROWS 5
#define BUTTONS_COLS 4


#define BUTTON_PRESSED 0
#define BUTTON_RELEASED 1


uint8_t ButtonStates[BUTTONS_COUNT];    

void InitButtons();
uint8_t IsButtonChanged();


#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

