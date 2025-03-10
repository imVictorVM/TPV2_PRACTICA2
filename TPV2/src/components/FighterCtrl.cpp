#include "FighterCtrl.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "Transform.h"
#include "../game/Game.h"
#include <cmath>

#include <iostream>

#include "../game/ConfigAsteroids.h"

FighterCtrl::FighterCtrl() : _myTransform(nullptr),
_up(SDL_SCANCODE_UP),
_left(SDL_SCANCODE_LEFT),
_right(SDL_SCANCODE_RIGHT),
_speedRotation(3.5f),
_thrust(0.2f),
_speedLimit(3.0f)
{

}

FighterCtrl::~FighterCtrl()
{
}

void FighterCtrl::initComponent()
{
	auto mngr = Game::Instance()->getManager();
	_myTransform = mngr->getComponent<Transform>(_ent);
	assert(_myTransform != nullptr);

	//ARCHIVO CONFIG PARA LA VELOCIDAD MAXIMA DEL CAZA Y LA VELOCIDAD DE ROTACION
	float configSpeed = Game::Instance()->getConfigAsteroids()->speedFigther();
	float configSpeedRotation = Game::Instance()->getConfigAsteroids()->speedRotationFigther();

	_speedLimit = configSpeed;
	_speedRotation = configSpeedRotation;
}

void FighterCtrl::update()
{
	auto& ihdlr = ih();

	auto& vel = _myTransform->getVel();
	 

		if (ihdlr.isKeyDown(_up)) {

			Vector2D newVel = vel + Vector2D(0, -1).rotate(_myTransform->getRot()) * _thrust;
			float velMag = newVel.magnitude();
			if (velMag > _speedLimit) {
				newVel = newVel.normalize() * _speedLimit;
			}
				
			vel.set(newVel);

			//sonido
			sdlutils().soundEffects().at("ship_acceleration").play();
			sdlutils().soundEffects().at("ship_acceleration").setChannelVolume(1);

		}
		if (ihdlr.isKeyDown(_left)) {
			_myTransform->setRot(_myTransform->getRot() - _speedRotation);
		}
		if (ihdlr.isKeyDown(_right)) {
			_myTransform->setRot(_myTransform->getRot() + _speedRotation);
		}
	
}
