#pragma once
#include <SFML/Graphics.hpp>
#include "Buttons.h"

class NewProfileButton : public Button
{
public:
	NewProfileButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color) : Button(size, position, color) {}

	NewProfileButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const sf::Text& text) : Button(size, position, color, text) {}

	void MousePress() override
	{
		// TODO: Implement functionality to create a new profile
	}
};
