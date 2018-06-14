#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../3rdparty/stb_image.h"

namespace nexc {

	void Texture::loadFromFile(const std::string& filename) {
		int w, h, c;

		void* pixels = stbi_load(filename.c_str(), &w, &h, &c, 4);

		if (bgfx::isValid(internal)) {
			bgfx::destroy(internal);
		}

		internal = bgfx::createTexture2D(w, h, false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_NONE, bgfx::makeRef(pixels, (uint32_t)(w * h * 4), [](void* data, void* userData) {
			stbi_image_free(data);
		}));
	}

	Texture::~Texture() {
		if (bgfx::isValid(internal)) {
			bgfx::destroy(internal);
		}
	}

}
