// RotateImage.h
// Header file for the Rotatable Image class
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

