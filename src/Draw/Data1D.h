// Data1D.h
// Header file for the Data1D class
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

#ifndef _DATA1D_H
#define _DATA1D_H
#include "Types.h"
#include "Point.h"
#include "IData.h"

namespace FBDraw
{

	class Data1D : public IData
	{
	public:
		Data1D(float* data, int dataLength);
		Data1D(float* data, int dataLength, char* label, float resolution, float lowerBoundX);

		virtual char* getLabel();
		virtual void setLabel(char* label);

		virtual float* getData();
		virtual void setData(float* data, int size);

		virtual int getSize();

		virtual float getResolution();
		virtual void setResolution(float resolution);

		virtual float getLowerBoundX();
		virtual void setLowerBoundX(float lowerBoundX);

	private:
		// Properties
		float* m_Data;
		char* m_Label;
		int m_DataLength;
		float m_Resolution;
		float m_LowerBoundX;
	};
}
#endif			// #define _POINT_H

