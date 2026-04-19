#pragma once
#include "ImageButton.h"
#include "UserSelectScreen.h"
#include "Textbox.h"
#include <SFML/Graphics.hpp>
#include <string>
using std::string;

struct CreateUserButton : public ImageButton
{
	/*==== Constructors ====*/
	CreateUserButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName, UserSelect& parentScreen);

	/*==== Main Functionality ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);

private:
	UserSelect& parent;
};

struct LoginButton : public ImageButton
{
	/*==== Constructors ====*/
	LoginButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName, UserSelect& parentScreen);

	/*==== Main Functionality ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);

private:
	UserSelect& parent;
};