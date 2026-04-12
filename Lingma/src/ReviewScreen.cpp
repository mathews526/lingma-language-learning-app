#include "ReviewScreen.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
using namespace std;

/*==== Constructor ====*/
Review::Review(const sf::Vector2f& winSize)
{

}

/*==== Main Behavior ====*/
void Review::Draw(sf::RenderWindow& window)
{
	Screen::Draw(window);

	// Draw unique screen-specific elements below
}

/*==== Helper Functions ====*/
void Review::PushBackElements(const sf::Vector2f& winSize)
{
	// If you change the button position here make sure to also change it in the UpdatePosition functions within the button classes

}