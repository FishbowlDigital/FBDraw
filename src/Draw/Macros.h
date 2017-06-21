// Macros.h
// Header file to define a bunch of data type conversion and pixel manimulation macros
//
// Copyright Fishbowl Digital 2017
//

#ifndef _MACROS_H
#define _MACROS_H

#include "Types.h"

#define BGRAColorToU32(color)					(color32_t) ((color.Blue << 24) | (color.Green << 16) | (color.Red << 8) | (color.Alpha));


#endif			// #define _MACROS_H