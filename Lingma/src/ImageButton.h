#pragma once
#include "Buttons.h"
#include <SFML/Graphics.hpp>
#include <string>
using std::string;

struct ImageButton : public Button
{
	/*==== Constructors ====*/
	ImageButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName);

	/*==== Main Functionality ====*/
	void DrawButton(sf::RenderWindow& window);
protected:
	sf::Sprite icon;

	/*==== Helper Functions ====*/
	void UpdateIcon();
	void SetPosition(const sf::Vector2f& pos);
};