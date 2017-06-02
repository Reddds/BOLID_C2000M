#ifndef SECTIONIDLE_H
#define SECTIONIDLE_H

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */


/**
 * ����������� ���������� ������ ��������
 */
void IdleStart();

/**
 * ���������� �����������
 */
void IdleUpdateView();

/**
 * ������������ �� ��������� ����� ����� ��������
 */
void IdleNextScreen();
/**
 * ��������� ������� ������
 * 
 * @param button ID ������
 */
void IdleOnButton(uint8_t button);


/**
 * ��������, ��������� �� ������� ��� �� ������� ������
 * ����� ����������� ������ <,> ��� ��������� ����� ���������
 * @return true - �� ������� ������
 */
bool IdleIsRoot();

#endif



