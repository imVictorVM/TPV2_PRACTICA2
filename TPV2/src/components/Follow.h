#pragma once

#include "../ecs/Component.h"

class Transform;
class Entity;

class Follow : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::FOLLOW)

	Follow(Transform* tr);
	virtual ~Follow();
	void initComponent() override;
	void update() override;


private:
	Transform* _myTransform;

	Transform*  _objective;
};

