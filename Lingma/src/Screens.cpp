#include "Screens.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
using namespace std;

/*==== Constructors/Destructors ====*/
Screen::~Screen()
{

}

/*==== Main Behaviors ====*/
void Screen::HandleEvents(const sf::Event& event, sf::RenderWindow& window)
{
	if (const auto* mousePress = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mousePress->button == sf::Mouse::Button::Left)
		{
			// Converts click position from window pixels to world coordinates. This is necessary for things to work after resizing the window.
			sf::Vector2 mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons[i]->Contains(mousePos))
					buttons[i]->MousePress();
			}
		}
	}
}
void Screen::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->DrawButton(window);
}
void Screen::Update(const sf::Vector2f& winSize)
{
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->UpdatePosition(winSize);
}

/*==== Helper Function ====*/
void Screen::LoadFont(const string& fontName)
{
	if (!font.openFromFile(fontName + ".ttf"))
	{
		std::cerr << "Error: Could not load font file." << endl;
	}
}