#pragma once

#include "../ecs/System.h"

#include <vector>

struct Transform;
class Vector2D;

class GhostSystem : public ecs::System {
public:

	GhostSystem(int numGhosts);
	virtual ~GhostSystem();
	void initSystem() override;
	void update() override;
	//voids para mensajes recibidos
	void killAllGhosts();
	//
	//recieve de mensajes, override, recibe un mensaje y ejecuta una función especifica del propio sistema
	void recieve(const Message& m) override;
private:
	std::vector<ecs::entity_t> _ghosts;
	int _numGhosts;
	Transform* _pmTR;
	float _timer;
};
