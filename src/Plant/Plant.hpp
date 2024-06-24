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
    Plant(ImageID img, int xGrid, int yGrid, int hp, int cost,int timeLeft,pGameWorld manager);
    TYPE_ID getType() const override;
    bool askHit(std::shared_ptr<Entity> other,int hit) override;

};

class SunFlower : public Plant {
public:
    SunFlower(int xGrid, int yGrid, pGameWorld manager);
    void OnClick() override;
    void Update() override;
};

class PeaShooter:public Plant{
public:
    PeaShooter(int xGrid, int yGrid, pGameWorld manager);
    void OnClick() override;
    void Update() override;
};
#endif //! PLANT_HPP__