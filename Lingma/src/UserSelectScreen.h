#pragma once
#include "Screens.h"
#include "Buttons.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;

struct UserSelect : public Screen
{
	/*==== Constructors / Destructors ====*/
	UserSelect(const sf::Vector2f& winSize); // Create buttons here

	// Draw, Update, and HandleEvents are inherited from Screen. 
	// If you want unique logic for one of these functions for this screen just create that function here, have it call the parent version, and include the unique logic below.

	void Draw(sf::RenderWindow& window);

	/*==== Helper Functions ====*/
	void PushBackElements(const sf::Vector2f& winSize); // Pushes all the button objects into the buttons vector
};