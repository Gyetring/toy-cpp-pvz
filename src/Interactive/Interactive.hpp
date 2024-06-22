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
public:
    OneLawn(int xGrid, int yGrid, pGameWorld manager);
    void Update() override {}
    int getXGrid()const { return mXGrid; }
    int getYGrid()const { return mYGrid; }
};

#endif // !INTERACTIVE_HPP__