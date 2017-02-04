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
    PT_DOOR_OPEN // ����� ����-����
};

// ������ �������� ��������� ����� ���������
typedef enum
{
    PPN_NONE, // �� ��������
    PPN_FULL, // ������ ���
    PPN_SHORT // �������� ���  
}PrintParamName;


/*typedef struct 
{
    uint8_t Type;
    uint16_t Value;
}ParameterTag;*/

void InitParameters();

uint8_t GetParamCount();
bool SetParameter(uint8_t id, uint16_t value);
uint16_t GetParameter(uint8_t id);

/**
 * ����� ��������� �� �����
 * @param paramId           ID ���������
 * @param col               ������� (-1 - � ������� �������)
 * @param row               ��� (-1 - � ������� �������)
 * @param printParamName    �������� �� �������� ���������
 */
void PrintParameter(uint8_t paramId, int8_t col, int8_t row, PrintParamName printParamName);

#endif