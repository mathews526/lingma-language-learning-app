#pragma once
#include "Screens.h"
#include "Buttons.h"
#include "ImageButton.h"
#include <SFML/Graphics.hpp>

/*==== Familiarity Buttons ====*/
struct RedButton : public Button
{
	/*==== Constructor ====*/
	RedButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color);

	/*==== Main Behaviors ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);
};
struct YellowButton : public Button
{
	/*==== Constructor ====*/
	YellowButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color);

	/*==== Main Behaviors ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);
};
struct GreenButton : public Button
{
	/*==== Constructor ====*/
	GreenButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color);

	/*==== Main Behaviors ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);
};

/*==== Other Buttons ====*/
struct AudioButton : public ImageButton
{
	/*==== Constructor ====*/
	AudioButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName);

	/*==== Main Behaviors ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);
};