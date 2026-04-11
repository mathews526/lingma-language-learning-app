#include "UserSelectScreen.h"
#include "UserSelectButtons.h"
#include "Textbox.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
using namespace std;

/*==== Constructor ====*/
UserSelect::UserSelect(const sf::Vector2f& winSize)
{
	LoadFont("Verdana");
	PushBackElements(static_cast<sf::Vector2f>(winSize));
}

/*==== Main Behavior ====*/
void UserSelect::HandleEvents(const sf::Event& event, sf::RenderWindow& window)
{
	Screen::HandleEvents(event, window);
	
	// Textbox will be selected when clicked on and deselected when clicking somewhere else
	if (const auto* mousePress = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mousePress->button == sf::Mouse::Button::Left)
		{
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

			for (int i = 0; i < textboxes.size(); i++)
			{
				if (textboxes[i]->Contains(mousePos))
					textboxes[i]->SetSelected(true);
				else
					textboxes[i]->SetSelected(false);
			}
		}
	}

	// Handles typing events if textbox is selected
	for (int i = 0; i < textboxes.size(); i++)
		textboxes[i]->TypedOn(event);
}
void UserSelect::Draw(sf::RenderWindow& window)
{
	Screen::Draw(window);

	// Draw unique screen-specific elements below
	for (int i = 0; i < textboxes.size(); i++)
		textboxes[i]->DrawTextbox(window);
}
void UserSelect::Update(const sf::Vector2f& winSize)
{
	Screen::Update(winSize);

	// If you change the textbox position here make sure to also change it in the PushBackElements function within the texbox class
	for (int i = 0; i < textboxes.size(); i++)
		textboxes[i]->SetPosition({ winSize.x / 2.0f, winSize.y / 5.0f });
}

/*==== Helper Functions ====*/
void UserSelect::PushBackElements(const sf::Vector2f& winSize)
{
	sf::Vector2f userButtonSize({ 100.0f, 50.0f });
	sf::Vector2f textboxSize({ 200.0f, 50.0f });
	unsigned int fontSize = 20;
	sf::Color lightBlue(0x669999);

	// If you change the button position here make sure to also change it in the UpdatePosition functions within the button classes
	buttons.push_back(make_unique<CreateUserButton>(userButtonSize, sf::Vector2f(winSize.x / 2.0f, (4.0f * winSize.y) / 5.0f), lightBlue, "AddUserIcon", *this));
	buttons.push_back(make_unique<LoginButton>(userButtonSize, sf::Vector2f(winSize.x / 2.0f, (2.0f * winSize.y) / 5.0f), lightBlue, "ContinueIcon", *this));

	// If you change the textbox position here make sure to also change it in the UpdatePosition function within the texbox class
	textboxes.push_back(make_unique<Textbox>(font, fontSize, textboxSize, sf::Vector2f(winSize.x / 2.0f, winSize.y / 5.0f), sf::Color::Black));
	textboxes.push_back(make_unique<Textbox>(font, fontSize, textboxSize, sf::Vector2f(winSize.x / 2.0f, (3.0f * winSize.y) / 5.0f), sf::Color::Black));
}