#include "Entity.hpp"

void Sunflower::Update()
{
    updateExist();
    if (mShootCounter > 0) mShootCounter--;
    else {
        mManager->generateSunflowerSun(GetX(), GetY());
        mShootCounter += randInt(600, 750);
    }
}
