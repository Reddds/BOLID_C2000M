/*
  Print.h - Base class that provides print() and println()
  Copyright (c) 2008 David A. Mellis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Print_h
#define Print_h

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

//#include "Printable.h"

#define DEC 10 // 0x0A
#define HEX 16 // 0x10
#define OCT 8  // 0x08
#define BIN 2  // 0x02

#define MASK_BASE 0x001F
#define MASK_FIELD_SIZE 0x0F00 // Ширина поля + 1.  

#define FIELD_SIZE(x) (((uint16_t)(x - 1)) << 8) // Задаём ширину поля

#define SHOW_SIGN 0x0020
#define SHOW_STARTING_ZEROES 0x0040 
#define SHOW_USE_FIELD_SIZE 0x0080





//size_t DisplayPrint(const __FlashStringHelper *);
//size_t DisplayPrint(const String &);
uint8_t DisplayPrintStr(const char *str);
uint8_t DisplayPrintChar(char);
uint8_t DisplayPrintSymbol(uint8_t c);
//uint8_t DisplayPrintInt(unsigned char, int = DEC);
//uint8_t DisplayPrint(int, int = DEC);
//uint8_t DisplayPrint(unsigned int, int = DEC);
uint8_t DisplayPrintInt(long, uint16_t);
uint8_t DisplayPrintUInt(unsigned long, uint16_t);
uint8_t DisplayPrintFloat(double, uint16_t);
//size_t DisplayPrint(const Printable&);

//size_t println(const __FlashStringHelper *);
////size_t println(const String &s);
//size_t println(const char[]);
//size_t println(char);
//size_t println(unsigned char, int = DEC);
//size_t println(int, int = DEC);
//size_t println(unsigned int, int = DEC);
//size_t println(long, int = DEC);
//size_t println(unsigned long, int = DEC);
//size_t println(double, int = 2);
////size_t println(const Printable&);
//size_t println(void);


#endif
