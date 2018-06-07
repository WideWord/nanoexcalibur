#include "ecs/ecs.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "common/Transform2D.hpp"
#include "gfx/Rendering.hpp"
#include "Engine.hpp"

using namespace nexc;


int main() {

	World world;

	Engine engine;

	world.addSystem(&engine);

	sf::Texture texture;
	texture.loadFromFile("data/test.jpg");

	auto sprite = std::make_shared<sf::Sprite>();
	sprite->setTexture(texture, true);

	auto obj = world.createEntity();
	SpriteRenderer sr;
	sr.sprite = sprite;
	obj.set(sr);
	obj.set(Transform2D());

	while (true) {
		world.update();
	}

	return 0;
}