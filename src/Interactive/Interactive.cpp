#include "Interactive.hpp"

Interactive::Interactive(ImageID img, int x, int y, int width, int height, pGameWorld manager)
    : GameObject(img, x, y, LAYER_UI, width, height, ANIMID_NO_ANIMATION)
        , mManager(manager) {}

void Interactive::OnClick()
{
    if (mManager) mManager->notifyMeClicked(std::static_pointer_cast<Interactive>(shared_from_this()));
}

OneLawn::OneLawn(int xGrid, int yGrid, pGameWorld manager) 
    : Interactive(IMGID_PEA, FIRST_ROW_CENTER + xGrid * LAWN_GRID_WIDTH,
    FIRST_COL_CENTER + yGrid * LAWN_GRID_HEIGHT, LAWN_GRID_WIDTH,
    LAWN_GRID_HEIGHT, manager), mXGrid(xGrid), mYGrid(yGrid),mOccupied(false) {}

void OneLawn::Update(){}

int OneLawn::getXGrid()const { return mXGrid; }
int OneLawn::getYGrid()const { return mYGrid; }

bool OneLawn::isOccupied()const { return mOccupied; }

void OneLawn::setOccupied(bool state) { mOccupied = state;}

TYPE_ID OneLawn::getType() const{ return TID_LAWN; }

Seed::Seed(ImageID img, int serial, int cost, int coolDown, pGameWorld manager)
    :Interactive(img,FIRST_SERIAL_X+serial*SERIAL_WIDTH,FIRST_SERIAL_Y,SERIAL_WIDTH,
        SERIAL_HEIGHT,manager), mCost(cost),mTimeLeft(coolDown){}

TYPE_ID Seed::getType() const{ return TID_SEED; }

SunFlowerSeed::SunFlowerSeed(pGameWorld manager)
    :Seed(IMGID_SEED_SUNFLOWER,SUNFLOWER_SERIAL,SUNFLOWER_COST,
        SUNFLOWER_COOLDOWN,manager){}

void SunFlowerSeed::Update(){}
