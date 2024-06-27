#include "Projectile.hpp"

void Projectile::hit(std::shared_ptr<Entity> target) const
{
	mManager->MinusHP(target, mHit);
}

void Pea::Update()
{
	//notice that exists() is necessary because kill() will not make it deleted right away.
	if(exists())
	{
		auto& objects = mManager->GetObjects();
		for (const auto& object : objects) {
			if (object->getType() == GameObjType::Zombie) {
				if (object->inMyDomain(shared_from_this()))
				{
					auto potentialTarget = std::static_pointer_cast<Entity>(object);
					hit(potentialTarget);
					kill();
				}
			}
		}
		MoveTo(GetX() + PEA_VELOCITY, GetY());
	}
}

void Explosion::Update()
{
	if (!mTriggered)
	{
		auto& objects = mManager->GetObjects();
		for (const auto& object : objects) {
			if (object->getType() == GameObjType::Zombie) {
				if (inMyDomain(object) && exists())
				{
					auto potentialTarget = std::static_pointer_cast<Entity>(object);
					hit(potentialTarget);
				}
			}
		}
		mTriggered = true;
	}
	else {
		if (mTimeLeft < 0) kill();
		else mTimeLeft--;
	}
}
