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
	virtual void HandleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Update(const sf::Vector2f& winSize) = 0;

	/*==== Helper Functions ====*/
	virtual void PushBackButtons(const sf::Vector2f& winSize) = 0; // Pushes all the button objects into the buttons vector
};