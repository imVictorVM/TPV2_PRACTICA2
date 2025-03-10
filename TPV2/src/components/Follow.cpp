#include "Follow.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../game/Game.h"


Follow::Follow(Transform* tr)
{
	_myTransform = nullptr;
	_objective = tr;
}

Follow::~Follow()
{
}

void Follow::initComponent()
{
	auto mngr = Game::Instance()->getManager();
	_myTransform = mngr->getComponent<Transform>(_ent);
	assert(_myTransform != nullptr);


}

void Follow::update()
{
	Vector2D& astVel = _myTransform->getVel();
	Vector2D astPos = _myTransform->getPos();
	Vector2D objPos = _objective->getPos();

	astVel.set(astVel.rotate(astVel.angle(objPos - astPos) >0 ? 1.0f : -1.0f));

}
