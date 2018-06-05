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
	world.createEntity().set(Position(4, 20));


	for (auto e : world.query<Position, Rotation>()) {
		std::cout << e.get<Position>().x << '\n';
	}


	return 0;
}