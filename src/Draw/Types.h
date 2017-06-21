// Canvas.h
// Header file to define a bunch of types used in the graphic lib
//
// Copyright Fishbowl Digital 2017
//

#ifndef _TYPES_H
#define _TYPES_H

// Native formats
typedef unsigned int			uint32_t;
typedef unsigned char			uint8_t;

// Pixel formats
typedef uint32_t				color32_t;


//#pragma pack(1)		// FIX!!!  DOUBLE CHECK THIS ON WINDOWS
typedef struct			/* packed as BGRA32 */
{
	uint8_t Alpha;
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
} BGRA_Color;

#ifndef NULL
	#define NULL		0
#endif


#endif			// #define _TYPES_H