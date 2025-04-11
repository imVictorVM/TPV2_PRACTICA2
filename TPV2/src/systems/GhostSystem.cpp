#include "GhostSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"

#include "../utils/Vector2D.h"

#include "../ecs/Entity.h"

#include "../components/ImageWithFrames.h"

#include "../sdlutils/RandomNumberGenerator.h"

GhostSystem::GhostSystem() : _numGhosts(0), _timerAnimation(0), _timerSpawn(0)
{
}

GhostSystem::~GhostSystem()
{
}

void GhostSystem::initSystem()
{
}

void GhostSystem::update()
{

	//std::cout << "TIME: " << sdlutils().virtualTimer().currTime() << std::endl;

	auto e = _mngr->getHandler(ecs::hdlr::PACMAN);
	auto ghosts = _mngr->getEntities(ecs::grp::GHOSTS);
	auto _pmTR = _mngr->getComponent<Transform>(e);

	for (auto ghost : ghosts) {
		if (_mngr->hasComponent<Transform>(ghost)) {
			//Obtenemos el transform del fantasma como primera opcion
			auto ghostTR = _mngr->getComponent<Transform>(ghost);
			
			//Actualizando velocidad en funcion de la posicion de Pacman y la de los fantasmas
			//uso del randomNumberGenerator
			auto& r = sdlutils().rand();
			int rnd = r.nextInt(0, 501); // 0 a 5000

			// 0.005 de probabilidad
			if (rnd <= 5) {
				ghostTR->_vel = ((_pmTR->_pos - ghostTR->_pos).normalize() * 1.1f);
			}

			//Para que pueda spawnear fuera
			//if (ghostTR->_vel.getX() != 0 && ghostTR->_vel.getY() != 0) {
				// check left/right borders
				if (ghostTR->_pos.getX() < 0) {
					ghostTR->_pos.setX(0.0f);
					ghostTR->_vel.setX(ghostTR->_vel.getX() * -1);
				}
				//IMPORTANTE, tomamos en cuenta la posicion del fantasma
				else if (ghostTR->_pos.getX() + ghostTR->_width > sdlutils().width()) {
					ghostTR->_pos.setX(sdlutils().width() - ghostTR->_width);
					ghostTR->_vel.setX(ghostTR->_vel.getX() * -1);
				}

				// check upper/lower borders
				if (ghostTR->_pos.getY() < 0) {
					ghostTR->_pos.setY(0.0f);
					ghostTR->_vel.setY(ghostTR->_vel.getY() * -1);
				}
				//IMPORTANTE, tomamos en cuenta la posicion del fantasma
				else if (ghostTR->_pos.getY() + ghostTR->_height > sdlutils().height()) {
					ghostTR->_pos.setY(sdlutils().height() - ghostTR->_height);
					ghostTR->_vel.setY(ghostTR->_vel.getY() * -1);
				}
			//}

			ghostTR->_pos = ghostTR->_pos + ghostTR->_vel;
		}


	}

	//IMPORTANTE, NO GENERAR SI HAY INMUNIDAD
	//Tiempo de spawn y que el numero de fantasmas sea como maximo 10 para generar uno nuevo
	if (_timerSpawn + 5000 <= sdlutils().virtualTimer().currTime() && _numGhosts < 10) {
		_timerSpawn = sdlutils().virtualTimer().currTime();
		generateOneGhost();
	}

	//Despues de generar nuestro primer fantasma controlamos su movimiento
//	if (_numGhosts > 0) {
//		for (int i = 0; i < _numGhosts; ++i) {
//
//			//Obtenemos el transform del fantasma como primera opcion
//			//auto GHTR = _mngr->getComponent<Transform>(_ghosts[i]);
//
//			//Tenemos el transform del fantasma registrado
//			//_ghTR;
//
//			//Actualizando velocidad en funcion de la posicion de Pacman y la de los fantasmas
//			//uso del randomNumberGenerator
//			auto& r = sdlutils().rand();
//			int rnd = r.nextInt(0, 5001); // 0 a 5000
//
//			// 0.005 de probabilidad
//			if (rnd <= 5) {
//				_ghTR[i]->_vel = ((_pmTR->_pos - _ghTR[i]->_pos).normalize() * 1.1f);
//			}
//
//			//Para que pueda spawnear fuera
//			//if (_ghTR[i]->_vel.getX() != 0 && _ghTR[i]->_vel.getY() != 0) {
//				// check left/right borders
//				if (_ghTR[i]->_pos.getX() < 0) {
//					_ghTR[i]->_pos.setX(0.0f);
//					_ghTR[i]->_vel.setX(_ghTR[i]->_vel.getX() * -1);
//				}
//				//IMPORTANTE, tomamos en cuenta la posicion del fantasma
//				else if (_ghTR[i]->_pos.getX() + _ghTR[i]->_width > sdlutils().width()) {
//					_ghTR[i]->_pos.setX(sdlutils().width() - _ghTR[i]->_width);
//					_ghTR[i]->_vel.setX(_ghTR[i]->_vel.getX() * -1);
//				}
//
//				// check upper/lower borders
//				if (_ghTR[i]->_pos.getY() < 0) {
//					_ghTR[i]->_pos.setY(0.0f);
//					_ghTR[i]->_vel.setY(_ghTR[i]->_vel.getY() * -1);
//				}
//				//IMPORTANTE, tomamos en cuenta la posicion del fantasma
//				else if (_ghTR[i]->_pos.getY() + _ghTR[i]->_height > sdlutils().height()) {
//					_ghTR[i]->_pos.setY(sdlutils().height() - _ghTR[i]->_height);
//					_ghTR[i]->_vel.setY(_ghTR[i]->_vel.getY() * -1);
//				}
//			//}
//
//
//			//Actualizando posicion del fantasma
//			//_ghTR[i]->_pos = _ghTR[i]->_pos + _ghTR[i]->_vel;
//			
//
//			//Actualizando frames de animacion
//	/*		if (_timerAnimation + 100 <= sdlutils().virtualTimer().currTime()) {
//				_timerAnimation = sdlutils().virtualTimer().currTime();
//
//				for (int i = 0; i < _numGhosts; ++i) {
//					assert(_ghosts[i] != nullptr);
//					auto img = _mngr->getComponent<ImageWithFrames>(_ghosts[i]);
//					if (img != nullptr) {
//						img->updateImage();
//					}
//				}
//			}
//*/
//			//IMPORTANTE, NO GENERAR SI HAY INMUNIDAD
//			//Tiempo de spawn y que el numero de fantasmas sea como maximo 10 para generar uno nuevo
//			if (_timerSpawn + 5000 <= sdlutils().virtualTimer().currTime() && _numGhosts < 10) {
//				_timerSpawn = sdlutils().virtualTimer().currTime();
//				generateOneGhost();
//			}
//		}
//	}

}

void GhostSystem::generateOneGhost()
{
	//uso del randomNumberGenerator
	auto& r = sdlutils().rand();
	int rnd = r.nextInt(0,3); // 0,1,2,3 (para una de las 4 esquinas)

	auto ghost = _mngr->addEntity(ecs::grp::GHOSTS);
	//_ghosts.push_back(ghost);
	auto trGhost = _mngr->addComponent<Transform>(ghost);
	//_ghTR.push_back(trGhost);

	auto s = 50.0f;

	//Generacion en el centro de la pantalla
	//float x = ((sdlutils().width() - s)) / 2.0f;
	//float y = ((sdlutils().height() - s)) / 2.0f;

	float x = 0.0f;
	float y = 0.0f;

	switch (rnd) {
		case 0:
			x = 0.0f - s;
			y = 0.0f - s;
			break;
		case 1:
			x = sdlutils().width() + s;
			y = 0.0f - s;
			break;
		case 2:
			x = sdlutils().width() + s;
			y = sdlutils().height() + s;
			break;
		case 3:
			x = 0.0f - s;
			y = sdlutils().height() + s;
			break;
		default:
			break;
	}

	trGhost->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	_mngr->addComponent<ImageWithFrames>(ghost, &sdlutils().images().at("sprites"), s, s, 0, 4, 6);

	_numGhosts++;
}

void GhostSystem::resetGhosts()
{
	//Matamos a todos los fantasmas
	killAllGhosts();
}

void GhostSystem::killAllGhosts()
{
	//Recorremos todos los fantamas
	auto ghosts = _mngr->getEntities(ecs::grp::GHOSTS);
	for (auto e : ghosts) {
		_mngr->setAlive(e,false);
	}
	_numGhosts = 0;
}



void GhostSystem::recieve(const Message& m)
{
	switch (m.id) {
	case _m_IMMUNITY_END: //ACABA LA INMUNIDAD
		//LLAMADA A FUNCION ESPECIFICA DEL PROPIO SISTEMA
		break;
	case _m_ROUND_START:
		killAllGhosts();
		break;
	case _m_ROUND_OVER:
		//reset de fantasmas
		break;
	default:
		break;
	}
}
