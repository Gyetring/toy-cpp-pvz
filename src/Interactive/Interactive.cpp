#include "GameObject.hpp"
#include "GameWorld.hpp"
#include "Interactive.hpp"

Interactive::Interactive(ImageID img, int x, int y, int width, int height, pGameWorld manager)
    : GameObject(img, x, y, LAYER_UI, width, height, ANIMID_NO_ANIMATION)
        , mManager(manager) {}

void Interactive::OnClick()
{
    if (mManager) mManager->notifyMeClicked(shared_from_this());
}

OneLawn::OneLawn(int xGrid, int yGrid, pGameWorld manager) 
    : Interactive(IMGID_PEA, FIRST_ROW_CENTER + xGrid * LAWN_GRID_WIDTH,
    FIRST_COL_CENTER + yGrid * LAWN_GRID_HEIGHT, LAWN_GRID_WIDTH,
    LAWN_GRID_HEIGHT, manager), mXGrid(xGrid), mYGrid(yGrid) {}
