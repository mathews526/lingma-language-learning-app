#include "Textbox.h"
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

/*==== Constructors ====*/
Textbox::Textbox(const sf::Font& font, unsigned int charSize, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& textColor)
	: text(font, "", charSize), isSelected(false), hasLimit(true), limit(10)
{
	box.setSize(size);
	box.setOrigin(box.getGeometricCenter());
	box.setPosition(position);
	box.setFillColor(sf::Color(200, 200, 200));
	box.setOutlineThickness(1.0f);
	box.setOutlineColor(sf::Color::Black);

	text.setFillColor(textColor);
	SetPosition(position);

	UpdateDisplay();
}

/*==== Main Behaviors ====*/
void Textbox::DrawTextbox(sf::RenderWindow& window)
{
	window.draw(box);
	window.draw(text);
}
void Textbox::TypedOn(const sf::Event& event)
{
	if (!isSelected)
		return;

	if (const auto* textEvent = event.getIf<sf::Event::TextEntered>())
	{
		const char32_t unicode = textEvent->unicode;

		if (unicode == DELETE_KEY)
			DeleteLastChar();
		else if ((unicode >= '0' && unicode <= '9') || (unicode >= 'A' && unicode < 'Z') || (unicode >= 'a' && unicode <= 'z')) // Only allows only numbers and letters
		{
			if (!hasLimit || value.size() < limit)
				value += static_cast<char>(unicode);
		}

		UpdateDisplay();
	}
}

/*==== Helper Functions ====*/
void Textbox::DeleteLastChar()
{
	if (!value.empty())
		value.pop_back();
}
void Textbox::UpdateDisplay()
{
	if (isSelected)
		text.setString(value + "_");
	else
		text.setString(value);
}

/*==== Setter Functions ====*/
void Textbox::SetPosition(const sf::Vector2f& pos)
{
	box.setPosition(pos);

	sf::Vector2f boxTopLeft = pos - (box.getSize() / 2.0f);

	text.setPosition({ boxTopLeft.x + 4.0f, boxTopLeft.y + 12.0f }); // Includes an offset so that the text is positioned better
}
void Textbox::SetSelected(bool sel)
{
	isSelected = sel;
	UpdateDisplay();
}
void Textbox::SetLimit(bool ToF)
{
	hasLimit = ToF;
}
void Textbox::SetLimit(bool ToF, unsigned int lim)
{
	hasLimit = ToF;
	limit = lim;
}

/*==== Getter Functions ====*/
string Textbox::GetText() const
{
	return value;
}
bool Textbox::Contains(sf::Vector2f mousePos) const
{
	return box.getGlobalBounds().contains(mousePos);
}