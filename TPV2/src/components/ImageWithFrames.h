#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
class Transform;
class Texture;


class ImageWithFrames : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::IMAGEWITHFRAMES)

	ImageWithFrames();
	ImageWithFrames(Texture* tex, float width, float height);
	virtual ~ImageWithFrames();

	void setTexture(Texture* tex) {
		_tex = tex;
	}

	void initComponent() override;
	void render() override;
	void update() override;
private:
	Transform* _tr;
	Texture* _tex;

	float _width;
	float _height;

	Vector2D _actFrame;

	float _texWidthMax;
	float _texHeigthMax;

	float _timer;
};

