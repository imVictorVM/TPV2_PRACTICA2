#include "FoodSystem.h"
#include <algorithm>
#include <random>
#include "../components/Image.h"
#include "../components/Points.h"
#include "../components/Transform.h"
#include "../components/MiracleFruit.h" 
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrlSystem.h"
#include "../components/ImageWithFrames.h"

FoodSystem::FoodSystem() : _currNumOfFood(0) {
}

FoodSystem::~FoodSystem() {
}

void FoodSystem::initSystem() {

}

void FoodSystem::update() {
    
    auto currentTime = sdlutils().currRealTime();
    auto& rand = sdlutils().rand();

    auto fruits = _mngr->getEntities(ecs::grp::STARS);

    for (auto e : fruits) {
        if (_mngr->hasComponent<MiracleFruit>(e)) {
            
            auto mf = _mngr->getComponent<MiracleFruit>(e);
           
            // Actualizar tiempo en estado actual
            float timeInState = (currentTime - mf->getLastStateChange()) / 1000.0f;
            mf->setTimeInState(timeInState);

            // Comprobar si necesita cambiar de estado
            if ((!mf->isMiracleState() && timeInState >= mf->getNormalDuration()) ||
                (mf->isMiracleState() && timeInState >= mf->getMiracleDuration())) {

                

                mf->toggleState();
                mf->resetTimers(currentTime);

                if (mf->isMiracleState()) {
                    // Establecer nueva duración milagrosa (1-5 segundos)
                    mf->setMiracleDuration(rand.nextInt(1,6));

                    // Cambiar imagen a pera
                    auto img = _mngr->getComponent<ImageWithFrames>(e);
                    img->setCol(7);
                    img->setFil(1);
                    img->resetFramePosition();
                }
                else {
                    // Cambiar imagen a cereza
                    auto img = _mngr->getComponent<ImageWithFrames>(e);
                    img->setCol(4);
                    img->setFil(1);
                    img->resetFramePosition();
                }
            }
        }
    }
}

void FoodSystem::addFood(unsigned int n) {
    auto& rand = sdlutils().rand();

    for (auto i = 0u; i < 8; ++i) {
        for (auto j = 0u; j < 6; ++j) {

            //Add entity to manager
            auto e = _mngr->addEntity(ecs::grp::STARS);

            // Add a transform component
            auto tr = _mngr->addComponent<Transform>(e);
            auto s = 50;
            auto x = (sdlutils().width() / 8 * (i + 1)) - s;
            auto y = (sdlutils().height() / 6 * (j + 1)) - s;
            tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

            // Image component
            _mngr->addComponent<ImageWithFrames>(e, &sdlutils().images().at("sprites"), s, s, 4, 1, 0);

            //Points component
            auto pts = _mngr->addComponent<Points>(e);
            pts->_points = 5;

            // 10% miracle fruit
            if (rand.nextInt(1, 101) < 10) {
                auto mf = _mngr->addComponent<MiracleFruit>(e);
                mf->setNormalDuration(rand.nextInt(10,21)); // 10-20 sec
                mf->resetTimers(sdlutils().currRealTime());
                std::cout << "miracle created" << std::endl;
            }

            _currNumOfFood++;
        }
    }
}

void FoodSystem::onFoodEaten(ecs::entity_t e) {
    if (_mngr->hasComponent<MiracleFruit>(e)) {
        auto mf = _mngr->getComponent<MiracleFruit>(e);
        if (mf->isMiracleState()) {
            Message m;
            m.id = _m_IMMUNITY_START;
            _mngr->send(m);
        }
    }

    _mngr->setAlive(e, false);
    _currNumOfFood--;

    //play sound on channel 1 (if there is something playing there
    // it will be cancelled
    sdlutils().soundEffects().at("pacman_eat").setVolume(16);
    sdlutils().soundEffects().at("pacman_eat").play(0, 1);
}


void FoodSystem::recieve(const Message& m) {
    switch (m.id) {
    case _m_PACMAN_FOOD_COLLISION:
   // case _m_STAR_EATEN:
        onFoodEaten(m.food_collision_data.e);
        break;
   // case _m_ROUND_START:
    case _m_CREATE_STARS:
        addFood(m.create_stars_data.n); 
        break;
    default:
        break;
    }
}