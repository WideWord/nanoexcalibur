#include "Rendering.hpp"
#include <bgfx/bgfx.h>

namespace nexc {

	Rendering::Rendering() {

		bgfx::Init init;
		init.type = bgfx::RendererType::Metal;
		init.resolution.width = 800;
		init.resolution.height = 600;
		init.resolution.reset = BGFX_RESET_VSYNC;

		bgfx::init(init);

		bgfx::setDebug(BGFX_DEBUG_STATS);


	}

	void Rendering::run() {
		bgfx::setViewClear(0, BGFX_CLEAR_COLOR, 0x303030ff, 0.1f, 0);
		bgfx::touch(0);
		bgfx::frame();
	}

}
