#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
class Transform;
class Texture;


class ImageWithFrames : public ecs::Component {
public:

	ImageWithFrames();
	ImageWithFrames(Texture* tex, float width, float height, int fil, int col, int numFrames);
	virtual ~ImageWithFrames();

	void setTexture(Texture* tex) {
		_tex = tex;
	}

	Texture* getTexture() {
		return _tex;
	}

	void initComponent() override;
	//void update() override;
	void updateImage();
private:
	Transform* _tr;
	Texture* _tex;

	float _width;
	float _height;

	Vector2D _actFrame;

	float _texWidthMax;
	float _texHeigthMax;


	float _timer;
	int _initialFil;
	int _initialCol;
	int _numFrames;
	int _actualFrame;
};

