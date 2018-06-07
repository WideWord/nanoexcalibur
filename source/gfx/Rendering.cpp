#include "Rendering.hpp"
#include "../common/Transform2D.hpp"

namespace nexc {

	void Rendering::run() {
		window.clear(sf::Color::Black);

		for (auto e : getWorld()->getEntitiesWith<Transform2D, SpriteRenderer>()) {
			auto transform = e.get<Transform2D>();
			auto sprite = e.get<SpriteRenderer>().sprite;
			if (sprite == nullptr) continue;

			sprite->setPosition(transform.position.x, transform.position.y);
			sprite->setRotation(transform.rotation);
			window.draw(*sprite);
		}

		window.display();
	}

}
