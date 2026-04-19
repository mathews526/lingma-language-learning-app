#pragma once
#include "Screens.h"
#include "Buttons.h"
#include "AppState.h"
#include "StarButtons.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <optional>
using std::string;
using std::array;
using std::optional;

struct MainMenu : public Screen
{
	/*==== Constructors ====*/
	MainMenu(const sf::Vector2f& winSize, AppState& appState); // Create buttons here

	/*==== Main Behaviors ====*/
	void Draw(sf::RenderWindow& window);
	void Update(const sf::Vector2f& winSize);
	// UPDATE: Handle click for goal bar elements; keeps MouseClick from getting too messy
	void HandleEvents(const sf::Event& event, sf::RenderWindow& window);

private:
	AppState& app;

	array<int, 6> levelCounts{};
	int totalCards = 0;
	
	sf::RectangleShape dashboardBox;
	sf::RectangleShape progressBack;
	sf::RectangleShape progressFill;
	array<sf::RectangleShape, 6> levelTiles;

	optional<sf::Text> levelLabelText;
	optional<sf::Text> countText;

	// UPDATE: Goal bar elements
	StarButton starButton;
	sf::RectangleShape goalBarBack;
	sf::RectangleShape goalBarFill;
	optional<sf::Text> goalBarLabel;

	/*==== Helper Functions ====*/
	void PushBackElements(const sf::Vector2f& winSize); // Pushes all the button objects into the buttons vector
	void LoadDashboardData();
	void BuildDashboardVisuals(const sf::Vector2f& winSize);
	void PositionDashboard(const sf::Vector2f& winSize);

	// UPDATE: Goal bar helper functions
	void BuildGoalVisuals(const sf::Vector2f& winSize);
	void PositionGoalVisuals(const sf::Vector2f& winSize);
};