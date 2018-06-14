#pragma once

#include <bgfx/bgfx.h>

namespace nexc {

	class GraphicsUtils {
	public:
		static bgfx::ProgramHandle loadProgram(const char* vsFilename, const char* fsFilename);

	};

}
