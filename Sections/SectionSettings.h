#ifndef SECTIONSETTINGS_H
#define SECTIONSETTINGS_H

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */


/**
 * ����������� ���������� ������ ��������
 */
void SettingsStart();

/**
 * ��������� ������� ������
 * 
 * @param button ID ������
 */
void SettingsOnButton(uint8_t button);


/**
 * ��������, ��������� �� ������� ��� �� ������� ������
 * ����� ����������� ������ <,> ��� ��������� ����� ���������
 * @return true - �� ������� ������
 */
bool SettingsIsRoot();

#endif



