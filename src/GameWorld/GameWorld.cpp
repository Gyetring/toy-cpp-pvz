#include "GameWorld.hpp"

GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::Init()
{
    mObjects.emplace_back(std::make_shared<BackGround>());
    for(int i=0;i<9;++i)
        for(int j=0;j<5;++j)
            mObjects.emplace_back(std::make_shared<OneLawn>(i,j,shared_from_this()));
}

LevelStatus GameWorld::Update()
{
    for (auto &object : mObjects)
        object->Update();
    return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
}
/*
void GameWorld::notifyMeClicked(std::shared_ptr<GameObject> gameObjectPtr) {
    //TODO
    auto position = std::static_pointer_cast<OneLawn> (gameObjectPtr);
    mObjects.emplace_back(std::make_shared<Plant>(
        position->getXGrid(), position->getYGrid()));}*/

