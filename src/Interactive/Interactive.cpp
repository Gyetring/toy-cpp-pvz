#include "Interactive.hpp"

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
    mXGrid(xGrid), mYGrid(yGrid),mOccupied(false) {}

void OneLawn::Update(){}

int OneLawn::getXGrid()const { return mXGrid; }
int OneLawn::getYGrid()const { return mYGrid; }

void OneLawn::setOccupied(bool set) { mOccupied = set; }

bool OneLawn::isOccupied()const { return mOccupied;}

TYPE_ID OneLawn::getType() const{ return TID_LAWN; }

bool OneLawn::inMyDomain(std::shared_ptr<GameObject> other) {
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
}

void Sun::Update()
{
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


