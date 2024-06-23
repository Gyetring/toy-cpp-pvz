#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include "ObjectBase.hpp"

class GameWorld;
using pGameWorld = std::shared_ptr<GameWorld>;

using TYPE_ID = int;
const TYPE_ID TID_BACKGROUND = 0;
const TYPE_ID TID_LAWN = 1;
const TYPE_ID TID_PLANT = 2;
const TYPE_ID TID_SEED = 3;

class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject>
{
public:
    using std::enable_shared_from_this<GameObject>::shared_from_this;

    virtual TYPE_ID getType() const = 0;

private:
protected:
    GameObject(const ImageID &imageID, const int &x, const int &y, const LayerID &layer,
               const int &width, const int &height, const AnimID &animID) 
        : ObjectBase(imageID, x, y, layer, width, height, animID) {}
};

class BackGround : public GameObject
{
public:
    BackGround() : GameObject(IMGID_BACKGROUND, (WINDOW_WIDTH - 1) / 2, (WINDOW_HEIGHT - 1) / 2,
                              LAYER_BACKGROUND, 0, 0, ANIMID_NO_ANIMATION) {}
    void OnClick() override {}
    void Update() override {}

    TYPE_ID getType() const override { return TID_BACKGROUND; }
};

class Entity : public GameObject {
private:
    int mHP;
public:
    Entity(const ImageID& imageID, const int& x, const int& y, const LayerID& layer,
        const AnimID& animID, const int& hp):GameObject(imageID,x,y,layer,0,0,animID),mHP(hp){}
};

class Plant :public Entity {
public:
    Plant(ImageID img, int xGrid, int yGrid, int hp)
        :Entity(img, FIRST_ROW_CENTER + xGrid * LAWN_GRID_WIDTH,
            FIRST_COL_CENTER + yGrid * LAWN_GRID_HEIGHT, LAYER_PLANTS,
            ANIMID_IDLE_ANIM, hp) {}

    TYPE_ID getType() const override { return TID_PLANT; }
};

class SunFlower : public Plant {
private:
    int mTimeLeft;

public:
    SunFlower(int xGrid, int yGrid) : Plant(IMGID_SUNFLOWER, xGrid, yGrid, 300){}
    void OnClick() override {};
    void Update() override {};
};

#endif // !GAMEOBJECT_HPP__