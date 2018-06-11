#pragma once

#include "../ecs/ecs.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include "Shader.hpp"
#include <vector>
#include "../common/Transform2D.hpp"
#include "../util/Memory.hpp"
#include "SpriteRenderer.hpp"
#include "HUDTextRenderer.hpp"
#include "HUDImageRenderer.hpp"

namespace nexc {

	class Sprite;

	class Texture;

	class Rendering : public System {
	public:
		explicit Rendering(sf::RenderWindow& window);

		void run() override;

	private:
		sf::RenderWindow& window;
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

			enum class Type {
				Sprite, HUDText, HUDImage
			};
			Type type;

			Transform2D transform;
			SpriteRenderer sprite;
			HUDTextRenderer hudText;
			HUDImageRenderer hudImage;
			Ref<Texture> texture;

		};

		std::vector<DrawTask> drawTasks;
	};

}
