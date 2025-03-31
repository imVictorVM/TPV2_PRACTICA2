#include "ImageWithFrames.h"

#include <cassert>

#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../game/Game.h"
#include "../sdlutils/SDLUtils.h"

ImageWithFrames::ImageWithFrames() :
	_tr(), _tex(),_width(0), _height(0), _texHeigthMax(0), _texWidthMax(0), _timer(0), _initialFil(0), _initialCol(0), _numFrames(0), _actualFrame(0) {
}

ImageWithFrames::ImageWithFrames(Texture* tex, float width, float height, int fil, int col, int numFrames) :
	_tr(), _tex(tex), _width(width), _height(height){
	_texWidthMax = _tex->width();
	_texHeigthMax = _tex->height();
	_actFrame = Vector2D(fil, col);
	_timer = 0;
	_numFrames = numFrames;
	_actualFrame = 0;
	_initialFil = fil;
	_initialCol = col;
}

ImageWithFrames::~ImageWithFrames() {
}

void ImageWithFrames::initComponent() {

	auto mngr = Game::Instance()->getManager();
	_tr = mngr->getComponent<Transform>(_ent);
	assert(_tr != nullptr);

	SDL_Rect dest = build_sdlrect(_tr->_pos, _tr->_width,
		_tr->_height);

	SDL_Rect frame = build_sdlrect(_actFrame, _width, _height);

	assert(_tex != nullptr);
	_tex->render(frame, dest, 0);
}


/*
 inline void render(const SDL_Rect &src, const SDL_Rect &dest, double angle,
			const SDL_Point *p = nullptr,
			SDL_RendererFlip flip = SDL_FLIP_NONE) {
		assert(_texture != nullptr);
		SDL_RenderCopyEx(_renderer, _texture, &src, &dest, angle, p, flip);
	}
*/

//void ImageWithFrames::update()
//{
//	if (_timer + 50 <= sdlutils().virtualTimer().currTime()) {
//		_timer = sdlutils().virtualTimer().currTime();
//	
//		if (_actFrame.getX() + _width < _texWidthMax) {
//			_actFrame.setX(_actFrame.getX() + _width);
//		}
//		else if (_actFrame.getY() + _height < _texHeigthMax) {
//			_actFrame.setX(0);
//			_actFrame.setY(_actFrame.getY() + _height);
//		}
//		else {
//			_actFrame.set(0, 0);
//		}
//	
//	}
//}

void ImageWithFrames::updateImage() {

	if (_actualFrame < _numFrames) {
		if (_actFrame.getX() + _width < _texWidthMax) {
			_actFrame.setX(_actFrame.getX() + _width);
		}
		else if (_actFrame.getY() + _height < _texHeigthMax) {
			_actFrame.setX(0);
			_actFrame.setY(_actFrame.getY() + _height);
		}
		else {
			_actFrame.set(_initialFil, _initialCol);
		}
	}
}
