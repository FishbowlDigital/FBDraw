// Font.cpp
// Implementation file for the Font class
//
// Copyright Fishbowl Digital 2019
//

#include "Font.h"

namespace FBDraw
{
	// Constructor
	Font::Font(color32_t* fontBuf, int w, int h)
	{
		m_buffer = fontBuf;
		m_width = w;
		m_height = h;
		m_startChar = (char)32;  // ' ' space char, 32-126 are all typeable chars
		m_endChar = (char)126;	// '~' tilda char

		m_cpyBuffer = m_buffer;

		InitializeFontTable();
	}

	Font::Font(color32_t* fontBuf, int w, int h, char start, char end)
	{
		m_buffer = fontBuf;
		m_width = w;
		m_height = h;
		m_startChar = start;
		m_endChar = end;

		m_cpyBuffer = m_buffer;

		InitializeFontTable();
	}

	Font::~Font()
	{
		if (m_buffer != NULL)
			delete m_buffer;
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
		int index = GetCharIndex(c);
		if (index >= 0)
		{
			if (index >= (int)m_startChar && index <= (int)m_endChar)
			{
				index -= (int)m_startChar;
				return &m_buffer[m_width * m_height * index];
			}
		}

		return NULL;
	}
}