#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include "ObjectBase.hpp"
#include "utils.hpp"

class GameWorld;
using pGameWorld = std::shared_ptr<GameWorld>;

enum class GameObjType
{
    Background,
    Lawn,
    Plant,
    Seed,
    Sun,
    CoolDown,
    Zombie,
    Projectile,
    Shovel
};



class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject>
{
public:
    using std::enable_shared_from_this<GameObject>::shared_from_this;
    virtual GameObjType getType() const = 0;
    void kill();
    bool exists() const;
    bool inMyDomain(const std::shared_ptr<GameObject> other) const;

private:
    bool mExist = true;

protected:
    pGameWorld mManager;

    GameObject(ImageID imageID, int x, int y, LayerID layer,
        int width, int height,AnimID animID, pGameWorld manager) 
        : ObjectBase(imageID, x, y, layer, width, height, animID),mManager(manager) {}

};




#endif // !GAMEOBJECT_HPP__