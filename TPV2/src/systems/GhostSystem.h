#pragma once

#include "../ecs/System.h"

struct Transform;

class GhostSystem : public ecs::System {
public:

	GhostSystem();
	virtual ~GhostSystem();
	void initSystem() override;
	void update() override;
	//voids para mensajes recibidos
	//
	//
	//recieve de mensajes, override, recibe un mensaje y ejecuta una función especifica del propio sistema
	void recieve(const Message& m) override;
private:
	Transform* _pmTR;
};
