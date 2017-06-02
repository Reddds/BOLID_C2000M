/* 
 * File:   SettingsController.h
 * Author: denis
 *
 * Created on 4 февраля 2017 г., 20:59
 */

#ifndef SETTINGSCONTROLLER_H
#define	SETTINGSCONTROLLER_H

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#ifdef	__cplusplus
extern "C" {
#endif

#define SETTINGS_COUNT 8
    
#define SETTING_LCD_BK 0    // Подсветка экрана 
#define SETTING_KB_BK 1     // Подсветка клавдии 
#define SETTING_SAVESCREEN_TIMEOUT 2 // Задержка перед хранителем экрана в секундах 
#define SETTING_SAVESCREEN_BK 3 // Подсветка в режиме заставки
#define SETTING_SAVESCREEN_KB_BK 4 // Подсветка кнопки в режиме заставки   
#define SETTING_IDLE_SCREEN_ROTATE_TIMEOUT 5 // Задержка между переключениями главных экранов

#define SETTING_MODBUS_MUSTER 7 // Режим мастера сети   
    
typedef enum 
{
    ST_0_100, // от 0 до 100
    ST_BOOL, // Да - нет
    ST_INT_4B, // Целое число, 4 байта вводится с клавиатуры       
    ST_MUL_0_1 = 0x10 // Значение отображать делёным на 10       
}SettingTypes; 

typedef struct 
{
    char *Name;
    char *FullName1Line;
    char *FullName2Line;
    uint8_t Line2Size;
    SettingTypes Type;
    uint8_t AddressInEeprom;
    uint32_t minValue;
    uint32_t maxValue;
    uint32_t step;
    
}SettingTag;    
   
//SettingTag settingsNames[] = 
//{
//    {   "Подсв.экр.", "Подсветка экра-", "на",        2,  ST_0_100, 2, 0, 100, 50},
//    {    "Подсв.кн.", "Подсветка кно-", "пок",        3,  ST_0_100, 3, 0, 100, 50},
//    {"Заде. застав.", "Задержка перед", "заставкой",  9,  ST_0_100, 4, 5,  60,  5},
//    // Подсвечивать ли заставку
//    {"Подсв.застав.", "Подсветка при", "заставке",    8,  ST_0_100, 5, 0, 100, 50},   
//    {"Подсв.кн.зас.", "Подсв.кнопки при", "заставке", 8,  ST_0_100, 6, 0, 100, 50},
//};


void InitSettings(); // !!! временно
    
//uint8_t GetSettingsCount();
char* GetSettingName(uint8_t settingId);
char* GetSettingFullName1Line(uint8_t settingId);
char* GetSettingFullName2Line(uint8_t settingId);
uint8_t GetSettingLine2Size(uint8_t settingId);
SettingTypes GetSettingType(uint8_t settingId);
uint32_t GetSettingMin(uint8_t settingId);
uint32_t GetSettingMax(uint8_t settingId);
uint32_t GetSettingStep(uint8_t settingId);

uint16_t GetSettingValue(uint8_t settingId);
uint32_t GetSettingValue32(uint8_t settingId);

void SetTempSettingValue(uint8_t settingId, uint16_t value);

void SaveSetting(uint8_t settingId, uint16_t value);
void SaveSetting32(uint8_t settingId, uint32_t value);
    



#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGSCONTROLLER_H */

