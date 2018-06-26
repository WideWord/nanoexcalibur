#include "Rendering.hpp"
#include "Sprite.hpp"
#include "../common/Transform2D.hpp"
#include <bx/math.h>
#include "Texture.hpp"
#include "Camera2D.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../engine/Engine.hpp"
#include <locale>
#include <codecvt>

namespace nexc {

	void Rendering::run() {

		struct RenderTask {
			Transform2D transform;
			SpriteRenderer sprite;
		};

		std::vector<RenderTask> tasks;

		for (auto e : getWorld()->getEntitiesWith<SpriteRenderer, Transform2D>()) {
			tasks.emplace_back();
			auto& task = tasks.back();
			task.transform = e.get<Transform2D>();
			task.sprite = e.get<SpriteRenderer>();
		}

		std::sort(tasks.begin(), tasks.end(), [](const RenderTask& a, const RenderTask& b) {
			return a.sprite.layer < b.sprite.layer;
		});


		auto cam = getWorld()->getAnyEntityWith<Transform2D, Camera2D>();

		if (!cam.isAlive()) return;

		sf::View view;
		{


			auto transform = cam.get<Transform2D>();
			auto camera = cam.get<Camera2D>();

			view.setCenter(transform.position.x, transform.position.y);
			view.setRotation(transform.rotation);

			auto screenSize = getWorld()->getSystem<Engine>()->getScreenSize();
			float verSize = (float)screenSize.y / camera.size;
			float horSize = verSize ;
			view.setSize(camera.size / (float)screenSize.y * (float)screenSize.x, camera.size);

		}

		auto& window = getSystem<Window>()->internal;

		window.clear(sf::Color::Black);

		sf::Sprite s;

		for (auto& task : tasks) {
			auto transform = task.transform;
			auto sprite = task.sprite.sprite;
			if (sprite == nullptr) continue;
			if (sprite->texture == nullptr) continue;

			if (task.sprite.guiSpace) {
				window.setView(sf::View());
			} else {
				window.setView(view);
			}

			s.setOrigin(sprite->origin.x, sprite->origin.y);
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

		for (auto e : getWorld()->getEntitiesWith<Transform2D, TextRenderer>()) {
			auto textRenderer = e.get<TextRenderer>();
			auto transform = e.get<Transform2D>();

			text.setPosition(transform.position.x, transform.position.y);
			text.setFont(textRenderer.font->internal);
			auto wtext = converter.from_bytes(textRenderer.text);
			text.setString(wtext);
			text.setCharacterSize(textRenderer.size);
			text.setFillColor(sf::Color::Red);

			window.draw(text);
		}

		window.display();

	}

}
