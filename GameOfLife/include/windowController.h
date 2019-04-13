#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "..\\vendor\\Dear_ImGui\\imgui.h"
#include "..\\vendor\\Dear_ImGui\\imgui-SFML.h"

#include "Grid.h"
#include "windowView.h"

namespace GOL {

	class windowController
	{
		Grid *gridModel;
		GOL::windowView *windowView;
	public:
		windowController(Grid*, GOL::windowView*);
		~windowController();

		void startGameOfLife();
	};

}