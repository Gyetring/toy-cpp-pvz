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
	void hit(std::shared_ptr<Entity>) const;
	GameObjType getType() const override { return GameObjType::Projectile; }
};


class Pea :public Projectile {
public:
	Pea(int startX, int startY, pGameWorld manager)
		:Projectile(IMGID_PEA,startX,startY, PEA_WIDTH, PEA_HEIGHT,manager,PEA_HIT){}
	void Update() override;
};


class Explosion : public Projectile {
private:
	bool mTriggered;
	int mTimeLeft;

public:
	Explosion(int x, int y, pGameWorld manager)
		: Projectile(IMGID_EXPLOSION, x, y,
			EXPLOSION_WIDTH,
			EXPLOSION_HEIGHT, manager, EXPLOSION_HIT),
		mTriggered(false), mTimeLeft(EXPLOSION_DELAY) {}
	void Update() override;
};

#endif // !PROJECTILE_HPP__
