#include "..\\include\\windowController.h"



GOL::windowController::windowController(Grid *g, GOL::windowView *wV) : gridModel{ g }, windowView{ wV }
{
}


GOL::windowController::~windowController()
{
}

void GOL::windowController::startGameOfLife()
{
	windowView->updateWindowState();
}
