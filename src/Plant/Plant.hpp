#ifndef PLANT_HPP__
#define PLANT_HPP__

#include "GameObject.hpp"
#include "interactive.hpp"
#include "utils.hpp"

class Plant :public Entity {
protected:
    int mTimeLeft;

public:
    const int mCost;//trivial
    Plant(ImageID img, int xGrid, int yGrid, int hp, int cost,int timeLeft);
    TYPE_ID getType() const override;

};

class SunFlower : public Plant {
private:
    pGameWorld mManager;

public:
    SunFlower(int xGrid, int yGrid, pGameWorld manager);
    void OnClick() override;
    void Update() override;
};

#endif //! PLANT_HPP__