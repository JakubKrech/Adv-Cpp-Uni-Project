#include <SFML/Graphics.hpp>

#include <vector>
#include <map>
#include <iostream>
#include <chrono>
#include <thread>

#include "Grid.h"
#include "Pattern.h"

int main()
{
	Grid grid{ 800,800,8 };
	//grid.window->setFramerateLimit(144);

	std::map<std::string, Pattern> patterns;
	// TODO: create class that will act as container of Patterns, fill it this way
	std::string path = "src\\PatternsRLE";
	for (const auto &entry : fs::directory_iterator(path)) {
		Pattern newPattern{ entry };
		patterns.insert(std::pair<std::string, Pattern>(newPattern.name, newPattern));
	}

	for (const auto &x : patterns)
		std::cout << x.second.name << std::endl;


	grid.spawnPattern(patterns.find("Gosper glider gun")->second, 20, 20);

	sf::Event event;
	while (grid.window->isOpen())
	{
		const clock_t begin_time = clock();
		while (grid.window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				grid.window->close();
		}

		for (auto x = 0; x < grid.cellGrid.size(); x++) {
			for (auto y = 0; y < grid.cellGrid[0].size(); y++) {
				if(grid.cellGrid[x][y].previousState) grid.window->draw(grid.cellGrid[x][y]);
			}
		}
		
		grid.calculateNextStep();
		grid.window->display();
		grid.window->clear();

		std::cout << 1 / (float(clock() - begin_time) / CLOCKS_PER_SEC) << " fps" <<
			" - " << float(clock() - begin_time) / CLOCKS_PER_SEC << "\n";
		
	}

	return 0;
}
