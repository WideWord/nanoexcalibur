#pragma once
#include <nexc/nexc.hpp>
#include "../common/GameStartEvent.hpp"
#include "../common/SpawnPoints.hpp"
#include "Player.hpp"
#include "../collision/Collider.hpp"
using namespace nexc;

class PlayerSpawning : public System<PlayerSpawning> {
public:

	void configure() override {
		/// спавним игрока при старте игры
		subscribe<GameStartEvent>([this](const GameStartEvent&) {

			auto spawnPoint = getWorld()->getAnyEntityWith<Transform2D, PlayerSpawn>();
			auto assets = getWorld()->getSystem<Engine>()->getAssetsManager();

			SpriteRenderer spriteRenderer;
			spriteRenderer.sprite = assets.getSprite("data/player.spr");
			spriteRenderer.layer = 10;

			getWorld()->createEntity()
					.set(spawnPoint.get<Transform2D>())
					.set(spriteRenderer)
					.set(Player())
					.set(Collider(Vec2(10.0f / 32.0f, 15.0f / 32.0f), true));
		});
	}

};