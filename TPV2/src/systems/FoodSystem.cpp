#include "FoodSystem.h"


#include <algorithm>
#include "../components/Image.h"
#include "../components/Points.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrlSystem.h"

FoodSystem::FoodSystem() : _currNumOfFood(0) {
}

FoodSystem::~FoodSystem() {
}

void FoodSystem::initSystem() {
}

void FoodSystem::update() {
}

void FoodSystem::addFood(unsigned int n) {

	for (auto i = 0u; i < 8; ++i) {

		for (auto j = 0u; j < 6; ++j) {
			// add and entity to the manager
			auto e = _mngr->addEntity(ecs::grp::STARS);

			// add a Transform component
			auto tr = _mngr->addComponent<Transform>(e);
			auto s = 70;
			auto x = (sdlutils().width()/8 * (i+1)) - s;
			auto y = (sdlutils().height()/6 * (j+1))- s;
			tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

			// add an Image Component
			_mngr->addComponent<Image>(e, &sdlutils().images().at("star"));

			auto pts = _mngr->addComponent<Points>(e);
			pts->_points = 5;
			_currNumOfFood++;
		}

		
	}
}

void FoodSystem::onFoodEaten(ecs::entity_t e) {
	_mngr->setAlive(e, false);
	_currNumOfFood--;

	// play sound on channel 1 (if there is something playing there
	// it will be cancelled
	sdlutils().soundEffects().at("pacman_eat").play(0, 1);
}

void FoodSystem::recieve(const Message& m) {
	switch (m.id) {
	case _m_STAR_EATEN:
		onFoodEaten(m.star_eaten_data.e);
		break;
	case _m_CREATE_STARS:
		addFood(m.create_stars_data.n);
		break;
	default:
		break;
	}
}
