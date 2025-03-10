#pragma once
#include "../ecs/Component.h"
#include <SDL_scancode.h>

class Transform;
class Vector2D;

class FighterCtrl : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::FIGHTERCTRL)

	FighterCtrl();
	virtual ~FighterCtrl();
	void initComponent() override;
	void update() override;

	inline void setKeys(SDL_Scancode up,
		SDL_Scancode left, SDL_Scancode right) {
		_up = up;
		_left = left;
		_right = right;
	}
	
private:

	Transform* _myTransform;
	SDL_Scancode _up;
	SDL_Scancode _left;
	SDL_Scancode _right;
	float _speedRotation;
	float _thrust;
	float _speedLimit;

};

