// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

#include "FigtherUtils.h"
#include "AsteroidsUtils.h"

#include "../utils/Singleton.h"

#include "GameState.h"

namespace ecs {
class Manager;
}

class Transform;
class GameState;
class ConfigAsteroids;

class Game : public Singleton<Game>{
private:
	friend class Singleton<Game>;
	Game();
public:

	virtual ~Game();

	void initGame(ConfigAsteroids &config);
	void start();
	ecs::Manager* getManager() { return _mngr; }
	FigtherUtils* getFigtherFacade() { return _myFighterUtils; }
	AsteroidsUtils* getAsteroidsFacade() { return _myAsteroidsUtils; }
	ecs::entity_t getFigther() { return _myFigther; }
	ConfigAsteroids* getConfigAsteroids() { return _config; }
	
	enum State { RUNNING, PAUSED, NEWGAME, NEWROUND, GAMEOVER };

	inline void setState(State s) {
		_state->leave();
		switch (s) {
		case RUNNING:
			_state = _running_State;
			break;
		case PAUSED:
			_state = _paused_State;
			break;
		case NEWGAME:
			_state = _newGame_State;
			break;
		case NEWROUND:
			_state = _newRound_State;
			break;
		case GAMEOVER:
			_state = _gameOver_State;
			break;
		}
		_state->enter();
	}
private:
	bool init();

	ecs::Manager *_mngr;
	FigtherUtils *_myFighterUtils;
	AsteroidsUtils* _myAsteroidsUtils;
	ConfigAsteroids* _config;


	GameState *_state;
	GameState *_paused_State;
	GameState *_running_State;
	GameState *_newGame_State;
	GameState *_newRound_State;
	GameState *_gameOver_State;

	ecs::entity_t _myFigther;
};

