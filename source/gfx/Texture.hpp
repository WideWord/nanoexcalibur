#pragma once

#include <bgfx/bgfx.h>
#include <string>

namespace nexc {

	class Texture {
	public:
		void loadFromFile(const std::string& filename);
		~Texture();
	private:
		friend class Rendering;
		bgfx::TextureHandle internal = BGFX_INVALID_HANDLE;
	};

}
