// Macros.h
// Header file to define a bunch of data type conversion and pixel manimulation macros
//
// Copyright(c) 2017 - 2022 Fishbowl Digital LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef _MACROS_H
#define _MACROS_H

#include "Types.h"


#define BGRAColorToU32(color)					(color32_t) ((color.Blue << 24) | (color.Green << 16) | (color.Red << 8) | (color.Alpha))
#define U32toBGRAColor(color)					ARGB_Color{ (color >> 24) & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF, (color & 0xFF)}

#define ARGBColorToU32(color)					(color32_t) ((color.Alpha << 24) | (color.Red << 16) | (color.Green << 8) | (color.Blue))
#define U32toARGBColor(color)					ARGB_Color{ color & 0xFF, (color >> 8) & 0xFF, (color >> 16) & 0xFF, (color >> 24) & 0xFF}


#define AlphaMix8(backcolor, forecolor, alpha)		(													\
														(												\
																(((uint32_t)0x100-alpha)*backcolor) + 	\
																(((uint32_t)(alpha+1))*forecolor) 		\
														) >> 8 											\
													)

#endif			// #define _MACROS_H
