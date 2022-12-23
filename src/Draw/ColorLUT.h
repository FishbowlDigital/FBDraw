// ColorLUT.h
// Header file for the ColorLUT class
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

#ifndef _COLORLUT_H
#define _COLORLUT_H
#include "Types.h"
#include "Point.h"

namespace FBDraw
{
	class ColorLUT
	{
	public:
		ColorLUT(int min, int max);
		ColorLUT(ARGB_Bytes* table, int size, int min, int max);
		~ColorLUT();

		ARGB_Bytes GetColor(int value);
		int GetMin();
		void SetMin(int value);
		int GetMax();
		void SetMax(int value);

	private:
		// Properties
		ARGB_Bytes*		m_colorTable;
		bool					m_ownsColorTable;

		int						m_size;
		int						m_min;
		int						m_max;

		float					m_invRange;
	};
}

#endif			// #define _COLORLUT_H

