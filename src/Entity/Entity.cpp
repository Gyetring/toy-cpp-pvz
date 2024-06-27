#include "Entity.hpp"

void Sunflower::Update()
{
    updateExist();
    if (mShootCounter > 0) mShootCounter--;
    else {
        mManager->generateSunflowerSun(GetX(), GetY());
        mShootCounter += randInt(600, 750);
    }
}


void Zombie::hit(std::shared_ptr<Entity> other, int hit)
{
    mManager->MinusHP(other, hit);
}

void Zombie::Update()
{
	updateExist();
	auto& objects = mManager->GetObjects();
	for (const auto& object : objects) 
	{
		if (object->getType() == TID_PLANT) 
		{
			auto target = std::static_pointer_cast<Entity>(object);
			if (target->inMyDomain(std::static_pointer_cast<Entity>(shared_from_this())))
			{
				hit(target, mHit);
				if(!mEating)
				{
						PlayAnimation(ANIMID_EAT_ANIM);
						mEating = true;
				}
				return;
			}
		}
	}
	if (mEating)
	{
		PlayAnimation(ANIMID_WALK_ANIM);
		mEating = false;
	}
	MoveTo(GetX() - mVelocity, GetY());
}
