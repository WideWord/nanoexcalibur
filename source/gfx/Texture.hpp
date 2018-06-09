#pragma once

#include <cstdint>
#include <string>

namespace nexc {

	class Texture {
	public:
		Texture();
		~Texture();
		void loadFromMemory(int width, int height, void* pixels);
		void loadFromFile(const std::string& filename);
	private:
		uint32_t id;
	};

}
