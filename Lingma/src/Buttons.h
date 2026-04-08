#pragma once
#include <SFML/Graphics.hpp>

/*==== Base Class ====*/
struct Button
{
	/*==== Constructor / Destructor ====*/
	Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color); // Button without text
	Button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const sf::Text& text); // Button with text TODO: Decide on a font and download a font file
	virtual ~Button();

	/*==== Behaviors ====*/
	virtual void MousePress() = 0; // Implement this for any child classes
	bool Contains(sf::Vector2f mousePos) const; // Indicates whether click was within the button
	void DrawButton(sf::RenderWindow& window);
	virtual void UpdatePosition(const sf::Vector2f& winSize) = 0;

protected:
	sf::RectangleShape button;
};

// To create a button, make a child class with its own functionality when you click on it

/*==== Derived Buttons ====*/
// New Profile Button //
// - Used to create a new profile
class NewProfileButton : public Button
{
public:
	NewProfileButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color) : Button(size, position, color) {}

	NewProfileButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const sf::Text& text) : Button(size, position, color, text) {}

	void MousePress() override
	{
		// TODO: Implement functionality to create a new profile
	}
};