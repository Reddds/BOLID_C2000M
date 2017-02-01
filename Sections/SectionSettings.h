#ifndef SECTIONSETTINGS_H
#define SECTIONSETTINGS_H

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */


/**
 * Обображение начального экрана настроек
 */
void SettingsStart();

/**
 * Обработка нажатия кнопок
 * 
 * @param button ID кнопки
 */
void SettingsOnButton(uint8_t button);


/**
 * Проверка, находится ли текущий вид на верхнем уровне
 * чтобы ипользовать кнопки <,> для переходов между разделами
 * @return true - на верхнем уровне
 */
bool SettingsIsRoot();

#endif



