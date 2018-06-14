#include "Rendering.hpp"
#include "GraphicsUtils.hpp"
#include "Sprite.hpp"
#include "SpriteRenderer.hpp"
#include "../common/Transform2D.hpp"
#include <bx/math.h>

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
	}

	void Rendering::run() {
		bgfx::setViewRect(0, 0, 0, 800, 600);
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR, 0x0000ffff, 0.0f, 0);
		bgfx::setViewMode(0, bgfx::ViewMode::DepthAscending);
		bgfx::touch(0);

		/*float proj[16];
		float view[16];
		bx::mtxIdentity(view);
		bx::mtxOrtho(proj, 1, -1, -1, 1, 0, 1, 0, true);
		bgfx::setViewTransform(0, view, proj);*/

		auto renderState = BGFX_STATE_BLEND_ALPHA | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A;

		for (auto e : getWorld()->getEntitiesWith<Transform2D, SpriteRenderer>()) {
			auto transform = e.get<Transform2D>();
			auto spriteRenderer = e.get<SpriteRenderer>();

			auto& sprite = spriteRenderer.sprite;

			if (!bgfx::isValid(sprite->vertexBuffer) || !bgfx::isValid(sprite->indexBuffer)) continue;

			bgfx::setState(renderState);
			bgfx::setVertexBuffer(0, sprite->vertexBuffer);
			bgfx::setIndexBuffer(sprite->indexBuffer);
			bgfx::submit(0, spriteProgram, spriteRenderer.layer);

		}

		bgfx::frame();
	}

}
