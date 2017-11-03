// Data1D.h
// Header file for the Data1D class
//
// Copyright Fishbowl Digital 2017
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

