#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace nexc {

	class Texture;

	class Sprite {
	public:
		std::shared_ptr<Texture> texture;
		glm::vec2 origin;
		float pixelsInUnit;
		glm::vec2 textureOrigin;
		glm::vec2 textureSize;
	};

}
