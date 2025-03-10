#include "ShowAtOppositeSide.h"

#include "Transform.h"

#include "../ecs/Manager.h"

#include "../sdlutils/SDLUtils.h"

#include "../game/Game.h"

ShowAtOppositeSide::ShowAtOppositeSide() : offset(0.f), _entityTransform(nullptr)
{

}

void ShowAtOppositeSide::initComponent()
{
	//auto mngr = _ent->getMngr();
	auto mngr = Game::Instance()->getManager();
	_entityTransform = mngr->getComponent<Transform>(_ent);
	offset = _entityTransform->getWidth(); //La nave es cuadrada tiene el mismo width que height
	assert(_entityTransform != nullptr);
}

void ShowAtOppositeSide::update()
{

	//OFFSET HORIZONTAL
	if (_entityTransform->getPos().getX() + offset < 0) {
		_entityTransform->getPos().set(sdlutils().width(), _entityTransform->getPos().getY());
	}
	if (_entityTransform->getPos().getX() > sdlutils().width() + offset) {
		_entityTransform->getPos().set(0.f - offset, _entityTransform->getPos().getY());
	}

	//OFFSET VERTICAL
	if (_entityTransform->getPos().getY() + offset < 0) {
		_entityTransform->getPos().set(_entityTransform->getPos().getX(), sdlutils().height());
	}
	if (_entityTransform->getPos().getY() > sdlutils().height() + offset) {
		_entityTransform->getPos().set(_entityTransform->getPos().getX(), 0.f - offset);
	}
}
