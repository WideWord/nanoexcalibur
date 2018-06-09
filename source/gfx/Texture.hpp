#pragma once

#include <cstdint>
#include <string>
#include "../util/Math.hpp"

namespace nexc {

	class Texture {
	public:
		Texture();
		~Texture();
		void loadFromMemory(int width, int height, void* pixels);
		void loadFromFile(const std::string& filename);

		uint32_t getId() {
			return id;
		}

		IVec2 getSize() {
			return size;
		}
	private:
		uint32_t id;
		IVec2 size;
	};

}
