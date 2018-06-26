#pragma once

#include <glm/glm.hpp>

namespace nexc {

	using Vec2 = glm::vec2;
	using Vec3 = glm::vec3;

	using IVec2 = glm::ivec2;
	using IVec3 = glm::ivec3;

	using Mat2 = glm::mat2;
	using Mat3 = glm::mat3;
	using Mat4 = glm::mat4;

	struct IRect {
		IVec2 origin;
		IVec2 size;

		IRect() = default;
		IRect(int x, int y, int width, int height) : origin(x, y), size(width, height) {}
		IRect(IVec2 origin, IVec2 size) : origin(origin), size(size) {}
	};

}
