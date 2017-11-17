// Image.h
// Header file for the Image class
//
// Copyright Fishbowl Digital 2017
//

#ifndef _COLORLUT_H
#define _COLORLUT_H
#include "Types.h"
#include "Point.h"

namespace FBDraw
{

	//template <typename T>
	class ColorLUT
	{
	public:
		ColorLUT(int min, int max);
		ColorLUT(BGRA_Bytes* table, int size, int min, int max);
		~ColorLUT();

		BGRA_Bytes GetColor(int value);
		int GetMin();
		void SetMin(int value);
		int GetMax();
		void SetMax(int value);

		BGRA_Bytes*	m_colorTable;

	private:
		// Properties
		int			m_size;
		int			m_min;
		int			m_max;

		float		m_invRange;
	};
}

#endif			// #define _COLORLUT_H

