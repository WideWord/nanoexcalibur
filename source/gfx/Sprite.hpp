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

			Vertex(Vec2 position) : position(position) {}
		};

		void setMesh(const bgfx::Memory* vertices, const bgfx::Memory* indices) {
			if (bgfx::isValid(vertexBuffer)) {
				bgfx::destroy(vertexBuffer);
			}
			if (bgfx::isValid(indexBuffer)) {
				bgfx::destroy(indexBuffer);
			}

			bgfx::VertexDecl vd;
			vd
					.begin()
					.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
					.end();

			vertexBuffer = bgfx::createVertexBuffer(vertices, vd);
			indexBuffer = bgfx::createIndexBuffer(indices);
		}

		void setTexture(Ref<Texture> newTexture) {
			texture = std::move(newTexture);
		}

		Ref<Texture> getTexture() {
			return texture;
		}

		~Sprite() {
			if (bgfx::isValid(vertexBuffer)) {
				bgfx::destroy(vertexBuffer);
			}
			if (bgfx::isValid(indexBuffer)) {
				bgfx::destroy(indexBuffer);
			}
		}
	private:
		friend class Rendering;
		bgfx::VertexBufferHandle vertexBuffer = BGFX_INVALID_HANDLE;
		bgfx::IndexBufferHandle indexBuffer = BGFX_INVALID_HANDLE;
		Ref<Texture> texture;
	};

}
