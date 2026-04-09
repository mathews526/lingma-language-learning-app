#pragma once
#include "Buttons.h"
#include <SFML/Graphics.hpp>

struct CreateUserButton : public Button
{
	/*==== Constructors ====*/
	CreateUserButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color);

	/*==== Main Functionality ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);
};