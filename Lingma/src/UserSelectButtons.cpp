#include "Buttons.h"
#include "UserSelectButtons.h"
#include <SFML/Graphics.hpp>

/*==== CreateUserButton Functions ====*/
CreateUserButton::CreateUserButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color)
	: Button(size, position, color)
{

}
void CreateUserButton::MousePress()
{
	// TODO: Implement button functionality
}
void CreateUserButton::UpdatePosition(const sf::Vector2f& winSize)
{
	button.setPosition({ winSize.x / 3.0f, winSize.y / 2.0f });
}