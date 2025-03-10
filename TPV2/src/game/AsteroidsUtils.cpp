#include "AsteroidsUtils.h"

#include "../components/Transform.h"

#include "../components/ImageWithFrames.h"

#include "../components/ShowAtOppositeSide.h"

#include "../components/Generations.h"

#include "../components/Follow.h"

#include "../components/TowardDestination.h"

#include "../sdlutils/SDLUtils.h"

#include "../game/Game.h"

#include "../game/ConfigAsteroids.h"

void AsteroidsUtils::create_asteroids(int n)
{
	auto _manager = Game::Instance()->getManager();

	for (int i = 0; i < n; ++i) {
		//new entity
		ecs::entity_t ast = _manager->addEntity(ecs::grp::ASTEROIDS);

		//random generations (1, 2 or 3)
		_manager->addComponent<Generations>(ast, sdlutils().rand().nextInt(1, 4));
		
		//transform
		auto _astTr = _manager->addComponent<Transform>(ast);

		//size of the asteroid
		auto astSize = 10.0f + 5.0f * _manager->getComponent<Generations>(ast)->getGenerations();

		//random position
		auto astX = sdlutils().rand().nextInt(0, sdlutils().width() - astSize);
		auto astY = sdlutils().rand().nextInt(0, sdlutils().height() - astSize);

		auto position = Vector2D(astX, astY);

		//speed
		float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;

		/* 
		random position in center
		centPos=(cx,cy)+(rx,ry)
		(cx,cy) is window center
		(rx,ry) random number between -100, 100
		*/
		auto centPos = Vector2D(sdlutils().width() / 2, sdlutils().height() / 2) + Vector2D(sdlutils().rand().nextInt(-100, 100), sdlutils().rand().nextInt(-100, 100));
		
		Vector2D vel = (centPos - position).normalize() * speed;

		//asteroid transform init
		_astTr->init(position, vel, astSize, astSize, 0.0f);


		_manager->addComponent<ShowAtOppositeSide>(ast);

		//random movement 
		int rand = sdlutils().rand().nextInt(0, 2);
		if (rand == 0) {
			_manager->addComponent<Follow>(ast, _manager->getComponent<Transform>(_ship));
			_manager->addComponent<ImageWithFrames>(ast, &sdlutils().images().at("asteroid"),85,100);
		}
		else {
			_manager->addComponent<TowardDestination>(ast);
			_manager->addComponent<ImageWithFrames>(ast, &sdlutils().images().at("asteroid_gold"), 85, 100);
		}

	}
}

void AsteroidsUtils::remove_all_asteroids()
{
	auto _manager = Game::Instance()->getManager();

	auto& ents = _manager->getEntities(ecs::grp::ASTEROIDS);
	for (auto ent : ents) {
		_manager->setAlive(ent,false);
	}
	_manager->refresh();
}

void AsteroidsUtils::split_asteroid(ecs::entity_t a)
{
	auto _manager = Game::Instance()->getManager();

	//a is dead
	_manager->setAlive(a, false);

	auto newGeneration = _manager->getComponent<Generations>(a)->getGenerations() - 1;
	if (newGeneration != 0) {

		//ARCHIVO CONFIG PARA EL NUMERO DE ASTEROIDES QUE QUEREMOS QUE APAREZCAN AL ROMPER UN ASTEROIDE
		for (int i = 0; i < Game::Instance()->getConfigAsteroids()->numSplitAsteroids(); ++i) {

			//new entity
			ecs::entity_t ast = _manager->addEntity(ecs::grp::ASTEROIDS);

			//random generations (1, 2 or 3)
			_manager->addComponent<Generations>(ast, newGeneration);

			//transform
			auto _astTr = _manager->addComponent<Transform>(ast);

			//size of the asteroid
			auto astSize = 10.0f + 5.0f * _manager->getComponent<Generations>(ast)->getGenerations();

			//new position and velocity
			Vector2D p = _manager->getComponent<Transform>(a)->getPos();
			Vector2D v = _manager->getComponent<Transform>(a)->getVel();

			float tam = _manager->getComponent<Transform>(a)->getWidth();

			int r = sdlutils().rand().nextInt(0, 360);
			Vector2D pos = p + v.rotate(r) * 2 * std::max(tam, tam);
			Vector2D vel = v.rotate(r) * 1.1f;

			//asteroid transform init
			_astTr->init(pos, vel, astSize, astSize, 0.0f);


			_manager->addComponent<ShowAtOppositeSide>(ast);

			//random movement 
			int rand = sdlutils().rand().nextInt(0, 2);
			if (rand == 0) {
				_manager->addComponent<Follow>(ast, _manager->getComponent<Transform>(_ship));
				_manager->addComponent<ImageWithFrames>(ast, &sdlutils().images().at("asteroid"), 85, 100);
			}
			else {
				_manager->addComponent<TowardDestination>(ast);
				_manager->addComponent<ImageWithFrames>(ast, &sdlutils().images().at("asteroid"), 85, 100);
			}
		}
	}
}
