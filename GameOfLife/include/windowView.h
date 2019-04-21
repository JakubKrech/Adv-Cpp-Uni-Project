#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "..\\vendor\\Dear_ImGui\\imgui.h"
#include "..\\vendor\\Dear_ImGui\\imgui-SFML.h"

#include "Grid.h"

namespace GOL {

	class windowView
	{
		Grid *grid;

		sf::Event event;
		sf::Clock deltaClock;

		bool showHelpMenu{ false };
		bool showFSPMenu{ true };

		bool paused = true;

		void updateMenu();
		void updateFPSWindow();

	public:
		int frameRate = 60;

		std::unique_ptr<sf::RenderWindow> window;
	
		windowView(Grid*);
		~windowView();

		void updateWindowState();
		void returnToMemento();
	};

}

