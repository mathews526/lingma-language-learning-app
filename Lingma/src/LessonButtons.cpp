#include "LessonButtons.h"
#include <SFML/Graphics.hpp>

/*==== RedButton Functions ====*/
RedButton::RedButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color)
	: Button(size, position, color)
{

}
void RedButton::MousePress()
{
	// TODO: Implement button functionality
}
void RedButton::UpdatePosition(const sf::Vector2f& winSize)
{
	// If you change the button position here make sure to also change it in the PushBackButtons function in the respective Screen class
	SetPosition({ winSize.x / 3.0f, (7.0f * winSize.y) / 8.0f });
}

/*==== YellowButton Functions ====*/
YellowButton::YellowButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color)
	: Button(size, position, color)
{

}
void YellowButton::MousePress()
{
	// TODO: Implement button functionality
}
void YellowButton::UpdatePosition(const sf::Vector2f& winSize)
{
	// If you change the button position here make sure to also change it in the PushBackButtons function in the respective Screen class
	SetPosition({ winSize.x / 2.0f, (7.0f * winSize.y) / 8.0f });
}

/*==== GreenButton Functions ====*/
GreenButton::GreenButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color)
	: Button(size, position, color)
{

}
void GreenButton::MousePress()
{
	// TODO: Implement button functionality
}
void GreenButton::UpdatePosition(const sf::Vector2f& winSize)
{
	// If you change the button position here make sure to also change it in the PushBackButtons function in the respective Screen class
	SetPosition({ (2.0f * winSize.x) / 3.0f, (7.0f * winSize.y) / 8.0f });
}