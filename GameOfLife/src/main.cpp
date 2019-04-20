#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "..\\vendor\\Dear_ImGui\\imgui.h"
#include "..\\vendor\\Dear_ImGui\\imgui-SFML.h"

#include <vector>
#include <map>
#include <iostream>

#include "..\\include\\Grid.h"
#include "..\\include\\Pattern.h"
#include "..\\include\\windowView.h"
#include "..\\include\\windowController.h"

int main()
{
	Grid grid{};
	GOL::windowView wView{ &grid };
	GOL::windowController wController{ &grid, &wView };

	grid.spawnPattern("Copperhead", 10, 10);
	grid.spawnPattern("Copperhead", 25, 25);
	grid.spawnPattern("Copperhead", 40, 40);
	grid.spawnPattern("Copperhead", 55, 55);
	grid.spawnPattern("Copperhead", 70, 70);
	grid.spawnPattern("Copperhead", 85, 85);

	wController.startGameOfLife();

	return 0;
}

