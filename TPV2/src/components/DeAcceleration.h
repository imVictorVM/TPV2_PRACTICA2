#pragma once

#include "../ecs/Component.h"

class Transform;
class Vector2D;

class DeAcceleration : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::DEACCELERATION)

	DeAcceleration();
	virtual ~DeAcceleration();
	void initComponent() override;
	void update() override;

private:
	Transform* _myTransform;
	
};