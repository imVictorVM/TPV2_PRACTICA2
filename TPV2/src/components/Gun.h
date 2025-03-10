#pragma once

#include "../ecs/Component.h"
#include <array>
#include "../ecs/ObjectPool.h"
#include <iterator>
#include "../utils/Vector2D.h"

class Texture;
class Transform;

class Gun : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::GUN)

	struct Bullet
	{
		bool used = false;
		Vector2D pos;
		Vector2D vel;
		int width;
		int height;
		float rot;
		uint32_t timeOfLife;
	};

	constexpr static uint8_t max_bullets = 20;
	typedef std::array<Bullet, max_bullets> bullets_array_t;
	typedef bullets_array_t::iterator iterator;

	Gun(Texture* tex);
	void reset();

	iterator begin() {
		return _bullets.begin();
	}
	iterator end() {
		return _bullets.end();
	}
	void initComponent() override;
	void render() override;
	void update() override;

private:

	void shoot(Vector2D p, Vector2D v, int width, int height, float r);
	bullets_array_t _bullets;
	uint32_t _cooldown;
	Texture* _img;
	Transform* _entityTransform;
};

