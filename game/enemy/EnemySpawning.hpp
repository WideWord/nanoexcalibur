#pragma once

#include <nexc/nexc.hpp>
#include "../common/GameStartEvent.hpp"
#include "../common/SpawnPoints.hpp"
#include "Enemy.hpp"

using namespace nexc;

class EnemySpawning : public System<EnemySpawning> {
public:

	void configure() override {
		subscribe<GameStartEvent>([this](const GameStartEvent&) {
			gameTime = 0;
			redTimer = 5f;
			greenTimer = 7.5f;
			running = true;
		});
	}

	void run() override {
		if (!running) {
			return;
		}

		auto engine = getWorld()->getSystem<Engine>();
		auto& assets = engine->getAssetsManager();

		gameTime += engine->getDeltaTime();

		int level = 0;
		if (gameTime >= 180) level = 3;
		else if (gameTime >= 120) level = 2;
		else if (gameTime >= 60) level = 1;

		redTimer -= engine->getDeltaTime();
		greenTimer -= engine->getDeltaTime();

		if (redTimer == 0) {
			redTimer = redReloadingTime[level];

			for (auto spawn : getWorld()->getEntitiesWith<RedSpawn>()) {
				SpriteRenderer sr;
				sr.sprite = assets.getSprite("data/enemy_red.spr");
				sr.layer = 10;

				Enemy enemy;
				enemy.hits = 3;
				enemy.speed = 1;
				enemy.isRed = true;

				getWorld()->createEntity()
						.set(spawn.get<Transform2D>())
						.set(sr)
						.set(enemy);
			}
		}

		if (greenTimer == 0) {
			greenTimer = greenReloadingTime[level];

			for (auto spawn : getWorld()->getEntitiesWith<GreenSpawn>()) {
				SpriteRenderer sr;
				sr.sprite = assets.getSprite("data/enemy_green.spr");
				sr.layer = 10;

				Enemy enemy;
				enemy.hits = 2;
				enemy.speed = 1.5;
				enemy.isRed = false;

				getWorld()->createEntity()
						.set(spawn.get<Transform2D>())
						.set(sr)
						.set(enemy);
			}
		}
	}

private:
	bool running = false;
	float redTimer = 0;
	float greenTimer = 0;
	float gameTime = 0;
	float redReloadingTime[] = {5, 4, 3, 2};
	float greenReloadingTime[] = {7.5f, 6, 4.5f, 3};

};