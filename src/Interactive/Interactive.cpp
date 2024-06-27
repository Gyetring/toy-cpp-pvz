#include "Interactive.hpp"

<<<<<<< HEAD
Interactive::Interactive(ImageID img, int x, int y, LayerID layer,
    int width,int height, AnimID animID, pGameWorld manager)
    : GameObject(img, x, y, layer, width, height, animID)
        , mManager(manager) {}

void Interactive::OnClick()
{
    if (mManager) mManager->notifyMeClicked(std::static_pointer_cast<Interactive>(shared_from_this()));
}

OneLawn::OneLawn(int xGrid, int yGrid, pGameWorld manager)
    : Interactive(IMGID_NONE, FIRST_ROW_CENTER + xGrid * LAWN_GRID_WIDTH,
        FIRST_COL_CENTER + yGrid * LAWN_GRID_HEIGHT,LAYER_LAWN_AND_SEED,
        LAWN_GRID_WIDTH,LAWN_GRID_HEIGHT,ANIMID_NO_ANIMATION, manager),
    mXGrid(xGrid), mYGrid(yGrid){}

void OneLawn::Update(){}

int OneLawn::getXGrid()const { return mXGrid; }
int OneLawn::getYGrid()const { return mYGrid; }

bool OneLawn::isOccupied()const {
    auto& objects = mManager->getObjects();
    for (auto& object : objects) {
        if (object->getType() == TID_PLANT && inMyDomain(object))
=======
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
>>>>>>> refined
            return true;
    }
    return false;
}

<<<<<<< HEAD
TYPE_ID OneLawn::getType() const{ return TID_LAWN; }

bool OneLawn::inMyDomain(const std::shared_ptr<GameObject> other) const {
    int x = other->GetX();
    int y = other->GetY();
    int x0 = GetX();
    int y0 = GetY();
    int rx = GetWidth() / 2;
    int ry = GetHeight() / 2;
    return x >= x0 - rx && x <= x0 + rx && y >= y0 - rx && y <= y0 + rx;
}

Seed::Seed(ImageID img, int serial, int cost,int coolDown,  pGameWorld manager)
    :Interactive(img,FIRST_SERIAL_X+serial*SERIAL_WIDTH,FIRST_SERIAL_Y,
        LAYER_LAWN_AND_SEED,SERIAL_WIDTH,SERIAL_HEIGHT,ANIMID_NO_ANIMATION,manager),
    mCost(cost),mCoolDown(coolDown){}

TYPE_ID Seed::getType() const{ return TID_SEED; }

SunFlowerSeed::SunFlowerSeed(pGameWorld manager)
    :Seed(IMGID_SEED_SUNFLOWER,SUNFLOWER_SERIAL,SUNFLOWER_COST,SUNFLOWER_COOLDOWN,manager){}

void SunFlowerSeed::Update(){}

bool SunFlowerSeed::askPlant(std::shared_ptr<OneLawn> lawn)
{
    return mManager->tryPlant(lawn, std::make_shared<SunFlower>
        (lawn->getXGrid(), lawn->getYGrid(), mManager));
}

PeaShooterSeed::PeaShooterSeed(pGameWorld manager) 
    :Seed(IMGID_SEED_PEASHOOTER, PEASHOOTER_SERIAL, PEASHOOTER_COST, PEASHOOTER_COOLDOWN, manager) {}

void PeaShooterSeed::Update(){}

bool PeaShooterSeed::askPlant(std::shared_ptr<OneLawn> lawn)
{
    return mManager->tryPlant(lawn, std::make_shared<PeaShooter>
        (lawn->getXGrid(), lawn->getYGrid(), mManager));
}


CoolDownMask::CoolDownMask(int x, int y, int time)
    :GameObject(IMGID_COOLDOWN_MASK, x, y, LAYER_COOLDOWN_MASK, SERIAL_WIDTH,
        SERIAL_HEIGHT, ANIMID_NO_ANIMATION),mTimeLeft(time) {}

void CoolDownMask::OnClick() {}

void CoolDownMask::Update(){
    if (mLife) {
        if (mTimeLeft <= 0) mLife = false;
        else mTimeLeft--;
    }
}

TYPE_ID CoolDownMask::getType() const { return TID_COOLDOWN; }



Sun::Sun(int xStart, int yStart,int moveDuration, pGameWorld manager)
    :Interactive(IMGID_SUN, xStart, yStart,LAYER_SUN,
        SUN_WIDTH, SUN_HEIGHT,ANIMID_IDLE_ANIM, manager),
    gain(SUN_GAIN), startPoint(xStart,yStart), moveTick(0),mMoveDuration(moveDuration) {}

TYPE_ID Sun::getType() const { return TID_SUN; }

Coordinate Sun::orbitNextCoord() { return startPoint; }


SunFromFlower::SunFromFlower(int xStart, int yStart, pGameWorld manager)
    :Sun(xStart, yStart,SUN_FROM_FLOWER_TIME,manager) {}

Coordinate SunFromFlower::orbitNextCoord()
{
    int x = - moveTick * SUN_FROM_FLOWER_VELOCITY;
    return { x +startPoint.first, -x * x/4 - 5 * x +startPoint.second };
=======
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
>>>>>>> refined
}

void Sun::Update()
{
<<<<<<< HEAD
    if (moveTick < mMoveDuration) {
        Coordinate next(orbitNextCoord());
        MoveTo(next.first, next.second);
        moveTick++;
    }
}

SunFromSky::SunFromSky(int xStart, int yStart, pGameWorld manager)
    :Sun(xStart, yStart,SUN_FROM_SKY_TIME, manager){}

Coordinate SunFromSky::orbitNextCoord()
{
    int y = -moveTick * SUN_FROM_SKY_VELOCITY;
    return { startPoint.first,y + startPoint.second };
}

Shovel::Shovel(pGameWorld manager)
    :Interactive(IMGID_SHOVEL,600,564,LAYER_LAWN_AND_SEED,
        SHOVEL_WIDTH,SHOVEL_HEIGHT,ANIMID_NO_ANIMATION,manager){}

void Shovel::OnClick()
{
    if (mManager) mManager->notifyMeClicked(std::static_pointer_cast<Interactive>(shared_from_this()));
}

void Shovel::Update(){}

TYPE_ID Shovel::getType() const
{
    return TID_SHOVEL;
}
bool Shovel::askRemove(std::shared_ptr<OneLawn> lawn) {
    return mManager->tryRemove(lawn);
}

WallNutSeed::WallNutSeed(pGameWorld manager)
    :Seed(IMGID_SEED_WALLNUT, WALLNUT_SERIAL, WALLNUT_COST, WALLNUT_COOLDOWN, manager) {}

void WallNutSeed::Update(){}

bool WallNutSeed::askPlant(std::shared_ptr<OneLawn> lawn)
{
    return mManager->tryPlant(lawn, std::make_shared<WallNut>
        (lawn->getXGrid(), lawn->getYGrid(), mManager));
}

CherryBombSeed::CherryBombSeed(pGameWorld manager)
    :Seed(IMGID_SEED_CHERRY_BOMB,CHERRYBOMB_SERIAL,CHERRYBOMB_COST,CHERRYBOMB_COOLDOWN,manager){}

void CherryBombSeed::Update(){}

bool CherryBombSeed::askPlant(std::shared_ptr<OneLawn> lawn)
{
    return mManager->tryPlant(lawn, std::make_shared<CherryBomb>
        (lawn->getXGrid(), lawn->getYGrid(), mManager));
}
=======
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


>>>>>>> refined
