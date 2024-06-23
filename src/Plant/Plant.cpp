#include "Plant.hpp"

Plant::Plant(ImageID img, int xGrid, int yGrid, int hp)
    :Entity(img, FIRST_ROW_CENTER + xGrid * LAWN_GRID_WIDTH,
    FIRST_COL_CENTER + yGrid * LAWN_GRID_HEIGHT, LAYER_PLANTS,
    ANIMID_IDLE_ANIM, hp) {}

TYPE_ID Plant::getType() const { return TID_PLANT; }

SunFlower::SunFlower(int xGrid, int yGrid,pGameWorld manager) 
    : Plant(IMGID_SUNFLOWER, xGrid, yGrid, 300),mTimeLeft(randInt(90,300)),
    mManager(manager){}
void SunFlower::OnClick(){}
void SunFlower::Update(){
    if (mTimeLeft > 0) mTimeLeft--;
    else {
        mManager->sunflowerNotifyMe(GetX(), GetY());
        mTimeLeft += randInt(600, 750);
    }
}
