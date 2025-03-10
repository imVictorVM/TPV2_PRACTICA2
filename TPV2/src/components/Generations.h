#pragma once

#include "../ecs/Component.h"

class Transform;
class Entity;

class Generations : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::GENERATIONS)

	Generations(int generations);
	virtual ~Generations();
	void setGenerations(int newGen);
	int getGenerations() const;


private:
	int _actualGenerations;
};
