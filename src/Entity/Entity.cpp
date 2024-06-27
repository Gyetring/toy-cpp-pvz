#include "Entity.hpp"

void Sunflower::Update()
{
    updateExist();
    if (mShootCounter > 0) mShootCounter--;
    else {
        mManager->generateSunflowerSun(GetX(), GetY());
        mShootCounter += randInt(SUNFLOWER_SHOOTDURATION_MIN,
			SUNFLOWER_SHOOTDURATION_MAX);
    }
}


void Zombie::hit(std::shared_ptr<Entity> other, int hit) const
{
    mManager->MinusHP(other, hit);
}

void Zombie::Update()
{
	updateExist();
	auto& objects = mManager->GetObjects();
	for (const auto& object : objects) 
	{
		if (object->getType() == GameObjType::Plant) 
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

void PeaShooter::Update()
{
	updateExist();
	if (mShootCounter > 0) mShootCounter--;
	else {
		mShootCounter += randInt(PEASHOOTER_SHOOTDURATION_MIN,
			PEASHOOTER_SHOOTDURATION_MAX);
		mManager->generatePea(GetX(), GetY());
	}
}

void WallNut::Update()
{
	updateExist();
	if (!mCracked && mHP < WALLNUT_CRACK) {
		ChangeImage(IMGID_WALLNUT_CRACKED);
	}
}

void CherryBomb::Update()
{
	updateExist();
	if (!mTriggered && mShootCounter > 0) mShootCounter--;
	else {
		mManager->generateExplosion(GetX(), GetY());
		mTriggered = true;
		mHP = -1;
	}
}

