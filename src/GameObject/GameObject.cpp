#include "GameObject.hpp"



void GameObject::kill()
{
	mExist = false;
}

bool GameObject::exists() const
{
	return mExist;
}

bool GameObject::inMyDomain(const std::shared_ptr<GameObject> other) const
{
    int x = other->GetX();
    int y = other->GetY();
    int x0 = GetX();
    int y0 = GetY();
    int rx = GetWidth() / 2;
    int ry = GetHeight() / 2;
    return x >= x0 - rx && x <= x0 + rx && y >= y0 - rx && y <= y0 + rx;
}
