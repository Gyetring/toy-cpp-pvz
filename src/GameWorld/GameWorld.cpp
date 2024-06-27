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
        AddObject(std::make_shared<SkySun>(randInt(SKYSUN_START_LEFT, SKYSUN_START_RIGHT),
            randInt(SKYSUN_START_DOWN, SKYSUN_START_UP), shared_from_this()));
        mSkyTimer = randInt(SKYTIMER_MIN, SKYTIMER_MAX);
    }
    if (mZombieTimer >= 0)
    {
        mZombieTimer--;
    }
    else
    {
        AddObject(std::make_shared<RegularZombie>(randInt(0, 4), shared_from_this()));
        mZombieTimer = randInt(ZOMBIETIMER_MIN, ZOMBIETIMER_MAX);
    }
    for (auto& object : mObjects)
    {
        object->Update();
        if (object->getType() == GameObjType::Zombie && object->GetX() <= ZOMBIE_PASS_X)
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
    SetSun(INIT_SUN_NUM);
}

void GameWorld::NotifyMeClicked(std::shared_ptr<Interactive> interactive)
{   
    if (interactive) {
        switch (interactive->getType())
        {
        case GameObjType::Seed:
        {
            mHand = interactive;
            break;
        }
        case GameObjType::Lawn:
        {
            auto lawn = std::static_pointer_cast<Lawn>(interactive);
            if (mHand)
            {
                if (mHand->getType() == GameObjType::Seed)
                {
                    auto seed = std::static_pointer_cast<Seed>(mHand);
                    
                    if (seed->getCost() <= mSunNum&& !lawn->isOccupied())
                    {
                            AddObject(seed->generate(lawn));
                            AddObject(std::make_shared<CoolDownMask>(seed->GetX(), seed->GetY(),
                                seed->getCoolDown(), shared_from_this()));
                            SetSun(GetSun() - seed->getCost());
                            
                    }
                }
                else if (mHand->getType() == GameObjType::Shovel && lawn->isOccupied())
                {
                    ClearLawn(lawn);
                }
                mHand = nullptr;
            }
            break;
        }
        case GameObjType::Sun:
        {
            RmObject(interactive);
            SetSun(GetSun() + SUN_GAIN);
            mHand = nullptr;
            break;
        }
        case GameObjType::Shovel:
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
    if (lawn->isOccupied() && mHand->getType() == GameObjType::Shovel) {
        mObjects.erase(
            std::remove_if(mObjects.begin(), mObjects.end(),
                [&lawn](const std::shared_ptr<GameObject>& obj) {
                    return lawn->inMyDomain(obj) && obj->getType() == GameObjType::Plant;
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
