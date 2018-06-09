#include <glad/glad.h>
#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../3rdparty/stb_image.h"

namespace nexc {

	Texture::Texture() {
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture() {
		glDeleteTextures(1, &id);
	}

	void Texture::loadFromMemory(int width, int height, void* pixels) {
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::loadFromFile(const std::string& filename) {
		int w, h, c;

		auto pixels = stbi_load(filename.c_str(), &w, &h, &c, 4);

		loadFromMemory(w, h, pixels);

		stbi_image_free(pixels);
	}

}
