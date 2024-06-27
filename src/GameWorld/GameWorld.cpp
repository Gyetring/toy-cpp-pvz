#include "GameWorld.hpp"

GameWorld::GameWorld(): mHand(nullptr),mSunNum(50), mSunShow(SUNSHOW_X,SUNSHOW_Y,"50"),
    mSkyTimer(randInt(180,210)),mZombieTimer(randInt(600,800)){}

GameWorld::~GameWorld() {}

void GameWorld::Init()
{
<<<<<<< HEAD
    mObjects.emplace_back(std::make_shared<BackGround>());
    for(int i=0;i<GAME_COLS;++i)
        for(int j=0;j<GAME_ROWS;++j)
            mObjects.emplace_back(std::make_shared<OneLawn>(i,j,shared_from_this()));
    mObjects.emplace_back(std::make_shared<SunFlowerSeed>(shared_from_this()));
    mObjects.emplace_back(std::make_shared<PeaShooterSeed>(shared_from_this()));
    mObjects.emplace_back(std::make_shared<WallNutSeed>(shared_from_this()));
    mObjects.emplace_back(std::make_shared<CherryBombSeed>(shared_from_this()));
    add(std::make_shared<Shovel>(shared_from_this()));
=======
    AddObject(std::make_shared<Background>(shared_from_this()));//this shared_from_this is necessary.
    for (int i = 0; i < GAME_COLS; ++i)
        for (int j = 0; j < GAME_ROWS; ++j)
            AddObject(std::make_shared<Lawn>(i, j, shared_from_this()));
    AddObject(std::make_shared<SunflowerSeed>(shared_from_this()));
    AddObject(std::make_shared<PeaShooterSeed>(shared_from_this()));
    AddObject(std::make_shared<WallNutSeed>(shared_from_this()));
    AddObject(std::make_shared<CherryBombSeed>(shared_from_this()));
    AddObject(std::make_shared<Shovel>(shared_from_this()));
>>>>>>> refined
}

LevelStatus GameWorld::Update()
{
<<<<<<< HEAD
    if (mSkyTimer >= 0) 
    {
        mSkyTimer--;
    }
    else 
    {
        add(std::make_shared<SunFromSky>(randInt(50, WINDOW_WIDTH - 50),
            randInt(50 + WINDOW_HEIGHT, 2 * WINDOW_HEIGHT - 50), shared_from_this()));
        mSkyTimer = randInt(180, 210);
=======
    if (mSkyTimer >= 0)
    {
        mSkyTimer--;
    }
    else
    {
        AddObject(std::make_shared<SkySun>(randInt(SKYSUN_START_LEFT, SKYSUN_START_RIGHT),
            randInt(SKYSUN_START_DOWN, SKYSUN_START_UP), shared_from_this()));
        mSkyTimer = randInt(SKYTIMER_MIN, SKYTIMER_MAX);
>>>>>>> refined
    }
    if (mZombieTimer >= 0)
    {
        mZombieTimer--;
    }
    else
    {
<<<<<<< HEAD
        add(std::make_shared<RegularZombie>(randInt(0, 4), shared_from_this()));
        mZombieTimer = randInt(300, 400);
    }
    for (auto &object : mObjects)
    {
        object->Update();
        if (object->getType() == TID_ZOMBIE && object->GetX() <= ZOMBIE_PASS_X)
            return LevelStatus::LOSING;
        
    }
    auto toBeEreased = std::remove_if(mObjects.begin(), mObjects.end(),
        [](std::shared_ptr<GameObject> object) {return
        (!object->lifeStatus())||(object->GetX()<-WINDOW_WIDTH || object->GetX()>2*WINDOW_WIDTH)
        ||object->GetY()<0||object->GetY()>2*WINDOW_HEIGHT; });
=======
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
>>>>>>> refined
    mObjects.erase(toBeEreased, mObjects.end());
    return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
    mObjects.erase(mObjects.begin(), mObjects.end());
<<<<<<< HEAD
    setSun(50);
=======
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
>>>>>>> refined
}

int GameWorld::getSun()const{return mSunNum;}

void GameWorld::setSun(int target){
    mSunNum = target;
    mSunShow.SetText(std::to_string(mSunNum));
}

const std::list<std::shared_ptr<GameObject>> &GameWorld::getObjects() const
{
    return mObjects;
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
            if (mHand )
            {
                if(mHand->getType() == TID_SEED)
                {
                    auto seed = std::static_pointer_cast<Seed>(mHand);
                    if (seed->mCost <= mSunNum)
                        if (seed->askPlant(lawn))
                            add(std::make_shared<CoolDownMask>(
                                seed->GetX(), seed->GetY(), seed->mCoolDown));
                }
                else if (mHand->getType() == TID_SHOVEL && lawn->isOccupied()) {
                    auto shovel = std::static_pointer_cast<Shovel>(mHand);
                    shovel->askRemove(lawn);
                }
                else {
                    mHand = nullptr;
                }
            }
            break;
        }
        case TID_SUN:
        {
            remove(interactive);
            setSun(getSun() + SUN_GAIN);
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

void GameWorld::sunflowerNotifyMe(int x, int y)
{
    mObjects.emplace_back(std::make_shared<SunFromFlower>(x, y, shared_from_this()));
}

void GameWorld::peaShooterNotifyMe(int x, int y)
{
    add(std::make_shared<Pea>(x, y, shared_from_this()));
}

void GameWorld::cherryWallNotifyMe(int x, int y)
{
    add(std::make_shared<Explosion>(x, y, shared_from_this()));
}

bool GameWorld::tryPlant(std::shared_ptr<OneLawn> lawn,std::shared_ptr<Plant> plant)
{
    if (!lawn->isOccupied() && mHand->getType() == TID_SEED) {
        mObjects.emplace_back(plant);
        setSun(getSun() - plant->mCost);
        mHand = nullptr;
        return true;
    }
    return false;
}

bool GameWorld::tryRemove(std::shared_ptr<OneLawn> lawn)
{
    if (lawn->isOccupied() && mHand->getType() == TID_SHOVEL) {
        mObjects.erase(
            std::remove_if(mObjects.begin(), mObjects.end(),
                [&lawn](const std::shared_ptr<GameObject>& obj) {
                    return lawn->inMyDomain(obj) && obj->getType() == TID_PLANT;
                }),
            mObjects.end());
        mHand = nullptr;
        return true;
    }
    return false;
}

bool GameWorld::tryHit(std::shared_ptr<Entity> entity,int hit)
{

    if (entity) {
        entity->mHP -= hit;
        return true;
    }
    return false;
}

void GameWorld::add(std::shared_ptr<GameObject> toBeAdded)
{
    mObjects.emplace_back(toBeAdded);
}

void GameWorld::remove(std::shared_ptr<GameObject> toBeRemoved)
{
    mObjects.remove_if([toBeRemoved](const std::shared_ptr<GameObject>& object)
        {return toBeRemoved == object; });
}

