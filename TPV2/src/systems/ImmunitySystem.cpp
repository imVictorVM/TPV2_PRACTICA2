#include "ImmunitySystem.h"
#include "../ecs/Manager.h"
#include "../components/Health.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"

ImmunitySystem::ImmunitySystem() {
    // Inicialización básica
}

ImmunitySystem::~ImmunitySystem() {
    // Limpieza si es necesaria
}

void ImmunitySystem::initSystem() {
    // Registro de tipos de mensajes que nos interesan
}

void ImmunitySystem::update() {
    auto pacman = _mngr->getHandler(ecs::hdlr::PACMAN);
    auto health = _mngr->getComponent<Health>(pacman);

    // Comprobar tiempo de inmunidad
    if (health->isImmune() &&
        sdlutils().currRealTime() - health->getImmunityStartTime() > 10000) {
        endImmunity(pacman);
    }
}

void ImmunitySystem::recieve(const Message& m) {
    switch (m.id) {
    case _m_IMMUNITY_START:
        std::cout << "message received" << std::endl;
        startImmunity(m.immunity_start_data.pacman);
        break;

    case _m_ROUND_START:
    case _m_IMMUNITY_END:
        // Finalizar inmunidad si estaba activa
        auto pacman = _mngr->getHandler(ecs::hdlr::PACMAN);
        auto health = _mngr->getComponent<Health>(pacman);
        if (health->isImmune()) {
            endImmunity(pacman);
        }
        break;
    }
}

void ImmunitySystem::startImmunity(ecs::entity_t pacman) {
    auto health = _mngr->getComponent<Health>(pacman);

    // Activar inmunidad
    health->activateImmunity(sdlutils().currRealTime());

    // Cambiar apariencia de fantasmas (ejemplo)
    auto ghosts = _mngr->getEntities(ecs::grp::GHOSTS);
    for (auto g : ghosts) {

     /*   auto img = _mngr->getComponent<ImageWithFrames>(g);
        img->setCol(7);
        img->setFil(1);
        img->resetFramePosition();
        */
    }
    std::cout << "message received" << std::endl;
    // Reproducir sonido
  //  sdlutils().soundEffects().at("immunity_start").play();
}

void ImmunitySystem::endImmunity(ecs::entity_t pacman) {
    auto health = _mngr->getComponent<Health>(pacman);
    health->deactivateImmunity();

    // Restaurar apariencia de fantasmas
    auto ghosts = _mngr->getEntities(ecs::grp::GHOSTS);
    for (auto g : ghosts) {
        auto img = _mngr->getComponent<Image>(g);
     //   img->setTexture(&sdlutils().images().at("ghost_red"));
    }

    // Enviar mensaje de fin de inmunidad
    Message m;
    m.id = _m_IMMUNITY_END;
    _mngr->send(m);

    // Reproducir sonido
    sdlutils().soundEffects().at("immunity_end").play();
}