#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

#include "Cell.h"

#define colorEmpty sf::Color::White
#define colorAlive sf::Color::Red

std::vector<std::vector<sf::RectangleShape>> calculateNextStep(std::vector<std::vector<sf::RectangleShape>>&& grid, unsigned int width, unsigned int height);

int main()
{
	constexpr int width = 400;
	constexpr int height = 400;
	constexpr int cellSize = 40;

	constexpr int gridWidth = width / cellSize;
	constexpr int gridHeight = height / cellSize;

	std::vector<std::vector<sf::RectangleShape>> cellGrid;
	cellGrid.resize(gridWidth, std::vector<sf::RectangleShape>(gridHeight));

	
	
	sf::RenderWindow window(sf::VideoMode(width, height), "GameOfLife");

	for (auto x = 0; x < gridWidth; x++) {
		for (auto y = 0; y < gridHeight; y++) {
			cellGrid[x][y].setSize(sf::Vector2f(cellSize, cellSize));
			cellGrid[x][y].setPosition(x*cellSize, y*cellSize);
			cellGrid[x][y].setFillColor(colorEmpty);
		}
	}

	//blinker oscillators
	cellGrid[2][2].setFillColor(colorAlive);
	cellGrid[2][3].setFillColor(colorAlive);
	cellGrid[2][4].setFillColor(colorAlive);

	cellGrid[6][7].setFillColor(colorAlive);
	cellGrid[7][7].setFillColor(colorAlive);
	cellGrid[8][7].setFillColor(colorAlive);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		cellGrid = calculateNextStep(std::move(cellGrid), gridWidth, gridHeight);

		window.clear();

		for (auto x = 0; x < gridWidth; x++) {
			for (auto y = 0; y < gridHeight; y++) {
				window.draw(cellGrid[x][y]);
			}
		}

		window.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	return 0;
}

std::vector<std::vector<sf::RectangleShape>> calculateNextStep(std::vector<std::vector<sf::RectangleShape>>&& grid, unsigned int width, unsigned int height)
{
	std::vector<std::vector<sf::RectangleShape>> temp = grid;

	for (auto x = 0; x < width; x++) {
		for (auto y = 0; y < height; y++) {
			int aliveNighbours = 0;

			//if (x >= 0 && x < width && y >= 0 && y < height)
			if (x - 1 >= 0 && y + 1 < height &&		grid[x - 1][y + 1].getFillColor() == colorAlive) aliveNighbours++;
			if (y + 1 < height &&					grid[x    ][y + 1].getFillColor() == colorAlive) aliveNighbours++;
			if (x + 1 < width && y + 1 < height &&	grid[x + 1][y + 1].getFillColor() == colorAlive) aliveNighbours++;
			if (x + 1 < width &&					grid[x + 1][y    ].getFillColor() == colorAlive) aliveNighbours++;
			if (x + 1 < width && y - 1 >= 0 &&		grid[x + 1][y - 1].getFillColor() == colorAlive) aliveNighbours++;
			if (x && y - 1 >= 0	 &&					grid[x    ][y - 1].getFillColor() == colorAlive) aliveNighbours++;
			if (x - 1 >= 0 && y - 1 >= 0 &&			grid[x - 1][y - 1].getFillColor() == colorAlive) aliveNighbours++;
			if (x - 1 >= 0 &&						grid[x - 1][y    ].getFillColor() == colorAlive) aliveNighbours++;

			//std::cout << x << " " << y << " " << aliveNighbours << std::endl;

			if (grid[x][y].getFillColor() == colorAlive) {
				if (aliveNighbours < 2) temp[x][y].setFillColor(colorEmpty); // alive cell dies by underpopulation
				//else if (aliveNighbours == 2 || aliveNighbours == 3) {}; // alive cell stays alive
				else if (aliveNighbours > 3) temp[x][y].setFillColor(colorEmpty); // alive cell dies by overpopulation
			}
			else if (grid[x][y].getFillColor() == colorEmpty) {
				if (aliveNighbours == 3) temp[x][y].setFillColor(colorAlive); // cell becomes alive by reproduction
			}
		}
	}

	//grid = temp;

	return temp;
}