#ifndef INTERACTIVE_HPP__
#define INTERACTIVE_HPP__

#include "GameObject.hpp"
#include "GameWorld.hpp"


class Interactive : public GameObject {
protected:
    pGameWorld mManager;
public:
    Interactive(ImageID img, int x, int y, int width, int height, pGameWorld manager);
    void OnClick() override;

};

class OneLawn : public Interactive {
private:
    int mXGrid;
    int mYGrid;
    bool mOccupied = false;

public:
    OneLawn(int xGrid, int yGrid, pGameWorld manager);
    void Update() override {}

    int getXGrid()const;
    int getYGrid()const;

    bool isOccupied() const;
    void setOccupied(bool);

    TYPE_ID getType() const override;
};

class Seed : public Interactive {
protected:
    const int mCost;
    int mTimeLeft;

public:
    Seed(ImageID img, int Serial, int cost, int coolDown, pGameWorld manager);

    TYPE_ID getType() const override;
};

class SunFlowerSeed : public Seed {
public:
    SunFlowerSeed(pGameWorld manager);
    void Update() override;
};

#endif // !INTERACTIVE_HPP__