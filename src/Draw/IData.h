// IData.h
// Header file for the IData pure virtual interface class
//
// Copyright Fishbowl Digital 2017
//

#ifndef _IDATA_H
#define _IDATA_H

#include <iostream>
#include "Types.h"

#define MAX_LABEL_LEN			50

class IData
{
public:

	IData();
	~IData();

	virtual char* getLabel() = 0;
	virtual void setLabel() = 0;

	/*virtual void Undo() = 0;
	virtual void Redo() = 0;*/

private:
	static int m_dataCount;
	char m_label[MAX_LABEL_LEN];
};

#endif			// #define _IData_H

