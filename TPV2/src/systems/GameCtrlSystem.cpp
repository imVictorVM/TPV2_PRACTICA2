// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrlSystem.h"

#include "../components/Points.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "StarsSystem.h"

#include "../game/Game.h"

GameCtrlSystem::GameCtrlSystem() :
		_score() {
	// TODO Auto-generated constructor stub

}

GameCtrlSystem::~GameCtrlSystem() {
	// TODO Auto-generated destructor stub
}

void GameCtrlSystem::initSystem() {
}

void GameCtrlSystem::update() {

}

void GameCtrlSystem::recieve(const Message &m) {
	switch (m.id) {
	//case _m_STAR_EATEN:
	  case _m_PACMAN_FOOD_COLLISION:
		break;
	  case _m_GAME_OVER:
		  Game::Instance()->setState(Game::GAMEOVER);
		  break;
	default:
		break;
	}
}
