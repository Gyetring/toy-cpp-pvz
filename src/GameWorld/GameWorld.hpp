#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "WorldBase.hpp"

class Interactive;
class Entity;
class Lawn;

using Coordinate = std::pair<int, int>;

#include "GameObject.hpp"
#include "Background.hpp"
#include "Interactive.hpp"
#include "Entity.hpp"
#include "Projectile.hpp"

#include "TextBase.hpp"
#include "utils.hpp"

const int SUNSHOW_X = 60;
const int SUNSHOW_Y = 520;

class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld>
{
public:
    // Use shared_from_this() instead of "this" to create a pointer to oneself.
    GameWorld();
    virtual ~GameWorld();

    void Init() override;

    LevelStatus Update() override;

    void CleanUp() override;

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


private:
    std::list<std::shared_ptr<GameObject>> mObjects;
    std::shared_ptr<Interactive> mHand=nullptr;
    int mSunNum = 50;
    TextBase mSunShow{ SUNSHOW_X,SUNSHOW_Y,"50" };
    int mSkyTimer = randInt(180, 210);
    int mZombieTimer = randInt(600, 800);

    void AddObject(std::shared_ptr<GameObject>);
};

#endif // !GAMEWORLD_HPP__
