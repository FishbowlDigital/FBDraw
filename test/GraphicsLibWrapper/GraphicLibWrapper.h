// GraphicLibWrapper.h

#pragma once

using namespace System;

namespace GraphicLibWrapper {

	public ref class GraphicLib
	{
	public:
		static array<Byte>^				GetDisplayBuffer();
		static array<Byte>^				DoATest();

	};
}
