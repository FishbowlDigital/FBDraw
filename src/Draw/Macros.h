// Macros.h
// Header file to define a bunch of data type conversion and pixel manimulation macros
//
// Copyright Fishbowl Digital 2017
//

#ifndef _MACROS_H
#define _MACROS_H

#include "Types.h"


#define BGRAColorToU32(color)					(color32_t) ((color.Blue << 24) | (color.Green << 16) | (color.Red << 8) | (color.Alpha))
#define U32toBGRAColor(color)					BGRA_Color{ (color >> 24) & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF, (color & 0xFF)}

//#define AlphaMix8(backcolor, forecolor, alpha)	(((((alpha+1)*forecolor + ((255-alpha)*backcolor))) & 0xFFFF) >> 8)
#define AlphaMix8(backcolor, forecolor, alpha)	(((((uint32_t)alpha)*forecolor + ((uint32_t)(0xFF-alpha))*backcolor)) >> 8)

//inline uint8_t AlphaMix8(uint16_t backcolor, uint16_t forecolor, uint16_t alpha) { return (uint8_t) (((alpha*forecolor) + ((0xFF - alpha)*backcolor)) >> 8); } 

#endif			// #define _MACROS_H