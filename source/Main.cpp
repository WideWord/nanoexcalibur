#include "ecs/ecs.hpp"
#include <iostream>

using namespace nanoecs;

struct Position {
	float x, y;
	Position(float x, float y) : x(x), y(y) {}
};

struct Rotation {
	float a;
	Rotation(float a) : a(a) {}
};

int main() {

	World world;

	auto player = world.createEntity();
	player.set(Position(1, -2));
	player.set(Rotation(5));

	world.createEntity().set(Rotation(-2));


	for (auto pos : world.queryComponents<Position>()) {
		std::cout << pos.x << ' ' << pos.y << '\n';
	}

	for (auto rot : world.queryComponents<Rotation>()) {
		std::cout << rot.a << '\n';
	}

	return 0;
}