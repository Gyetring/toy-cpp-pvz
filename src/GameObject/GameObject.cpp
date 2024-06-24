#include "GameObject.hpp"

// Your everything begins from here.

bool GameObject::lifeStatus() const{	return mLife;}

GameObject::GameObject(const ImageID& imageID, const int& x, const int& y, const LayerID& layer,
	const int& width, const int& height, const AnimID& animID) 
	: ObjectBase(imageID, x, y, layer, width, height, animID),mLife(true) {}

BackGround::BackGround() : GameObject(IMGID_BACKGROUND, (WINDOW_WIDTH - 1) / 2, (WINDOW_HEIGHT - 1) / 2,
	LAYER_BACKGROUND, 0, 0, ANIMID_NO_ANIMATION) {}

void BackGround::OnClick(){}

void BackGround::Update(){}

TYPE_ID BackGround::getType() const
{
	return TID_BACKGROUND;
}

Entity::Entity( ImageID imageID,  int x,  int y,	 LayerID layer,
	 AnimID animID,  int hp,int width,int height,pGameWorld manager)
	: GameObject(imageID, x, y, layer, 0, 0, animID),
	mHP(hp),mWidth(width),mHeight(height),mManager(manager){}

void Entity::OnClick(){}
void Entity::updateLife() { if (mHP <= 0) mLife = false; }

bool Entity::inMyDomain(std::shared_ptr<Entity> other)
{
	int x = other->GetX();
	int y = other->GetY();
	int x0 = GetX();
	int y0 = GetY();
	int rx = mWidth / 2;
	int ry = mHeight / 2;
	return x >= x0 - rx && x <= x0 + rx && y >= y0 - rx && y <= y0 + rx;
}
