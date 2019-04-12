// Text.h
// Header file for the Text class
//
// Copyright Fishbowl Digital 2019
//

#ifndef _TEXT_H
#define _TEXT_H

#include "IDrawable.h"
#include "Font.h"

namespace FBDraw
{
	class Text : public IDrawable
	{
	public:
		// Constructor/Destructor
		Text(Font* pFont, int x, int y, const char* text);
		~Text();

		//Properties
		int GetXPos()					{ return m_xPos; }
		int GetYPos()					{ return m_yPos; }
		int GetWidth();
		int GetHeight();

		int SetXPos(int xPos)			{ m_xPos = xPos; }
		int SetYPos(int yPos)			{ m_yPos = yPos; }
		int SetText(const char* text)	{ m_text = text; }
		
		virtual void Render(color32_t* backBuffer, int width, int height);

	private:
		Font*			m_font;
		int				m_xPos;
		int				m_yPos;
		const char*		m_text;
	};
}

#endif		// #define _TEXT_H