#include "GhostSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"

GhostSystem::GhostSystem() : _pmTR(nullptr)
{
}

GhostSystem::~GhostSystem()
{
}

void GhostSystem::initSystem()
{
	auto ghost = _mngr->addEntity();
	//_mngr->setHandler(ecs::hdlr::PACMAN, pacman);

	_pmTR = _mngr->addComponent<Transform>(ghost);
	auto s = 30.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	_pmTR->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
	//_mngr->addComponent<Image>(ghost, &sdlutils().images().at("pacman"));
}

void GhostSystem::update()
{
}
