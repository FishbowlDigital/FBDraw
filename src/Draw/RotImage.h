// RotateImage.h
// Header file for the Image class
//
// Copyright Fishbowl Digital 2017
//

#ifndef _ROTIMAGE_H
#define _ROTIMAGE_H
#include "Types.h"
#include "IDrawable.h"
#include "Point.h"
#include "Image.h"

namespace FBDraw
{
	namespace RotatePt
	{
		typedef enum
		{
			TopLeft,
			TopCenter,
			TopRight,
			CenterLeft,
			Center,
			CenterRight,
			BottomLeft,
			BottomCenter,
			BottomRight

		} Location;
	}

	class RotatableImage : public Image
	{
	public:
		RotatableImage(int x, int y, int w, int h, color32_t* image, bool hasAlpha = true);
		virtual ~RotatableImage();

		void Rotate(float deg);
		void RotateAbout(float deg, RotatePt::Location loc);
		void RotateAbout(float deg, int x, int y);

		virtual void 	Render(color32_t* backBuffer, int width, int height);

	protected:
		// Internal support operations
		inline Point GetRotatedPoint(Point pt);

		// properties

	private:
		// Properties
		Point		m_ptRotate;		// Rotate about this pixel location offset
		float		m_theta;		// degrees
	};

}

#endif			// #define _ROTIMAGE_H

