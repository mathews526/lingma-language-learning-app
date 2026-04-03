#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Buttons.h"
using namespace std;

/*==== Button Functions ====*/
Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color)
{
	button.setSize(size);
	button.setOrigin(button.getGeometricCenter());
	button.setPosition(position);
	button.setFillColor(color);
}
Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const sf::Text& text)
{
	button.setSize(size);
	button.setOrigin(button.getGeometricCenter());
	button.setPosition(position);
	button.setFillColor(color);
	// TODO: Decide on a font and download a font file
}
Button::~Button()
{

}
bool Button::Contains(sf::Vector2f mousePos) const
{
	return button.getGlobalBounds().contains(mousePos);
}
void Button::DrawButton(sf::RenderWindow& window)
{
	window.draw(button);
}
void Button::UpdatePosition(const sf::Vector2f& position)
{
	button.setPosition(position);
}