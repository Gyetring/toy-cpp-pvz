#ifndef BACKGROUND_HPP__
#define BACKGROUND_HPP__

#include "GameObject.hpp"


const int BACKGROUND_WIDTH=0;
const int BACKGROUND_HEIGHT=0;

class Background :public GameObject {
public:
	Background(pGameWorld manager) : GameObject(IMGID_BACKGROUND, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LAYER_BACKGROUND,
		BACKGROUND_WIDTH, BACKGROUND_HEIGHT, ANIMID_NO_ANIMATION, manager){}
	void OnClick() override{}
	void Update() override{}
	TYPE_ID getType() const override { return TID_BACKGROUND; }

};


class CoolDownMask :public GameObject {
private:
	int mTimeLeft;

public:
	CoolDownMask(int x, int y, int time,pGameWorld manager)
		: GameObject(IMGID_COOLDOWN_MASK, x, y, LAYER_COOLDOWN_MASK, SERIAL_WIDTH,
			SERIAL_HEIGHT, ANIMID_NO_ANIMATION,manager), mTimeLeft(time) {}
	void OnClick() override{}
	void Update() override;
	TYPE_ID getType() const override { return TID_COOLDOWN; }
};

#endif // !BACKGROUND_HPP__
