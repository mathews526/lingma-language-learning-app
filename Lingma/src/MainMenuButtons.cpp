#include "MainMenuButtons.h"
#include "Screens.h"
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

/*==== LearnButton Functions ====*/
LessonButton::LessonButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName, Screen& parentScreen)
	: ImageButton(size, position, color, textureName), parent(parentScreen)
{

}
void LessonButton::MousePress()
{
	// TODO: Implement button functionality

	parent.nextScreen = ScreenType::Lesson;
}
void LessonButton::UpdatePosition(const sf::Vector2f& winSize)
{
	// If you change the button position here make sure to also change it in the PushBackButtons function in the respective Screen class
	SetPosition({ winSize.x / 4.0f, winSize.y / 4.0f });
}

/*==== ReviewButton Functions ====*/
ReviewButton::ReviewButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName, Screen& parentScreen)
	: ImageButton(size, position, color, textureName), parent(parentScreen)
{

}
void ReviewButton::MousePress()
{
	// TODO: Implement button functionality

	parent.nextScreen = ScreenType::Review;
}
void ReviewButton::UpdatePosition(const sf::Vector2f& winSize)
{
	// If you change the button position here make sure to also change it in the PushBackButtons function in the respective Screen class
	SetPosition({ (3.0f * winSize.x) / 4.0f, winSize.y / 4.0f });
}