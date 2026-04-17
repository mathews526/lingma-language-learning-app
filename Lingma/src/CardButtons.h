#pragma once
#include "Buttons.h"
#include "Screens.h"
#include "ReviewScreen.h"
#include "LessonScreen.h"
#include "ImageButton.h"
#include <SFML/Graphics.hpp>
#include <functional>
using std::function;

/*==== Familiarity Buttons ====*/
struct RedButton : public Button
{
	/*==== Constructor ====*/
	RedButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, Review& parentScreen);

	/*==== Main Behaviors ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);
private:
	Review& parent;
};
struct YellowButton : public Button
{
	/*==== Constructor ====*/
	YellowButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, Review& parentScreen);

	/*==== Main Behaviors ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);
private:
	Review& parent;
};
struct GreenButton : public Button
{
	/*==== Constructor ====*/
	GreenButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, Review& parentScreen);

	/*==== Main Behaviors ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);
private:
	Review& parent;
};

/*==== Navigation Buttons ====*/
struct NextButton : public ImageButton
{
	/*==== Constructor ====*/
	NextButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName, Lesson& parentScreen);

	/*==== Main Behaviors ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);
private:
	Lesson& parent;
};
struct BackButton : public ImageButton
{
	/*==== Constructor ====*/
	BackButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName, Screen& parentScreen);

	/*==== Main Behaviors ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);
private:
	Screen& parent;
};

/*==== Other Buttons ====*/
struct AudioButton : public ImageButton
{
	/*==== Constructor ====*/
	AudioButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName, Lesson& parentScreen);

	/*==== Main Behaviors ====*/
	void MousePress();
	void UpdatePosition(const sf::Vector2f& winSize);
private:
	Lesson& parent;
};