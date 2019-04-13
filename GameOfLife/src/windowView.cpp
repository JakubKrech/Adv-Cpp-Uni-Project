#include "..\\include\\windowView.h"



GOL::windowView::windowView(Grid *g) : grid{ g }
{
	window = std::unique_ptr<sf::RenderWindow>(
		new sf::RenderWindow(sf::VideoMode(pixelWidth + menuWidth, pixelHeight), "GameOfLife"));
	ImGui::SFML::Init(*window);

	window->setFramerateLimit(frameRate);
	window->setVerticalSyncEnabled(true);
}


GOL::windowView::~windowView()
{
	ImGui::SFML::Shutdown();
}

void GOL::windowView::updateWindowState()
{
	while (this->window->isOpen())
	{
		while (this->window->pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed)
				this->window->close();
		}

		sf::RectangleShape menuBackground{};
		menuBackground.setSize(sf::Vector2f(menuWidth, pixelWidth));
		menuBackground.setPosition(sf::Vector2f(pixelWidth, 0.f));
		menuBackground.setFillColor(sf::Color(66, 66, 66, 255));
		this->window->draw(menuBackground);

		ImGui::SFML::Update(*this->window, deltaClock.restart());
		ImGui::Begin("Hello, world!");
		if (ImGui::Button("Look at this pretty button")) {
			if (showHelpMenu) showHelpMenu = false;
			else showHelpMenu = true;
		};
		ImGui::SliderInt("Frame Rate", &frameRate, 1, 144);
		ImGui::End();

		this->window->setFramerateLimit(frameRate);

		for (auto x = 0; x < grid->cellGrid.size(); x++) {
			for (auto y = 0; y < grid->cellGrid[0].size(); y++) {
				if (grid->cellGrid[x][y].previousState) this->window->draw(grid->cellGrid[x][y]);
			}
		}

		if (showHelpMenu) ImGui::ShowDemoWindow();

		ImGui::SFML::Render(*this->window);
		grid->calculateNextStep();
		this->window->display();
		this->window->clear();

	}
}
