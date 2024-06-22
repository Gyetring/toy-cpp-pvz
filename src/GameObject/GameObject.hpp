#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include "ObjectBase.hpp"

class GameWorld;
// Declares the class name GameWorld so that its pointers can be used.
using pGameWorld = std::shared_ptr<GameWorld>;

class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject>
{
public:
    using std::enable_shared_from_this<GameObject>::shared_from_this;

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
};

class Interactive : public GameObject {
protected:
    pGameWorld mManager;
public:
    Interactive(ImageID img,int x, int y,int width,int height,pGameWorld manager)
        : GameObject(img,x, y,LAYER_UI, width, height, ANIMID_NO_ANIMATION)
        ,mManager(manager) {}
    void OnClick() override { /*mManager->notifyMeClicked(nullptr);*/ }
};

class OneLawn : public Interactive {
private:
    int mXGrid;
    int mYGrid;

public:
    OneLawn(int xGrid,int yGrid, pGameWorld manager)
        : Interactive(IMGID_PEA,FIRST_ROW_CENTER+xGrid*LAWN_GRID_WIDTH,
            FIRST_COL_CENTER+yGrid*LAWN_GRID_HEIGHT,LAWN_GRID_WIDTH,
            LAWN_GRID_HEIGHT ,manager), mXGrid(xGrid), mYGrid(yGrid) {}
    void Update() override {}
    int getXGrid()const { return mXGrid; }
    int getYGrid()const { return mYGrid; }
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
};

class SunFlower : public Plant {
public:
    SunFlower(int xGrid, int yGrid) : Plant(IMGID_SUNFLOWER, xGrid, yGrid, 300){}
};

#endif // !GAMEOBJECT_HPP__