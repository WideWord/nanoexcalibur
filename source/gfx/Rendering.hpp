#pragma once

#include "../ecs/ecs.hpp"
#include <bgfx/bgfx.h>

namespace nexc {

	class Rendering : public System<Rendering> {
	public:
		Rendering();
		void run() override;
	private:
		bgfx::ProgramHandle spriteProgram;
		bgfx::DynamicVertexBufferHandle vertexBuffer;
		bgfx::DynamicIndexBufferHandle indexBuffer;
	};

}
