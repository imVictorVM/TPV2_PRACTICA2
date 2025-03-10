#include "GameOverState.h"

#include "../sdlutils/SDLUtils.h"

#include "../sdlutils/InputHandler.h"

#include "../game/Game.h"

GameOverState::GameOverState() :
	_msgWin(sdlutils().msgs().at("GameOverWinAsteroids")),
	_msgLose(sdlutils().msgs().at("GameOverLoseAsteroids")),
	win(false)
{
}

GameOverState::~GameOverState()
{
}

void GameOverState::enter()
{

	if (Game::Instance()->getManager()->getEntities(ecs::grp::ASTEROIDS).size() == 0) {
		win = true;
	}
	else win = false;

}

void GameOverState::leave()
{
}

void GameOverState::update()
{
	auto& inputHandler = ih();

	if (inputHandler.keyDownEvent() && inputHandler.isKeyDown(SDL_SCANCODE_RETURN)) {
		Game::Instance()->setState(Game::NEWGAME);
	}

	sdlutils().clearRenderer();

	if (win) {
		_msgWin.render((sdlutils().width() - _msgWin.width()) / 2,
			(sdlutils().height() - _msgWin.height()) / 2);
	}
	else {
		_msgLose.render((sdlutils().width() - _msgWin.width()) / 2,
			(sdlutils().height() - _msgLose.height()) / 2);
	}


	sdlutils().presentRenderer();
}
