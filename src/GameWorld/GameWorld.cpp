#include "GameWorld.hpp"

GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::Init()
{
    objects.emplace_back(std::make_shared<BackGround>());
}

LevelStatus GameWorld::Update()
{
    for (auto& object : objects)
        object->Update();
    return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
}
