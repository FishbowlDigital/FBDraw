// Text.h
// Header file for the Text class
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

#ifndef _TEXT_H
#define _TEXT_H

#include "IDrawable.h"

#include "Font.h"

namespace FBDraw
{

	typedef enum
	{
		TEXTALIGN_LEFT,
		TEXTALIGN_CENTER,
		TEXTALIGN_RIGHT,
	}TextJustification;


	class Text : public IDrawable
	{
	public:
		// Constructor/Destructor
		Text(Font* pFont, int x, int y, const char* text = "\0", TextJustification align = TEXTALIGN_CENTER);
		Text(Font* pFont, int x, int y, int containerWidth, int containerHeight, const char* text = "\0", TextJustification align = TEXTALIGN_CENTER);
		~Text();

		//Properties
		int GetXPos()					{ return m_xPos; }
		int GetYPos()					{ return m_yPos; }
		int GetWidth()					{ return m_width; }
		int GetHeight()					{ return m_height; }
		ARGB_Color GetColor()			{ return m_color; }

		void SetXPos(int xPos);
		void SetYPos(int yPos);
		void SetColor(ARGB_Color color);
		void SetText(const char* text);

		void 				SetAlignment(TextJustification align);
		TextJustification 	GetAlignment() { return m_alignment; }

		virtual void Render(color32_t* backBuffer, int width, int height);

		virtual bool	HitTest(int x, int y)
		{
			return false; /* NOT YET IMPLEMENTED */
		};

	private:
		int				m_xPos;
		int				m_yPos;

		int*			m_arrWidths;
		int*			m_arrAlignedTextPositionsInX;	// This is an array containing the text aligned x position for each line of text

		int				m_numLinesOfText;

		Font*			m_font;
		char*			m_text;
		int				m_lenText;

		bool			m_doUseSpecifiedDimensions;
		int				m_width;
		int				m_height;

		ARGB_Color		m_color;

		TextJustification   m_alignment;			// Contains the left/center/right Justification for the text.
	};
}

#endif		// #define _TEXT_H
