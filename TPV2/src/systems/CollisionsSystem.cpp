// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "StarsSystem.h"

CollisionsSystem::CollisionsSystem() : isMiraclePC(false) {
	// TODO Auto-generated constructor stub

}

CollisionsSystem::~CollisionsSystem() {
	// TODO Auto-generated destructor stub
}

void CollisionsSystem::initSystem() {
}

void CollisionsSystem::update() {

	// the PacMan's Transform
	//
	auto pm = _mngr->getHandler(ecs::hdlr::PACMAN);
	auto pTR = _mngr->getComponent<Transform>(pm);

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list stars is not
	// modified.
	//
	auto &fruits = _mngr->getEntities(ecs::grp::FRUITS);
	auto n = fruits.size();
	for (auto i = 0u; i < n; i++) {
		auto f = fruits[i];
		if (_mngr->isAlive(f)) { // if the fruit is active (it might have died in this frame)

			// the Fruit's Transform
			//
			auto fTR = _mngr->getComponent<Transform>(f);

			// check if PacMan collides with the Star (i.e., eat it)
			if (Collisions::collides(			//
					pTR->_pos, pTR->_width, pTR->_height, //
					fTR->_pos, fTR->_width, fTR->_height)) {

				Message m;
				//m.id = _m_STAR_EATEN;
				m.id = _m_PACMAN_FOOD_COLLISION;
				m.food_collision_data.fruit = f;
				_mngr->send(m);

			}
		}
	}

	//IMPORTANTE, COMPROBAR SI ESTA CON UNA FRUTA MILAGROSA
	//IMPORTANTE, SI TIENE TODAVIA VIDAS CAMBIAMOS A NEWROUND, SINO GAMEOVER
	auto& ghosts = _mngr->getEntities(ecs::grp::GHOSTS);
	auto m = ghosts.size();
	for (auto i = 0u; i < m; i++) {
		auto e = ghosts[i];
		if (_mngr->isAlive(e)) { //si el fantasma esta vivo

			// transform del fantasma
			auto eTR = _mngr->getComponent<Transform>(e);

			// comprueba colision con el pacman
			if (Collisions::collides(			//
				pTR->_pos, pTR->_width, pTR->_height, //
				eTR->_pos, eTR->_width, eTR->_height)) {
				if (!isMiraclePC) {
					Message m;
					m.id = _m_ROUND_OVER;
					_mngr->send(m);
					
				}
				else {
					
					_mngr->setAlive(e, false);
				}
			}
		}
	}

}

void CollisionsSystem::changeMiraclePC(bool b)
{
	isMiraclePC = b;
}

void CollisionsSystem::recieve(const Message& m)
{
	switch (m.id) {
	case _m_IMMUNITY_START:
		changeMiraclePC(true);
		break;
	case _m_IMMUNITY_END:
		std::cout << "asfafasfsafas";
		changeMiraclePC(false);
		break;
	default:
		break;
	}

}