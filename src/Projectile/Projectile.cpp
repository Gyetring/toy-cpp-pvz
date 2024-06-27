#include "Projectile.hpp"

<<<<<<< HEAD

Projectile::Projectile(ImageID img, int startX, int startY,int width,
	int height,pGameWorld manager, int hit)
	:GameObject(img,startX,startY,LAYER_PROJECTILES,width,height,ANIMID_NO_ANIMATION),
	mManager(manager),mWidth(width),mHeight(height),mHit(hit){}

//why this again? Because Projectile is distinct from Entity.
bool Projectile::inMyDomain(std::shared_ptr<Entity> other)
{
	int x = other->GetX();
	int y = other->GetY();
	int x0 = GetX();
	int y0 = GetY();
	int rx = mWidth / 2;
	int ry = mHeight / 2;
	return x >= x0 - rx && x <= x0 + rx && y >= y0 - rx && y <= y0 + rx;
}

void Projectile::OnClick(){}

bool Projectile::askHit(std::shared_ptr<Entity> other)
{
	return mManager->tryHit(other, mHit);
}

TYPE_ID Projectile::getType()const {
	return TID_PROJECTILE;
}

Pea::Pea(int startX, int startY, pGameWorld manager)
	:Projectile(IMGID_PEA,startX,startY,0,0,manager,PEA_HIT){}

void Pea::Update()
{
	auto& objects = mManager->getObjects();
	for (const auto& object : objects) {
		if (object->getType() == TID_ZOMBIE) {
			auto potentialTarget = std::static_pointer_cast<Entity>(object);
			if (potentialTarget->inMyDomain(std::static_pointer_cast<Entity>(shared_from_this())))
			{
				askHit(potentialTarget);
					mLife = false;
				}
			}
		}
	MoveTo(GetX() + PEA_VELOCITY, GetY());
}

Explosion::Explosion(int x, int y, pGameWorld manager)
	: Projectile(IMGID_EXPLOSION, x, y, 3 * LAWN_GRID_WIDTH, 3 * LAWN_GRID_HEIGHT, manager, CHERRYBOMB_HIT),
	mTriggered(false), mTimeLeft(10) {}

void Explosion::Update()
{
	if(!mTriggered)
	{
		auto& objects = mManager->getObjects();
		for (const auto& object : objects) {
			if (object->getType() == TID_ZOMBIE) {
				auto potentialTarget = std::static_pointer_cast<Entity>(object);
				if (inMyDomain(potentialTarget))
					askHit(potentialTarget);
=======
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
}

void Explosion::Update()
{
	if (!mTriggered)
	{
		auto& objects = mManager->GetObjects();
		for (const auto& object : objects) {
			if (object->getType() == GameObjType::Zombie) {
				auto potentialTarget = std::static_pointer_cast<Entity>(object);
				if (inMyDomain(potentialTarget) && exists())
					hit(potentialTarget);
>>>>>>> refined
			}
		}
		mTriggered = true;
	}
	else {
<<<<<<< HEAD
		if (mTimeLeft < 0) mLife = false;
=======
		if (mTimeLeft < 0) kill();
>>>>>>> refined
		else mTimeLeft--;
	}
}
