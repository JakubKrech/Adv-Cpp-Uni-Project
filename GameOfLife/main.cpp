#include <SFML/Graphics.hpp>

#include <vector>
#include <map>
#include <iostream>
#include <chrono>
#include <thread>

#include "src\\Grid.h"
#include "src\\Pattern.h"

int main()
{
	Grid grid{ 800,800,8 };
	grid.window->setFramerateLimit(30);

	std::map<std::string, Pattern> patterns;
	// TODO: create class that will act as container of Patterns, fill it this way
	std::string path = "src\\PatternsRLE";
	for (const auto &entry : fs::directory_iterator(path)) {
		Pattern newPattern{ entry };
		patterns.insert(std::pair<std::string, Pattern>{ newPattern.name, newPattern});
	}

	grid.spawnPattern(patterns.find("Gosper glider gun")->second, 20, 20);

	//blinker oscillators
	/*grid.cellGrid[20][32].setNextState(true);
	grid.cellGrid[20][33].setNextState(true);
	grid.cellGrid[20][34].setNextState(true);

	grid.spawnGlider(86, 7);
	grid.spawnGlider(96, 47);
	grid.spawnGlider(76, 17);
	grid.spawnGlider(56, 37);
	grid.spawnGlider(66, 67);
	grid.spawnGlider(46, 57);

	grid.spawnFrog(50, 53);
	grid.spawnFrog(5, 5);*/

	// Copperheads
	/*grid.spawnCopperhead(5, 5);
	grid.spawnCopperhead(25, 25);
	grid.spawnCopperhead(45, 45);
	grid.spawnCopperhead(65, 65);
	grid.spawnCopperhead(85, 85);*/
	/*grid.spawnPattern(patterns[3], 5, 10);
	grid.spawnPattern(patterns[3], 25, 10);
	grid.spawnPattern(patterns[3], 45, 10);
	grid.spawnPattern(patterns[3], 65, 10);
	grid.spawnPattern(patterns[3], 85, 10);

	grid.spawnPattern(patterns[1], 15, 40);
	grid.spawnPattern(patterns[1], 35, 40);
	grid.spawnPattern(patterns[1], 55, 40);
	grid.spawnPattern(patterns[1], 75, 40);

	grid.spawnPattern(patterns[1], 25, 60);
	grid.spawnPattern(patterns[1], 45, 60);
	grid.spawnPattern(patterns[1], 65, 60);
	grid.spawnPattern(patterns[1], 85, 60);

	grid.spawnPattern(patterns[1], 15, 80);
	grid.spawnPattern(patterns[1], 35, 80);
	grid.spawnPattern(patterns[1], 55, 80);
	grid.spawnPattern(patterns[1], 75, 80);*/

	// 5 for marching gliders
	// 3 for cool effect
	/*for (size_t i = 5; i < 95; i+=5)
	{
		for (size_t j = 5; j < 95; j+=5)
		{
			grid.spawnGlider(i, j);
		}
	}*/
	
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
