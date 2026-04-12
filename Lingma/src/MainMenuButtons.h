#pragma once
#include "Screens.h"
#include "ImageButton.h"
#include <SFML/Graphics.hpp>
#include <string>
using std::string;

struct LessonButton : public ImageButton
{
	/*==== Constructor ====*/
	LessonButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName, Screen& parentScreen);

	/*==== Main Behaviors ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);
private:
	Screen& parent;
};

struct ReviewButton : public ImageButton
{
	/*==== Constructor ====*/
	ReviewButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName, Screen& parentScreen);

	/*==== Main Behaviors ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);
private:
	Screen& parent;
};