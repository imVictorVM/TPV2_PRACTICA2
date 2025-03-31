#pragma once

#include "../ecs/System.h"

struct Transform;

class GhostSystem : public ecs::System {
public:

	GhostSystem();
	virtual ~GhostSystem();
	void initSystem() override;
	void update() override;
private:
	Transform* _pmTR;
};
