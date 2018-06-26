#pragma once
#include <nexc/nexc.hpp>
#include "Utils.hpp"
#include "../collision/Collider.hpp"
#include "SpawnPoints.hpp"

class GameField : public System<GameField> {
public:

	void configure() override {

		auto& assets = getWorld()->getSystem<Engine>()->getAssetsManager();

		// Пробегаемся по всем тайлам
		for (int x = 0; x < 8; ++x) {
			for (int y = 0; y < 8; ++y) {

				Transform2D transform;
				transform.position = Vec2(x, y);
				transform.rotation = 0;

				SpriteRenderer spriteRenderer;

				/// Выбираем нужный спрайт для текущего тайла
				if (x == 3 && y == 6) { /// База
					spriteRenderer.sprite = assets.getSprite("data/tile_top_left.spr");
				} else if (x == 3 && y == 7) {
					spriteRenderer.sprite = assets.getSprite("data/tile_bottom_left.spr");
				} else if (x == 4 && y == 6) {
					spriteRenderer.sprite = assets.getSprite("data/tile_top_right.spr");
				} else if (x == 4 && y == 7) {
					spriteRenderer.sprite = assets.getSprite("data/tile_bottom_right.spr");
				} else if ((x == 1 && y == 2) || (x == 6 && y == 2) || (x == 3 && y == 4) || (x == 4 && y == 4) || (x == 1 && y == 6) || (x == 6 && y == 6)) { /// Блоки
					spriteRenderer.sprite = assets.getSprite("data/tile_block.spr");
					spriteRenderer.layer = 1; /// Блоки могут закрывать другие тайлы
				} else if (x == 0) { /// Остальное поле
					if (y == 0) {
						spriteRenderer.sprite = assets.getSprite("data/tile_top_left.spr");
					} else if (y == 7) {
						spriteRenderer.sprite = assets.getSprite("data/tile_bottom_left.spr");
					} else {
						spriteRenderer.sprite = assets.getSprite("data/tile_left.spr");
					}
				} else if (x == 7) {
					if (y == 0) {
						spriteRenderer.sprite = assets.getSprite("data/tile_top_right.spr");
					} else if (y == 7) {
						spriteRenderer.sprite = assets.getSprite("data/tile_bottom_right.spr");
					} else {
						spriteRenderer.sprite = assets.getSprite("data/tile_right.spr");
					}
				} else if (y == 0) {
					spriteRenderer.sprite = assets.getSprite("data/tile_top.spr");
				} else if (y == 7) {
					spriteRenderer.sprite = assets.getSprite("data/tile_bottom.spr");
				} else {
					spriteRenderer.sprite = assets.getSprite("data/tile_middle.spr");
				}

				getWorld()->createEntity()
						.set(transform)
						.set(spriteRenderer);
			}
		}

		/// синий бэкграунд
		Transform2D backgroundTransform;
		backgroundTransform.position = Vec2(0, 0);
		backgroundTransform.rotation = 0;

		SpriteRenderer backgroundSpriteRenderer;
		backgroundSpriteRenderer.layer = -1;
		backgroundSpriteRenderer.sprite = assets.getSprite("data/background.spr");

		getWorld()->createEntity()
				.set(backgroundTransform)
				.set(backgroundSpriteRenderer);

		/// располагаем коллайдеры уровня
		{
			/// границы уровня

			getWorld()->createEntity()
					.set(makeTransform(Vec2(-1, 3.5f)))
					.set(Collider(Vec2(1, 10)));

			getWorld()->createEntity()
					.set(makeTransform(Vec2(8, 3.5f)))
					.set(Collider(Vec2(1, 10)));

			getWorld()->createEntity()
					.set(makeTransform(Vec2(3.5f, -1)))
					.set(Collider(Vec2(10, 1)));

			getWorld()->createEntity()
					.set(makeTransform(Vec2(3.5f, 8)))
					.set(Collider(Vec2(10, 1)));


			/// блоки

			getWorld()->createEntity()
					.set(makeTransform(Vec2(1, 2.0f - 0.25f)))
					.set(Collider(Vec2(1, 1.5f)));

			getWorld()->createEntity()
					.set(makeTransform(Vec2(6, 2.0f - 0.25f)))
					.set(Collider(Vec2(1, 1.5f)));

			getWorld()->createEntity()
					.set(makeTransform(Vec2(3.5f, 4.0f - 0.25f)))
					.set(Collider(Vec2(2, 1.5f)));

			getWorld()->createEntity()
					.set(makeTransform(Vec2(1, 6.0f - 0.25f)))
					.set(Collider(Vec2(1, 1)));

			getWorld()->createEntity()
					.set(makeTransform(Vec2(6, 6.0f - 0.25f)))
					.set(Collider(Vec2(1, 1)));
		}

		/// спавны
		{
			getWorld()->createEntity()
					.set(makeTransform(Vec2(1, 0)))
					.set(RedSpawn());

			getWorld()->createEntity()
					.set(makeTransform(Vec2(6, 0)))
					.set(RedSpawn());

			getWorld()->createEntity()
					.set(makeTransform(Vec2(3.5f, 0)))
					.set(GreenSpawn());

			getWorld()->createEntity()
					.set(makeTransform(Vec2(3.5f, 6.5f)))
					.set(PlayerSpawn());
		}


		/// камера
		Transform2D cameraTransform;
		cameraTransform.rotation = 0;
		cameraTransform.position = Vec2(3.5f, 3.5f); /// камера смотрит на центр поля

		Camera2D camera;
		camera.size = 9; /// камера видит в высоту 9 тайлов

		getWorld()->createEntity()
				.set(camera)
				.set(cameraTransform);

	}

};
