#include "SectionSettings.h"
#include "../LCD/xlcd.h"
#include "../buttons.h"
#include "../user.h"



typedef enum 
{
    VS_ROOT,
    VS_SELECT_SETTING,
    VS_EDIT_SETTING
}ViewStates;


uint8_t dummyEeprom[20];



#define SETTINGS_COUNT 3
// Заготовки данных, которые потом будут в EEPROM
//uint8_t roomsCount = SETTINGS_COUNT;

typedef enum 
{
    ST_0_100, // от 0 до 100
}SettingTypes;

typedef struct 
{
    char *Name;
    SettingTypes Type;
    uint8_t AddressInEeprom;
    uint8_t minValue;
    uint8_t maxValue;
    uint8_t step;
    
}SettingTag;

SettingTag settingsNames[] = 
{
    {"Подсв.экр.", ST_0_100, 10, 0, 100, 5},
    {"Подсв.кл.", ST_0_100, 11, 0, 100, 5},
    {"Зад.на застав.", ST_0_100, 12, 5, 60, 5},
};

uint8_t _currentSetting;
ViewStates _currentState;
uint8_t tmpSetting8;

void SettingsDisplayRedraw()
{
    DisplayClear();
    
    switch(_currentState)
    {
        case VS_ROOT:
        case VS_SELECT_SETTING:
        {
            if(_currentState == VS_ROOT)
            DisplayPrintChar(CH_LEFT_RIGHT);
            else
                DisplayPrintChar(' ');
            DisplayPrintStr("Настройки");
            DisplaySetCursorPos(0, 1);
            if(_currentState == VS_SELECT_SETTING)
                DisplayPrintChar(CH_LEFT_RIGHT);
            if(_currentSetting >= SETTINGS_COUNT)
            {
                DisplayPrintStr("Ошибка");
                return;
            }
            DisplayPrintStr(settingsNames[_currentSetting].Name);
        }
        break;
        case VS_EDIT_SETTING:
        {
            // Первая строка - название комнаты
            DisplayPrintStr(settingsNames[_currentSetting].Name);
            // Вторая строка название параметра и значение
            DisplaySetCursorPos(0, 1);
            DisplayPrintChar(CH_LEFT_RIGHT);
            //PrintParameter(roomParams[_currentRoom].ParamAddresses[_currentParam], -1, -1, PPN_FULL);
            DisplayPrintUInt(tmpSetting8, DEC | SHOW_USE_FIELD_SIZE | FIELD_SIZE(3));
            DisplayPrintProgress(4, 10, 1, (tmpSetting8 - settingsNames[_currentSetting].minValue) / (float)(settingsNames[_currentSetting].maxValue - settingsNames[_currentSetting].minValue) * 100);

            
            
            
//            switch(settingsNames[_currentSetting].Type)
//            {
//                
//                case ST_0_100:
//                {
//                    DisplayPrintUInt(tmpSetting8, DEC | SHOW_USE_FIELD_SIZE | FIELD_SIZE(3));
//                    //DisplaySetCursorPos(4, 1);
//                    DisplayPrintProgress(4, 10, 1, tmpSetting8); //tmpSetting8
//                }
//                    break;
//            }
        }
        break;
    }

}

bool inited = false;
void SettingsStart()
{
    
    if(!inited)
    {
        inited = true;
        dummyEeprom[10] = 20;

        dummyEeprom[11] = 35;
        dummyEeprom[12] = 30;
    }
    //---------------------------
    
    
    
    _currentState = VS_ROOT;
    DisplayNoBlink();
    DisplayNoCursor();
    
    _currentSetting = 0;
    
    SettingsDisplayRedraw();

}

void SettingChanged()
{
    switch(_currentSetting)
    {
        case 0: // Подсветка экрана
            SetBakLightDuty(tmpSetting8 / 100.0 * 0x3ff);
            break;
    }
}

//void DiscardChanges()
//{
//    switch(_currentSetting)
//    {
//        case 0: // Подсветка экрана
//            SetBakLightDuty(tmpSetting8 / 100.0 * 0x3ff);
//            break;
//    }    
//}


void SettingsOnButton(uint8_t button)
{
    if (ButtonStates[button] != BUTTON_PRESSED)
        return;
    switch (button)
    {
        case BTN_LEFT:
        {
            switch(_currentState)
            {
                case VS_SELECT_SETTING:// выход в корень
                {
                    if(_currentSetting == 0)
                        _currentSetting = SETTINGS_COUNT - 1;
                    else
                        _currentSetting--;
                    //tmpSetting8 = dummyEeprom[settingsNames[_currentSetting].AddressInEeprom];
                    SettingsDisplayRedraw();
                }
                break;
                case VS_EDIT_SETTING:
                {
                    
                    if(tmpSetting8 >= settingsNames[_currentSetting].minValue + settingsNames[_currentSetting].step)
                    {
                        tmpSetting8 -= settingsNames[_currentSetting].step;
                        
                    }
                    else
                        tmpSetting8 = settingsNames[_currentSetting].minValue;
                    
                    
//                    switch(settingsNames[_currentSetting].Type)
//                    {
//                        case ST_0_100:
//                        {
//                            if(tmpSetting8 > 0)
//                                tmpSetting8--;
//                        }
//                        break;
//                    }          
                    SettingChanged();
                    SettingsDisplayRedraw();
                }
                break;        
            }
        }
        break;
        case BTN_RIGHT:
        {
            switch(_currentState)
            {
                case VS_SELECT_SETTING:// выход в корень
                {
                    if(_currentSetting == SETTINGS_COUNT - 1)
                        _currentSetting = 0;
                    else
                        _currentSetting++;
                    //tmpSetting8 = dummyEeprom[settingsNames[_currentSetting].AddressInEeprom];
                    SettingsDisplayRedraw();
                }
                break;
                case VS_EDIT_SETTING:
                {
                    
                    if(tmpSetting8 <= settingsNames[_currentSetting].maxValue - settingsNames[_currentSetting].step)
                        tmpSetting8 += settingsNames[_currentSetting].step;
                    
                    
//                    switch(settingsNames[_currentSetting].Type)
//                    {
//                        case ST_0_100:
//                        {
//                            if(tmpSetting8 < 100)
//                                tmpSetting8++;
//                        }
//                        break;
//                    }          
                    SettingChanged();
                    SettingsDisplayRedraw();
                }
                break;        
            }
        }
        break;   
        
        
        case BTN_ENT: 
        {
            switch(_currentState)
            {
                case VS_ROOT:// Вход в режим выбора комнат
                {
                    _currentState = VS_SELECT_SETTING;
                }
                break;
                case VS_SELECT_SETTING:
                {
                    _currentState = VS_EDIT_SETTING;
                    tmpSetting8 = dummyEeprom[settingsNames[_currentSetting].AddressInEeprom];
                }
                break;
                case VS_EDIT_SETTING:// Сохранение изменений
                {
                    _currentState = VS_SELECT_SETTING;
                    dummyEeprom[settingsNames[_currentSetting].AddressInEeprom] = tmpSetting8;
                }
                break;
                
                
            }
            SettingsDisplayRedraw();
        }
            break;
        case BTN_CLR:
        {
            switch(_currentState)
            {
                case VS_SELECT_SETTING:// выход в корень
                {
                    _currentState = VS_ROOT;
                }
                break;
                case VS_EDIT_SETTING: // Отмена изменений
                {
                    _currentState = VS_SELECT_SETTING;
                    tmpSetting8 = dummyEeprom[settingsNames[_currentSetting].AddressInEeprom];
                    SettingChanged();
                }
                break;
            }
            SettingsDisplayRedraw();
        }
            break;
    }    
}

bool SettingsIsRoot()
{
    return _currentState == VS_ROOT;
}