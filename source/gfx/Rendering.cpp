#include "Rendering.hpp"
#include "../common/Transform2D.hpp"
#include "Camera2D.hpp"
#include "Texture.hpp"
#include "Font.hpp"
#include "SpriteRenderer.hpp"
#include "HUDTextRenderer.hpp"

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
				view.setSize(camera.size, camera.size / (float)screenSize.x * (float)screenSize.y);
			} else {
				float verSize = (float)screenSize.y / camera.size;
				float horSize = verSize ;
				view.setSize(camera.size / (float)screenSize.y * (float)screenSize.x, camera.size);
			}

			window.setView(view);

			sf::Sprite s;

			for (auto e : getWorld()->getEntitiesWith<Transform2D, SpriteRenderer>()) {
				auto transform = e.get<Transform2D>();
				auto sprite = e.get<SpriteRenderer>().sprite;
				if (sprite == nullptr) continue;
				if (sprite->texture == nullptr) continue;

				s.setOrigin(sprite->origin.x * sprite->pixelsInUnit, sprite->origin.y * sprite->pixelsInUnit);
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

			sf::Text text;

			window.setView(sf::View());

			for (auto e : getWorld()->getEntitiesWith<HUDTextRenderer>()) {
				auto textRenderer = e.get<HUDTextRenderer>();

				text.setPosition(textRenderer.position.x, textRenderer.position.y);
				text.setFont(textRenderer.font->internal);
				text.setString(textRenderer.text);
				text.setCharacterSize(textRenderer.size);
				text.setFillColor(sf::Color::Red);

				window.draw(text);
			}

		}

		window.display();
	}

}
