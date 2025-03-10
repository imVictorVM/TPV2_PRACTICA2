#pragma once

#include "../ecs/Component.h"

class Transform;
class Entity;

class TowardDestination : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::TOWARDDESTINATION)

	TowardDestination();
	virtual ~TowardDestination();
	void initComponent() override;
	void update() override;


private:
	Transform* _myTransform;

	int _objX;
	int _objY;
};

