#ifndef SECTIONROOMS_H
#define SECTIONROOMS_H

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

/**
 * ����������� ���������� ������ ������
 */
void RoomsStart();

/**
 * ��������� ������� ������
 * 
 * @param button ID ������
 */
void RoomsOnButton(uint8_t button);


/**
 * ��������, ��������� �� ������� ��� �� ������� ������
 * ����� ����������� ������ <,> ��� ��������� ����� ���������
 * @return true - �� ������� ������
 */
bool RoomsIsRoot();

#endif



