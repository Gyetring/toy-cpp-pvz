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

    void setOccupied(bool);
    bool isOccupied() const;

    bool inMyDomain(std::shared_ptr<GameObject> other);

    TYPE_ID getType() const override;

};

class CoolDownMask :public GameObject {
private:
    int mTimeLeft;

public:
    CoolDownMask(int x, int y, int time);
    void OnClick() override;
    void Update() override;
    TYPE_ID getType() const override;
};

class Seed : public Interactive {
public:
    const int mCost;//trivial
    const int mCoolDown;//trivial
    Seed(ImageID img, int Serial, int cost, int coolDown, pGameWorld manager);
    TYPE_ID getType() const override;
    virtual bool askPlant(std::shared_ptr<OneLawn>) = 0;
};

class SunFlowerSeed : public Seed {
public:
    SunFlowerSeed(pGameWorld manager);
    void Update() override;
    bool askPlant(std::shared_ptr<OneLawn>) override;
};

class PeaShooterSeed :public Seed {
public:
    PeaShooterSeed(pGameWorld manager);
    void Update() override;
    bool askPlant(std::shared_ptr<OneLawn>) override;
};

class Shovel : public Interactive {
public:
    Shovel(pGameWorld manager);
    void OnClick()override;
    void Update()override;
    TYPE_ID getType()const override;
    bool askRemove(std::shared_ptr<OneLawn>);
};

using Coordinate = std::pair<int, int>;

class Sun : public Interactive {
protected:
    Coordinate startPoint;
    int moveTick;
    int mMoveDuration;

public:
    const int gain; //trivial
    Sun(int xStart, int yStart,int moveDuration, pGameWorld manager);
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