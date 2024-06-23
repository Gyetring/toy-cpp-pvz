#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "WorldBase.hpp"

#include "GameObject.hpp"
#include "Interactive.hpp"

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

    void tryPlant(std::shared_ptr<OneLawn>,std::shared_ptr<Seed>);

    void notifyMeClicked(std::shared_ptr<Interactive>);



private:
    std::list<std::shared_ptr<GameObject>> mObjects;
    std::shared_ptr<Interactive> mHand=nullptr;

};

#endif // !GAMEWORLD_HPP__