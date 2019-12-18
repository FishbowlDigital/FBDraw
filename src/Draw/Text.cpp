// Text.cpp
// Implementation file for the Text class
//
// Copyright Fishbowl Digital 2019
//

#include <string>

#include "Point.h"
#include "Text.h"
#include "Image.h"
#include "Macros.h"

#define SPACE_BETWEEN_CHARACTERS		1

namespace FBDraw
{
	// Constructor
	Text::Text(Font* pFont, int x, int y, const char* text)
	{
		m_font = pFont;
		m_xPos = x;
		m_yPos = y;
		m_text = text;
		m_color = ARGB_Color{ 0xFF, 0xFF, 0xFF, 0xFF };

		Visible = true;
	}

	Text::Text(Font* pFont, Rectangle rectContainer, const char* text) 
	{
		m_font = pFont;
		m_text = text;
		m_color = ARGB_Color{ 0xFF, 0xFF, 0xFF, 0xFF };

		int x = rectContainer.GetTopLeft().X + ((rectContainer.GetWidth() - GetWidth()) / 2);
		int y = rectContainer.GetTopLeft().Y + ((rectContainer.GetHeight() - GetHeight()) / 2);

		m_xPos = x;
		m_yPos = y;

		Visible = true;
	}

	// Destructor
	Text::~Text()
	{
		//if (m_font != NULL)
		//	delete m_font;

		//if (m_text != NULL)
		//	delete m_text;
	}

	int Text::GetWidth()
	{
		if (m_font)
		{
			char c = m_text[0];
			int iter = 0;
			int width = 0;

			while (c != '\0')
			{
				c = m_text[iter++];
				width += m_font->CharWidth(c) + SPACE_BETWEEN_CHARACTERS;
			}

			iter--;

			return width;
		}

		return 0;
	}

	int Text::GetHeight()
	{
		if (m_font)
		{
			return m_font->Height();
		}

		return 0;
	}

	void Text::Render(color32_t* backBuffer, int width, int height)
	{
		if (m_font == NULL)
			return;

		int iter = 0;
		int xPos = m_xPos;
		int charHeight = m_font->Height();
		char c = m_text[0];

		// Simple Y Bounds check
		if ((m_yPos < 0) || ((m_yPos + charHeight) > height))
			return;

		while (c != '\0')
		{
			int iCanvasStart = (m_yPos * width) + xPos;
			int charWidth = m_font->CharWidth(c);

			// Simple X bounds check
			if ((xPos >= 0) && ((xPos + charWidth) < width))
			{
				color32_t* charBuffer = m_font->GetCharImage(c);

				if (charBuffer != NULL)
				{
					ARGB_Color mixBGRA = ARGB_Color{ 0x00, 0x00, 0x00, 0x00 };
					for (int iY = 0; iY < charHeight; iY++)
					{
						int iCanvasRowStart = iCanvasStart + (iY * width);
						int iImageRowStart = (iY * charWidth);

						for (int iX = 0; iX < charWidth; iX++)
						{
							// Alpha mix the image pixel and the back buffer
							ARGB_Bytes imgColor, backColor, mixColor;
							imgColor.U32 = charBuffer[iImageRowStart + iX];
							backColor.U32 = backBuffer[iCanvasRowStart + iX];

							// Apply color to the font pixels which is grayscale
							imgColor.Color.Red = (((uint16_t)m_color.Red) * imgColor.Color.Red) >> 8;
							imgColor.Color.Green = (((uint16_t)m_color.Green) * imgColor.Color.Green) >> 8;
							imgColor.Color.Blue = (((uint16_t)m_color.Blue) * imgColor.Color.Blue) >> 8;

							//uint8_t alpha = 0xFF - imgColor.Color.Alpha;	// CRAP!!! BACKWARDS!!!
							uint8_t alpha = imgColor.Color.Alpha;	// CRAP!!! BACKWARDS!!!
							mixColor.Color.Red = AlphaMix8(backColor.Color.Red, imgColor.Color.Red, alpha);
							mixColor.Color.Green = AlphaMix8(backColor.Color.Green, imgColor.Color.Green, alpha);
							mixColor.Color.Blue = AlphaMix8(backColor.Color.Blue, imgColor.Color.Blue, alpha);
							mixColor.Color.Alpha = AlphaMix8(backColor.Color.Alpha, alpha, alpha);

							backBuffer[iCanvasRowStart + iX] = mixColor.U32;
						}
					}
				}
			}

			xPos += charWidth + SPACE_BETWEEN_CHARACTERS;	// 1 pixel between chars
			c = m_text[++iter];
		}
	}
}
