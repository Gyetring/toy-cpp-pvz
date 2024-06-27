#include "Projectile.hpp"

void Projectile::hit(std::shared_ptr<Entity> target)
{
	mManager->MinusHP(target, mHit);
}

void Pea::Update()
{
	auto& objects = mManager->GetObjects();
	for (const auto& object : objects) {
		if (object->getType() == TID_ZOMBIE) {
			auto potentialTarget = std::static_pointer_cast<Entity>(object);
			if (potentialTarget->inMyDomain(std::static_pointer_cast<Entity>(shared_from_this())))
			{
				hit(potentialTarget);
				kill();
			}
		}
	}
	MoveTo(GetX() + PEA_VELOCITY, GetY());
}

void Explosion::Update()
{
	if (!mTriggered)
	{
		auto& objects = mManager->GetObjects();
		for (const auto& object : objects) {
			if (object->getType() == TID_ZOMBIE) {
				auto potentialTarget = std::static_pointer_cast<Entity>(object);
				if (inMyDomain(potentialTarget))
					hit(potentialTarget);
			}
		}
		mTriggered = true;
	}
	else {
		if (mTimeLeft < 0) kill();
		else mTimeLeft--;
	}
}
