// Text.cpp
// Implementation file for the Text class
//
// Copyright Fishbowl Digital 2019
//

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
		char c = m_text[0];
		int iter = 0;

		while (c != '\0')
		{
			c = m_text[iter++];
		}

		iter--;

		return (iter * m_font->Width() + iter * SPACE_BETWEEN_CHARACTERS);
	}

	int Text::GetHeight()
	{
		return m_font->Height();
	}

	void Text::Render(color32_t* backBuffer, int width, int height)
	{
		if (m_font == NULL)
			return;

		int iter = 0;
		int xPos = m_xPos;
		int charWidth = m_font->Width();
		int charHeight = m_font->Height();
		char c = m_text[0];

		// Simple Y Bounds check
		if ((m_yPos < 0) || ((m_yPos + charHeight) > height))
			return;

		while (c != '\0')
		{
			int iCanvasStart = (m_yPos * width) + xPos;

			// Simple X bounds check
			if ((xPos >= 0) && ((xPos + charWidth) < width))
			{
				color32_t* charBuffer = m_font->GetCharImage(c);

				if (charBuffer != NULL)
				{
					BGRA_Color mixBGRA = BGRA_Color{ 0x00, 0x00, 0x00, 0x00 };
					for (int iY = 0; iY < charHeight; iY++)
					{
						int iCanvasRowStart = iCanvasStart + (iY * width);
						int iImageRowStart = (iY * charWidth);

						for (int iX = 0; iX < charWidth; iX++)
						{
							// Alpha mix the image pixel and the back buffer
							BGRA_Bytes imgColor, backColor, mixColor;
							imgColor.U32 = charBuffer[iImageRowStart + iX];
							backColor.U32 = backBuffer[iCanvasRowStart + iX];

							uint8_t alpha = 0xFF - imgColor.Color.Alpha;	// CRAP!!! BACKWARDS!!!
							mixColor.Color.Red = AlphaMix8(backColor.Color.Red, imgColor.Color.Red, alpha);
							mixColor.Color.Green = AlphaMix8(backColor.Color.Green, imgColor.Color.Green, alpha);
							mixColor.Color.Blue = AlphaMix8(backColor.Color.Blue, imgColor.Color.Blue, alpha);

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
