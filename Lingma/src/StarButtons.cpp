#include "StarButtons.h"
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

/*==== StarButton Functions ====*/
StarButton::StarButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, int starCount, AppState& appState)
	: Button(size, position, color), app(appState), _starCount(starCount), _index(starCount - 1), label(GetSharedFont(), string(_starCount, '*'), 14)
{
	label.setFillColor(sf::Color::Yellow);
}

void StarButton::MousePress()
{
	app.goal.SetGoal(_starCount);
}

void StarButton::DrawButton(sf::RenderWindow& window) 
{
	Button::DrawButton(window);

	sf::FloatRect bounds = label.getLocalBounds();
	label.setOrigin({ bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f });
	label.setPosition(button.getPosition());

	window.draw(label);
}

void StarButton::UpdatePosition(const sf::Vector2f& winSize)
{
	float buttonWidth = 50.0f;
	float gap = 10.0f;
	float totalWidth = (5 * buttonWidth) + (4 * gap);
	float startX = winSize.x - totalWidth - 20.0f;
	float y = 30.0f;
	SetPosition({ startX + _index * (buttonWidth + gap) + buttonWidth / 2.0f, y });
}

/*==== Helper Function ====*/
sf::Font& StarButton::GetSharedFont()
{
	static sf::Font font;
	static bool loaded = false;
	if (!loaded)
	{
		font.openFromFile("Verdana.ttf");
		loaded = true;
	}
	return font;
}

