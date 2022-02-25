// Font.h
// Header file for the Font class
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

#ifndef _FONT_H
#define _FONT_H

#include "IDrawable.h"

#define	CHARACTER_COUNT					128
#define SPACE_BETWEEN_CHARACTERS		1

namespace FBDraw
{
	typedef struct
	{
		int Height;								// Height of all characters
		int* WidthTable;							// Contains the width of each individual character
		int* OffsetTable;							// Contains 32-bit word offset into ImageBuffer for the individual image of each character

		void* ImageBuffer;				// Contains concatenated images of characters in grayscale

	} FontDescriptor;

	class Font
	{
	public:
		// Constructor/Destructor
		Font(color32_t* fontBuf, int w, int h);
		Font(color32_t* fontBuf, int w, int h, char start, char end);
		Font(FontDescriptor desc);
		~Font();

		int				Width(char* str);
		int				Width(char c) { return m_fontDesc.WidthTable[GetCharIndex(c) - m_startChar]; }
		color32_t*		GetCharImage(char c);

		//properties
		int Height() { return m_fontDesc.Height; }

		int				GetCharacterSpacing() { return m_characterSpacing; }
		void			SetCharacterSpacing(int characterSpacing);


	protected:
		void			InitializeFontTable();
		int				GetCharIndex(char c);

	private:
		char			m_startChar;
		char			m_endChar;
		int				m_fontTable[CHARACTER_COUNT];
		int*			m_widthTable;
		int*			m_offsetTable;
		int				m_characterSpacing;

		FontDescriptor	m_fontDesc;
	};
}

#endif		// #define _FONT_H
