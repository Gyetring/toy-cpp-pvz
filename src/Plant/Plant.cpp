#include "Plant.hpp"

Plant::Plant(ImageID img, int xGrid, int yGrid, int hp,int cost,int timeLeft,pGameWorld manager)
    :Entity(img, FIRST_ROW_CENTER + xGrid * LAWN_GRID_WIDTH,
    FIRST_COL_CENTER + yGrid * LAWN_GRID_HEIGHT, LAYER_PLANTS,ANIMID_IDLE_ANIM,
        hp,PLANT_WIDTH,PLANT_HEIGHT,manager),mCost(cost),mTimeLeft(timeLeft) {}

TYPE_ID Plant::getType() const { return TID_PLANT; }

bool Plant::askHit(std::shared_ptr<Entity> other, int hit)
{
    return mManager->tryHit(other,hit);
}

SunFlower::SunFlower(int xGrid, int yGrid,pGameWorld manager) 
    : Plant(IMGID_SUNFLOWER, xGrid, yGrid, 300, SUNFLOWER_COST, randInt(90, 300),manager){}
void SunFlower::OnClick(){}
void SunFlower::Update(){
    updateLife();
    if (mTimeLeft > 0) mTimeLeft--;
    else {
        mManager->sunflowerNotifyMe(GetX(), GetY());
        mTimeLeft += randInt(600, 750);
    }
}

PeaShooter::PeaShooter(int xGrid, int yGrid, pGameWorld manager)
    :Plant(IMGID_PEASHOOTER, xGrid, yGrid, 300, PEASHOOTER_COST, randInt(40, 45), manager){}
void PeaShooter::OnClick(){}

void PeaShooter::Update()
{
    updateLife();
    if (mTimeLeft > 0) mTimeLeft--;
    else {
        mTimeLeft += randInt(40, 45);
        std::cout << "shoot" << std::endl;
    }
}

