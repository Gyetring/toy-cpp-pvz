#ifndef ENTITY_HPP__
#define ENTITY_HPP__

#include "GameObject.hpp"
#include "GameWorld.hpp"
#include "Interactive.hpp"

class Entity : public GameObject {
protected:
    int mHP;;
    void updateExist() { if (mHP <= 0) kill(); }

public:
    Entity(ImageID imageID, int x, int y, LayerID layer,
        AnimID animID, int hp, int width, int height, pGameWorld manager)
        :GameObject(imageID, x, y, layer, width, height, animID,manager),
        mHP(hp){}
    void OnClick() override {}
};

const int PLANT_WIDTH = 100;
const int PLANT_HEIGHT = 70;

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

#endif // !ENTITY_HPP__
