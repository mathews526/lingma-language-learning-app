#include "ImageButton.h"
#include "UserSelectButtons.h"
#include <SFML/Graphics.hpp>

/*==== CreateUserButton Functions ====*/
CreateUserButton::CreateUserButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const std::string& textureName, Screen& parentScreen)
	: ImageButton(size, position, color, textureName), parent(parentScreen)
{

}
void CreateUserButton::MousePress()
{
	// TODO: Implement button functionality

	parent.nextScreen = ScreenType::MainMenu; // Tells parent screen to switch to the MainMenu
}
void CreateUserButton::UpdatePosition(const sf::Vector2f& winSize)
{
	// If you change the button position here make sure to also change it in the PushBackButtons function in the respective Screen class
	SetPosition({ winSize.x / 6.0f, (4.0f * winSize.y) / 5.0f });
}

/*==== LoginButton Functions ====*/
LoginButton::LoginButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName, Screen& parentScreen)
	: ImageButton(size, position, color, textureName), parent(parentScreen)
{

}
void LoginButton::MousePress()
{
	// TODO: Implement button functionality

	parent.nextScreen = ScreenType::MainMenu; // Tells parent screen to switch to the MainMenu
}
void LoginButton::UpdatePosition(const sf::Vector2f& winSize)
{
	// If you change the button position here make sure to also change it in the PushBackButtons function in the respective Screen class
	SetPosition({ winSize.x / 6.0f, (2.0f * winSize.y) / 5.0f });
}