#include "DeAcceleration.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

#include "../game/Game.h"

DeAcceleration::DeAcceleration() : _myTransform(nullptr)
{}

DeAcceleration::~DeAcceleration()
{
}

void DeAcceleration::initComponent()
{
	auto mngr = Game::Instance()->getManager();
	_myTransform = mngr->getComponent<Transform>(_ent);
	assert(_myTransform != nullptr);
}

void DeAcceleration::update()
{

	auto& vel = _myTransform->getVel();

	if ( vel.magnitude() <= 0.05)
		vel.set(0.0, 0.0);
	else {
		vel = vel * 0.995;
	}
}
