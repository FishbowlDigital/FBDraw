// This is the main DLL file.

#include "stdafx.h"

#include "GraphicLibWrapper.h"

#include "Canvas.h"
#include "Types.h"
#include "Macros.h"
#include "Image.h"
#include "Line.h"
#include "Rectangle.h"
#include "Point.h"

// TEMP FOR TESTING
//#include "Test.h"

#include <string.h>


namespace GraphicLibWrapper {

	array<Byte>^ GraphicLib::GetDisplayBuffer()
	{
#if 0
		//// TEMP!
		int width = 100;
		int height = 100;
		int numPixels = width*height;

		//// GET THIS DATA FROM THE GRAPHICS LIBRARY...THIS IS JUST TEMPORARY!!!
		//UInt32* buffer = new UInt32[numPixels];
		//for (int i = 0; i < (width*height); i++)
		//{
		//	buffer[i] = 0xFF00;	// RANDOM COLOR FOR TESTING!!!
		//}
		Test testObject;
		UInt32* buffer = testObject.TestData();

		// Create array
		array<Byte>^ data = gcnew array<Byte>(numPixels * sizeof(UInt32));

		// Copy data
		pin_ptr<System::Byte> p = &data[0];
		unsigned char* pData = p;
		memcpy(pData, buffer, numPixels * sizeof(UInt32));

		// Return the managed buffer
		return data;
#endif

		return nullptr;
	}

	array<Byte>^ GraphicLib::DoATest()
	{
		//// TEMP!
		int width = 500;
		int height = 500;
		int numPixels = width*height;

		//Buffer to test image renderer
		color32_t* testImage = new color32_t[numPixels];
		for (int i = 0; i < (numPixels); i++)
		{
			testImage[i] = BGRAColorToU32((BGRA_Color{ 0x80, 0x80, 0xFF, 0x00 }));
		}
			
		// Create a Canvas and draw some stuff
		Canvas canvas(width, height, BGRA_Color{ 0x00, 0x00, 0x00, 0x00 });
		Line line1(Point(100, 100), Point(400, 400), BGRA_Color{ 0x00, 0xFF, 0x00, 0x00 });
		Line line2(Point(100, 400), Point(400, 100), BGRA_Color{ 0x00, 0xFF, 0x00, 0x00 });
		Rectangle rec1(60, 120, Point(220, 210), BGRA_Color{ 0xFF, 0x00, 0xFF, 0x00 });
		Image img(width, height, testImage);

		canvas.AddDrawable(&line1);
		canvas.AddDrawable(&line2);
		canvas.AddDrawable(&rec1);
		canvas.AddDrawable(&img);

		// Render it
		canvas.Render();

		// Get the backbuffer & Copy the data to return as managed array
		UInt32* buffer = canvas.GetBackBuffer();
		array<Byte>^ data = gcnew array<Byte>(numPixels * sizeof(UInt32));
		pin_ptr<System::Byte> p = &data[0];
		unsigned char* pData = p;
		memcpy(pData, buffer, numPixels * sizeof(UInt32));

		// Return the managed buffer
		return data;
	}

}
