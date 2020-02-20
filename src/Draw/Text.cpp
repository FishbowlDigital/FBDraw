// Text.cpp
// Implementation file for the Text class
//
// Copyright Fishbowl Digital 2019
//

#include <string.h>

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
		m_color = ARGB_Color{ 0xFF, 0xFF, 0xFF, 0xFF };

		m_lenText = 0;
		m_text = new char[1];
		SetText(text);

		Visible = true;
	}

	Text::Text(Font* pFont, int x, int y, int containerWidth, int containerHeight, const char* text)
	{
		m_font = pFont;

		// Bounding area
		m_width = containerWidth;
		m_height = containerHeight;

		m_lenText = 0;
		m_text = new char[1];
		SetText(text);

		// Center justified
		m_xPos = x + ((m_width - GetWidth()) / 2);
		m_yPos = y + ((m_height - GetHeight()) / 2);


		Visible = true;
	}

	// Destructor
	Text::~Text()
	{

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

	void Text::SetColor(ARGB_Color color)
	{
		m_color = color;
	}

	void Text::SetText(const char* text)
	{
		int len = strlen(text);
		if (len > m_lenText)	// reallocate larger string?
		{

			delete m_text;
			m_text = new char[len+1];
			m_lenText = len;
		}

		// Copy
		strcpy(m_text, text);
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

							uint8_t alpha = imgColor.Color.Alpha;
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
