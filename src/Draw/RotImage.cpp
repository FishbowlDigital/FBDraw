// RotateImage.cpp
// Implementation file for the Image class
//
// Copyright Fishbowl Digital 2019
//

#include "RotImage.h"
#include "Macros.h"
#include <math.h>

#ifndef PI
#define PI		3.14159265359
#endif

#define RoundInt(f)		((int)(f+0.5f))

namespace FBDraw
{

	// Constructor
	RotatableImage::RotatableImage(int x, int y, int w, int h, color32_t* image, bool hasAlpha /* = true */)
		: Image(x, y, w, h, image, hasAlpha)
	{
		// Default rotate point is about the center
		m_ptRotate = Point(w / 2, h / 2);
		m_theta = 0.0f;
	}

	RotatableImage::~RotatableImage()
	{

	}

	void RotatableImage::Rotate(float deg)
	{
		// Rotate about center of image
		m_ptRotate = Point(Width() / 2, Height() / 2);
		m_theta = deg;
	}

	void RotatableImage::RotateAbout(float deg, RotatePt::Location loc)
	{
		int w = Width();
		int h = Height();

		switch (loc)
		{
		case RotatePt::TopLeft:
			return RotateAbout(deg, 0, 0);

		case RotatePt::TopCenter:
			return RotateAbout(deg, w / 2, 0);

		case RotatePt::TopRight:
			return RotateAbout(deg, w-1, 0);

		case RotatePt::CenterLeft:
			return RotateAbout(deg, 0, h / 2);

		case RotatePt::Center:
			return RotateAbout(deg, w / 2, h / 2);

		case RotatePt::CenterRight:
			return RotateAbout(deg, w - 1, h / 2);

		case RotatePt::BottomLeft:
			return RotateAbout(deg, 0, h - 1);

		case RotatePt::BottomCenter:
			return RotateAbout(deg, w / 2, h - 1);

		case RotatePt::BottomRight:
			return RotateAbout(deg, w - 1, h - 1);

		default:	// Default is center
			Rotate(deg);
		}
	}

	void RotatableImage::RotateAbout(float deg, int x, int y)
	{
		m_theta = deg;
		m_ptRotate = Point(x, y);
	}

	Point RotatableImage::GetRotatedPoint(Point pt)
	{
		float angle = -m_theta * (PI / 180.0);

		// Translate to center
		int x1 = pt.X - m_ptRotate.X;
		int y1 = pt.Y - m_ptRotate.Y;

		// Rotate
		int xRot = RoundInt((x1 * cos(angle)) + (y1 * sin(angle)));
		int yRot = RoundInt((x1 * -sin(angle)) + (y1 * cos(angle)));

		// Revert center translation
		int x2 = xRot + m_ptRotate.X;
		int y2 = yRot + m_ptRotate.Y;
		
		return Point(x2, y2);
	}

	void RotatableImage::Render(color32_t* backBuffer, int width, int height)
	{
		if (ImageData() == NULL)
			return;

		color32_t* imageBuffer = ImageData();
		int xLoc = Location().X;
		int yLoc = Location().Y;
		int imgWidth = Width();
		int imgHeight = Height();
		//int iCanvasStart = (yLoc * width) + xLoc;
		float angle = -m_theta * (PI/180.0); //GetAngle(xLoc, yLoc);

		//Canvas coordinates four corners of the image
		Point topLeft = Point(xLoc, yLoc);
		Point topRight = Point(xLoc + imgWidth, yLoc);
		Point botLeft = Point(xLoc, yLoc + imgHeight);
		Point botRight = Point(xLoc + imgWidth, yLoc + imgHeight);

		//Rotate the points
		Point rotTopLeft = GetRotatedPoint(topLeft);
		Point rotTopRight = GetRotatedPoint(topRight);
		Point rotBotLeft = GetRotatedPoint(botLeft);
		Point rotBotRight = GetRotatedPoint(botRight);

		//Get Bounds of the rotated points
		int xMin = rotTopLeft.X;
		int yMin = rotTopLeft.Y;
		int xMax = rotTopLeft.X;
		int yMax = rotTopLeft.Y;

		if (xMin > rotTopRight.X)
			xMin = rotTopRight.X;
		if (xMin > rotBotLeft.X)
			xMin = rotBotLeft.X;
		if (xMin > rotBotRight.X)
			xMin = rotBotRight.X;

		if (yMin > rotTopRight.Y)
			yMin = rotTopRight.Y;
		if (yMin > rotBotLeft.Y)
			yMin = rotBotLeft.Y;
		if (yMin > rotBotRight.Y)
			yMin = rotBotRight.Y;

		if (xMax < rotTopRight.X)
			xMax = rotTopRight.X;
		if (xMax < rotBotLeft.X)
			xMax = rotBotLeft.X;
		if (xMax < rotBotRight.X)
			xMax = rotBotRight.X;

		if (yMax < rotTopRight.Y)
			yMax = rotTopRight.Y;
		if (yMax < rotBotLeft.Y)
			yMax = rotBotLeft.Y;
		if (yMax < rotBotRight.Y)
			yMax = rotBotRight.Y;

		//Clip if it goes off the canvas
		if (xMin < 0)
			xMin = 0;
		if (yMin < 0)
			yMin = 0;
		if (xMax > width)
			xMax = width;
		if (yMax > height)
			yMax = height;

		//Look up the source pixel
		for (int iY = yMin; iY < yMax; iY++)
		{
			for (int iX = xMin; iX < xMax; iX++)
			{
				// Translate to center
				int x1 = iX - m_ptRotate.X;
				int y1 = iY - m_ptRotate.Y;

				// Rotate
				int xRot = (x1 * cos(-angle)) + (y1 * sin(-angle));
				int yRot = (x1 * -sin(-angle)) + (y1 * cos(-angle));

				// Revert center translation
				int x2 = xRot + m_ptRotate.X;
				int y2 = yRot + m_ptRotate.Y;

				//If source pixel exists, save to back buffer
				if (x2 >= xLoc && x2 < (xLoc + imgWidth) && y2 >= yLoc && y2 < (yLoc + imgHeight))
				{
					backBuffer[iY * width + iX] = imageBuffer[(y2 - yLoc) * imgWidth + (x2 - xLoc)];
				}
			}
		}
	}

}
