#ifndef INTERACTIVE_HPP__
#define INTERACTIVE_HPP__

#include "GameObject.hpp"
#include "GameWorld.hpp"
#include "Entity.hpp"

class Plant;//???


class Interactive : public GameObject {
public:
    Interactive(ImageID img, int x, int y, LayerID layer, int width, int height, AnimID animID,
        pGameWorld manager):GameObject(img,x,y,layer,width,height,animID,manager){}
    void OnClick() override;
};

class Lawn : public Interactive {
private:
    const int mXGrid;
    const int mYGrid;

public:
    Lawn(int xGrid, int yGrid, pGameWorld manager) :Interactive(IMGID_NONE,
        FIRST_ROW_CENTER + xGrid * LAWN_GRID_WIDTH,
        FIRST_COL_CENTER + yGrid * LAWN_GRID_HEIGHT,
        LAYER_INTERACTIVE,
        LAWN_GRID_WIDTH, LAWN_GRID_HEIGHT, ANIMID_NO_ANIMATION, manager),
        mXGrid(xGrid), mYGrid(yGrid) {}
    void Update() override {}

    int getXGrid()const { return mXGrid; }
    int getYGrid()const { return mYGrid; }

    bool isOccupied() const;

    TYPE_ID getType() const override { return TID_LAWN; }

};



class Seed : public Interactive {
public:
    const int mCost;//trivial
    const int mCoolDown;//trivial

    Seed(ImageID img, int serial, int cost, int coolDown, pGameWorld manager)
        :Interactive(
            img,
            FIRST_SERIAL_X + serial * SERIAL_WIDTH,
            FIRST_SERIAL_Y,
            LAYER_INTERACTIVE,
            SERIAL_WIDTH, SERIAL_HEIGHT,
            ANIMID_NO_ANIMATION, manager
        ),mCost(cost),mCoolDown(coolDown){}
    TYPE_ID getType() const override { return TID_SEED; }

    void Update() override{}

    virtual std::shared_ptr<Plant> generate(std::shared_ptr<Lawn>) = 0;
};

const int SUNFLOWER_COOLDOWN = 250;
const int SUNFLOWER_COST = 50;
const int SUNFLOWER_SERIAL = 0;

class SunflowerSeed : public Seed {
public:
    SunflowerSeed(pGameWorld manager)
        :Seed(IMGID_SEED_SUNFLOWER, SUNFLOWER_SERIAL,
            SUNFLOWER_COST, SUNFLOWER_COOLDOWN, manager) {}
    std::shared_ptr<Plant> generate(std::shared_ptr<Lawn>) override;
};

const int PEASHOOTER_SERIAL = 1;
const int PEASHOOTER_COST = 100;
const int PEASHOOTER_COOLDOWN = 250;

class PeaShooterSeed :public Seed {
public:
    PeaShooterSeed(pGameWorld manager)
        :Seed(IMGID_SEED_PEASHOOTER, PEASHOOTER_SERIAL,
            PEASHOOTER_COST, PEASHOOTER_COOLDOWN, manager){}

    std::shared_ptr<Plant> generate(std::shared_ptr<Lawn>) override;
};


const int SUN_WIDTH = 80;
const int SUN_HEIGHT = 80;
const int SUN_GAIN = 25;

class Sun : public Interactive {
protected:
    Coordinate mStartPoint;
    int mMoveTick;
    int mMoveDuration;

public:
    const int gain; //trivial
    Sun(int xStart, int yStart, int moveDuration, pGameWorld manager)
        :Interactive(IMGID_SUN, xStart, yStart, LAYER_SUN,
            SUN_WIDTH, SUN_HEIGHT, ANIMID_IDLE_ANIM, manager),
        gain(SUN_GAIN), mStartPoint(xStart, yStart), mMoveTick(0), mMoveDuration(moveDuration){}
    TYPE_ID getType() const override { return TID_SUN; }
    virtual Coordinate orbitNextCoord();
    void Update()override;
};


const int SUN_FROM_FLOWER_TIME = 10;
const int SUN_FROM_FLOWER_VELOCITY = 2;

class SunflowerSun :public Sun {
public:
    SunflowerSun(int xStart, int yStart, pGameWorld manager)
        :Sun(xStart, yStart, SUN_FROM_FLOWER_TIME, manager) {}
    Coordinate orbitNextCoord() override;
};

const int SUN_FROM_SKY_VELOCITY = 5;
const int SUN_FROM_SKY_TIME = 120;

class SkySun :public Sun {
public:
    SkySun(int xStart, int yStart, pGameWorld manager)
        :Sun(xStart, yStart, SUN_FROM_SKY_TIME, manager){}
    Coordinate orbitNextCoord() override;
};

#endif // !INTERACTIVE_HPP__
