#include "TowardDestination.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../game/Game.h"

TowardDestination::TowardDestination()
{
	_myTransform = nullptr;

	_objX = 0;
	_objY = 1;
}

TowardDestination::~TowardDestination()
{
}

void TowardDestination::initComponent()
{
	auto mngr = Game::Instance()->getManager();
	_myTransform = mngr->getComponent<Transform>(_ent);
	assert(_myTransform != nullptr);

}

void TowardDestination::update()
{
	Vector2D& astVel = _myTransform->getVel(); //v
	Vector2D astPos = _myTransform->getPos(); //p
	Vector2D _objective = Vector2D(_objX,_objY); // q

	astVel.rotate(astVel.angle(_objective - astPos));
}
