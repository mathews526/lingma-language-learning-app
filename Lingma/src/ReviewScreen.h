#pragma once
#include "Screens.h"
#include "Buttons.h"
#include <SFML/Graphics.hpp>

struct Review : public Screen
{
	/*==== Constructor ====*/
	Review(const sf::Vector2f& winSize);

	/*==== Main Behavior ====*/
	void Draw(sf::RenderWindow& window);

private:
	/*==== Helper Functions ====*/
	void PushBackElements(const sf::Vector2f& winSize); // Pushes all the button objects into the buttons vector
};