#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include "ObjectBase.hpp"

class GameWorld;
using pGameWorld = std::shared_ptr<GameWorld>;

using TYPE_ID = int;
const TYPE_ID TID_BACKGROUND = 0;
const TYPE_ID TID_LAWN = 1;
const TYPE_ID TID_PLANT = 2;
const TYPE_ID TID_SEED = 3;
const TYPE_ID TID_SUN = 4;
const TYPE_ID TID_COOLDOWN = 5;
const TYPE_ID TID_ZOMBIE = 6;
const TYPE_ID TID_PROJECTILE = 7;
const TYPE_ID TID_SHOVEL = 8;



class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject>
{
public:
    using std::enable_shared_from_this<GameObject>::shared_from_this;
    virtual TYPE_ID getType() const = 0;
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