#include "SettingsController.h"
#include <xc.h> // include processor files - each processor file is guarded.  
#include <eeprom_routines.h>
#include "user.h"


uint16_t cachedSettings[SETTINGS_COUNT];

SettingTag settingsNames[] = 
{
    //Name             FullName1Line FullName2Line Line2Size  Type   AddressInEeprom minValue maxValue step
    {   "Подсв.экр.", "Подсветка экра-", "на",        2,  ST_0_100,              2, 0,  100, 50},
    {    "Подсв.кн.", "Подсветка кно-", "пок",        3,  ST_0_100,              3, 0,  100, 50},
    {"Заде. застав.", "Задержка перед", "заставкой",  9,  ST_0_100,              4, 5,   60,  5},
    // Подсвечивать ли заставку
    {"Подсв.застав.", "Подсветка при", "заставке",    8,  ST_0_100,              5, 0,  100, 50},   
    {"Подсв.кн.зас.", "Подсв.кнопки при", "заставке", 8,  ST_0_100,              6, 0,  100, 50},
    {"Перекл.гл.эк.", "Задержка между", "гл. экр.",   8,  ST_0_100 | ST_MUL_0_1, 7, 10, 100,  5}, // 1 - 10 c
};


void InitSettings()
{
    for(uint8_t i = 0; i < SETTINGS_COUNT; i++)
    {
        uint8_t val = eeprom_read(settingsNames[i].AddressInEeprom);
        cachedSettings[i] = val;
        SetTempSettingValue(i, val);
    }
}


char* GetSettingName(uint8_t settingId)
{
    return settingsNames[settingId].Name;
}
char* GetSettingFullName1Line(uint8_t settingId)
{
    return settingsNames[settingId].FullName1Line;
}
char* GetSettingFullName2Line(uint8_t settingId)
{
    return settingsNames[settingId].FullName2Line;
}
uint8_t GetSettingLine2Size(uint8_t settingId)
{
    return settingsNames[settingId].Line2Size;
}
SettingTypes GetSettingType(uint8_t settingId)
{
    return settingsNames[settingId].Type;
}
uint8_t GetSettingMin(uint8_t settingId)
{
    return settingsNames[settingId].minValue;
}
uint8_t GetSettingMax(uint8_t settingId)
{
    return settingsNames[settingId].maxValue;
}
uint8_t GetSettingStep(uint8_t settingId)
{
    return settingsNames[settingId].step;
}


uint16_t GetSettingValue(uint8_t settingId)
{
    if(settingId > SETTINGS_COUNT)
        return 0;
    return cachedSettings[settingId];
}


void SetTempSettingValue(uint8_t settingId, uint16_t value)
{
    switch(settingId)
    {
        case SETTING_LCD_BK: // Подсветка экрана
            SetBakLightDuty(value / 50);
            break;
        case SETTING_KB_BK: // Подсветка клавдии
            SetKbBakLightDuty(value / 50);
            break;
    }
}

void SaveSetting(uint8_t settingId, uint16_t value)
{
    SetTempSettingValue(settingId, value);
    cachedSettings[settingId] = value;
    eeprom_write(settingsNames[settingId].AddressInEeprom, value);
}