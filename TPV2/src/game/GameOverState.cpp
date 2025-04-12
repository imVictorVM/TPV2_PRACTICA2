#include "GameOverState.h"

#include "../sdlutils/SDLUtils.h"

#include "../sdlutils/InputHandler.h"

#include "../game/Game.h"

GameOverState::GameOverState() :
	_msg(sdlutils().msgs().at("GameOverStatePacman"))
{
}

GameOverState::~GameOverState()
{
}

void GameOverState::enter()
{
}

void GameOverState::leave()
{
}

void GameOverState::update()
{
	auto& inputHandler = ih();

	if (inputHandler.keyDownEvent()) {
		Game::Instance()->setState(Game::NEWGAME);
	}

	sdlutils().clearRenderer();

	_msg.render((sdlutils().width() - _msg.width()) / 2,
		(sdlutils().height() - _msg.height()) / 2);

	sdlutils().presentRenderer();
}
