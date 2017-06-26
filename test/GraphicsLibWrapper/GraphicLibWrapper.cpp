// This is the main DLL file.

#include <iostream>
#include <math.h>

#include "stdafx.h"
#include "GraphicLibWrapper.h"

#include "Canvas.h"
#include "Types.h"
#include "Macros.h"
#include "Image.h"
#include "Line.h"
#include "Rectangle.h"
#include "Point.h"
#include "Plot1D.h"

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
		/*int imgWidth = 200;
		int imgHeight = 160;
		int imgNumPixels = imgWidth * imgHeight;
		color32_t* testImage = new color32_t[imgNumPixels];
		for (int iY = 0; iY < imgHeight; iY++)
		{
			for (int iX = 0; iX < imgWidth; iX++)
			{
				testImage[(iY*imgWidth) + iX] = BGRAColorToU32((BGRA_Color{ (uint8_t)iX, (uint8_t)iY, 0x00, 0x80 }));
			}
		}*/
			

		int testPlot[500];
		for (int i = 0; i < 500; i++)
		{
			float ySin = (System::Math::Sin(((float)i * .1)));
			float yValue = (100 * ySin);

			testPlot[i] = (int)yValue;
			//std::cout << testPlot[i] << "\n";
			System::Diagnostics::Debug::WriteLine(testPlot[i]);
		}

		// Create a Canvas and draw some stuff
		Canvas canvas(width, height, BGRA_Color{ 0x00, 0x00, 0x00, 0x00 });
		Line line1(Point(35, 5), Point(60, 90), BGRA_Color{ 0x00, 0xFF, 0x00, 0x00 });
		Line line2(Point(80, 5), Point(20, 65), BGRA_Color{ 0xFF, 0x00, 0xFF, 0x00 });
		Line line3(Point(2, 45), Point(90, 55), BGRA_Color{ 0xFF, 0x80, 0x00, 0x00 });
		Line line4(Point(95, 15), Point(45, 75), BGRA_Color{ 0x00, 0x00, 0xFF, 0x00 });
		Line line5(Point(45, 15), Point(95, 75), BGRA_Color{ 0x00, 0x00, 0xFF, 0x00 });
		Plot1D plot(testPlot, 500, Point(0, 250), BGRA_Color{ 0x00, 0xFF, 0xFF, 0x00 });
		
		/*Rectangle rec1(60, 120, Point(325, 210), BGRA_Color{ 0xFF, 0x80, 0x00, 0x00 });
		Image img(Point(150, 80), imgWidth, imgHeight, testImage);*/

		/*canvas.AddDrawable(&line1);
		canvas.AddDrawable(&line2);
		canvas.AddDrawable(&line3);
		canvas.AddDrawable(&line4);
		canvas.AddDrawable(&line5);*/
		canvas.AddDrawable(&plot);
		/*canvas.AddDrawable(&rec1);
		canvas.AddDrawable(&img);*/

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
