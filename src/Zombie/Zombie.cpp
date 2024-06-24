#include "Zombie.hpp"

Zombie::Zombie(ImageID img, int row, int hp, int velocity, pGameWorld manager,int hit)
	:Entity(img,ZOMBIE_START_X,FIRST_ROW_CENTER+row*LAWN_GRID_HEIGHT,
		LAYER_ZOMBIE,ANIMID_WALK_ANIM,hp,ZOMBIE_WIDTH,ZOMBIE_HEIGHT,manager),
	mVelocity(velocity),mHit(hit),mEating(false) {}

bool Zombie::askHit(std::shared_ptr<Entity> other, int hit)
{
	return mManager->tryHit(other,hit);
}

void Zombie::Update()
{
	updateLife();
		auto& objects = mManager->getObjects();
		for (const auto& object : objects) {
			if (object->getType() == TID_PLANT) {
				auto target = std::static_pointer_cast<Entity>(object);
				if (target->inMyDomain(std::static_pointer_cast<Entity>(shared_from_this())))
				{
					if (askHit(target, mHit) && !mEating)
					{
						PlayAnimation(ANIMID_EAT_ANIM);
						mEating = true;
					}
					return;
				}
			}
		}
		if(mEating)
		{
			PlayAnimation(ANIMID_WALK_ANIM);
			mEating = false;
		}
		MoveTo(GetX() - mVelocity, GetY());
}

TYPE_ID Zombie::getType() const
{
	return TID_ZOMBIE;
}

RegularZombie::RegularZombie(int row,pGameWorld manager): Zombie(IMGID_REGULAR_ZOMBIE,row,
	REGULAR_ZOMBIE_HP,REGULAR_ZOMBIE_VELOCITY,manager,REGULAR_ZOMBIE_HIT){}
