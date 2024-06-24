#ifndef ZOMBIE_HPP__
#define ZOMBIE_HPP__

#include "GameObject.hpp"
#include "Interactive.hpp"

class Zombie : public Entity {
protected:
	int mVelocity;
	int mHit;
	bool mEating;

public:
	Zombie(ImageID img,int row, int hp,int velocity,pGameWorld manager,int hit);
	bool askHit(std::shared_ptr<Entity> other, int hit) override;
	void Update() override;
	TYPE_ID getType()const override;
};

class RegularZombie :public Zombie {
public:
	RegularZombie(int row, pGameWorld manager);
};

#endif // !ZOMBIE_HPP__
