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
    {   "�����.���.", "��������� ����-", "��",        2,  ST_0_100,              EE_LCD_BACKLIGHT,       0,  100,  50},
    {    "�����.��.", "��������� ���-", "���",        3,  ST_0_100,              EE_KEYPAD_BACKLIGHT,    0,  100,  50},
    {"����. ������.", "�������� �����", "���������",  9,  ST_0_100,              EE_SCRENSAVE_DELAY,     5,   60,   5},
    // ������������ �� ��������
    {"�����.������.", "��������� ���", "��������",    8,  ST_0_100,              EE_SS_LCD_BACKLIGHT,    0,  100,  50},   
    {"�����.��.���.", "�����.������ ���", "��������", 8,  ST_0_100,              EE_SS_KEYPAD_BACKLIGHT, 0,  100,  50},
    {"�����.��.��.",  "�������� �����", "��.���.",    7,  ST_0_100 | ST_MUL_0_1, EE_MAIN_SCREEN_DELAY,   0,  250,   5}, // 0 - 10 c, 0 - �� ������������� ���
    // ����� �� ������� ������, � �������� ������� �������� ���������� � ������ ���������
    {"���.����.",     "����� �� �������", "������",   6,  ST_INT_4B,             EE_PARAMS_STARTADDRESS, 0,  EXT_MEM_CHIP_SIZE * 2 - 1,  0},    
    {  "������ ����", "����� MODBUS", "�������",      7,  ST_0_100,              EE_MASTER_MODE,         0,  255, 255},
    {"�������� ���.", "�������� ������", "�������",   7,  ST_0_100,              EE_MASTER_HEART_BEAT,   5,  255,   5},
 */

__EEPROM_DATA(0x11, MODBUD_INITIAL_ID, 100, 100, 30, 50, 0, 0x00);

__EEPROM_DATA(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    /* TODO Add clock switching code if appropriate.  */

    /* Typical actions in this function are to tweak the oscillator tuning
    register, select new clock sources, and to wait until new clock sources
    are stable before resuming execution of the main project. */
}
