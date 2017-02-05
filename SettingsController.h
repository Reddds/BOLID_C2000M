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

#define SETTINGS_COUNT 5
    
#define SETTING_LCD_BK 0    // Подсветка экрана 
#define SETTING_KB_BK 1     // Подсветка клавдии 
#define SETTING_SAVESCREEN_TIMEOUT 2 // Задержка перед хранителем экрана в секундах 
#define SETTING_SAVESCREEN_BK 3 // Подсветка в режиме заставки
#define SETTING_SAVESCREEN_KB_BK 4 // Подсветка кнопки в режиме заставки    
    
typedef enum 
{
    ST_0_100, // от 0 до 100
    ST_BOOL, // Да - нет
}SettingTypes; 

typedef struct 
{
    char *Name;
    char *FullName1Line;
    char *FullName2Line;
    uint8_t Line2Size;
    SettingTypes Type;
    uint8_t AddressInEeprom;
    uint8_t minValue;
    uint8_t maxValue;
    uint8_t step;
    
}SettingTag;    
   
SettingTag settingsNames[] = 
{
    {   "Подсв.экр.", "Подсветка экра-", "на",        2,  ST_0_100, 2, 0, 100, 50},
    {    "Подсв.кн.", "Подсветка кно-", "пок",        3,  ST_0_100, 3, 0, 100, 50},
    {"Заде. застав.", "Задержка перед", "заставкой",  9,  ST_0_100, 4, 5,  60,  5},
    // Подсвечивать ли заставку
    {"Подсв.застав.", "Подсветка при", "заставке",    8,  ST_0_100, 5, 0, 100, 50},   
    {"Подсв.кн.зас.", "Подсв.кнопки при", "заставке", 8,  ST_0_100, 6, 0, 100, 50},
};

void InitSettings(); // !!! временно
    
//uint8_t GetSettingsCount();
#define GetSettingName(settingId) (settingsNames[settingId].Name)
#define GetSettingFullName1Line(settingId) (settingsNames[settingId].FullName1Line)
#define GetSettingFullName2Line(settingId) (settingsNames[settingId].FullName2Line)
#define GetSettingLine2Size(settingId) (settingsNames[settingId].Line2Size)
#define GetSettingType(settingId) (settingsNames[settingId].Type)
#define GetSettingMin(settingId) (settingsNames[settingId].minValue)
#define GetSettingMax(settingId) (settingsNames[settingId].maxValue)
#define GetSettingStep(settingId) (settingsNames[settingId].step)

uint16_t GetSettingValue(uint8_t settingId);


void SetTempSettingValue(uint8_t settingId, uint16_t value);

void SaveSetting(uint8_t settingId, uint16_t value);

    



#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGSCONTROLLER_H */

