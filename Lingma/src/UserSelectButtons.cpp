#include "Buttons.h"
#include "UserSelectButtons.h"
#include <SFML/Graphics.hpp>

/*==== CreateUserButton Functions ====*/
CreateUserButton::CreateUserButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, Screen& parentScreen)
	: Button(size, position, color), parent(parentScreen)
{

}
void CreateUserButton::MousePress()
{
	// TODO: Implement button functionality

	parent.nextScreen = ScreenType::MainMenu; // Tells parent screen to switch to the MainMenu
}
void CreateUserButton::UpdatePosition(const sf::Vector2f& winSize)
{
	button.setPosition({ winSize.x / 3.0f, winSize.y / 2.0f });
}