#include "Sprite.hpp"

namespace nexc {

	void Sprite::setMesh(const bgfx::Memory* vertices, const bgfx::Memory* indices) {
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
				.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
				.end();

		vertexBuffer = bgfx::createVertexBuffer(vertices, vd);
		indexBuffer = bgfx::createIndexBuffer(indices);
	}

	Sprite::~Sprite() {
		if (bgfx::isValid(vertexBuffer)) {
			bgfx::destroy(vertexBuffer);
		}
		if (bgfx::isValid(indexBuffer)) {
			bgfx::destroy(indexBuffer);
		}
	}

}
