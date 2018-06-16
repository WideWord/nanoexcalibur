#pragma once

#include "../ecs/ecs.hpp"

#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "../3rdparty/nuklear.h"

#include "Input.hpp"
#include <bgfx/bgfx.h>

namespace nexc {

	class GUI : public System<GUI> {
	public:
		GUI();
		~GUI();

		void configure() override;
		void run() override;

		nk_context* getNuklear() {
			return &context;
		}
	private:
		nk_context context;
		nk_font_atlas fontAtlas;
		nk_font* font;
		nk_draw_null_texture nullTexture;

		Input guiInput;

		bgfx::DynamicVertexBufferHandle vertexBuffer;
		bgfx::DynamicIndexBufferHandle indexBuffer;
		bgfx::TextureHandle fontAtlasTexture;
		bgfx::ProgramHandle program;
		bgfx::UniformHandle transformUniform;
	};

}
