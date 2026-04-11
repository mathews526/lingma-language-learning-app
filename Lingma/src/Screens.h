#pragma once
#include "UserSelectButtons.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
using std::unique_ptr;
using std::vector;

struct Screen
{
	// Store button types here
	vector<unique_ptr<Button>> buttons;

	/*==== Constructors / Destructors ====*/
	virtual ~Screen();

	/*==== Main Functions ====*/
	virtual void HandleEvents(const sf::Event& event, sf::RenderWindow& window); // Handles events such as mouse clicks
	virtual void Draw(sf::RenderWindow& window); // Draws elements onto the screen
	virtual void Update(const sf::Vector2f& winSize); // Mostly used to update the position of elements when the window is resized

	/*==== Helper Functions ====*/
	virtual void PushBackButtons(const sf::Vector2f& winSize) = 0; // Pushes all the button objects into the buttons vector
};