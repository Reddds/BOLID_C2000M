#include "SectionSettings.h"
#include "../LCD/xlcd.h"
#include "../buttons.h"

#include "../SettingsController.h"



typedef enum 
{
    VS_ROOT,
    VS_SELECT_SETTING,
    VS_EDIT_SETTING
}ViewStates;







// Заготовки данных, которые потом будут в EEPROM
//uint8_t roomsCount = SETTINGS_COUNT;






uint8_t _currentSetting;
ViewStates _currentSsState;
uint8_t tmpSetting8;

void SettingsDisplayRedraw()
{
    DisplayClear();
    
    switch(_currentSsState)
    {
        case VS_ROOT:
        case VS_SELECT_SETTING:
        {
            if(_currentSsState == VS_ROOT)
                DisplayPrintChar(CH_LEFT_RIGHT);
            else
                DisplayPrintChar(' ');
            DisplayPrintStr("Настройки");
            DisplaySetCursorPos(0, 1);
            if(_currentSsState == VS_SELECT_SETTING)
                DisplayPrintChar(CH_LEFT_RIGHT);
            if(_currentSetting >= SETTINGS_COUNT)
            {
                DisplayPrintStr("Ошибка");
                return;
            }
            DisplayPrintStr(GetSettingName(_currentSetting));
            
            switch(GetSettingType(_currentSetting))
            {
                
                case ST_0_100:
                {
                    DisplayPrintUInt(GetSettingValue(_currentSetting), DEC);                
                }
                    break;
                case ST_BOOL:
                {
                    if(GetSettingValue(_currentSetting) == 1)
                        DisplayPrintChar('+');
                    else
                        DisplayPrintStr('-');
                }
                break;
            }
            
            
        }
        break;
        case VS_EDIT_SETTING:
        {
            // Первая строка - название комнаты
            DisplayPrintStr(GetSettingFullName1Line(_currentSetting));
            // Вторая строка название параметра и значение
            DisplaySetCursorPos(0, 1);
            DisplayPrintChar(CH_LEFT_RIGHT);
            uint8_t line2Size = DisplayPrintStr(GetSettingFullName2Line(_currentSetting)) + 2;
            DisplayPrintChar(' ');
            
            switch(GetSettingType(_currentSetting))
            {
                
                case ST_0_100:
                {
                    DisplayPrintUInt(tmpSetting8, DEC | SHOW_USE_FIELD_SIZE | FIELD_SIZE(3));
                    
                    if(line2Size + 3 + 2 < SCREEN_WIDTH)
                        DisplayPrintProgress(line2Size + 3, SCREEN_WIDTH - (line2Size + 3), 1, (tmpSetting8 - GetSettingMin(_currentSetting)) / (float)(GetSettingMax(_currentSetting) - GetSettingMin(_currentSetting)) * 100);
                }
                    break;
                case ST_BOOL:
                {
                    if(tmpSetting8 == 1)
                        DisplayPrintStr("Да");
                    else
                        DisplayPrintStr("Нет");
                }
                break;
            }
        }
        break;
    }

}

bool inited = false;
void SettingsStart()
{
    
    if(inited == false)
    {
        inited = true;
        InitSettings();
    }
    //---------------------------
    
    
    
    _currentSsState = VS_ROOT;
    DisplayNoBlink();
    DisplayNoCursor();
    
    _currentSetting = 0;
    
    SettingsDisplayRedraw();

}

void SettingChanged()
{
    SetTempSettingValue(_currentSetting, tmpSetting8);
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
            switch(_currentSsState)
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
                    
                    if(tmpSetting8 >= GetSettingMin(_currentSetting) + GetSettingStep(_currentSetting))
                    {
                        tmpSetting8 -= GetSettingStep(_currentSetting);
                        
                    }
                    else
                        tmpSetting8 = GetSettingMin(_currentSetting);
         
                    SettingChanged();
                    SettingsDisplayRedraw();
                }
                break;        
            }
        }
        break;
        case BTN_RIGHT:
        {
            switch(_currentSsState)
            {
                case VS_SELECT_SETTING:// выход в корень
                {
                    if(_currentSetting == SETTINGS_COUNT - 1)
                        _currentSetting = 0;
                    else
                        _currentSetting++;
                    SettingsDisplayRedraw();
                }
                break;
                case VS_EDIT_SETTING:
                {                    
                    if(tmpSetting8 <= GetSettingMax(_currentSetting) - GetSettingStep(_currentSetting))
                        tmpSetting8 += GetSettingStep(_currentSetting);   
                    else
                        tmpSetting8 = GetSettingMax(_currentSetting);
                    SettingChanged();
                    SettingsDisplayRedraw();
                }
                break;        
            }
        }
        break;   
        
        
        case BTN_ENT: 
        {
            switch(_currentSsState)
            {
                case VS_ROOT:// Вход в режим выбора комнат
                {
                    _currentSsState = VS_SELECT_SETTING;
                }
                break;
                case VS_SELECT_SETTING:
                {
                    _currentSsState = VS_EDIT_SETTING;
                    tmpSetting8 = GetSettingValue(_currentSetting);
                }
                break;
                case VS_EDIT_SETTING:// Сохранение изменений
                {
                    _currentSsState = VS_SELECT_SETTING;
                    SaveSetting(_currentSetting, tmpSetting8);
                    
                }
                break;
                
                
            }
            SettingsDisplayRedraw();
        }
            break;
        case BTN_CLR:
        {
            switch(_currentSsState)
            {
                case VS_SELECT_SETTING:// выход в корень
                {
                    _currentSsState = VS_ROOT;
                }
                break;
                case VS_EDIT_SETTING: // Отмена изменений
                {
                    _currentSsState = VS_SELECT_SETTING;
                    SetTempSettingValue(GetSettingValue(_currentSetting), tmpSetting8);
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
    return _currentSsState == VS_ROOT;
}