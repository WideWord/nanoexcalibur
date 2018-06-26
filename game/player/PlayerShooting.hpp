#pragma once
#include <nexc/nexc.hpp>
#include "Player.hpp"
#include "../projectile/Projectile.hpp"

using namespace nexc;

class PlayerShooting : public System<PlayerShooting> {

	void run() override {
		auto engine = getWorld()->getSystem<Engine>();

		timer -= engine->getDeltaTime();
		if (timer < 0) timer = 0;

		if (timer == 0 && engine->getMouseButton(0)) {
			auto player = getWorld()->getAnyEntityWith<Player, Transform2D>();
			if (!player.isAlive()) return;

			auto transform = player.get<Transform2D>();

			auto camera = getWorld()->getAnyEntityWith<Camera2D, Transform2D>();
			auto mouse = engine->getMousePosition();
			auto screenSize = engine->getScreenSize();


			auto camSize = camera.get<Camera2D>().size;

			mouse -= Vec2(screenSize) * 0.5f;
			mouse = mouse / (float)screenSize.y * camSize;
			mouse += camera.get<Transform2D>().position;

			auto direction = mouse - transform.position;

			/// добавляем снаряд
			getWorld()->createEntity()
					.set(transform) /// положение как у игрока
					.set(Projectile(direction))
					.set(SpriteRenderer(engine->getAssetsManager().getSprite("data/projectile.spr"), 20));

			timer = 1.0f / 5.0f;
		}
	}

private:
	float timer = 0;

};