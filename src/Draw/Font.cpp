// Font.cpp
// Implementation file for the Font class
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

#include "Font.h"

#define DEFAULT_CHARACTER_SPACING	1

namespace FBDraw
{
	// Constructor
	Font::Font(color32_t* fontBuf, int w, int h)
	{

		m_fontDesc.ImageBuffer = fontBuf;
		m_fontDesc.Height = h;
		m_startChar = (char)32;  // ' ' space char, 32-126 are all typeable chars
		m_endChar = (char)126;	// '~' tilda char

		InitializeFontTable();

		// Init width and offset tables
		m_widthTable = new int[CHARACTER_COUNT];
		m_offsetTable = new int[CHARACTER_COUNT];
		for (int i = 0; i < CHARACTER_COUNT; i++)
		{
			m_widthTable[i] = w;		// monospaced
			m_offsetTable[i] = i * w * h * sizeof(color32_t);
		}

		m_fontDesc.WidthTable = m_widthTable;
		m_fontDesc.OffsetTable = m_offsetTable;

		m_characterSpacing = DEFAULT_CHARACTER_SPACING;

	}

	Font::Font(color32_t* fontBuf, int w, int h, char start, char end)
	{
		m_fontDesc.ImageBuffer = fontBuf;
		m_fontDesc.Height = h;
		m_startChar = start;
		m_endChar = end;


		InitializeFontTable();

		// Init width and offset tables
		m_widthTable = new int[CHARACTER_COUNT];
		m_offsetTable = new int[CHARACTER_COUNT];
		for (int i = 0; i < CHARACTER_COUNT; i++)
		{
			m_widthTable[i] = w;		// monospaced
			m_offsetTable[i] = i * w * h * sizeof(color32_t);
		}

		m_fontDesc.WidthTable = m_widthTable;
		m_fontDesc.OffsetTable = m_offsetTable;

		m_characterSpacing = DEFAULT_CHARACTER_SPACING;
	}
	
	Font::Font(FontDescriptor desc)
	{
		m_fontDesc = desc;
		m_startChar = (char)32;  // ' ' space char, 32-126 are all typeable chars
		m_endChar = 126;	// '~' tilda char

		InitializeFontTable();
		m_widthTable = NULL;
		m_offsetTable = NULL;

		m_characterSpacing = DEFAULT_CHARACTER_SPACING;
	}


	Font::~Font()
	{
		if (m_widthTable != NULL)
			delete m_widthTable;

		if (m_offsetTable != NULL)
			delete m_offsetTable;
	}

	void Font::InitializeFontTable()
	{
		int iter = 0;

		//Load all 128 chars in the ascii table
		for (int i = 0; i <= 127; i++)
		{
			m_fontTable[(char) i] = iter++;
		}
	}

	int Font::Width(char* str)
	{
		char c = str[0];
		int iter = 0;
		int width = 0;

		while (c != '\0')
		{
			width += Width(c) + m_characterSpacing;
			c = str[++iter];
		}

		return width;
	}


	int Font::GetCharIndex(char c)
	{
		int i = -1;
		if (c < 128)
			i = m_fontTable[c];

		if (i >= 0 && (i < (int)m_startChar || i > (int)m_endChar))
			return m_fontTable[' '];						//Return Space character if its untypable
		else
			return i;										//Return -1 Index if character doesnt exist
	}

	color32_t* Font::GetCharImage(char c)
	{
		uint32_t* imgbuf = (color32_t*) m_fontDesc.ImageBuffer;
		int index = GetCharIndex(c);
		if (index >= 0)
		{
			if (index >= (int)m_startChar && index <= (int)m_endChar)
			{
				index -= (int)m_startChar;

				return &imgbuf[m_fontDesc.OffsetTable[index] >> 2];	// divide by 4 (sizeof color32_t) as offsets are in bytes
			}
		}

		return NULL;
	}

	void Font::SetCharacterSpacing(int characterSpacing)
	{
		if (characterSpacing >= 0)
		{
			m_characterSpacing = characterSpacing;
		}
	}

}