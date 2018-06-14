#include <bx/platform.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#	define GLFW_EXPOSE_NATIVE_X11
#	define GLFW_EXPOSE_NATIVE_GLX
#elif BX_PLATFORM_OSX
#	define GLFW_EXPOSE_NATIVE_COCOA
#	define GLFW_EXPOSE_NATIVE_NSGL
#elif BX_PLATFORM_WINDOWS
#	define GLFW_EXPOSE_NATIVE_WIN32
#	define GLFW_EXPOSE_NATIVE_WGL
#endif //
#include <GLFW/glfw3native.h>

#include <bgfx/platform.h>

#include "Window.hpp"

namespace nexc {

	Window::Window(const Config& config) {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		internal = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);

		bgfx::PlatformData pd;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
		pd.ndt      = glfwGetX11Display();
		pd.nwh      = (void*)(uintptr_t)glfwGetX11Window(internal);
#	elif BX_PLATFORM_OSX
		pd.ndt      = NULL;
		pd.nwh      = glfwGetCocoaWindow(internal);
#	elif BX_PLATFORM_WINDOWS
		pd.ndt      = NULL;
		pd.nwh      = glfwGetWin32Window(internal);
#	endif // BX_PLATFORM_WINDOWS
		pd.context      = NULL;
		pd.backBuffer   = NULL;
		pd.backBufferDS = NULL;
		bgfx::setPlatformData(pd);
	}

	void Window::run() {
		glfwPollEvents();
	}

}