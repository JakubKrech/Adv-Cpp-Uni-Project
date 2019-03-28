#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

#include "Grid.h"
#include "Pattern.h"

int main()
{
	Grid grid{ 800,800,8 };
	//grid.window->setFramerateLimit(20);
	Pattern pat{ "PatternsRLE/copperhead.rle" };

	// TODO: create class that will act as container of Patterns, fill it this way
	/*std::string path = "/path/to/directory";
	for (const auto & entry : fs::directory_iterator(path))
		std::cout << entry.path() << std::endl;*/

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
	grid.spawnCopperhead(5, 5);
	grid.spawnCopperhead(25, 25);
	grid.spawnCopperhead(45, 45);
	grid.spawnCopperhead(65, 65);
	grid.spawnCopperhead(85, 85);

	// 5 for marching gliders
	// 3 for cool effect
	/*for (size_t i = 5; i < 95; i+=5)
	{
		for (size_t j = 5; j < 95; j+=5)
		{
			grid.spawnGlider(i, j);
		}
	}*/

	while (grid.window->isOpen())
	{
		const clock_t begin_time = clock();

		sf::Event event;
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
		//system("pause");
		
		grid.window->clear();
		std::cout << 1 / (float(clock() - begin_time) / CLOCKS_PER_SEC) << " fps" << 
			" - " << float(clock() - begin_time) / CLOCKS_PER_SEC << "\n";
	}

	return 0;
}
