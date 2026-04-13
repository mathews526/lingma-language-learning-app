#include "ReviewScreen.h"
#include "CardButtons.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
using namespace std;

/*==== Constructor ====*/
Review::Review(const sf::Vector2f& winSize)
{
	PushBackElements(winSize);
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
	sf::Vector2f coloredButtonsSize({ 100.0f, 50.0f });
	sf::Vector2f audioButtonSize({ 50.0f, 50.0f });
	sf::Color gray(200, 200, 200);

	// If you change the button position here make sure to also change it in the UpdatePosition functions within the button classes
	buttons.push_back(make_unique<RedButton>(coloredButtonsSize, sf::Vector2f(winSize.x / 3.0f, (7.0f * winSize.y) / 8.0f), sf::Color::Red));
	buttons.push_back(make_unique<YellowButton>(coloredButtonsSize, sf::Vector2f(winSize.x / 2.0f, (7.0f * winSize.y) / 8.0f), sf::Color::Yellow));
	buttons.push_back(make_unique<GreenButton>(coloredButtonsSize, sf::Vector2f((2.0f * winSize.x) / 3.0f, (7.0f * winSize.y) / 8.0f), sf::Color::Green));
	buttons.push_back(make_unique<AudioButton>(audioButtonSize, sf::Vector2f(winSize.x / 2.0f, (5.0f * winSize.y) / 8.0f), gray, "audioicon"));
}