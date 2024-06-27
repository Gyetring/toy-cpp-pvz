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
    AddObject(std::make_shared<PeaShooterSeed>(shared_from_this()));
    AddObject(std::make_shared<WallNutSeed>(shared_from_this()));
    AddObject(std::make_shared<CherryBombSeed>(shared_from_this()));
    AddObject(std::make_shared<Shovel>(shared_from_this()));
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
    if (mZombieTimer >= 0)
    {
        mZombieTimer--;
    }
    else
    {
        AddObject(std::make_shared<RegularZombie>(randInt(0, 4), shared_from_this()));
        mZombieTimer = randInt(300, 400);
    }
    for (auto& object : mObjects)
    {
        object->Update();
        if (object->getType() == TID_ZOMBIE && object->GetX() <= ZOMBIE_PASS_X)
            return LevelStatus::LOSING;

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
    mObjects.erase(mObjects.begin(), mObjects.end());
    SetSun(50);
}

void GameWorld::NotifyMeClicked(std::shared_ptr<Interactive> interactive)
{   
    if (interactive) {
        switch (interactive->getType())
        {
        case TID_SEED:
        {
            mHand = interactive;
            break;
        }
        case TID_LAWN:
        {
            auto lawn = std::static_pointer_cast<Lawn>(interactive);
            if (mHand)
            {
                if (mHand->getType() == TID_SEED)
                {
                    auto seed = std::static_pointer_cast<Seed>(mHand);
                    
                    if (seed->mCost <= mSunNum&& !lawn->isOccupied())
                    {
                            AddObject(seed->generate(lawn));
                            AddObject(std::make_shared<CoolDownMask>(seed->GetX(), seed->GetY(),
                                seed->mCoolDown,shared_from_this()));
                            SetSun(GetSun() - seed->mCost);
                            
                    }
                }
                else if (mHand->getType() == TID_SHOVEL && lawn->isOccupied())
                {
                    ClearLawn(lawn);
                }
                mHand = nullptr;
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
        {
            mHand = interactive;
            break;
        }
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

void GameWorld::ClearLawn(std::shared_ptr<Lawn> lawn)
{
    if (lawn->isOccupied() && mHand->getType() == TID_SHOVEL) {
        mObjects.erase(
            std::remove_if(mObjects.begin(), mObjects.end(),
                [&lawn](const std::shared_ptr<GameObject>& obj) {
                    return lawn->inMyDomain(obj) && obj->getType() == TID_PLANT;
                }),
            mObjects.end());
    }
}

void GameWorld::MinusHP(std::shared_ptr<Entity> target,int hit)
{
    if (target)
        target->mHP -= hit;
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

void GameWorld::generatePea(int x, int y)
{
    AddObject(std::make_shared<Pea>(x, y, shared_from_this()));
}

void GameWorld::generateExplosion(int x, int y)
{
    AddObject(std::make_shared<Explosion>(x, y, shared_from_this()));
}

void GameWorld::AddObject(std::shared_ptr<GameObject> obj)
{
    mObjects.emplace_back(obj);
}
