#pragma once

#include "../ecs/Component.h"

class Transform;
class Vector2D;
class Texture;

class Health : public ecs::Component {
public:

	//__CMPID_DECL__(ecs::cmp::HEALTH)

	Health(int initialLives);
	virtual ~Health();
	void initComponent() override;
	//void render() override;

	void addOneLive();
	void loseOneLive();

	void resetLives();

	int checkLives();

private:
	Transform* _myTransform;
	Texture* _tex;
	int _lives;
	int _initialLives;
	float _tam;
};