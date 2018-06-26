#pragma once
#include <nexc/nexc.hpp>
#include "Player.hpp"

using namespace nexc;

class PlayerWalking : public System<PlayerWalking> {

	void run() override {
		auto engine = getWorld()->getSystem<Engine>();

		Vec2 direction;

		/// да, без кейкодов грустно
		if (engine->getKey(22)) {
			direction.y -= 1;
		}
		if (engine->getKey(18)) {
			direction.y += 1;
		}
		if (engine->getKey(0)) {
			direction.x -= 1;
		}
		if (engine->getKey(3)) {
			direction.x += 1;
		}

		float movementSpeed = 1.5f; /// тайла в секунду
		Vec2 movement = direction * movementSpeed * engine->getDeltaTime();

		/// применим движение для всех объектов с меткой игрока
		for (auto e : getWorld()->getEntitiesWith<Transform2D, Player>()) {
			auto transform = e.get<Transform2D>();
			transform.position += movement;
			e.set(transform);
		}
	}


};
