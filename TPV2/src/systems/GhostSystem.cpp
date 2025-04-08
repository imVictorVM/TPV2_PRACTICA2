#include "GhostSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"

#include "../utils/Vector2D.h"

#include "../ecs/Entity.h"

#include "../components/ImageWithFrames.h"

GhostSystem::GhostSystem(int numGhosts) : _pmTR(nullptr), _numGhosts(numGhosts)
{
	_ghosts.resize(_numGhosts);
}

GhostSystem::~GhostSystem()
{
	_ghosts.clear();
}

void GhostSystem::initSystem()
{
	for (int i = 0; i < _numGhosts; ++i) {
		auto ghost = _mngr->addEntity(ecs::grp::GHOSTS);
		_ghosts.push_back(ghost);
		//_mngr->setHandler(ecs::hdlr::PACMAN, pacman);

		_pmTR = _mngr->addComponent<Transform>(ghost);
		auto s = 50.0f;
		auto x = (sdlutils().width() - s) / 2.0f;
		auto y = (sdlutils().height() - s) / 2.0f;
		_pmTR->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
		//_mngr->addComponent<Image>(ghost, &sdlutils().images().at("pacman"));
		_mngr->addComponent<ImageWithFrames>(ghost, &sdlutils().images().at("sprites"), s, s, 0, 4, 1);
	}
}

void GhostSystem::update()
{
	//movimiento hacia el pacman que sea dentro del espacio de juego
	for (int i = 0; i < _numGhosts; ++i) {

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
