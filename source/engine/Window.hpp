#pragma once

#include <cstdint>
#include <string>
#include "../ecs/ecs.hpp"

struct GLFWwindow;

namespace nexc {

	class Window : public System<Window> {
	public:
		struct Config {
			uint32_t width;
			uint32_t height;
			bool fullscreen;
			std::string title;

			explicit Config(uint32_t width = 800, uint32_t height = 600, bool fullscreen = false, std::string title = "nexc")
					: width(width),
					  height(height),
					  fullscreen(fullscreen),
					  title(title) {}

		};

		explicit Window(const Config& config = Config());
		void run() override;
	private:
		GLFWwindow* internal;
	};

}
