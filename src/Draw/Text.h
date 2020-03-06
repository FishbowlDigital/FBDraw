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
		int GetWidth();
		int GetHeight();
		ARGB_Color GetColor()			{ return m_color; }

		void SetXPos(int xPos)			{ m_xPos = xPos; }
		void SetYPos(int yPos)			{ m_yPos = yPos; }
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
		Font*			m_font;
		int				m_xPos;
		int				m_yPos;
		int				m_textPosX;
		int				m_textPosY;
		char*			m_text;
		int				m_lenText;

		int				m_width;
		int				m_height;

		ARGB_Color		m_color;

		TextJustification   m_alignment;			// Contains the left/center/right Justification for the text.
	};
}

#endif		// #define _TEXT_H
