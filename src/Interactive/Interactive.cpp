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
    : Interactive(IMGID_PEA, FIRST_ROW_CENTER + xGrid * LAWN_GRID_WIDTH,
        FIRST_COL_CENTER + yGrid * LAWN_GRID_HEIGHT,LAYER_LAWN_AND_SEED,
        LAWN_GRID_WIDTH,LAWN_GRID_HEIGHT,ANIMID_NO_ANIMATION, manager),
    mXGrid(xGrid), mYGrid(yGrid),mOccupied(false) {}

void OneLawn::Update(){}

int OneLawn::getXGrid()const { return mXGrid; }
int OneLawn::getYGrid()const { return mYGrid; }

bool OneLawn::isOccupied()const { return mOccupied; }

void OneLawn::setOccupied(bool state) { mOccupied = state;}

TYPE_ID OneLawn::getType() const{ return TID_LAWN; }

Seed::Seed(ImageID img, int serial, int cost, int coolDown,  pGameWorld manager)
    :Interactive(img,FIRST_SERIAL_X+serial*SERIAL_WIDTH,FIRST_SERIAL_Y,
        LAYER_LAWN_AND_SEED,SERIAL_WIDTH,SERIAL_HEIGHT,ANIMID_NO_ANIMATION,manager),
    mCost(cost),mTimeLeft(coolDown){}

TYPE_ID Seed::getType() const{ return TID_SEED; }

SunFlowerSeed::SunFlowerSeed(pGameWorld manager)
    :Seed(IMGID_SEED_SUNFLOWER,SUNFLOWER_SERIAL,SUNFLOWER_COST,
        SUNFLOWER_COOLDOWN,manager){}

void SunFlowerSeed::Update(){}

Sun::Sun(int xStart, int yStart, pGameWorld manager)
    :Interactive(IMGID_SUN, xStart, yStart,LAYER_SUN,
        SUN_WIDTH, SUN_HEIGHT,ANIMID_IDLE_ANIM, manager),
    gain(SUN_GAIN), startPoint(xStart,yStart), moveTick(0) {}

TYPE_ID Sun::getType() const { return TID_SUN; }

Coordinate Sun::orbitNextCoord() { return startPoint; }


SunFromFlower::SunFromFlower(int xStart, int yStart, pGameWorld manager)
    :Sun(xStart, yStart, manager) {}

Coordinate SunFromFlower::orbitNextCoord()
{
    int x = - moveTick * SUN_FROM_FLOWER_VELOCITY;
    return { x +startPoint.first, -x * x/4 - 5 * x +startPoint.second };
}

void Sun::Update()
{
    if (moveTick < SUN_FROM_FLOWER_TIME) {
        Coordinate next(orbitNextCoord());
        MoveTo(next.first, next.second);
        moveTick++;
    }
}

SunFromSky::SunFromSky(int xStart, int yStart, pGameWorld manager)
    :Sun(xStart, yStart, manager){}

Coordinate SunFromSky::orbitNextCoord()
{
    int y = -moveTick * SUN_FROM_SKY_VELOCITY;
    return { startPoint.first,y + startPoint.second };
}
