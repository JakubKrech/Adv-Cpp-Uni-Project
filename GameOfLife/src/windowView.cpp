#include "..\\include\\windowView.h"

namespace ImGui
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

	bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return ListBox(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

}


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

		updateMenu();
		if (showFSPMenu) updateFPSWindow();
		if (showHelpMenu) ImGui::ShowDemoWindow();

		ImGui::SFML::Render(*this->window);
		if(!paused) grid->calculateNextStep();
		this->window->display();
		this->window->clear();

	}
}

void GOL::windowView::updateMenu()
{
	ImGui::Begin("Convay's Game of Life", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

	// WINDOW DESCRIPTION
	ImGui::Text("Window size in pixels: %.0f x %.0f", pixelWidth, pixelHeight);
	ImGui::Text("Cell size in pixels: %.0f x %.0f", cellSize, cellSize);
	ImGui::Text("Window size in cells: %.0f x %.0f", pixelWidth / cellSize, pixelHeight / cellSize);

	// FLOW CONTROL
	ImGui::Separator();
	ImGui::AlignTextToFramePadding();
	ImGui::Text("Flow Control"); ImGui::SameLine();
	if (ImGui::Button("<<")) {
		//
	};
	ImGui::SameLine();
	if (ImGui::Button("Play")) {
		if (paused) paused = false;
	};
	ImGui::SameLine();
	if (ImGui::Button("Stop")) {
		
		if (!paused) paused = true;
	};
	ImGui::SameLine();
	if (ImGui::Button(">>")) {
		grid->calculateNextStep();
	};
	ImGui::SliderInt("Frame Rate", &frameRate, 1, 144);
	
	//SPAWNING PATTERNS
	ImGui::Separator();
	ImGui::Text("Choose Pattern to spawn...");

	std::vector<std::string> patternsNames;
	for each (auto patPair in grid->patterns)
	{
		patternsNames.push_back(patPair.first);
	}
	static int listbox_item_current = 1;
	ImGui::ListBox("listbox\n(single select)", &listbox_item_current, patternsNames);
	ImGui::Text("...and click on grid to spawn it.");

	ImGui::Text("\nCurrently choosen Pattern");
	Pattern choosenPattern = grid->patterns.find(patternsNames[listbox_item_current])->second;
	ImGui::Text("Name: %s", choosenPattern.name.c_str());
	ImGui::Text("Size: %i x %i", choosenPattern.width, choosenPattern.height);


	

	ImGuiIO& io = ImGui::GetIO();
	//for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) {
	if (ImGui::IsMouseClicked(0)) {
		if (ImGui::GetIO().MousePos.x / cellSize >= 0 &&
			ImGui::GetIO().MousePos.x / cellSize <= pixelWidth / cellSize &&
			ImGui::GetIO().MousePos.y / cellSize >= 0 &&
			ImGui::GetIO().MousePos.y / cellSize <= pixelHeight / cellSize)
		{

			grid->spawnPattern(patternsNames[listbox_item_current], 
				ImGui::GetIO().MousePos.x / cellSize, ImGui::GetIO().MousePos.y / cellSize);
			if(paused) grid->calculateNextStep();
		}
	}
	//}

	ImGui::Separator();
	if (ImGui::Button("Clear grid")) {
		for (auto x = 0; x < grid->cellGrid.size(); x++) {
			for (auto y = 0; y < grid->cellGrid[0].size(); y++) {
				grid->cellGrid[x][y].nextState = false;
				grid->cellGrid[x][y].previousState = false;
			}
		}
		if (paused) grid->calculateNextStep();
	}; 
	ImGui::SameLine();
	if (ImGui::Button("Show Window Help")) {
		if (showHelpMenu) showHelpMenu = false;
		else showHelpMenu = true;
	}; 
	


	ImGui::End();

	this->window->setFramerateLimit(frameRate);

	for (auto x = 0; x < grid->cellGrid.size(); x++) {
		for (auto y = 0; y < grid->cellGrid[0].size(); y++) {
			if (grid->cellGrid[x][y].previousState) this->window->draw(grid->cellGrid[x][y]);
		}
	}
}

void GOL::windowView::updateFPSWindow()
{
	const float DISTANCE = 10.0f;
	static int corner = 0;
	ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : DISTANCE);
	ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.3f)); // Transparent background

	if (ImGui::Begin("FpsWindow", &showFSPMenu, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::Text("FPS: %.1f   Mouse Cell Position: (%.0f,%.0f)", 
			ImGui::GetIO().Framerate,
			ImGui::GetIO().MousePos.x / cellSize,
			ImGui::GetIO().MousePos.y / cellSize);
		//ImGui::Separator();

		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
			//if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
			//if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
			ImGui::EndPopup();
		}
		ImGui::End();
	}
	ImGui::PopStyleColor();
}