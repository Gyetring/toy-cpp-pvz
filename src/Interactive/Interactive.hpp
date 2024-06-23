#ifndef INTERACTIVE_HPP__
#define INTERACTIVE_HPP__

#include "GameObject.hpp"
#include "GameWorld.hpp"


class Interactive : public GameObject {
protected:
    pGameWorld mManager;

public:
    Interactive(ImageID img, int x, int y,LayerID layer, int width, int height,AnimID animID, 
        pGameWorld manager);
    void OnClick() override;

};

class OneLawn : public Interactive {
private:
    int mXGrid;
    int mYGrid;
    bool mOccupied;

public:
    OneLawn(int xGrid, int yGrid, pGameWorld manager);
    void Update() override;

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

using Coordinate = std::pair<int, int>;

class Sun : public Interactive {
protected:
    Coordinate startPoint;
    int moveTick;

public:
    const int gain; //because it is trivial and const
    Sun(int xStart, int yStart, pGameWorld manager);
    TYPE_ID getType() const override;
    virtual Coordinate orbitNextCoord();
    void Update()override;
};

class SunFromFlower :public Sun {
public:
    SunFromFlower(int xStart, int yStart, pGameWorld manager);
    Coordinate orbitNextCoord() override;
};

class SunFromSky :public Sun {
public:
    SunFromSky(int xStart, int yStart, pGameWorld manager);
    Coordinate orbitNextCoord() override;
};


#endif // !INTERACTIVE_HPP__