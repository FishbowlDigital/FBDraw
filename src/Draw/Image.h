// Image.h
// Header file for the Image class
//
// Copyright Fishbowl Digital 2017
//

#ifndef _IMAGE_H
#define _IMAGE_H
#include "Types.h"
#include "IDrawable.h"

class Image : public IDrawable
{
	public:
	Image(int w, int h, color32_t* image);
	Image(int w, int h, color32_t* image, BGRA_Color color);

	virtual void Render(color32_t* backBuffer, int width, int height);

	private:
		// Properties
		int			i_height; 
		int			i_width;
		BGRA_Color	i_color;
		color32_t*	i_imageBuffer;
};

#endif			// #define _POINT_H

