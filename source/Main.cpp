#include "ecs/ecs.hpp"
#include <iostream>

using namespace nexc;

struct Position {
	float x, y;
	Position(float x, float y) : x(x), y(y) {}
	Position() : x(0), y(0) {}
};

struct Acceleration {
	float x, y;
	Acceleration() : x(0), y(0) {}
	Acceleration(float x, float y) : x(x), y(y) {}
};

struct QuitEvent {};

class AccelerationProcessing : public System {
public:
	void run() override {
		for (auto e : getWorld()->getEntitiesWith<Position, Acceleration>()) {
			auto pos = e.get<Position>();
			auto accel = e.get<Acceleration>();
			pos.x += accel.x;
			pos.y += accel.y;
			if (pos.y > 30) {
				getWorld()->emitEvent(QuitEvent());
			}
			e.set(pos);
		}
	}
};

class Debug : public System {
public:
	void run() override {
		for (auto e : getWorld()->getEntitiesWith<Position>()) {
			auto pos = e.get<Position>();
			std::cout << pos.x << ' ' << pos.y << '\n';
		}
	}
};

class QuitHandler : public System {
public:
	bool quit = false;

	void configure() override {
		subscribe<QuitEvent>([&](const QuitEvent&) {
			quit = true;
		});
	}
};

int main() {

	World world;

	AccelerationProcessing accelerationProcessing;
	Debug debug;
	QuitHandler quitHandler;

	world.addSystem(&accelerationProcessing);
	world.addSystem(&debug);
	world.addSystem(&quitHandler);

	auto a = world.createEntity();
	a.set(Position(1, 2));
	a.set(Acceleration(-1, 1));

	while (!quitHandler.quit) {
		world.update();
	}

	return 0;
}