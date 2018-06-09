#include "Rendering.hpp"
#include "../common/Transform2D.hpp"
#include "Camera2D.hpp"
#include "Texture.hpp"
#include "Font.hpp"
#include "SpriteRenderer.hpp"
#include "HUDTextRenderer.hpp"
#include <locale>
#include <codecvt>
#include <string>

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

				s.setOrigin(sprite->pivot.x, sprite->pivot.y);
				s.setPosition(transform.position.x, transform.position.y);
				s.setRotation(transform.rotation);
				s.setTexture(sprite->texture->internal);
				sf::IntRect rect;
				rect.left = sprite->rect.origin.x;
				rect.top = sprite->rect.origin.y;
				rect.width = sprite->rect.size.x;
				rect.height = sprite->rect.size.y;
				s.setTextureRect(rect);
				float scale = 1.0f / sprite->pixelsInUnit;
				s.setScale(scale, scale);

				window.draw(s);
			}

			sf::Text text;

			window.setView(sf::View());

			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

			for (auto e : getWorld()->getEntitiesWith<HUDTextRenderer>()) {
				auto textRenderer = e.get<HUDTextRenderer>();

				text.setPosition(textRenderer.position.x, textRenderer.position.y);
				text.setFont(textRenderer.font->internal);
				auto wtext = converter.from_bytes(textRenderer.text);
				text.setString(wtext);
				text.setCharacterSize(textRenderer.size);
				text.setFillColor(sf::Color::Red);

				window.draw(text);
			}

		}

		window.display();
	}

}
