#include "FigtherUtils.h"

#include "../components/Transform.h"

#include "../components/DeAcceleration.h"

#include "../components/FighterCtrl.h"

#include "../components/Image.h"

#include "../components/Health.h"

#include "../components/Gun.h"

#include "../components/ShowAtOppositeSide.h"

#include "../sdlutils/SDLUtils.h"

#include "../game/Game.h"

FigtherUtils::FigtherUtils() :
	_ship(nullptr)
{

}

void FigtherUtils::create_figther()
{
	assert(_ship == nullptr);

	auto _manager = Game::Instance()->getManager();

	_ship = _manager->addEntity();

	auto _shipTransform = _manager->addComponent<Transform>(_ship);
	auto shipSize = 40.0f;
	auto shipX = (sdlutils().width() - shipSize) / 2.0f;
	auto shipY = (sdlutils().height() - shipSize) / 2.0f;
	_shipTransform->init(Vector2D(shipX, shipY), Vector2D(), shipSize, shipSize, 0.0f);

	_manager->addComponent<DeAcceleration>(_ship);
	_manager->addComponent<FighterCtrl>(_ship);

	_manager->addComponent<Image>(_ship, &sdlutils().images().at("fighter"));

	_manager->addComponent<Health>(_ship, 3);

	_manager->addComponent<Gun>(_ship, &sdlutils().images().at("fire_figther"));

	_manager->addComponent<ShowAtOppositeSide>(_ship);
}

void FigtherUtils::reset_figther()
{
	assert(_ship != nullptr);

	auto _manager = Game::Instance()->getManager();

	Transform* figtherTransform = _manager->getComponent<Transform>(_ship);
	figtherTransform->getPos().set((sdlutils().width() - figtherTransform->getWidth()) / 2.0f, (sdlutils().width() - figtherTransform->getHeight()) / 2.0f);
	figtherTransform->getVel().set(0, 0);
	Gun* figtherGun = _manager->getComponent<Gun>(_ship);
	figtherGun->reset();
}

void FigtherUtils::reset_lives()
{
	assert(_ship != nullptr);

	auto _manager = Game::Instance()->getManager();

	Health* figtherHealth = _manager->getComponent<Health>(_ship);
	figtherHealth->resetLives();
}

int FigtherUtils::update_lives(int n)
{
	assert(_ship != nullptr);

	auto _manager = Game::Instance()->getManager();

	Health* figtherHealth = _manager->getComponent<Health>(_ship);
	if (n < 0) {
		int np = n * -1;
		for (int i = 0; i < np; ++i) {
			figtherHealth->loseOneLive();
		}
	}
	else if (n > 0) {
		for (int i = 0; i < n; ++i) {
			figtherHealth->addOneLive();
		}
	}

	return (figtherHealth->checkLives());
}
