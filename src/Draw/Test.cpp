#include "Test.h"

#define ColorToBGR565(color) = (color.Red >> 3) | ((((unsigned int)color.Green) >> 2) << 5) | (((unsigned int)color.Blue >> 3) << 11)
#define ColorFromBGR565(u16)						(Draw_Color) { 255, ((u16 & 0x1F) << 3), ((u16 & 0x7E0) >> 3), ((u16 & 0xF800) >> 8) }
#define ColorFromBGRA32(u32)						(Draw_Color) { ((u32 >> 24) & 0xFF), ((u32 >> 16) & 0xFF), ((u32 >> 8) & 0xFF), (u32 & 0xFF) }
#define ColorToGray12(color)						(((color.Red*5) + (color.Green*7) + (color.Blue*4)));
#define ColorFromGray12(u16)						(Draw_Color) { 255, (u16>>4), (u16>>4), (u16>>4) }
#define AlphaMix8(backcolor, forecolor, alpha)		(uint8_t) (((alpha+1)*forecolor + ((255-alpha)*backcolor)) >> 8)
#define RGBToBGR565(r,g,b)							(r >> 3) | ((((uint16_t)g) & 0xFC) << 5) | (((uint16_t)b & 0xF8) << 11)

#ifdef DRAW_ENABLE_CANVAS_FMT_BGR565
#define Draw_SetPixel(canvas, color, x, y) Draw_SetPixelBGR565(canvas, color, x, y)
#endif

const int DRAW_SIZEOF_PYTHAGORUS = 10;
const int DRAW_SCALE_PYTHAGORUS = 8;

/*pedef PlotTool*;
*/
Test::Test() 
{
	// TEMP!
	x = 100;
	y = 100;
	int numPixels = x*y;
	
	int hexColor = 0x000000;
	// GET THIS DATA FROM THE GRAPHICS LIBRARY...THIS IS JUST TEMPORARY!!!
	for (int i = 0; i < numPixels; i++)
	{
		
		hexColor = hexColor++;
		m_testData[i] = hexColor;
	}

}

Test::~Test()
{
}

unsigned int* Test::TestData()
{
	return m_testData;
}

