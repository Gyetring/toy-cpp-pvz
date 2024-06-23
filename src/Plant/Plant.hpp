#ifndef PLANT_HPP__
#define PLANT_HPP__

#include "GameObject.hpp"
#include "utils.hpp"

class Plant :public Entity {
public:
    Plant(ImageID img, int xGrid, int yGrid, int hp);
    TYPE_ID getType() const override;
};

class SunFlower : public Plant {
private:
    int mTimeLeft;

public:
    SunFlower(int xGrid, int yGrid);
    void OnClick() override;
    void Update() override;
};

#endif //! PLANT_HPP__