#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "WorldBase.hpp"

class Interactive;
<<<<<<< HEAD
class OneLawn;
class Seed;
class Sun;
class Plant;
class CoolDownMask;
// 这个前向声明疑似不加不行，因为在Interactive中为了使用GameWorld::notifyMeClicked
// 不得不在头文件中引入GameWorld.hpp，而这个GameWorld又要用到这几个类
// 所以不得不前向声明

#include "GameObject.hpp"
#include "Interactive.hpp"
#include "Plant.hpp"
#include "Zombie.hpp"
=======
class Entity;
class Lawn;

using Coordinate = std::pair<int, int>;

#include "GameObject.hpp"
#include "Background.hpp"
#include "Interactive.hpp"
#include "Entity.hpp"
>>>>>>> refined
#include "Projectile.hpp"

#include "TextBase.hpp"
#include "utils.hpp"


class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld>
{
public:
    GameWorld();
    virtual ~GameWorld();

    void Init() override;

    LevelStatus Update() override;

    void CleanUp() override;

<<<<<<< HEAD
    int getSun() const;
    void setSun(int target);

    const std::list<std::shared_ptr<GameObject>> &getObjects() const;

    bool tryPlant(std::shared_ptr<OneLawn>, std::shared_ptr<Plant>);
    bool tryRemove(std::shared_ptr<OneLawn>);
    bool tryHit(std::shared_ptr<Entity> entity, int hit);

    void add(std::shared_ptr<GameObject>);
    void remove(std::shared_ptr<GameObject>);

    void notifyMeClicked(std::shared_ptr<Interactive>);
    void sunflowerNotifyMe(int x, int y);
    void peaShooterNotifyMe(int x, int y);
    void cherryWallNotifyMe(int x, int y);
=======
    void NotifyMeClicked(std::shared_ptr<Interactive>);

    const std::list<std::shared_ptr<GameObject>>& GetObjects() const;
    void RmObject(std::shared_ptr<GameObject> toBeRemoved);
    void ClearLawn(std::shared_ptr<Lawn> lawn);

    void MinusHP(std::shared_ptr<Entity> target,int hit);

    int GetSun()const;
    void SetSun(int target);

    void generateSunflowerSun(int x, int y);
    void generatePea(int x, int y);
    void generateExplosion(int x, int y);
>>>>>>> refined


private:
    std::list<std::shared_ptr<GameObject>> mObjects;
<<<<<<< HEAD
    std::shared_ptr<Interactive> mHand;
    int mSunNum;
    TextBase mSunShow;
    int mSkyTimer;
    int mZombieTimer;
=======
    std::shared_ptr<Interactive> mHand=nullptr;
    int mSunNum = INIT_SUN_NUM;
    TextBase mSunShow{ SUNSHOW_X,SUNSHOW_Y,INIT_SUN_STR };
    int mSkyTimer = randInt(SKYTIMER_INIT_MIN, SKYTIMER_INIT_MAX);
    int mZombieTimer = randInt(ZOMBIETIMER_INIT_MIN, ZOMBIETIMER_INIT_MAX);

    void AddObject(std::shared_ptr<GameObject>);
>>>>>>> refined
};

#endif // !GAMEWORLD_HPP__