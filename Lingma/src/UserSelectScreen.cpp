#include "UserSelectScreen.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
using namespace std;

UserSelect::UserSelect(const sf::Vector2f& winSize)
{
	PushBackButtons(static_cast<sf::Vector2f>(winSize));
}
void UserSelect::HandleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	if (const auto* mousePress = event.getIf<sf::Event::MouseButtonPressed>())
	{
		// TODO: Call the mouse press function for the respective button if clicked on.
	}
}
void UserSelect::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->DrawButton(window);
}
void UserSelect::Update(const sf::Vector2f& winSize)
{
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->UpdatePosition(winSize);
}
void UserSelect::PushBackButtons(const sf::Vector2f& winSize)
{
	sf::Vector2f userButtonSize({ 100.0f, 50.0f });
	// If you change the button position here make sure to also change it in the UpdatePosition functions within the button classes
	buttons.push_back(make_unique<CreateUserButton>(userButtonSize, sf::Vector2f(winSize.x / 3.0f, winSize.y / 2.0f), sf::Color(0x669999)));
}