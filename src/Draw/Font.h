// Font.h
// Header file for the Font class
//
// Copyright Fishbowl Digital 2019
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

	protected:
		void			InitializeFontTable();
		int				GetCharIndex(char c);

	private:
		char			m_startChar;
		char			m_endChar;
		int				m_fontTable[CHARACTER_COUNT];
		int*			m_widthTable;
		int*			m_offsetTable;

		FontDescriptor	m_fontDesc;
	};
}

#endif		// #define _FONT_H
