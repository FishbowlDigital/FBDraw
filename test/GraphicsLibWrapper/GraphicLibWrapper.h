// GraphicLibWrapper.h

#pragma once

using namespace System;

namespace GraphicsLibWrapper {

	public ref class GraphicLib
	{
	public:
		static array<Byte>^				GetDisplayBuffer();
		static array<Byte>^				DoATest();

		static array<Byte>^				DoAFontTest();
	};
}
