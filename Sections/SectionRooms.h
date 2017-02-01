#ifndef SECTIONROOMS_H
#define SECTIONROOMS_H

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

/**
 * ќтображение начального выбора комнат
 */
void RoomsStart();

/**
 * ќбработка нажати€ кнопок
 * 
 * @param button ID кнопки
 */
void RoomsOnButton(uint8_t button);


/**
 * ѕроверка, находитс€ ли текущий вид на верхнем уровне
 * чтобы ипользовать кнопки <,> дл€ переходов между разделами
 * @return true - на верхнем уровне
 */
bool RoomsIsRoot();

#endif



