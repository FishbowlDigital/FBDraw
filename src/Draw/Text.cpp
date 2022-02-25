// Text.cpp
// Implementation file for the Text class
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
//

#include <string.h>
#include <stdio.h>

#include "Point.h"
#include "Text.h"
#include "Image.h"
#include "Macros.h"


namespace FBDraw
{
	// Constructor
	Text::Text(Font* pFont, int x, int y, const char* text, TextJustification align/* = TEXTALIGN_CENTER*/)
	{
		m_numLinesOfText = 0;		// initialize this to 0 and we'll calculate when we set the text
		m_font = pFont;

		m_color = ARGB_Color{ 0xFF, 0xFF, 0xFF, 0xFF };

		m_xPos = x;
		m_yPos = y;

		m_width = 0;	//Initialize to 0. Will be set in SetText()
		m_height = 0;	//Initialize to 0. Will be set in SetText()
		m_doUseSpecifiedDimensions = false;

		m_text = NULL;
		m_arrAlignedTextPositionsInX = NULL;
		m_arrWidths = NULL;

		m_alignment = align;

		m_lenText = 0;
		SetText(text);

		Visible = true;
	}

	Text::Text(Font* pFont, int x, int y, int containerWidth, int containerHeight, const char* text, TextJustification align /*= TEXTALIGN_CENTER*/)
		: Text(pFont, x, y, text, align)
	{
		// Bounding area
		m_width = containerWidth;
		m_height = containerHeight;
		m_doUseSpecifiedDimensions = true;

		//Center Justified on Height.
		if (pFont != NULL)
			m_yPos = y + ((m_height - pFont->Height()) / 2);

		SetText(text);
	}

	// Destructor
	Text::~Text()
	{
		if (m_text != NULL)
			delete m_text;

		if (m_arrWidths != NULL)
			delete m_arrWidths;

		if (m_arrAlignedTextPositionsInX != NULL)
			delete m_arrAlignedTextPositionsInX;

		m_text = NULL;
		m_arrWidths = NULL;
		m_arrAlignedTextPositionsInX = NULL;
	}

	

	void Text::SetColor(ARGB_Color color)
	{
		m_color = color;
	}

	void Text::SetText(const char* text)
	{
		// Array allocation
		int len = strlen(text);

		if (len > m_lenText)	// reallocate larger string?
		{
			if (m_text != NULL)
				delete m_text;
			m_text = new char[len+1];
			m_lenText = len;
		}

		//Copy
		strcpy(m_text, text);

		// Calculate the number of lines of text
		int numLinesOfText = 1;
		for (int i = 0; i < m_lenText; i++)
		{
			if (m_text[i] == '\n')
			{
				numLinesOfText++;
			}
		}

		// Allocate arrays to keep track of parameters for each line of text
		//if (numLinesOfText > m_numLinesOfText)
		{
			if (m_arrAlignedTextPositionsInX != NULL)
				delete m_arrAlignedTextPositionsInX;

			m_arrAlignedTextPositionsInX = new int[numLinesOfText];

			if (m_arrWidths != NULL)
				delete m_arrWidths;

			m_arrWidths = new int[numLinesOfText];
		}

		// Cache number of lines of text
		m_numLinesOfText = numLinesOfText;

		// Calculate widths of each line
		int indxChar = 0;
		int indxLineNum = 0;
		char c = m_text[indxChar];
		m_arrWidths[0] = 0;
		while (c != '\0')
		{
			if (c == '\n')
			{
				m_arrWidths[++indxLineNum] = 0;
			}
			else
			{
				m_arrWidths[indxLineNum] += m_font->Width(c) + m_font->GetCharacterSpacing();
			}

			c = m_text[++indxChar];
		}
		
		
		// If dimensions were not specified, specify now
		// m_width will be the width of the longest line of text
		if (!m_doUseSpecifiedDimensions)
		{
			int maxWidth = 0;
			for (int i = 0; i < m_numLinesOfText; i++)
			{
				if (maxWidth < m_arrWidths[i])
				{
					maxWidth = m_arrWidths[i];
				}
			}
			m_width = maxWidth;
			m_height = m_font->Height();
		}

		// Justify each line of text
		for (int lineNum = 0; lineNum < m_numLinesOfText; lineNum++)
		{
			switch (m_alignment)
			{
			case TEXTALIGN_LEFT:
				m_arrAlignedTextPositionsInX[lineNum] = m_xPos;
				break;

			case TEXTALIGN_CENTER:
				m_arrAlignedTextPositionsInX[lineNum] = m_xPos + ((m_width - m_arrWidths[lineNum]) / 2);
				break;

			case TEXTALIGN_RIGHT:
				m_arrAlignedTextPositionsInX[lineNum] = m_xPos + m_width - m_arrWidths[lineNum];
				break;
			}
		}
	}

	void Text::SetAlignment(TextJustification align)
	{
		m_alignment = align;
		SetText(m_text);
	}

	void Text::SetXPos(int xPos)
	{
		m_xPos = xPos;
		SetText(m_text);
	}
	void Text::SetYPos(int yPos)
	{
		m_yPos = yPos;
		SetText(m_text);
	}

	void Text::Render(color32_t* backBuffer, int width, int height)
	{
		if (m_font == NULL)
			return;

		int indxChar = 0;
		int indxLineNum = 0;
		int xPos = m_arrAlignedTextPositionsInX[indxLineNum];
		int yPos = m_yPos;
		int charHeight = m_font->Height();
		char c = m_text[0];

		// Simple Y Bounds check
		if ((yPos < 0) || ((yPos + charHeight) > height))
			return;

		while (c != '\0')
		{
			// Check if we've got a new line
			if (c == '\n')
			{
				xPos = m_arrAlignedTextPositionsInX[++indxLineNum];
				yPos += charHeight;
			}
			else
			{
				int iCanvasStart = (yPos * width) + xPos;
				int charWidth = m_font->Width(c);

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

				xPos += charWidth + m_font->GetCharacterSpacing();
			}

			// next character
			c = m_text[++indxChar];
		}
	}

	
}
