#pragma once
#include "Buttons.h"
#include "AppState.h"
#include <SFML/Graphics.hpp>

/*==== Star Goal Buttons ====*/
struct StarButton : public Button
{
	/*==== Constructor ====*/
	StarButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, int starCount, AppState& appState);

	/*==== Main Behaviors ====*/
	void MousePress();
	void DrawButton(sf::RenderWindow& window);
	void UpdatePosition(const sf::Vector2f& winSize);

private:
	AppState& app;
	int _starCount;
	int _index;
	sf::Text label;
	static sf::Font& GetSharedFont();
};