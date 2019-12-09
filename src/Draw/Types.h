// Canvas.h
// Header file to define a bunch of types used in the graphic lib
//
// Copyright Fishbowl Digital 2017
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


	//#pragma pack(1)		// FIX!!!  DOUBLE CHECK THIS ON WINDOWS
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