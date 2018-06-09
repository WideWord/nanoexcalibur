#pragma once

#include "../ecs/ecs.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include "Shader.hpp"
#include <vector>
#include "../common/Transform2D.hpp"
#include "../util/Memory.hpp"

namespace nexc {

	class Sprite;

	class Rendering : public System {
	public:
		explicit Rendering(sf::Window& window);

		void run() override;

	private:
		sf::Window& window;
		Shader shader;
		uint32_t vao;
		uint32_t vertexVBO;
		uint32_t indexVBO;

		struct Vertex {
			Vec2 position;
			Vec2 texCoord;

			Vertex(Vec2 position, Vec2 texCoord)
					: position(position),
					  texCoord(texCoord) {}
		};

		struct DrawTask {
			uint32_t elementsNum;
			int16_t layer;
			Transform2D transform;
			Ref<Sprite> sprite;
		};

		std::vector<DrawTask> drawTasks;
	};

}
