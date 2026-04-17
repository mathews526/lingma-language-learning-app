#pragma once
#include "Screens.h"
#include "Buttons.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;

struct MainMenu : public Screen
{
	/*==== Constructors ====*/
	MainMenu(const sf::Vector2f& winSize); // Create buttons here

	/*==== Main Behaviors ====*/
	void Draw(sf::RenderWindow& window);

private:
	/*==== Helper Functions ====*/
	void PushBackElements(const sf::Vector2f& winSize); // Pushes all the button objects into the buttons vector
};