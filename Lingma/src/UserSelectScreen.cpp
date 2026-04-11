#include "UserSelectScreen.h"
#include "UserSelectButtons.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
using namespace std;

UserSelect::UserSelect(const sf::Vector2f& winSize)
{
	PushBackButtons(static_cast<sf::Vector2f>(winSize));
}
void UserSelect::Draw(sf::RenderWindow& window)
{
	Screen::Draw(window);

	// Draw unique screen-specific elements below
}
void UserSelect::PushBackButtons(const sf::Vector2f& winSize)
{
	sf::Vector2f userButtonSize({ 100.0f, 50.0f });
	// If you change the button position here make sure to also change it in the UpdatePosition functions within the button classes
	buttons.push_back(make_unique<CreateUserButton>(userButtonSize, sf::Vector2f(winSize.x / 3.0f, winSize.y / 2.0f), sf::Color(0x669999), *this));
}