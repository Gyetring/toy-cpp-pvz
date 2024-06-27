#ifndef ENTITY_HPP__
#define ENTITY_HPP__

#include "GameObject.hpp"
#include "GameWorld.hpp"
#include "Interactive.hpp"

class Entity : public GameObject {
protected:
    int mHP;
    void updateExist() { if (mHP <= 0) kill(); }
    friend GameWorld;

public:
    Entity(ImageID imageID, int x, int y, LayerID layer,
        AnimID animID, int hp, int width, int height, pGameWorld manager)
        :GameObject(imageID, x, y, layer, width, height, animID,manager),
        mHP(hp){}
    void OnClick() override {}
    int getHP() const { return mHP; }
};

const int PLANT_WIDTH = 100;
const int PLANT_HEIGHT = 70;
const int NO_SHOOT_DURATION = 0;

class Plant :public Entity {
protected:
    int mShootCounter;

public:
    Plant(ImageID img, int xGrid, int yGrid, int hp, int shootDuration, pGameWorld manager)
        :Entity(img,
            FIRST_ROW_CENTER + xGrid * LAWN_GRID_WIDTH, 
            FIRST_COL_CENTER + yGrid * LAWN_GRID_HEIGHT, 
            LAYER_PLANTS, ANIMID_IDLE_ANIM,
            hp, PLANT_WIDTH, PLANT_HEIGHT, manager),mShootCounter(shootDuration){}
    TYPE_ID getType() const override { return TID_PLANT; }

};



class Sunflower : public Plant {
public:
    Sunflower(int xGrid, int yGrid, pGameWorld manager)
        :Plant(IMGID_SUNFLOWER, xGrid, yGrid, 300, randInt(90, 300), manager){}
    void Update() override;
};

class PeaShooter :public Plant {
public:
    PeaShooter(int xGrid, int yGrid, pGameWorld manager)
        :Plant(IMGID_PEASHOOTER, xGrid, yGrid, 300, randInt(40, 45), manager) {}
    void Update() override;
};


class WallNut :public Plant {
private:
    bool mCracked=false;

public:
    WallNut(int xGrid, int yGrid, pGameWorld manager)
        :Plant(IMGID_WALLNUT, xGrid, yGrid, 4000,  NO_SHOOT_DURATION, manager){}
    void Update() override;
};

class CherryBomb :public Plant {
private:
    bool mTriggered;

public:
    CherryBomb(int xGrid, int yGrid, pGameWorld manager)
        :Plant(IMGID_CHERRY_BOMB, xGrid, yGrid, 10000, 10, manager), mTriggered(false) {}

    void Update() override;
};

const int ZOMBIE_WIDTH = 40;
const int ZOMBIE_HEIGHT = 70;
const int ZOMBIE_START_X = WINDOW_WIDTH + 25;
const int ZOMBIE_PASS_X = -25;

class Zombie : public Entity {
protected:
    int mVelocity;
    int mHit;
    bool mEating;

public:
    Zombie(ImageID img, int row, int hp, int velocity, pGameWorld manager, int hit)
        :  Entity(img, ZOMBIE_START_X, FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT,
            LAYER_ZOMBIE, ANIMID_WALK_ANIM, hp, ZOMBIE_WIDTH, ZOMBIE_HEIGHT, manager),
        mVelocity(velocity), mHit(hit), mEating(false) {}
    void hit(std::shared_ptr<Entity> other, int hit);
    void Update() override;
    TYPE_ID getType()const override { return TID_ZOMBIE; }
};

const int REGULAR_ZOMBIE_VELOCITY = 1;
const int REGULAR_ZOMBIE_HIT = 2;
const int REGULAR_ZOMBIE_HP = 190;

class RegularZombie :public Zombie {
public:
    RegularZombie(int row, pGameWorld manager)
        : Zombie(IMGID_REGULAR_ZOMBIE, row,
            REGULAR_ZOMBIE_HP, REGULAR_ZOMBIE_VELOCITY, manager, REGULAR_ZOMBIE_HIT) {}
};

#endif // !ENTITY_HPP__
