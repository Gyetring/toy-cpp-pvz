#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <memory>
#include "ObjectBase.hpp"
#include "utils.hpp"

class GameWorld;
using pGameWorld = std::shared_ptr<GameWorld>;

<<<<<<< HEAD
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
=======
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


>>>>>>> refined

class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject>
{
public:
    using std::enable_shared_from_this<GameObject>::shared_from_this;
<<<<<<< HEAD
    virtual TYPE_ID getType() const = 0;
    bool lifeStatus() const;
=======
    virtual GameObjType getType() const = 0;
    void kill();
    bool exists() const;
    bool inMyDomain(const std::shared_ptr<GameObject> other) const;
>>>>>>> refined

private:
    bool mExist = true;

protected:
<<<<<<< HEAD
    bool mLife;
    GameObject(const ImageID& imageID, const int& x, const int& y, const LayerID& layer,
        const int& width, const int& height, const AnimID& animID);
};

class BackGround : public GameObject
{
public:
    BackGround();
    void OnClick() override;
    void Update() override;
    TYPE_ID getType() const override;
};

class Entity : public GameObject {
protected:
    int mHP;
    const int mWidth;
    const int mHeight;
    pGameWorld mManager;
    friend GameWorld;
    void updateLife();

public:
    Entity( ImageID imageID,  int x,  int y,  LayerID layer,
         AnimID animID,  int hp,int width,int height,pGameWorld);
    virtual bool askHit(std::shared_ptr<Entity> other, int hit)=0;
    void OnClick() override;
    virtual bool inMyDomain(std::shared_ptr<Entity> other);
};
=======
    pGameWorld mManager;

    GameObject(ImageID imageID, int x, int y, LayerID layer,
        int width, int height,AnimID animID, pGameWorld manager) 
        : ObjectBase(imageID, x, y, layer, width, height, animID),mManager(manager) {}

};



>>>>>>> refined

#endif // !GAMEOBJECT_HPP__