#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "WorldBase.hpp"

class Interactive;
class OneLawn;
class Seed;
class Sun;
class Plant;
class CoolDownMask;
// 这个前向声明疑似不加不行，因为在Interactive中为了使用GameWorld::notifyMeClicked
// 不得不在头文件中引入GameWorld.hpp，而这个GameWorld又要用到这几个类
// 所以不得不前向声明

#include "GameObject.hpp"
#include "Sun.hpp"
#include "Interactive.hpp"
#include "Plant.hpp"

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

    int getSun() const;
    void setSun(int target);

    bool tryPlant(std::shared_ptr<OneLawn>, std::shared_ptr<Plant>);

    void add(std::shared_ptr<GameObject>);
    void remove(std::shared_ptr<GameObject>);

    void notifyMeClicked(std::shared_ptr<Interactive>);
    void sunflowerNotifyMe(int x, int y);


private:
    std::list<std::shared_ptr<GameObject>> mObjects;
    std::shared_ptr<Interactive> mHand;
    int mSunNum;
    TextBase mSunShow;
    int mSkyTimer;
};

#endif // !GAMEWORLD_HPP__