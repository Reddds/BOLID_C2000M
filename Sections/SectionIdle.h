#ifndef SECTIONIDLE_H
#define SECTIONIDLE_H

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */


/**
 * Отображение начального экрана ожидания
 */
void IdleStart();

/**
 * Обновление отображения
 */
void IdleUpdateView();

/**
 * Переключение на следующий экран после задержки
 */
void IdleNextScreen();
/**
 * Обработка нажатия кнопок
 * 
 * @param button ID кнопки
 */
void IdleOnButton(uint8_t button);


/**
 * Проверка, находится ли текущий вид на верхнем уровне
 * чтобы ипользовать кнопки <,> для переходов между разделами
 * @return true - на верхнем уровне
 */
bool IdleIsRoot();

#endif



