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
    GameObjType getType() const override { return GameObjType::Plant; }

};

class Sunflower : public Plant {
public:
    Sunflower(int xGrid, int yGrid, pGameWorld manager)
        :Plant(IMGID_SUNFLOWER, xGrid, yGrid, SUNFLOWER_HP,
            randInt(SUNFLOWER_SHOOTDURATION_INIT_MIN, SUNFLOWER_SHOOTDURATION_INIT_MAX), manager){}
    void Update() override;
};

class PeaShooter :public Plant {
public:
    PeaShooter(int xGrid, int yGrid, pGameWorld manager)
        :Plant(IMGID_PEASHOOTER, xGrid, yGrid, PEASHOOTER_HP,
            randInt(PEASHOOTER_SHOOTDURATION_MIN, PEASHOOTER_SHOOTDURATION_MAX), manager) {}
    void Update() override;
};


class WallNut :public Plant {
private:
    bool mCracked=false;

public:
    WallNut(int xGrid, int yGrid, pGameWorld manager)
        :Plant(IMGID_WALLNUT, xGrid, yGrid, WALLNUT_HP,  NO_SHOOT_DURATION, manager){}
    void Update() override;
};

class CherryBomb :public Plant {
private:
    bool mTriggered;

public:
    CherryBomb(int xGrid, int yGrid, pGameWorld manager)
        :Plant(IMGID_CHERRY_BOMB, xGrid, yGrid, CHERRYBOMB_HP, CHERRYBOMB_DELAY, manager),
        mTriggered(false) {}
    void Update() override;
};



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
    void hit(std::shared_ptr<Entity> other, int hit) const;
    void Update() override;
    GameObjType getType()const override { return GameObjType::Zombie; }
};

class RegularZombie :public Zombie {
public:
    RegularZombie(int row, pGameWorld manager)
        : Zombie(IMGID_REGULAR_ZOMBIE, row,
            REGULAR_ZOMBIE_HP, REGULAR_ZOMBIE_VELOCITY, manager, REGULAR_ZOMBIE_HIT) {}
};

#endif // !ENTITY_HPP__
