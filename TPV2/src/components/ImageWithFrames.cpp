#include "ImageWithFrames.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../game/Game.h"
#include "../sdlutils/SDLUtils.h"

ImageWithFrames::ImageWithFrames() :
	_tr(), _tex(), _width(0), _height(0), _texHeigthMax(0), _texWidthMax(0), _timer(0) {
}

ImageWithFrames::ImageWithFrames(Texture* tex, float width, float height) :
	_tr(), _tex(tex), _width(width), _height(height){
	_texWidthMax = _tex->width();
	_texHeigthMax = _tex->height();
	_actFrame = Vector2D(0, 0);
	_timer = 0;
}

ImageWithFrames::~ImageWithFrames() {
}

void ImageWithFrames::initComponent() {
	auto mngr = Game::Instance()->getManager();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);
}


/*
 inline void render(const SDL_Rect &src, const SDL_Rect &dest, double angle,
			const SDL_Point *p = nullptr,
			SDL_RendererFlip flip = SDL_FLIP_NONE) {
		assert(_texture != nullptr);
		SDL_RenderCopyEx(_renderer, _texture, &src, &dest, angle, p, flip);
	}
*/

void ImageWithFrames::render() {

	SDL_Rect dest = build_sdlrect(_tr->getPos(), _tr->getWidth(),
		_tr->getHeight());

	SDL_Rect frame = build_sdlrect(_actFrame, _width, _height);

	assert(_tex != nullptr);
	_tex->render(frame, dest, 0);
}

void ImageWithFrames::update()
{
	if (_timer + 50 <= sdlutils().virtualTimer().currTime()) {
		_timer = sdlutils().virtualTimer().currTime();

		if (_actFrame.getX() + _width < _texWidthMax) {
			_actFrame.setX(_actFrame.getX() + _width);
		}
		else if (_actFrame.getY() + _height < _texHeigthMax) {
			_actFrame.setX(0);
			_actFrame.setY(_actFrame.getY() + _height);
		}
		else {
			_actFrame.set(0, 0);
		}

	}

}
