#include "Buttons.h"
#include <SFML/Graphics.hpp>
using namespace std;

/*==== Constructor / Destructor ====*/
Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color)
{
	button.setSize(size);
	button.setOrigin(button.getGeometricCenter());
	button.setPosition(position);
	button.setFillColor(color);
	button.setOutlineThickness(1.0f);
	button.setOutlineColor(sf::Color::Black);
}
Button::~Button()
{

}

/*==== Main Behaviors ====*/
bool Button::Contains(sf::Vector2f mousePos) const
{
	return button.getGlobalBounds().contains(mousePos);
}
void Button::DrawButton(sf::RenderWindow& window)
{
	window.draw(button);
}

/*==== Helper Functions ====*/
void Button::SetPosition(const sf::Vector2f& pos)
{
	button.setPosition(pos);
}