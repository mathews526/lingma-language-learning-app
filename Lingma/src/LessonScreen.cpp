#include "LessonScreen.h"
#include "CardButtons.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
using namespace std;

/*==== Constructor ====*/
Lesson::Lesson(const sf::Vector2f& winSize)
{
	PushBackElements(winSize);
}

/*==== Main Behavior ====*/
void Lesson::Draw(sf::RenderWindow& window)
{
	Screen::Draw(window);

	// Draw unique screen-specific elements below
}

/*==== Helper Functions ====*/
void Lesson::PushBackElements(const sf::Vector2f& winSize)
{
	sf::Vector2f audioButtonSize({ 50.0f, 50.0f });
	sf::Color gray(200, 200, 200);

	// If you change the button position here make sure to also change it in the UpdatePosition functions within the button classes
	buttons.push_back(make_unique<AudioButton>(audioButtonSize, sf::Vector2f(winSize.x / 2.0f, (5.0f * winSize.y) / 8.0f), gray, "audioicon"));
}