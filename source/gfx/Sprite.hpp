#pragma once

#include <vector>
#include "../util/Math.hpp"
#include "../util/Memory.hpp"
#include <bgfx/bgfx.h>

namespace nexc {

	class Texture;

	class Sprite {
	public:
		struct Vertex {
			Vec2 position;
			Vec2 texCoord;
		};

		void setMesh(const bgfx::Memory* vertices, const bgfx::Memory* indices);

		void setTexture(Ref<Texture> newTexture) {
			texture = std::move(newTexture);
		}

		Ref<Texture> getTexture() {
			return texture;
		}

		~Sprite();
	private:
		friend class Rendering;
		bgfx::VertexBufferHandle vertexBuffer = BGFX_INVALID_HANDLE;
		bgfx::IndexBufferHandle indexBuffer = BGFX_INVALID_HANDLE;
		Ref<Texture> texture;
	};

}
