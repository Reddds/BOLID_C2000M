/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "system.h"

#define MODBUD_INITIAL_ID       0x7F

/*
     {   "Подсв.экр.", "Подсветка экра-", "на",        2,  ST_0_100, 2, 0, 100, 50},
    {    "Подсв.кн.", "Подсветка кно-", "пок",        3,  ST_0_100, 3, 0, 100, 50},
    {"Заде. застав.", "Задержка перед", "заставкой",  9,  ST_0_100, 4, 5,  60,  5},
    // Подсвечивать ли заставку
    {"Подсв.застав.", "Подсветка при", "заставке",    8,  ST_0_100, 5, 0, 100, 50},   
    {"Подсв.кн.зас.", "Подсв.кнопки при", "заставке", 8,  ST_0_100, 6, 0, 100, 50},
 
 
 
 */

__EEPROM_DATA(0x11, MODBUD_INITIAL_ID, 100, 100, 30, 50, 0, 0x00);


/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    /* TODO Add clock switching code if appropriate.  */

    /* Typical actions in this function are to tweak the oscillator tuning
    register, select new clock sources, and to wait until new clock sources
    are stable before resuming execution of the main project. */
}
