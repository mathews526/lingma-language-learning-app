#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
using std::ostringstream;
using std::string;

#define DELETE_KEY 8

// Made with the helps of this video: https://www.youtube.com/watch?v=T31MoLJws4U

class Textbox
{
	sf::RectangleShape box;
	sf::Text text;
	
	string value;
	bool isSelected;
	bool hasLimit;
	unsigned int limit;

	/*==== Helper Functions ====*/
	void DeleteLastChar();
	void UpdateDisplay();
public:
	/*==== Constructors ====*/
	Textbox(const sf::Font& font, unsigned int charSize, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& textColor);

	/*==== Main Behaviors ====*/
	void DrawTextbox(sf::RenderWindow& window);
	void TypedOn(const sf::Event& event); // Checks for key presses to add characters to the screen

	/*==== Setter Functions ====*/
	void SetPosition(const sf::Vector2f& pos);
	void SetSelected(bool sel);
	void SetLimit(bool ToF);
	void SetLimit(bool ToF, unsigned int lim);

	/*==== Getter Functions ====*/
	bool Contains(sf::Vector2f mousePos) const;
	string GetText() const;
};