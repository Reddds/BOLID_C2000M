#include "SettingsController.h"
#include <xc.h> // include processor files - each processor file is guarded.  
#include <eeprom_routines.h>
#include "user.h"


uint16_t cachedSettings[SETTINGS_COUNT];

void InitSettings()
{
    for(uint8_t i = 0; i < SETTINGS_COUNT; i++)
    {
        uint8_t val = eeprom_read(settingsNames[i].AddressInEeprom);
        cachedSettings[i] = val;
        SetTempSettingValue(i, val);
    }
}


//uint8_t GetSettingsCount()
//{
//    return SETTINGS_COUNT;
//}
//
//uint16_t GetSettingMin(uint8_t settingId)
//{
//    return settingsNames[settingId].minValue;
//}
//
//uint16_t GetSettingMax(uint8_t settingId)
//{
//    return settingsNames[settingId].maxValue;    
//}
//uint16_t GetSettingStep(uint8_t settingId)
//{
//    return settingsNames[settingId].step;      
//}
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