#ifndef PROJECTILE_HPP__
#define PROJECTILE_HPP__

#include "Entity.hpp"

class Projectile :public GameObject {
public:

	friend GameWorld;
	
	const int mHit;

	Projectile(ImageID img, int startX, int startY, int width, int height, pGameWorld manager, int hit)
		:GameObject(img, startX, startY, LAYER_PROJECTILES, width, height, ANIMID_NO_ANIMATION,manager),
	mHit(hit){}
	void OnClick() override {}
	void hit(std::shared_ptr<Entity>);
	TYPE_ID getType() const override { return TID_PROJECTILE; }
};

const int PEA_HIT = 50;
const int PEA_VELOCITY = 10;

class Pea :public Projectile {
public:
	Pea(int startX, int startY, pGameWorld manager)
		:Projectile(IMGID_PEA,startX,startY,0,0,manager,PEA_HIT){}
	void Update() override;
};


class Explosion : public Projectile {
private:
	bool mTriggered;
	int mTimeLeft;

public:
	Explosion(int x, int y, pGameWorld manager)
		: Projectile(IMGID_EXPLOSION, x, y,
			3 * LAWN_GRID_WIDTH,
			3 * LAWN_GRID_HEIGHT, manager, 114514),
		mTriggered(false), mTimeLeft(10) {}
	void Update() override;
};

#endif // !PROJECTILE_HPP__
