#include "Background.hpp"

void CoolDownMask::Update()
{
    if (exists()) {
        if (mTimeLeft <= 0) kill();
        else mTimeLeft--;
    }
}
