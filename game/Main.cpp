#include <nexc/nexc.hpp>
using namespace nexc;

#include "common/GameField.hpp"
#include "player/PlayerSpawning.hpp"
#include "player/PlayerWalking.hpp"
#include "player/PlayerShooting.hpp"
#include "projectile/ProjectileProcessing.hpp"
#include "collision/CollisionDetection.hpp"



int main() {

	World world;
	Engine engine;
	world.addSystem(&engine);

	GameField gameField;
	PlayerSpawning playerSpawning;
	PlayerWalking playerWalking;
	PlayerShooting playerShooting;
	ProjectileProcessing projectileProcessing;
	CollisionDetection collisionDetection;

	world.addSystem(&gameField);
	world.addSystem(&playerSpawning);
	world.addSystem(&playerWalking);
	world.addSystem(&playerShooting);
	world.addSystem(&projectileProcessing);
	world.addSystem(&collisionDetection);


	world.emitEvent(GameStartEvent());

	while (true) {
		world.update();
	}

	return 0;
}