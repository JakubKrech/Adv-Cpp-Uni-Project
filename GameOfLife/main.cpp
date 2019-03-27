#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

#include "Grid.h"

int main()
{
	Grid grid{ 800,600,8 };

	//blinker oscillators
	grid.cellGrid[2][2].setAlive();
	grid.cellGrid[2][3].setAlive();
	grid.cellGrid[2][4].setAlive();

	grid.spawnGlider(86, 7);
	grid.spawnGlider(96, 47);

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
				grid.window->draw(grid.cellGrid[x][y]);
			}
		}

		grid.window->display();
		//system("pause");
		grid.calculateNextStep();
		grid.window->clear();
		std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << "\n";
	}

	return 0;
}
