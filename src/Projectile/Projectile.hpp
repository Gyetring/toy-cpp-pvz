#ifndef PROJECTILE_HPP__
#define PROJECTILE_HPP__

<<<<<<< HEAD
#include "GameObject.hpp"
#include "Zombie.hpp"
#include "Plant.hpp"

class Projectile :public GameObject {
protected:
	const int mWidth;
	const int mHeight;
	pGameWorld mManager;
	friend GameWorld;

public:
	const int mHit;
	Projectile(ImageID img, int startX, int startY, int width,int height,pGameWorld manager,int hit);
	bool inMyDomain(std::shared_ptr<Entity> entity);
	void OnClick() override;
	bool askHit(std::shared_ptr<Entity> other);
	TYPE_ID getType()const override;
};

class Pea :public Projectile {
public:
	Pea(int startX, int startY, pGameWorld manager);
	void Update() override;
};

=======
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


>>>>>>> refined
class Explosion : public Projectile {
private:
	bool mTriggered;
	int mTimeLeft;

public:
<<<<<<< HEAD
	Explosion(int x, int y, pGameWorld manager);
=======
	Explosion(int x, int y, pGameWorld manager)
		: Projectile(IMGID_EXPLOSION, x, y,
			EXPLOSION_WIDTH,
			EXPLOSION_HEIGHT, manager, EXPLOSION_HIT),
		mTriggered(false), mTimeLeft(EXPLOSION_DELAY) {}
>>>>>>> refined
	void Update() override;
};

#endif // !PROJECTILE_HPP__
