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




uint8_t fieldBuf[10];// Для ввода 32-битного числа
uint8_t _fieldLen;


// Заготовки данных, которые потом будут в EEPROM
//uint8_t roomsCount = SETTINGS_COUNT;






uint8_t _currentSetting;
ViewStates _currentSsState;
uint8_t tmpSetting8;
//uint32_t tmpSetting32;

void SettingsDisplayRedraw()
{
    DisplayClear();
    
    switch(_currentSsState)
    {
        case VS_ROOT:
        case VS_SELECT_SETTING:
        {
//            if(_currentSsState == VS_ROOT)
//                DisplaySetCursorPos(0, 0);
//                //DisplayPrintChar(CH_LEFT_RIGHT);
//            else
//                DisplayPrintChar(' ');
            DisplayPrintStr("Настройки");
            DisplaySetCursorPos(0, 1);
//            if(_currentSsState == VS_SELECT_SETTING)
//                DisplaySetCursorPos(0, 0);
                //DisplayPrintChar(CH_LEFT_RIGHT);
            if(_currentSetting >= SETTINGS_COUNT)
            {
                DisplayPrintStr("Ошибка");
                return;
            }
            DisplayPrintStr((const char *)GetSettingName(_currentSetting));
            
            switch(GetSettingType(_currentSetting))
            {
                
                case ST_0_100:
                {
                    DisplayPrintUInt(GetSettingValue(_currentSetting), DEC);                
                }
                    break;
                case ST_0_100 | ST_MUL_0_1:                              
                {
                    DisplayPrintFloat(GetSettingValue(_currentSetting) * 0.1, 1 | SHOW_USE_FIELD_SIZE | FIELD_SIZE(4));
                }
                break;
                case ST_BOOL:
                {
                    DisplaySetCursorPos(13, 1);      
                    if(GetSettingValue(_currentSetting) != 0)
                        DisplayPrintStr("Да");
                    else
                        DisplayPrintStr("Нет");
                }
                break;
                case ST_INT_4B:
                {
                    DisplayPrintUInt(GetSettingValue32(_currentSetting), DEC);                
                }
            }
            
            if(_currentSsState == VS_ROOT)
                DisplaySetCursorPos(0, 0);
            else
                DisplaySetCursorPos(0, 1);
        }
        break;
        case VS_EDIT_SETTING:
        {
            // Первая строка 
            DisplayPrintStr((const char *)GetSettingFullName1Line(_currentSetting));
            // Вторая строка название параметра и значение
            DisplaySetCursorPos(0, 1);
            //DisplayPrintChar(CH_LEFT_RIGHT);
            uint8_t line2Size = DisplayPrintStr((const char *)GetSettingFullName2Line(_currentSetting)) + 1;
            DisplayPrintChar(' ');
            
            switch(GetSettingType(_currentSetting))
            {
                
                case ST_0_100:                              
                {
                    
                    DisplayPrintUInt(tmpSetting8, DEC | SHOW_USE_FIELD_SIZE | FIELD_SIZE(3));
                    
                    if(line2Size + 3 + 2 < SCREEN_WIDTH)
                        DisplayPrintProgress(line2Size + 3, SCREEN_WIDTH - (line2Size + 3), 1, (tmpSetting8 - GetSettingMin(_currentSetting)) / (float)(GetSettingMax(_currentSetting) - GetSettingMin(_currentSetting)) * 100);
                    DisplaySetCursorPos(line2Size, 1);
                }
                    break;
                case ST_0_100 | ST_MUL_0_1:                              
                {
                    
                    DisplayPrintFloat(tmpSetting8 * 0.1, 1 | SHOW_USE_FIELD_SIZE | FIELD_SIZE(4));
                    
                    if(line2Size + 3 + 2 < SCREEN_WIDTH)
                        DisplayPrintProgress(line2Size + 4, SCREEN_WIDTH - (line2Size + 4), 1, (tmpSetting8 - GetSettingMin(_currentSetting)) / (float)(GetSettingMax(_currentSetting) - GetSettingMin(_currentSetting)) * 100);
                    DisplaySetCursorPos(line2Size, 1);
                }
                    break;
                case ST_BOOL:
                {
                    DisplaySetCursorPos(13, 1); 
                    if(tmpSetting8 != 0)
                        DisplayPrintStr("Да");
                    else
                        DisplayPrintStr("Нет");
                    DisplaySetCursorPos(13, 1);
                }
                break;
                case ST_INT_4B:
                {
                    DisplaySetCursorPos(SCREEN_WIDTH - 1 - _fieldLen, 1);
                    for(uint8_t i = 0; i < _fieldLen; i++)
                        DisplayPrintChar('0' + fieldBuf[sizeof(fieldBuf) - _fieldLen + i]);
                    DisplaySetCursorPos(SCREEN_WIDTH - 1, 1);
                    
//                    uint8_t *str = &fieldBuf[sizeof(fieldBuf) - 1];
//                    
//                    _fieldLen = 0;
//                    //fieldBuf
//                    do 
//                    {
//                        uint8_t c = n % 10;
//                        n /= 10;
//
//                        *str = c;
//
//                        str--;
//                        _fieldLen++;
//                    } while(n);
//                    
//                    
//                    DisplayPrintUInt(GetSettingValue32(_currentSetting), DEC);                
                }
            }
        }
        break;
    }
    DisplayCursor();
    DisplayBlink();
}

void SettingsUpdateView()
{
    SettingsDisplayRedraw();
}

uint32_t GetFieldValue()
{
    if(_fieldLen == 0)
        return 0;
    
    
    if(_fieldLen == 1)
        return fieldBuf[sizeof(fieldBuf) - 1];
    
    
    
    uint32_t res = fieldBuf[sizeof(fieldBuf) - _fieldLen];
    
    for(uint8_t i = sizeof(fieldBuf) - _fieldLen + 1; i < sizeof(fieldBuf); i++)
    {
        res = res * 10 + fieldBuf[i];
        
    }
    return res;
}


void PutNum(uint8_t num)
{
    if(_fieldLen >= sizeof(fieldBuf))
        return;
    
    
    uint32_t maxValue = GetSettingMax(_currentSetting);
    uint32_t minValue = GetSettingMin(_currentSetting);
    
    if(_fieldLen == 1 && fieldBuf[sizeof(fieldBuf) - 1] == 0)
    {
        if(num == 0)
            return;
        
        if(num > maxValue)
            return;
        fieldBuf[sizeof(fieldBuf) - 1] = num;
    }
    else
    {    
        if(GetFieldValue() * 10 + num > maxValue)
            return;
        
        for(uint8_t i = sizeof(fieldBuf) - _fieldLen; i < sizeof(fieldBuf); i++)
            fieldBuf[i - 1] = fieldBuf[i];
        fieldBuf[sizeof(fieldBuf) - 1] = num;
        _fieldLen++;
    }
    SettingsDisplayRedraw();
}

void DelDigit()
{
    if(_fieldLen == 0)
        return;
    
    if(_fieldLen > 1)
    {
        for(uint8_t i = sizeof(fieldBuf) - 1; i > sizeof(fieldBuf) - _fieldLen; i--)
            fieldBuf[i] = fieldBuf[i - 1];
        
    }
        
    
    
    _fieldLen--;
    SettingsDisplayRedraw();
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
    //DisplayNoBlink();
    //DisplayNoCursor();
    
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
                    switch(GetSettingType(_currentSetting))
                    {
                        case ST_INT_4B:
                            DelDigit();
                            break;
                        case ST_BOOL:
                        {
                            if(tmpSetting8 == GetSettingMin(_currentSetting))
                                tmpSetting8 = GetSettingMax(_currentSetting);
                            else
                                tmpSetting8 = GetSettingMin(_currentSetting);
                        }
                        break;
                        case ST_0_100:        
                        case ST_0_100 | ST_MUL_0_1:       
                        {
                            if(tmpSetting8 >= GetSettingMin(_currentSetting) + GetSettingStep(_currentSetting))
                            {
                                tmpSetting8 -= GetSettingStep(_currentSetting);

                            }
                            else
                                tmpSetting8 = GetSettingMin(_currentSetting);
                        }  
                    }
                    
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
                    switch(GetSettingType(_currentSetting))
                    {
                        case ST_INT_4B:
                            break;
                            
                        case ST_BOOL:
                        {
                            if(tmpSetting8 == GetSettingMin(_currentSetting))
                                tmpSetting8 = GetSettingMax(_currentSetting);
                            else
                                tmpSetting8 = GetSettingMin(_currentSetting);
                        }
                        break;
                        case ST_0_100:        
                        case ST_0_100 | ST_MUL_0_1:       
                        {
                            if(tmpSetting8 <= GetSettingMax(_currentSetting) - GetSettingStep(_currentSetting))
                                tmpSetting8 += GetSettingStep(_currentSetting);   
                            else
                                tmpSetting8 = GetSettingMax(_currentSetting);
                        }                              
                    }                    
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
                    if(GetSettingType(_currentSetting) == ST_INT_4B)
                    {
                        //tmpSetting32 = GetSettingValue32(_currentSetting);
                        
                        uint32_t n = GetSettingValue32(_currentSetting);
                        uint8_t *str = &fieldBuf[sizeof(fieldBuf) - 1];
                        _fieldLen = 0;
                        //fieldBuf
                        do 
                        {
                            uint8_t c = n % 10;
                            n /= 10;

                            *str = c;
                            
                            str--;
                            _fieldLen++;
                        } while(n);
                    }
                    else
                    {
                        tmpSetting8 = GetSettingValue(_currentSetting);
                    }
                }
                break;
                case VS_EDIT_SETTING:// Сохранение изменений
                {
                    _currentSsState = VS_SELECT_SETTING;
                    if(GetSettingType(_currentSetting) == ST_INT_4B)
                    {
                        SaveSetting32(_currentSetting, GetFieldValue());
                    }
                    else
                    {
                        SaveSetting(_currentSetting, tmpSetting8);
                    }
                    
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
                    if(GetSettingType(_currentSetting) == ST_INT_4B)
                    {
                        if(_fieldLen == 0)
                        {
                            _currentSsState = VS_SELECT_SETTING;
                        }
                        else
                        {
                            _fieldLen = 0;
                        }
                    }
                    else
                    {                    
                        _currentSsState = VS_SELECT_SETTING;
                        SetTempSettingValue(GetSettingValue(_currentSetting), tmpSetting8);
                    }
                }
                break;
            }
            SettingsDisplayRedraw();
        }
            break;
            
            
        case BTN_1:
        {
           if(VS_EDIT_SETTING && GetSettingType(_currentSetting) == ST_INT_4B) 
           {
               PutNum(1);
           }
        }
        break;
        case BTN_2:
        {
           if(VS_EDIT_SETTING && GetSettingType(_currentSetting) == ST_INT_4B) 
           {
               PutNum(2);
           }
        }
        break;
        case BTN_3:
        {
           if(VS_EDIT_SETTING && GetSettingType(_currentSetting) == ST_INT_4B) 
           {
               PutNum(3);
           }
        }
        break;
        case BTN_4:
        {
           if(VS_EDIT_SETTING && GetSettingType(_currentSetting) == ST_INT_4B) 
           {
               PutNum(4);
           }
        }
        break;
        case BTN_5:
        {
           if(VS_EDIT_SETTING && GetSettingType(_currentSetting) == ST_INT_4B) 
           {
               PutNum(5);
           }
        }
        break;
        case BTN_6:
        {
           if(VS_EDIT_SETTING && GetSettingType(_currentSetting) == ST_INT_4B) 
           {
               PutNum(6);
           }
        }
        break;
        case BTN_7:
        {
           if(VS_EDIT_SETTING && GetSettingType(_currentSetting) == ST_INT_4B) 
           {
               PutNum(7);
           }
        }
        break;
        case BTN_8:
        {
           if(VS_EDIT_SETTING && GetSettingType(_currentSetting) == ST_INT_4B) 
           {
               PutNum(8);
           }
        }
        break;
        case BTN_9:
        {
           if(VS_EDIT_SETTING && GetSettingType(_currentSetting) == ST_INT_4B) 
           {
               PutNum(9);
           }
        }
        break;
        case BTN_0:
        {
           if(VS_EDIT_SETTING && GetSettingType(_currentSetting) == ST_INT_4B) 
           {
               PutNum(0);
           }
        }
        break;
    }    
}

bool SettingsIsRoot()
{
    return _currentSsState == VS_ROOT;
}