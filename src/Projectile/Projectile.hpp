#ifndef PROJECTILE_HPP__
#define PROJECTILE_HPP__

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

#endif // !PROJECTILE_HPP__
