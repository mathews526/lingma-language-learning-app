#pragma once
#include "Buttons.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
using std::unique_ptr;
using std::string;
using std::vector;

enum class ScreenType { None, UserSelect, MainMenu, Lesson, Review };

struct Screen
{
	ScreenType nextScreen = ScreenType::None; // This tells main which screen to switch to next.

	/*==== Constructors / Destructors ====*/
	virtual ~Screen();

	/*==== Main Functions ====*/
	virtual void HandleEvents(const sf::Event& event, sf::RenderWindow& window); // Handles events such as mouse clicks
	virtual void Draw(sf::RenderWindow& window); // Draws elements onto the screen
	virtual void Update(const sf::Vector2f& winSize); // Mostly used to update the position of elements when the window is resized

protected:
	vector<unique_ptr<Button>> buttons; // Store button types here
	sf::Font font;

	/*==== Helper Functions ====*/
	virtual void PushBackElements(const sf::Vector2f& winSize) = 0; // Pushes all the elements such as buttons and textboxes
	void LoadFont(const string& fontName);
};