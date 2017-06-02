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

#define SETTINGS_COUNT 8
    
#define SETTING_LCD_BK 0    // ��������� ������ 
#define SETTING_KB_BK 1     // ��������� ������� 
#define SETTING_SAVESCREEN_TIMEOUT 2 // �������� ����� ���������� ������ � �������� 
#define SETTING_SAVESCREEN_BK 3 // ��������� � ������ ��������
#define SETTING_SAVESCREEN_KB_BK 4 // ��������� ������ � ������ ��������   
#define SETTING_IDLE_SCREEN_ROTATE_TIMEOUT 5 // �������� ����� �������������� ������� �������

#define SETTING_MODBUS_MUSTER 7 // ����� ������� ����   
    
typedef enum 
{
    ST_0_100, // �� 0 �� 100
    ST_BOOL, // �� - ���
    ST_INT_4B, // ����� �����, 4 ����� �������� � ����������       
    ST_MUL_0_1 = 0x10 // �������� ���������� ������ �� 10       
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
//    {   "�����.���.", "��������� ����-", "��",        2,  ST_0_100, 2, 0, 100, 50},
//    {    "�����.��.", "��������� ���-", "���",        3,  ST_0_100, 3, 0, 100, 50},
//    {"����. ������.", "�������� �����", "���������",  9,  ST_0_100, 4, 5,  60,  5},
//    // ������������ �� ��������
//    {"�����.������.", "��������� ���", "��������",    8,  ST_0_100, 5, 0, 100, 50},   
//    {"�����.��.���.", "�����.������ ���", "��������", 8,  ST_0_100, 6, 0, 100, 50},
//};


void InitSettings(); // !!! ��������
    
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

