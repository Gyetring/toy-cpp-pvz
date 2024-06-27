#include "GameWorld.hpp"

GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::Init()
{
    AddObject(std::make_shared<Background>(shared_from_this()));//this shared_from_this is necessary.
    for (int i = 0; i < GAME_COLS; ++i)
        for (int j = 0; j < GAME_ROWS; ++j)
            AddObject(std::make_shared<Lawn>(i, j, shared_from_this()));
    AddObject(std::make_shared<SunflowerSeed>(shared_from_this()));



}

LevelStatus GameWorld::Update()
{
    if (mSkyTimer >= 0)
    {
        mSkyTimer--;
    }
    else
    {
        AddObject(std::make_shared<SkySun>(randInt(50, WINDOW_WIDTH - 50),
            randInt(50 + WINDOW_HEIGHT, 2 * WINDOW_HEIGHT - 50), shared_from_this()));
        mSkyTimer = randInt(180, 210);
    }

    for (auto& object : mObjects)
        object->Update();
    auto toBeEreased = std::remove_if(mObjects.begin(), mObjects.end(),
        [](std::shared_ptr<GameObject> object) {return
        (!object->exists()) || (object->GetX() < -WINDOW_WIDTH || object->GetX() > 2 * WINDOW_WIDTH)
        || object->GetY() < 0 || object->GetY() > 2 * WINDOW_HEIGHT; });
    mObjects.erase(toBeEreased, mObjects.end());
    return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
}

void GameWorld::NotifyMeClicked(std::shared_ptr<Interactive> interactive)
{
    std::cout << mHand << std::endl;
    
    if (interactive) {
        switch (interactive->getType())
        {
        case TID_SEED:
        {
            std::cout << "catched" << std::endl;
            mHand = interactive;
            break;
        }
        case TID_LAWN:
        {
            auto lawn = std::static_pointer_cast<Lawn>(interactive);
            if (mHand)
            {
                std::cout << "here1" << std::endl;
                if (mHand->getType() == TID_SEED)
                {
                    auto seed = std::static_pointer_cast<Seed>(mHand);
                    
                    if (seed->mCost <= mSunNum&& !lawn->isOccupied())
                    {
                            AddObject(seed->generate(lawn));
                            AddObject(std::make_shared<CoolDownMask>(seed->GetX(), seed->GetY(),
                                seed->mCoolDown,shared_from_this()));
                            SetSun(GetSun() - seed->mCost);
                            mHand = nullptr;
                    }
                }
            }
            break;
        }
        case TID_SUN:
        {
            RmObject(interactive);
            SetSun(GetSun() + SUN_GAIN);
            break;
        }
        case TID_SHOVEL:
        default:
            break;
        }
    }
}

const std::list<std::shared_ptr<GameObject>>& GameWorld::GetObjects() const
{
    return mObjects;
}

void GameWorld::RmObject(std::shared_ptr<GameObject> toBeRemoved)
{
    mObjects.remove_if([toBeRemoved](const std::shared_ptr<GameObject>& object) 
        {return toBeRemoved == object; });
}

int GameWorld::GetSun() const
{
    return mSunNum;
}

void GameWorld::SetSun(int target)
{
    mSunNum = target;
    mSunShow.SetText(std::to_string(mSunNum));
}

void GameWorld::generateSunflowerSun(int x, int y)
{
    AddObject(std::make_shared<SunflowerSun>(x, y, shared_from_this()));
}

void GameWorld::AddObject(std::shared_ptr<GameObject> obj)
{
    mObjects.emplace_back(obj);
}
