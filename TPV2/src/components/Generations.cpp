#include "Generations.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"


Generations::Generations(int generations)
{
	_actualGenerations = generations;
}

Generations::~Generations()
{
}


void Generations::setGenerations(int newGen)
{
	_actualGenerations = newGen;
}

int Generations::getGenerations() const 
{
	return _actualGenerations;
}
