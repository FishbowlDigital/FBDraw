// Font.h
// Header file for the Font class
//
// Copyright Fishbowl Digital 2019
//

#ifndef _FONT_H
#define _FONT_H

#include "IDrawable.h"

#define	CHARACTER_COUNT			128

namespace FBDraw
{
	class Font
	{
	public:
		// Constructor/Destructor
		Font(color32_t* fontBuf, int w, int h);
		Font(color32_t* fontBuf, int w, int h, char start, char end);
		~Font();

		color32_t*		GetCharImage(char c);

		//properties
		int	Width() { return m_width; }
		int Height() { return m_height; }

	protected:
		void			InitializeFontTable();
		int				GetCharIndex(char c);

	private:
		int				m_width;
		int				m_height;
		color32_t*		m_buffer;
		color32_t*		m_cpyBuffer;
		char			m_startChar;
		char			m_endChar;
		int				m_fontTable[128];
	};
}

#endif		// #define _TEXT_H