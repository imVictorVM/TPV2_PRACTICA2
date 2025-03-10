#pragma once

#include "../ecs/Component.h"

class Transform;

class ShowAtOppositeSide : public ecs::Component {
public:
	__CMPID_DECL__(ecs::cmp::SHOWATOPPOSITESIDE)

	ShowAtOppositeSide();
	void initComponent() override;
	void update() override;
private:
	Transform* _entityTransform;
	float offset;
};