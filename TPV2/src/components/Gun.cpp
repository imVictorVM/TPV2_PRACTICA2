#include "Gun.h"
#include "../sdlutils/SDLUtils.h"

#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"

#include "Transform.h"

#include "../ecs/Manager.h"
#include "../game/Game.h"

#include "../game/ConfigAsteroids.h"

Gun::Gun(Texture* tex) : _img(tex)
{
	for (auto& bullet : _bullets) {
		bullet.timeOfLife = 0;
	}
	_cooldown = 0;
}

void Gun::reset()
{
	for (auto& bullet : _bullets) {
		bullet.used = false; //Marcando las balas como no usadas
		bullet.timeOfLife = 0;
	}
	_cooldown = 0;
}

void Gun::initComponent()
{
	auto mngr = Game::Instance()->getManager();
	_entityTransform = mngr->getComponent<Transform>(_ent);
	assert(_entityTransform != nullptr);
}

void Gun::render()
{
	for (auto& bullet : _bullets) {
		if (bullet.used) {
			SDL_Rect bulletRect = build_sdlrect(bullet.pos, bullet.width, bullet.height);
			assert(_img != nullptr);
			_img->render(bulletRect, bullet.rot);
		}
	}
}

void Gun::update()
{
	auto& ihdlr = ih();

	uint32_t _actualTime = sdlutils().virtualTimer().regCurrTime();

	for (auto& bullet : _bullets) {
		if (bullet.used) {
			bullet.pos = bullet.pos + bullet.vel;
			if (bullet.timeOfLife + 2500.f < _actualTime) {
				bullet.used = false;
				bullet.timeOfLife == 0;
			}
		}
		else {
			//ARCHIVO CONFIG PARA EL TIEMPO DE RECARGA DE LA BALA
			if (ihdlr.isKeyDown(SDL_SCANCODE_S) && (_cooldown + Game::Instance()->getConfigAsteroids()->gunReloadTime() < _actualTime)) {
				

				sdlutils().soundEffects().at("ship_shoot").play();
				sdlutils().soundEffects().at("ship_shoot").setChannelVolume(1);
				
				_cooldown = sdlutils().virtualTimer().regCurrTime();

				int _bulletWidth = 5;
				int _bulletHeight = 20;
				Vector2D c = _entityTransform->getPos() + Vector2D(_entityTransform->getWidth() / 2.0f, _entityTransform->getHeight() / 2.0f);
				Vector2D _bulletPosition = c - Vector2D(_bulletWidth / 2.0f, _entityTransform->getHeight() / 2.0f + 5.0f + _bulletHeight).rotate(_entityTransform->getRot()) - Vector2D(_bulletWidth / 2, _bulletHeight / 2);
				Vector2D _bulletVelocity = Vector2D(0, -1).rotate(_entityTransform->getRot()) * (_entityTransform->getVel().magnitude() + 5.0f);
				float _bulletRotation = Vector2D(0, -1).angle(_bulletVelocity);
				
				shoot(_bulletPosition, _bulletVelocity, _bulletWidth, _bulletHeight, _bulletRotation);
			}
		}

	}
}

void Gun::shoot(Vector2D p, Vector2D v, int width, int height, float rotation)
{
	for (auto& bullet : _bullets) {
		if (!bullet.used) {
			bullet.used = true;
			bullet.pos = p;
			bullet.vel = v;
			bullet.width = width;
			bullet.height = height;
			bullet.rot = rotation;
			bullet.timeOfLife = sdlutils().virtualTimer().regCurrTime();
			break;
		}
	}

	//for (Gun::Bullet& b : *fighterGUN)
	//	if (b.used) { ... }

}
