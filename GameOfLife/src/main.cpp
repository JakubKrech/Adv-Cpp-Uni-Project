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

	std::map<std::string, Pattern> patterns;
	// TODO: create class that will act as container of Patterns, fill it this way
	std::string path = "PatternsRLE";
	for (const auto &entry : fs::directory_iterator(path)) {
		Pattern newPattern{ entry };
		patterns.insert(std::pair<std::string, Pattern>(newPattern.name, newPattern));
	}

	for (const auto &x : patterns)
		std::cout << x.second.name << std::endl;

	grid.spawnPattern(patterns.find("Gosper glider gun")->second, 20, 20);

	//windowView.updateWindowState();
	wController.startGameOfLife();

	return 0;
}

