#include "GameWorld.hpp"

GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::Init()
{
    mObjects.emplace_back(std::make_shared<BackGround>());
    for(int i=0;i<GAME_COLS;++i)
        for(int j=0;j<GAME_ROWS;++j)
            mObjects.emplace_back(std::make_shared<OneLawn>(i,j,shared_from_this()));
    mObjects.emplace_back(std::make_shared<SunFlowerSeed>(shared_from_this()));
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


void GameWorld::notifyMeClicked(std::shared_ptr<Interactive> interactive) {

    // be careful that mHand may be nullptr
    if(interactive)
        switch (interactive->getType())
        {
        case TID_SEED:
        {
        mHand = interactive;
        break;
        }
        case TID_LAWN:
        {
            auto lawn = std::static_pointer_cast<OneLawn>(interactive);
            if (mHand && mHand->getType() == TID_SEED)
            {
                auto seed = std::static_pointer_cast<Seed>(mHand);
                tryPlant(lawn, seed);
            }
            break;
        }
        default:
            break;
        }
}

void GameWorld::tryPlant(std::shared_ptr<OneLawn> lawn,std::shared_ptr<Seed> seed)
{
    if (!lawn->isOccupied() && mHand->getType() == TID_SEED) {
        mObjects.emplace_back(std::make_shared<SunFlower>(lawn->getXGrid(), lawn->getYGrid()));
        lawn->setOccupied(true);
        mHand = nullptr;
    }
}
