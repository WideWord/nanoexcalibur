#pragma once

#include "../ecs/ecs.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include "Shader.hpp"

namespace nexc {

	class Rendering : public System {
	public:
		explicit Rendering(sf::Window& window);

		void run() override;

	private:
		sf::Window& window;
		Shader shader;
		uint32_t vao;
		uint32_t vbo;
	};

}
