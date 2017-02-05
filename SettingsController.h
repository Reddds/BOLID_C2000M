/* 
 * File:   SettingsController.h
 * Author: denis
 *
 * Created on 4 ������� 2017 �., 20:59
 */

#ifndef SETTINGSCONTROLLER_H
#define	SETTINGSCONTROLLER_H

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#ifdef	__cplusplus
extern "C" {
#endif

#define SETTINGS_COUNT 5
    
#define SETTING_LCD_BK 0    // ��������� ������ 
#define SETTING_KB_BK 1     // ��������� ������� 
#define SETTING_SAVESCREEN_TIMEOUT 2 // �������� ����� ���������� ������ � �������� 
#define SETTING_SAVESCREEN_BK 3 // ��������� � ������ ��������
#define SETTING_SAVESCREEN_KB_BK 4 // ��������� ������ � ������ ��������    
    
typedef enum 
{
    ST_0_100, // �� 0 �� 100
    ST_BOOL, // �� - ���
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
    {   "�����.���.", "��������� ����-", "��",        2,  ST_0_100, 2, 0, 100, 50},
    {    "�����.��.", "��������� ���-", "���",        3,  ST_0_100, 3, 0, 100, 50},
    {"����. ������.", "�������� �����", "���������",  9,  ST_0_100, 4, 5,  60,  5},
    // ������������ �� ��������
    {"�����.������.", "��������� ���", "��������",    8,  ST_0_100, 5, 0, 100, 50},   
    {"�����.��.���.", "�����.������ ���", "��������", 8,  ST_0_100, 6, 0, 100, 50},
};

void InitSettings(); // !!! ��������
    
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

