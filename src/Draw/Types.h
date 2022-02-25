// Canvas.h
// Header file to define a bunch of types used in the graphic lib
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

#ifndef _TYPES_H
#define _TYPES_H

#include <stdint.h>

namespace FBDraw
{

	//// Native formats
	//typedef unsigned int			uint32_t;
	//typedef unsigned char			uint8_t;

	// Pixel formats
	typedef uint32_t				color32_t;

#pragma pack (push, 1)
	typedef struct			/* packed as ARGB32 */
	{						/* Format: ARGB_Color{ Blue, Green, Red, Alpha }) */
		uint8_t Blue;
		uint8_t Green;
		uint8_t Red;
		uint8_t Alpha;
	} ARGB_Color;
#pragma pack(pop)

	typedef union
	{
		ARGB_Color	Color;
		color32_t	U32;
	} ARGB_Bytes;

#ifndef NULL
#define NULL		0
#endif

}

#endif			// #define _TYPES_H