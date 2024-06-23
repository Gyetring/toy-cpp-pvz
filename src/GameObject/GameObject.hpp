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

class GameObject : public ObjectBase, public std::enable_shared_from_this<GameObject>
{
public:
    using std::enable_shared_from_this<GameObject>::shared_from_this;
    virtual TYPE_ID getType() const = 0;
    bool lifeStatus() const;

private:
protected:
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
private:
    int mHP;
public:
    Entity(const ImageID& imageID, const int& x, const int& y, const LayerID& layer,
        const AnimID& animID, const int& hp);
};

#endif // !GAMEOBJECT_HPP__