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
		Text(Font* pFont, int x, int y, int containerWidth, int containerHeight, const char* text);
		~Text();

		//Properties
		int GetXPos()					{ return m_xPos; }
		int GetYPos()					{ return m_yPos; }
		int GetWidth();
		int GetHeight();
		ARGB_Color GetColor()			{ return m_color; }

		void SetXPos(int xPos)			{ m_xPos = xPos; }
		void SetYPos(int yPos)			{ m_yPos = yPos; }
		void SetColor(ARGB_Color color);
		void SetText(const char* text);

		virtual void Render(color32_t* backBuffer, int width, int height);

		virtual bool	HitTest(int x, int y)
		{
			return false; /* NOT YET IMPLEMENTED */
		};

	private:
		Font*			m_font;
		int				m_xPos;
		int				m_yPos;
		char*			m_text;
		int				m_lenText;

		int				m_width;
		int				m_height;

		ARGB_Color		m_color;
	};
}

#endif		// #define _TEXT_H
