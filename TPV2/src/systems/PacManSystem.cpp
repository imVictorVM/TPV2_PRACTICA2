// This file is part of the course TPV2@UCM - Samir Genaim

#include "PacManSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../components/ImageWithFrames.h"


PacManSystem::PacManSystem() :
		_pmTR(nullptr), _pmIWF(nullptr), _tex(nullptr), _timer(0) {
}

PacManSystem::~PacManSystem() {
}

void PacManSystem::initSystem() {
	// create the PacMan entity
	//
	auto pacman = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::PACMAN, pacman);


	_pmTR = _mngr->addComponent<Transform>(pacman);
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	_pmTR->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

	_pmIWF = _mngr->addComponent<ImageWithFrames>(pacman, &sdlutils().images().at("pacman"),s,s,0,0,4);

}

void PacManSystem::update() {

	auto &ihdlr = ih();

	if (ihdlr.keyDownEvent()) {
		if (ihdlr.isKeyDown(SDL_SCANCODE_UP)) {
			_pmTR->_vel.set(Vector2D(0.0f, -3.0f).rotate(_pmTR->_rot));
		}
		else if (ihdlr.isKeyDown(SDL_SCANCODE_DOWN)) {
			_pmTR->_vel.set(Vector2D(0.0f, 0.0f));
		}
		else if (ihdlr.isKeyDown(SDL_SCANCODE_LEFT)) {
			_pmTR->_rot -= 90.f;
			_pmTR->_vel.set(Vector2D(_pmTR->_vel.getX(), _pmTR->_vel.getY()).rotate(-90.f));
		}
		else if (ihdlr.isKeyDown(SDL_SCANCODE_RIGHT)) {
			_pmTR->_rot += 90.f;
			_pmTR->_vel.set(Vector2D(_pmTR->_vel.getX(),_pmTR->_vel.getY()).rotate(90.f));
		}
	}

	_pmTR->_pos = _pmTR->_pos + _pmTR->_vel;

	// check left/right borders
	if (_pmTR->_pos.getX() < 0) {
		_pmTR->_pos.setX(0.0f);
		_pmTR->_vel.set(0.0f, 0.0f);
	} else if (_pmTR->_pos.getX() + _pmTR->_width > sdlutils().width()) {
		_pmTR->_pos.setX(sdlutils().width() - _pmTR->_width);
		_pmTR->_vel.set(0.0f, 0.0f);
	}
	
	// check upper/lower borders
	if (_pmTR->_pos.getY() < 0) {
		_pmTR->_pos.setY(0.0f);
		_pmTR->_vel.set(0.0f, 0.0f);
	} else if (_pmTR->_pos.getY() + _pmTR->_height > sdlutils().height()) {
		_pmTR->_pos.setY(sdlutils().height() - _pmTR->_height);
		_pmTR->_vel.set(0.0f, 0.0f);
	}

	if (_timer + 50 <= sdlutils().virtualTimer().currTime()) {
		_timer = sdlutils().virtualTimer().currTime();
		_pmIWF->updateImage();
	}

	//auto &ihldr = ih();
	//
	//if (ihldr.keyDownEvent()) {
	//
	//	if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
	//		_pmTR->_rot = _pmTR->_rot + 5.0f;
	//
	//		// also rotate the PacMan so it looks in the same
	//		// direction where it moves
	//		//
	//		_pmTR->_vel = _pmTR->_vel.rotate(5.0f);
	//	} else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
	//		_pmTR->_rot = _pmTR->_rot - 5.0f;
	//
	//		// also rotate the PacMan so it looks in the same
	//		// direction where it moves
	//		//
	//		_pmTR->_vel = _pmTR->_vel.rotate(-5.0f);
	//	} else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed
	//
	//		// add 1.0f to the speed (respecting the limit 3.0f). Recall
	//		// that speed is the length of the velocity vector
	//		float speed = std::min(3.0f, _pmTR->_vel.magnitude() + 1.0f);
	//
	//		// change the length of velocity vecto to 'speed'. We need
	//		// '.rotate(rot)' for the case in which the current speed is
	//		// 0, so we rotate it to the same direction where the PacMan
	//		// is looking
	//		//
	//		_pmTR->_vel = Vector2D(0, -speed).rotate(_pmTR->_rot);
	//	} else if (ihldr.isKeyDown(SDL_SCANCODE_DOWN)) { // decrease speed
	//		// subtract 1.0f to the speed (respecting the limit 0.0f). Recall
	//		// that speed is the length of the velocity vector
	//		float speed = std::max(0.0f, _pmTR->_vel.magnitude() - 1.0f);
	//
	//		// change the length of velocity vector to 'speed'. We need
	//		// '.rotate(rot)' for the case in which the current speed is
	//		// 0, so we rotate it to the same direction where the PacMan
	//		// is looking
	//		//
	//		_pmTR->_vel = Vector2D(0, -speed).rotate(_pmTR->_rot);
	//	}
	//
	//}
	//
	//// move the pacman
	//_pmTR->_pos = _pmTR->_pos + _pmTR->_vel;
	//
	//// check left/right borders
	//if (_pmTR->_pos.getX() < 0) {
	//	_pmTR->_pos.setX(0.0f);
	//	_pmTR->_vel.set(0.0f, 0.0f);
	//} else if (_pmTR->_pos.getX() + _pmTR->_width > sdlutils().width()) {
	//	_pmTR->_pos.setX(sdlutils().width() - _pmTR->_width);
	//	_pmTR->_vel.set(0.0f, 0.0f);
	//}
	//
	//// check upper/lower borders
	//if (_pmTR->_pos.getY() < 0) {
	//	_pmTR->_pos.setY(0.0f);
	//	_pmTR->_vel.set(0.0f, 0.0f);
	//} else if (_pmTR->_pos.getY() + _pmTR->_height > sdlutils().height()) {
	//	_pmTR->_pos.setY(sdlutils().height() - _pmTR->_height);
	//	_pmTR->_vel.set(0.0f, 0.0f);
	//}

}
