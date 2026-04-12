#include "MainMenuScreen.h"
#include "MainMenuButtons.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
using namespace std;

MainMenu::MainMenu(const sf::Vector2f& winSize)
{
	PushBackElements(static_cast<sf::Vector2f>(winSize));
}
void MainMenu::Draw(sf::RenderWindow& window)
{
	Screen::Draw(window);

	// Draw unique screen-specific elements below
}
void MainMenu::PushBackElements(const sf::Vector2f& winSize)
{
	sf::Vector2f largeButtonSize({ 350.0f, 125.0f });
	sf::Color lightBlue(0xcc, 0xff, 0xff);
	sf::Color limeGreen(0xccff66ff);

	// If you change the button position here make sure to also change it in the UpdatePosition functions within the button classes
	buttons.push_back(make_unique<LessonButton>(largeButtonSize, sf::Vector2f(winSize.x / 4.0f, winSize.y / 4.0f), lightBlue, "learn", *this));
	buttons.push_back(make_unique<ReviewButton>(largeButtonSize, sf::Vector2f((3.0f * winSize.x) / 4.0f, winSize.y / 4.0f), limeGreen, "review", *this));
}