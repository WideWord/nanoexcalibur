#include "Rendering.hpp"
#include "GraphicsUtils.hpp"
#include "Sprite.hpp"
#include "SpriteRenderer.hpp"
#include "../common/Transform2D.hpp"
#include <bx/math.h>
#include "Texture.hpp"
#include "Camera2D.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace nexc {

	Rendering::Rendering() {

		bgfx::Init init;
		init.type = bgfx::RendererType::Metal;
		init.resolution.width = 800;
		init.resolution.height = 600;
		init.resolution.reset = BGFX_RESET_VSYNC;

		bgfx::init(init);

		//bgfx::setDebug(BGFX_DEBUG_STATS);

		spriteProgram = GraphicsUtils::loadProgram("sprite.vs", "sprite.fs");
		texColorUniform = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);
		transformUniform = bgfx::createUniform("u_transform", bgfx::UniformType::Mat3);
	}

	void Rendering::run() {
		bgfx::setViewRect(0, 0, 0, 800, 600);
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR, 0x0000ffff, 0.0f, 0);
		bgfx::setViewMode(0, bgfx::ViewMode::DepthAscending);
		bgfx::touch(0);

		auto renderState = BGFX_STATE_BLEND_ALPHA | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A;

		auto camera = getWorld()->getAnyEntityWith<Transform2D, Camera2D>();

		if (!camera.isAlive()) return;

		Mat3 viewMatrix;

		{
			auto transform = camera.get<Transform2D>();
			auto cam = camera.get<Camera2D>();

			float vHalfSize = cam.size * 0.5f;
			float hHalfSize = vHalfSize / 600.0f * 800.0f;


			viewMatrix = glm::scale(glm::rotate(glm::translate(Mat3(1), -transform.position), -transform.rotation), Vec2(1.0f / hHalfSize, 1.0f / vHalfSize));
		}

		for (auto e : getWorld()->getEntitiesWith<Transform2D, SpriteRenderer>()) {
			auto transform = e.get<Transform2D>();
			auto spriteRenderer = e.get<SpriteRenderer>();

			auto& sprite = spriteRenderer.sprite;

			if (!bgfx::isValid(sprite->vertexBuffer) || !bgfx::isValid(sprite->indexBuffer) || sprite->texture == nullptr) continue;

			Mat3 transformMatrix = viewMatrix * glm::translate(glm::rotate(Mat3(1), transform.rotation), transform.position);

			bgfx::setState(renderState);
			bgfx::setVertexBuffer(0, sprite->vertexBuffer);
			bgfx::setIndexBuffer(sprite->indexBuffer);
			bgfx::setTexture(0, texColorUniform, sprite->texture->internal);
			bgfx::setUniform(transformUniform, glm::value_ptr(transformMatrix), 1);
			bgfx::submit(0, spriteProgram, spriteRenderer.layer);
		}

		bgfx::frame();
	}

}
