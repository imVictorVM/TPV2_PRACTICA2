// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "NewGameState.h"
#include "NewRoundState.h"
#include "PausedState.h"
#include "RunningState.h"
#include "GameOverState.h"

#include "../game/ConfigAsteroids.h"


using ecs::Manager;

Game::Game() :
	
	_myFighterUtils(nullptr),
	_state(nullptr),
	_paused_State(nullptr),
	_running_State(nullptr),
	_newGame_State(nullptr),
	_newRound_State(nullptr),
	_gameOver_State(nullptr),
	_myFigther(nullptr),
	_config(nullptr)
{
}

Game::~Game() {

	delete _paused_State;
	delete _running_State;
	delete _newGame_State;
	delete _newRound_State;
	delete _gameOver_State;

	delete _myFighterUtils;
	delete _myFigther;


	// release InputHandler if the instance was created correctly.
	if (InputHandler::HasInstance())
		InputHandler::Release();

	// release SLDUtil if the instance was created correctly.
	if (SDLUtils::HasInstance())
		SDLUtils::Release();
}

bool Game::init() {

	// initialize the SDL singleton
	if (!SDLUtils::Init("Asteroids", 800, 600,
			"resources/config/asteroid.resources.json")) {

		std::cerr << "Something went wrong while initializing SDLUtils"
				<< std::endl;
		return false;
	}

	// initialize the InputHandler singleton
	if (!InputHandler::Init()) {
		std::cerr << "Something went wrong while initializing SDLHandler"
				<< std::endl;
		return false;

	}
	sdlutils().hideCursor();

	return true;
	

}

void Game::initGame(ConfigAsteroids& config)
{
	_mngr = new Manager();
	_config = &config;

	_newGame_State = new NewGameState();
	_newRound_State = new NewRoundState();
	_paused_State = new PausedState();
	_running_State = new RunningState();
	_gameOver_State = new GameOverState();

	_myFighterUtils = new FigtherUtils();
	_myFighterUtils->create_figther();

	_myFigther = _myFighterUtils->getShipEntity();
	
	//_AsteroidsUtils creation
	_myAsteroidsUtils = new AsteroidsUtils(_myFigther);

	_state = _newGame_State;

	_state->enter();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();
	auto& vt = sdlutils().virtualTimer();

	// reset the time before starting - so we calculate correct
	// delta-time in the first iteration
	//
	//sdlutils().resetTime();
	vt.resetTime();

	while (!exit) {
		// store the current time -- all game objects should use this time when
		// then need to the current time. They also have accessed to the time elapsed
		// between the last two calls to regCurrTime().
		//Uint32 startTime = sdlutils().regCurrTime();
		Uint32 startTime = vt.regCurrTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		

		_state->update();


		SDL_Delay(8);
	}

}


