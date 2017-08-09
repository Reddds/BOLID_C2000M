#include "SettingsController.h"
#include <xc.h> // include processor files - each processor file is guarded.  
#include <eeprom_routines.h>
#include "user.h"


uint16_t cachedSettings[SETTINGS_COUNT];
// Костыль, но пока так
#define SETTINGS_COUNT32 1
uint32_t cachedSettings32[SETTINGS_COUNT32];

SettingTag settingsNames[] = 
{
    //Name             FullName1Line FullName2Line Line2Size  Type               AddressInEeprom    minValue maxValue step
    {   "Подсв.экр.", "Подсветка экра-", "на",        2,  ST_0_100,              EE_LCD_BACKLIGHT,       0,  100,  50},
    {    "Подсв.кн.", "Подсветка кно-", "пок",        3,  ST_0_100,              EE_KEYPAD_BACKLIGHT,    0,  100,  50},
    {"Заде. застав.", "Задержка перед", "заставкой",  9,  ST_0_100,              EE_SCRENSAVE_DELAY,     5,   60,   5},
    // Подсвечивать ли заставку
    {"Подсв.застав.", "Подсветка при", "заставке",    8,  ST_0_100,              EE_SS_LCD_BACKLIGHT,    0,  100,  50},   
    {"Подсв.кн.зас.", "Подсв.кнопки при", "заставке", 8,  ST_0_100,              EE_SS_KEYPAD_BACKLIGHT, 0,  100,  50},
    {"Перек.гл.эк.",  "Задержка между", "гл.экр.",    7,  ST_0_100 | ST_MUL_0_1, EE_MAIN_SCREEN_DELAY,   0,  250,   5}, // 0 - 10 c, 0 - не переключается сам
    // Адрес во внешней памяти, с которого грузить описание параметров и другие настройки
    {"Адр.загр.",     "Адрес во внешней", "памяти",   6,  ST_INT_4B,             EE_PARAMS_STARTADDRESS, 0,  EXT_MEM_CHIP_SIZE * 2 - 1,  0},    
    {  "Мастер сети", "Режим MODBUS", "мастера",      7,  ST_BOOL,               EE_MASTER_MODE,         0,  255, 255},
    {"Интервал опр.", "Интервал опроса", "мастера",   7,  ST_0_100,              EE_MASTER_HEART_BEAT,   5,  255,   5},
 };

//#if sizeof(settingsNames) != SETTINGS_COUNT
//#error "Setting count not equal to SETTINGS_COUNT!"
//#endif

void InitSettings()
{
    for(uint8_t i = 0; i < SETTINGS_COUNT; i++)
    {
        switch(settingsNames[i].Type)
        {
            case ST_INT_4B:
            {
                cachedSettings[i] = 0; // индекс 32-разрядного значения
                uint32_t val = eeprom_read(settingsNames[i].AddressInEeprom);
                val <<= 8;
                val |= eeprom_read(settingsNames[i].AddressInEeprom + 1);
                val <<= 8;
                val |= eeprom_read(settingsNames[i].AddressInEeprom + 2);
                val <<= 8;
                val |= eeprom_read(settingsNames[i].AddressInEeprom + 3);
                cachedSettings32[0] = val;
            }
                break;
            default:
            {
                uint8_t val = eeprom_read(settingsNames[i].AddressInEeprom);
                cachedSettings[i] = val;
                SetTempSettingValue(i, val);                
            }
                break;
        }
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
uint32_t GetSettingMin(uint8_t settingId)
{
    return settingsNames[settingId].minValue;
}
uint32_t GetSettingMax(uint8_t settingId)
{
    return settingsNames[settingId].maxValue;
}
uint32_t GetSettingStep(uint8_t settingId)
{
    return settingsNames[settingId].step;
}


uint16_t GetSettingValue(uint8_t settingId)
{
    if(settingId > SETTINGS_COUNT)
        return 0;
    return cachedSettings[settingId];
}
uint32_t GetSettingValue32(uint8_t settingId)
{
    if(settingId > SETTINGS_COUNT)
        return 0;
    settingId = cachedSettings[settingId]; // получаем индекс
    if(settingId > SETTINGS_COUNT32)
        return 0;
    return cachedSettings32[settingId];    
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
        //case SETTING_MODBUS_MASTER: // Мастер сети
        //    SetMODBUSMode(value);
        //    break;
        case SETTING_MASTER_HEART_BEAT:
            SetHeartBeat(value);
            break;
    }
}

void SaveSetting(uint8_t settingId, uint16_t value)
{
    if(settingId > SETTINGS_COUNT)
        return;
    
    SetTempSettingValue(settingId, value);
    cachedSettings[settingId] = value;

    eeprom_write(settingsNames[settingId].AddressInEeprom, value);
    // Ждём пока запишется
    while (EECON1bits.WR) 
    { 				
        continue; 							
    } 
    switch(settingId)
    {
        case SETTING_MODBUS_MASTER: // Мастер сети
            SetMODBUSMode(value);
            break;
    }
}

void SaveSetting32(uint8_t settingId, uint32_t value)
{
    if(settingId > SETTINGS_COUNT)
        return;
    
    settingId = cachedSettings[settingId]; // получаем индекс
    if(settingId > SETTINGS_COUNT32)
        return;    
    
    //SetTempSettingValue(settingId, value);
    cachedSettings32[settingId] = value;

    eeprom_write(settingsNames[settingId].AddressInEeprom,     value >> 24);
    eeprom_write(settingsNames[settingId].AddressInEeprom + 1, (value >> 16) & 0xff);
    eeprom_write(settingsNames[settingId].AddressInEeprom + 2, (value >> 8) & 0xff);
    eeprom_write(settingsNames[settingId].AddressInEeprom + 3, (value) & 0xff);
    // Ждём пока запишется
    while (EECON1bits.WR) 
    { 				
        continue; 							
    } 
}
