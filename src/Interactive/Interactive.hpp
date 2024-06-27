#ifndef INTERACTIVE_HPP__
#define INTERACTIVE_HPP__

#include "GameObject.hpp"
#include "GameWorld.hpp"
#include "Entity.hpp"

class Plant;//!!!


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

    GameObjType getType() const override { return GameObjType::Lawn; }

};



class Seed : public Interactive {
protected:
    const int mCost;
    const int mCoolDown;

public:
    Seed(ImageID img, int serial, int cost, int coolDown, pGameWorld manager)
        :Interactive(
            img,
            FIRST_SERIAL_X + serial * SERIAL_WIDTH,
            FIRST_SERIAL_Y,
            LAYER_INTERACTIVE,
            SERIAL_WIDTH, SERIAL_HEIGHT,
            ANIMID_NO_ANIMATION, manager
        ),mCost(cost),mCoolDown(coolDown){}
    GameObjType getType() const override { return GameObjType::Seed; }

    void Update() override{}

    int getCost() const { return mCost; }
    int getCoolDown() const { return mCoolDown; }

    virtual std::shared_ptr<Plant> generate(std::shared_ptr<Lawn>) const = 0;
};

class SunflowerSeed : public Seed {
public:
    SunflowerSeed(pGameWorld manager)
        :Seed(IMGID_SEED_SUNFLOWER, SUNFLOWER_SERIAL,
            SUNFLOWER_COST, SUNFLOWER_COOLDOWN, manager) {}
    std::shared_ptr<Plant> generate(std::shared_ptr<Lawn>) const override;
};

class PeaShooterSeed :public Seed {
public:
    PeaShooterSeed(pGameWorld manager)
        :Seed(IMGID_SEED_PEASHOOTER, PEASHOOTER_SERIAL,
            PEASHOOTER_COST, PEASHOOTER_COOLDOWN, manager){}

    std::shared_ptr<Plant> generate(std::shared_ptr<Lawn>) const override;
};

class WallNutSeed :public Seed {
public:
    WallNutSeed(pGameWorld manager)
        :Seed(IMGID_SEED_WALLNUT, WALLNUT_SERIAL, WALLNUT_COST, WALLNUT_COOLDOWN, manager) {}
    std::shared_ptr<Plant> generate(std::shared_ptr<Lawn>) const override;
};

class CherryBombSeed :public Seed {
public:
    CherryBombSeed(pGameWorld manager)
        :Seed(IMGID_SEED_CHERRY_BOMB, CHERRYBOMB_SERIAL, CHERRYBOMB_COST, CHERRYBOMB_COOLDOWN, manager) {}
    std::shared_ptr<Plant> generate(std::shared_ptr<Lawn>) const override;
};


class Sun : public Interactive {
protected:
    Coordinate mStartPoint;
    int mMoveTick;
    int mMoveDuration;
    const int gain;

public:
    Sun(int xStart, int yStart, int moveDuration, pGameWorld manager)
        :Interactive(IMGID_SUN, xStart, yStart, LAYER_SUN,
            SUN_WIDTH, SUN_HEIGHT, ANIMID_IDLE_ANIM, manager),
        gain(SUN_GAIN), mStartPoint(xStart, yStart), mMoveTick(0), mMoveDuration(moveDuration){}
    GameObjType getType() const override { return GameObjType::Sun; }
    virtual Coordinate orbitNextCoord() const;
    void Update()override;
};


class Shovel : public Interactive {
public:
    Shovel(pGameWorld manager)
        :Interactive(IMGID_SHOVEL,SHOVEL_X,SHOVEL_Y,LAYER_INTERACTIVE,
            SHOVEL_WIDTH, SHOVEL_HEIGHT, ANIMID_NO_ANIMATION, manager) {}
    void OnClick()override;
    void Update()override{}
    GameObjType getType()const override { return GameObjType::Shovel; }
};

class SunflowerSun :public Sun {
public:
    SunflowerSun(int xStart, int yStart, pGameWorld manager)
        :Sun(xStart, yStart, SUN_FROM_FLOWER_TIME, manager) {}
    Coordinate orbitNextCoord() const override;
};

class SkySun :public Sun {
public:
    SkySun(int xStart, int yStart, pGameWorld manager)
        :Sun(xStart, yStart, SUN_FROM_SKY_TIME, manager){}
    Coordinate orbitNextCoord() const override;
};

#endif // !INTERACTIVE_HPP__
