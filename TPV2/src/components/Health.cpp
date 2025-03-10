#include "Health.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

#include "../sdlutils/Texture.h"
#include "../game/Game.h"

Health::Health(int initialLives) : _myTransform(nullptr), 
_lives(initialLives), _initialLives(initialLives), _tam(50.f), _tex(&sdlutils().images().at("heart_figther"))
{
}

Health::~Health()
{
}

void Health::initComponent()
{
	auto mngr = Game::Instance()->getManager();
	_myTransform = mngr->getComponent<Transform>(_ent);
	assert(_myTransform != nullptr);
}

void Health::render()
{
	for (int i = 0; i < _lives;++i) {
		//pintar corazones
		SDL_Rect heart = build_sdlrect(i * _tam, 0, _tam, _tam);
		assert(_tex != nullptr);
		_tex->render(heart, 0.0f);
	}
}


void Health::addOneLive()
{
	_lives++;
}

void Health::loseOneLive()
{
	_lives--;
}

void Health::resetLives()
{
	_lives = _initialLives;
}

int Health::checkLives()
{
	return _lives;
}