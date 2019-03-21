#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

//#include "Cell.h"

#define colorEmpty sf::Color::White
#define colorAlive sf::Color::Red

std::vector<std::vector<sf::RectangleShape>> calculateNextStep(std::vector<std::vector<sf::RectangleShape>>& grid, unsigned int width, unsigned int height);
void spawnGlider(std::vector<std::vector<sf::RectangleShape>>& grid, int xx, int yy);

int main()
{
	constexpr int width = 800;
	constexpr int height = 800;
	constexpr int cellSize = 8;

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

	spawnGlider(cellGrid, 86, 7);
	spawnGlider(cellGrid, 96, 47);

	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//const clock_t begin_time = clock();
		cellGrid = std::move(calculateNextStep(cellGrid, gridWidth, gridHeight));
		//std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << "\n";
		window.clear();

		for (auto x = 0; x < gridWidth; x++) {
			for (auto y = 0; y < gridHeight; y++) {
				window.draw(cellGrid[x][y]);
			}
		}

		window.display();
		
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	return 0;
}

std::vector<std::vector<sf::RectangleShape>> calculateNextStep(std::vector<std::vector<sf::RectangleShape>>& grid, unsigned int width, unsigned int height)
{
	const clock_t begin_time = clock();

	std::vector<std::vector<sf::RectangleShape>> temp = grid;
	//temp.resize(width, std::vector<sf::RectangleShape>(height));

	int leftN;	// x - 1
	int rightN; // x + 1
	//int topN;	// y + 1
	//int botN;	// y - 1

	for (auto x = 0; x < width; x++) {
		for (auto y = 0; y < height; y++) {

			int aliveNighbours = 0;
			
			x == 0 ? leftN = width - 1 : leftN = x - 1;
			x == width - 1 ? rightN = 0 : rightN = x + 1;

			if (y + 1 < height) {
				if (grid[leftN][y + 1].getFillColor() == colorAlive) aliveNighbours++;
				if (grid[x][y + 1].getFillColor() == colorAlive) aliveNighbours++;
				if (grid[rightN][y + 1].getFillColor() == colorAlive) aliveNighbours++;
			}
			
			if (y - 1 >= 0) {
				if (grid[rightN][y - 1].getFillColor() == colorAlive) aliveNighbours++;
				if (grid[x][y - 1].getFillColor() == colorAlive) aliveNighbours++;
				if (grid[leftN][y - 1].getFillColor() == colorAlive) aliveNighbours++;
			}

			if (grid[rightN][y].getFillColor() == colorAlive) aliveNighbours++;
			if (grid[leftN][y].getFillColor() == colorAlive) aliveNighbours++;

			if (grid[x][y].getFillColor() == colorEmpty) {
				if (aliveNighbours == 3) temp[x][y].setFillColor(colorAlive); // cell becomes alive by reproduction
			}
			else if (grid[x][y].getFillColor() == colorAlive) {
				if (aliveNighbours < 2) temp[x][y].setFillColor(colorEmpty); // alive cell dies by underpopulation
				//else if (aliveNighbours == 2 || aliveNighbours == 3) {}; // alive cell stays alive
				else if (aliveNighbours > 3) temp[x][y].setFillColor(colorEmpty); // alive cell dies by overpopulation
			}
			
		}
	}

	std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << "\n";

	return temp;
}

void spawnGlider(std::vector<std::vector<sf::RectangleShape>>& grid, int xx, int yy)
{
	grid[xx][yy].setFillColor(colorAlive);
	grid[xx+1][yy].setFillColor(colorAlive);
	grid[xx+2][yy].setFillColor(colorAlive);
	grid[xx+2][yy-1].setFillColor(colorAlive);
	grid[xx+1][yy-2].setFillColor(colorAlive);
}