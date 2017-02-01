#ifndef PARAMETERSCONTROLLER_H
#define PARAMETERSCONTROLLER_H

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */


enum 
{
    PT_INT,
    PT_UINT,
    PT_FLOAT_1, // �������� ��������� ����� �� 10
    PT_FLOAT_2, // �������� ��������� ����� �� 100
    
    PT_TEMP, // �����������
    PT_HYM, // ���������
    PT_PRESS, // ��������
    PT_LIGHT, // ���� ���-����
};



typedef struct 
{
    uint8_t Type;
    uint16_t Value;
}ParameterTag;

void InitParameters();

/**
 * ����� ��������� �� �����
 * @param paramId   ID ���������
 * @param col       ������� (-1 - � ������� �������)
 * @param row       ��� (-1 - � ������� �������)
 */
void PrintParameter(uint8_t paramId, uint8_t col, uint8_t row);

#endif