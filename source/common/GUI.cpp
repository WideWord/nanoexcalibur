#define NK_IMPLEMENTATION

#include "GUI.hpp"
#include "../engine/Engine.hpp"
#include "../gfx/GraphicsUtils.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace nexc {

	GUI::GUI() {
		struct nk_font_config cfg = nk_font_config(0);
		cfg.oversample_h = 3; cfg.oversample_v = 2;

		nk_font_atlas_init_default(&fontAtlas);
		nk_font_atlas_begin(&fontAtlas);
		font = nk_font_atlas_add_from_file(&fontAtlas, "data/bignoodletoo.ttf", 22.0f, &cfg);

		int w, h;
		const void* image = nk_font_atlas_bake(&fontAtlas, &w, &h, NK_FONT_ATLAS_RGBA32);
		fontAtlasTexture = bgfx::createTexture2D(w, h, false, 1, bgfx::TextureFormat::RGBA8, 0, bgfx::makeRef(image, w * h * 4));
		nk_font_atlas_end(&fontAtlas, nk_handle_id(fontAtlasTexture.idx), &nullTexture);

		nk_init_default(&context, &font->handle);

		bgfx::VertexDecl vd;
		vd.begin()
				.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
				.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
				.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8)
				.end();

		vertexBuffer = bgfx::createDynamicVertexBuffer((uint32_t)0, vd, BGFX_BUFFER_ALLOW_RESIZE);
		indexBuffer = bgfx::createDynamicIndexBuffer((uint32_t)0, BGFX_BUFFER_ALLOW_RESIZE);

		program = GraphicsUtils::loadProgram("gui.vs", "gui.fs");
		transformUniform = bgfx::createUniform("u_transform", bgfx::UniformType::Mat3);
	}

	GUI::~GUI() {
		bgfx::destroy(fontAtlasTexture);
		bgfx::destroy(vertexBuffer);
		bgfx::destroy(indexBuffer);
		bgfx::destroy(program);
	}

	void GUI::configure() {
		addChildSystem(&guiInput, Engine::beginFrameQueue - 100);
	}

	void GUI::run() {

		nk_begin(&context, "Grid Demo", nk_rect(0, 0, 275, 250),
					 NK_WINDOW_TITLE|NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|
					 NK_WINDOW_NO_SCROLLBAR);

		nk_end(&context);

		nk_convert_config cfg = {};
		static const nk_draw_vertex_layout_element vertex_layout[] = {
				{NK_VERTEX_POSITION, NK_FORMAT_FLOAT, 0},
				{NK_VERTEX_TEXCOORD, NK_FORMAT_FLOAT, sizeof(float) * 2},
				{NK_VERTEX_COLOR, NK_FORMAT_R8G8B8A8, sizeof(float) * 4},
				{NK_VERTEX_LAYOUT_END}
		};
		cfg.shape_AA = NK_ANTI_ALIASING_ON;
		cfg.line_AA = NK_ANTI_ALIASING_ON;
		cfg.vertex_layout = vertex_layout;
		cfg.vertex_size = sizeof(float) * 4 + 4;
		cfg.vertex_alignment = sizeof(float) * 4 + 4;
		cfg.circle_segment_count = 22;
		cfg.curve_segment_count = 22;
		cfg.arc_segment_count = 22;
		cfg.global_alpha = 1.0f;
		cfg.null = nullTexture;

		nk_buffer cmds, verts, idx;
		nk_buffer_init_default(&cmds);
		nk_buffer_init_default(&verts);
		nk_buffer_init_default(&idx);
		nk_convert(&context, &cmds, &verts, &idx, &cfg);

		bgfx::update(vertexBuffer, 0, bgfx::copy(verts.memory.ptr, verts.memory.size));

		bgfx::update(indexBuffer, 0, bgfx::copy(idx.memory.ptr, idx.memory.size));

		auto screenSize = getWorld()->getSystem<Engine>()->getScreenSize();
		Mat3 transform = glm::translate(glm::scale(Mat3(1), Vec2(2.0f / (float)screenSize.x, 2.0f / (float)screenSize.y)), Vec2(-0.5f, -0.5f));

		const nk_draw_command* cmd;
		unsigned offset = 0;
		nk_draw_foreach(cmd, &context, &cmds) {
			bgfx::setState(BGFX_STATE_BLEND_ALPHA | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A);
			bgfx::setVertexBuffer(0, vertexBuffer);
			bgfx::setIndexBuffer(indexBuffer, offset, cmd->elem_count);
			bgfx::setScissor(cmd->clip_rect.x, cmd->clip_rect.y, cmd->clip_rect.w, cmd->clip_rect.h);
			bgfx::setUniform(transformUniform, glm::value_ptr(transform));
			bgfx::submit(0, program, 10000);
			offset += cmd->elem_count;
		}
		nk_buffer_free(&cmds);
		nk_buffer_free(&verts);
		nk_buffer_free(&idx);

		nk_clear(&context);

	}

}

