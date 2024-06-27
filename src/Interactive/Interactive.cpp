#include "Interactive.hpp"

void Interactive::OnClick()
{
	if (mManager)
		mManager->NotifyMeClicked(std::static_pointer_cast<Interactive>(shared_from_this()));
} 

bool Lawn::isOccupied() const
{
    auto& objects = mManager->GetObjects();
    for (auto& object : objects) {
        if (object->getType() == GameObjType::Plant && inMyDomain(object))
            return true;
    }
    return false;
}

std::shared_ptr<Plant> SunflowerSeed::generate(std::shared_ptr<Lawn> lawn)const
{
    return std::make_shared<Sunflower>(lawn->getXGrid(),lawn->getYGrid(),mManager);
}

std::shared_ptr<Plant> PeaShooterSeed::generate(std::shared_ptr<Lawn> lawn)const
{
    return std::make_shared<PeaShooter>(lawn->getXGrid(), lawn->getYGrid(), mManager);
}

std::shared_ptr<Plant> WallNutSeed::generate(std::shared_ptr<Lawn> lawn)const
{
    return std::make_shared<WallNut>(lawn->getXGrid(), lawn->getYGrid(), mManager);
}

std::shared_ptr<Plant> CherryBombSeed::generate(std::shared_ptr<Lawn> lawn)const
{
    return std::make_shared<CherryBomb>(lawn->getXGrid(), lawn->getYGrid(), mManager);
}

Coordinate Sun::orbitNextCoord() const
{
    return mStartPoint;
}

void Sun::Update()
{
    if (mMoveTick < mMoveDuration) {
        Coordinate next(orbitNextCoord());
        MoveTo(next.first, next.second);
        mMoveTick++;
    }
}

Coordinate SunflowerSun::orbitNextCoord() const
{
    int x = -mMoveTick * SUN_FROM_FLOWER_VELOCITY;
    return { x + mStartPoint.first, -x * x / 4 - 5 * x + mStartPoint.second };
}

Coordinate SkySun::orbitNextCoord() const
{
    int y = -mMoveTick * SUN_FROM_SKY_VELOCITY;
    return { mStartPoint.first,y + mStartPoint.second };
}

void Shovel::OnClick()
{
    if (mManager) mManager->NotifyMeClicked(std::static_pointer_cast<Interactive>(shared_from_this()));
}


