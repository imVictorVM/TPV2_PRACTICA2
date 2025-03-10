#pragma once

#include "FigtherFacade.h"

#include "../ecs/Manager.h"

class FigtherUtils : public FigtherFacade {
public:
	FigtherUtils();
	ecs::entity_t getShipEntity() { return _ship; }
	void create_figther() override;
	void reset_figther() override;
	void reset_lives() override;
	int update_lives(int n) override;
private:
	ecs::entity_t _ship;
};