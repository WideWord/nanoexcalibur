#include "Rendering.hpp"
#include "../common/Transform2D.hpp"
#include "Camera2D.hpp"
#include "Texture.hpp"

namespace nexc {

	void Rendering::run() {
		window.clear(sf::Color::Black);

		auto cameras = getWorld()->getEntitiesWith<Camera2D, Transform2D>();
		auto cameraIt = cameras.begin();

		if (cameraIt != cameras.end()) {

			auto cameraObj = *cameraIt;

			Camera2D camera = cameraObj.get<Camera2D>();
			Transform2D cameraTransform = cameraObj.get<Transform2D>();

			sf::View view;
			view.setCenter(cameraTransform.position.x, cameraTransform.position.y);
			view.setRotation(cameraTransform.rotation);
			auto screenSize = window.getSize();
			if (camera.keepHorizontalSize) {
				float horSize = camera.pixelsInUnit / (float)screenSize.x;
				float verSize = horSize / (float)screenSize.x * (float)screenSize.y;
				view.setSize(horSize, verSize);
			} else {
				float verSize = camera.pixelsInUnit / (float)screenSize.y;
				float horSize = verSize / (float)screenSize.y * (float)screenSize.x;
				view.setSize(horSize, verSize);
			}

			window.setView(view);

			sf::Sprite s;

			for (auto e : getWorld()->getEntitiesWith<Transform2D, SpriteRenderer>()) {
				auto transform = e.get<Transform2D>();
				auto sprite = e.get<SpriteRenderer>().sprite;
				if (sprite == nullptr) continue;
				if (sprite->texture == nullptr) continue;

				s.setPosition(transform.position.x, transform.position.y);
				s.setRotation(transform.rotation);
				s.setTexture(sprite->texture->internal);
				sf::IntRect rect;
				rect.left = (int)sprite->textureOrigin.x;
				rect.top = (int)sprite->textureOrigin.y;
				rect.width = (int)sprite->textureSize.x;
				rect.height = (int)sprite->textureSize.y;
				s.setTextureRect(rect);
				float scale = 1.0f / sprite->pixelsInUnit;
				s.setScale(scale, scale);

				window.draw(s);
			}

		}

		window.display();
	}

}
