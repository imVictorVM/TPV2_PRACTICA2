#include "NewRoundState.h"

#include "../sdlutils/Texture.h"

#include "../sdlutils/SDLUtils.h"

#include "../sdlutils/InputHandler.h"

#include "../game/Game.h"

#include "../game/ConfigAsteroids.h"



NewRoundState::NewRoundState() :
	_msg(sdlutils().msgs().at("NewRoundStatePacman"))
{
}

NewRoundState::~NewRoundState()
{
}

void NewRoundState::enter()
{
}

void NewRoundState::leave()
{
	sdlutils().virtualTimer().resetTime();
}

void NewRoundState::update()
{
	auto& inputHandler = ih();

	if (inputHandler.keyDownEvent() && inputHandler.isKeyDown(SDL_SCANCODE_RETURN)) {
		//Game::Instance()->getFigtherFacade()->reset_figther();
		//Game::Instance()->getAsteroidsFacade()->remove_all_asteroids();
		//ARCHIVO CONFIG PARA EL NUMERO DE ASTEROIDES GENERADOS EN UNA NUEVA RONDA
		//Game::Instance()->getAsteroidsFacade()->create_asteroids(Game::Instance()->getConfigAsteroids()->numAsteroids());
		Game::Instance()->setState(Game::RUNNING);
	}

	sdlutils().clearRenderer();

	_msg.render((sdlutils().width() - _msg.width()) / 2,
		(sdlutils().height() - _msg.height()) / 2);

	sdlutils().presentRenderer();

}
