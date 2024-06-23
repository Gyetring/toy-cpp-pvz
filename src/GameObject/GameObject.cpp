#include "GameObject.hpp"

// Your everything begins from here.

GameObject::GameObject(const ImageID& imageID, const int& x, const int& y, const LayerID& layer, 
	const int& width, const int& height, const AnimID& animID) 
	: ObjectBase(imageID, x, y, layer, width, height, animID) {}

BackGround::BackGround() : GameObject(IMGID_BACKGROUND, (WINDOW_WIDTH - 1) / 2, (WINDOW_HEIGHT - 1) / 2,
	LAYER_BACKGROUND, 0, 0, ANIMID_NO_ANIMATION) {}

void BackGround::OnClick(){}

void BackGround::Update(){}

TYPE_ID BackGround::getType() const
{
	return TID_BACKGROUND;
}

Entity::Entity(const ImageID& imageID, const int& x, const int& y,
	const LayerID& layer, const AnimID& animID, const int& hp)
	: GameObject(imageID, x, y, layer, 0, 0, animID), mHP(hp){}
