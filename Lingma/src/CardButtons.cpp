#include "CardButtons.h"
#include "Screens.h"
#include "ReviewScreen.h"
#include "LessonScreen.h"
#include <SFML/Graphics.hpp>
#include <functional>
using namespace std;

/*==== RedButton Functions ====*/
RedButton::RedButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, Review& parentScreen)
	: Button(size, position, color), parent(parentScreen)
{

}
void RedButton::MousePress()
{
	parent.RateCurrentCard(1); // Down
}
void RedButton::UpdatePosition(const sf::Vector2f& winSize)
{
	// If you change the button position here make sure to also change it in the PushBackButtons function in the respective Screen class
	SetPosition({ winSize.x / 3.0f, (7.0f * winSize.y) / 8.0f });
}

/*==== YellowButton Functions ====*/
YellowButton::YellowButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, Review& parentScreen)
	: Button(size, position, color), parent(parentScreen)
{

}
void YellowButton::MousePress()
{
	parent.RateCurrentCard(2); // Same
}
void YellowButton::UpdatePosition(const sf::Vector2f& winSize)
{
	// If you change the button position here make sure to also change it in the PushBackButtons function in the respective Screen class
	SetPosition({ winSize.x / 2.0f, (7.0f * winSize.y) / 8.0f });
}

/*==== GreenButton Functions ====*/
GreenButton::GreenButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, Review& parentScreen)
	: Button(size, position, color), parent(parentScreen)
{

}
void GreenButton::MousePress()
{
	parent.RateCurrentCard(3); // Up
}
void GreenButton::UpdatePosition(const sf::Vector2f& winSize)
{
	// If you change the button position here make sure to also change it in the PushBackButtons function in the respective Screen class
	SetPosition({ (2.0f * winSize.x) / 3.0f, (7.0f * winSize.y) / 8.0f });
}

/*==== NextButton Functions ====*/
NextButton::NextButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName, Lesson& parentScreen)
	: ImageButton(size, position, color, textureName), parent(parentScreen)
{

}
void NextButton::MousePress()
{
	parent.NextCard();
}
void NextButton::UpdatePosition(const sf::Vector2f& winSize)
{
	// If you change the button position here make sure to also change it in the PushBackButtons function in the respective Screen class
	SetPosition({ (7.0f * winSize.x) / 8.0f, (7.0f * winSize.y) / 8.0f });
}

/*==== BackButton Functions ====*/
BackButton::BackButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName, Screen& parentScreen)
	: ImageButton(size, position, color, textureName), parent(parentScreen)
{

}
void BackButton::MousePress()
{
	parent.nextScreen = ScreenType::MainMenu;
}
void BackButton::UpdatePosition(const sf::Vector2f& winSize)
{
	// If you change the button position here make sure to also change it in the PushBackButtons function in the respective Screen class
	SetPosition({ winSize.x / 8.0f, winSize.y / 8.0f });
}

/*==== AudioButton Functions ====*/
AudioButton::AudioButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const string& textureName, Lesson& parentScreen)
	: ImageButton(size, position, color, textureName), parent(parentScreen)
{

}
void AudioButton::MousePress()
{
	parent.PlayCurrentAudio();
}
void AudioButton::UpdatePosition(const sf::Vector2f& winSize)
{
	// If you change the button position here make sure to also change it in the PushBackButtons function in the respective Screen class
	SetPosition({ winSize.x / 2.0f, (5.0f * winSize.y) / 8.0f });
}