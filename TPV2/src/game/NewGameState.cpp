#include "NewGameState.h"

#include "../game/Game.h"

#include "../sdlutils/Texture.h"

#include "../sdlutils/SDLUtils.h"

#include "../sdlutils/InputHandler.h"
#include "../game/ConfigAsteroids.h"

NewGameState::NewGameState() :
	_msg(sdlutils().msgs().at("NewGameStatePacman")) 
{
}

NewGameState::~NewGameState(){
}

void NewGameState::enter(){
}

void NewGameState::leave(){
}

void NewGameState::update(){

	auto& inputHandler = ih();

	if (inputHandler.keyDownEvent()) {
		//Game::Instance()->getFigtherFacade()->reset_lives();
		Game::Instance()->setState(Game::NEWROUND);
	}

	sdlutils().clearRenderer();

	_msg.render((sdlutils().width() - _msg.width()) / 2,
		(sdlutils().height() - _msg.height()) / 2);

	sdlutils().presentRenderer();
}
