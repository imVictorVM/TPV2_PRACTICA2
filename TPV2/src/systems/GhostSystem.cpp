#include "GhostSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"

#include "../utils/Vector2D.h"

#include "../ecs/Entity.h"

#include "../components/ImageWithFrames.h"

GhostSystem::GhostSystem(int numGhosts) : _pmTR(nullptr), _numGhosts(numGhosts)
{

}

GhostSystem::~GhostSystem()
{
	_ghosts.clear();
}

void GhostSystem::initSystem()
{
	int offset = 0;
	for (int i = 0; i < _numGhosts; ++i) {
		auto ghost = _mngr->addEntity(ecs::grp::GHOSTS);
		_ghosts.push_back(ghost);
		//_mngr->setHandler(ecs::hdlr::PACMAN, pacman);

		_pmTR = _mngr->addComponent<Transform>(ghost);
		auto s = 50.0f;
		auto x = ((sdlutils().width() - s) + offset) / 2.0f;
		auto y = ((sdlutils().height() - s) + offset) / 2.0f;
		_pmTR->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
		_mngr->addComponent<ImageWithFrames>(ghost, &sdlutils().images().at("sprites"), s, s, 0, 4, 6);
		offset += 80;
	}

	_timer = 0;
}

void GhostSystem::update()
{

	auto e = _mngr->getHandler(ecs::hdlr::PACMAN);
	auto PCTR = _mngr->getComponent<Transform>(e);

	//movimiento hacia el pacman que sea dentro del espacio de juego
	for (int i = 0; i < _numGhosts; ++i) {

		auto GHTR = _mngr->getComponent<Transform>(_ghosts[i]);
		GHTR->_vel.set(PCTR->_pos.getX() - GHTR->_pos.getX(), PCTR->_pos.getY() - GHTR->_pos.getY());
		
		if (_timer + 100 <= sdlutils().virtualTimer().currTime()) {
			_timer = sdlutils().virtualTimer().currTime();

			for (int i = 0; i < _numGhosts; ++i) {
				_mngr->getComponent<ImageWithFrames>(_ghosts[i])->updateImage();
			}
		}
	}
	
}

void GhostSystem::killAllGhosts()
{
	for (int i = 0; i < _numGhosts; ++i) {
		_mngr->setAlive(_ghosts[i],false);
	}
}



void GhostSystem::recieve(const Message& m)
{
	switch (m.id) {
	case _m_IMMUNITY_END: //ACABA LA INMUNIDAD
		//LLAMADA A FUNCION ESPECIFICA DEL PROPIO SISTEMA
		break;
	case _m_ROUND_OVER:
		//reset de fantasmas
	default:
		break;
	}
}
