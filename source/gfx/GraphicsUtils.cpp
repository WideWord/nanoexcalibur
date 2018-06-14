#include "GraphicsUtils.hpp"
#include "../util/MakeString.hpp"
#include <fstream>
#include <vector>

namespace nexc {

	bgfx::ProgramHandle GraphicsUtils::loadProgram(const char* vsFilename, const char* fsFilename) {

		const char* gfxApi;
		switch (bgfx::getRendererType())
		{
			case bgfx::RendererType::Direct3D11: gfxApi = "dx11";  break;
			case bgfx::RendererType::Metal:      gfxApi = "metal"; break;
			case bgfx::RendererType::OpenGL:     gfxApi = "ogl"; break;
			default:
				gfxApi = "none";
		}

		std::ifstream vsStream(MakeString() << "data/nexc/shaders/" << gfxApi << "/" << vsFilename);
		std::vector<char> vsSource((std::istreambuf_iterator<char>(vsStream)), std::istreambuf_iterator<char>());

		auto vs = bgfx::createShader(bgfx::copy(vsSource.data(), (uint32_t)vsSource.size()));

		std::ifstream fsStream(MakeString() << "data/nexc/shaders/" << gfxApi << "/" << fsFilename);
		std::vector<char> fsSource((std::istreambuf_iterator<char>(fsStream)), std::istreambuf_iterator<char>());

		auto fs = bgfx::createShader(bgfx::copy(fsSource.data(), (uint32_t)fsSource.size()));

		return bgfx::createProgram(vs, fs, true);
	}

}
