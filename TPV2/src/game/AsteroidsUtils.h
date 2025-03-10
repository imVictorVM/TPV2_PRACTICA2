#pragma once

#include "AsteroidsFacade.h"

#include "../ecs/Manager.h"

class AsteroidsUtils : public AsteroidsFacade {
public:
	AsteroidsUtils(ecs::entity_t ship) { _ship = ship; };
	void create_asteroids(int n) override;
	void remove_all_asteroids() override;
	void split_asteroid(ecs::entity_t a) override;

private:
	ecs::entity_t _ship;
};