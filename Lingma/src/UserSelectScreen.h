#pragma once
#include "Screens.h"
#include "Buttons.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;

struct UserSelect : public Screen
{
	/*==== Constructors / Destructors ====*/
	UserSelect(const sf::Vector2f& winSize); // Create buttons here

	void HandleEvent(const sf::Event& event, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void Update(const sf::Vector2f& winSize);

	/*==== Helper Functions ====*/
	void PushBackButtons(const sf::Vector2f& winSize); // Pushes all the button objects into the buttons vector
};