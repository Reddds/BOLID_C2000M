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
//#include <stdio.h> // for size_t

//#include "Printable.h"

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2



//size_t DisplayPrint(const __FlashStringHelper *);
//size_t DisplayPrint(const String &);
uint8_t DisplayPrintStr(const char *str);
uint8_t DisplayPrintChar(char);
//uint8_t DisplayPrintInt(unsigned char, int = DEC);
//uint8_t DisplayPrint(int, int = DEC);
//uint8_t DisplayPrint(unsigned int, int = DEC);
uint8_t DisplayPrintInt(long, int);
uint8_t DisplayPrintUInt(unsigned long, int);
uint8_t DisplayPrintFloat(double, uint8_t);
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
