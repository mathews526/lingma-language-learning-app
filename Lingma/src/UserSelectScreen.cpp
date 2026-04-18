#include "UserSelectScreen.h"
#include "UserSelectButtons.h"
#include "Textbox.h"
#include "LocalStorage.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <cctype>
using namespace std;

/*==== Constructor ====*/
UserSelect::UserSelect(const sf::Vector2f& winSize, AppState& appState)
	: app(appState)
{
	LoadFont("Verdana");
	PushBackElements(static_cast<sf::Vector2f>(winSize));
}

/*==== Main Behavior ====*/
void UserSelect::HandleEvents(const sf::Event& event, sf::RenderWindow& window)
{
	// Let the base screen handle button MousePress calls.
	Screen::HandleEvents(event, window);
	
	// Textbox will be selected when clicked on and deselected when clicking somewhere else
	if (const auto* mousePress = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mousePress->button == sf::Mouse::Button::Left)
		{
			sf::Vector2f mousePos = window.mapPixelToCoords(mousePress->position);

			bool clickedButton = false;
			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons[i]->Contains(mousePos))
				{
					clickedButton = true;
					break;
				}
			}

			if (!clickedButton)
			{
				for (int i = 0; i < textboxes.size(); i++)
					textboxes[i]->SetSelected(textboxes[i]->Contains(mousePos));
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
	textboxes[0]->SetPosition({ winSize.x / 2.0f, winSize.y / 5.0f });
	textboxes[1]->SetPosition({ winSize.x / 2.0f, (3.0f * winSize.y) / 5.0f });
}
void UserSelect::CreateUserFromBottomTextbox()
{
	if (textboxes.empty())
		return;

	ActivateUser(textboxes[1]->GetText(), true);
}
void UserSelect::LoginUserFromTopTextbox()
{
	ActivateUser(textboxes[0]->GetText(), false);
}

/*==== Helper Functions ====*/
void UserSelect::PushBackElements(const sf::Vector2f& winSize)
{
	sf::Vector2f userButtonSize({ 100.0f, 50.0f });
	sf::Vector2f textboxSize({ 200.0f, 50.0f });
	unsigned int fontSize = 20;
	sf::Color lightBlue(0x669999);

	// If you change the textbox position here make sure to also change it in the UpdatePosition function within the texbox class
	textboxes.push_back(make_unique<Textbox>(font, fontSize, textboxSize, sf::Vector2f(winSize.x / 2.0f, winSize.y / 5.0f), sf::Color::Black)); // Login textbox
	textboxes.push_back(make_unique<Textbox>(font, fontSize, textboxSize, sf::Vector2f(winSize.x / 2.0f, (3.0f * winSize.y) / 5.0f), sf::Color::Black)); // CreateUser textbox

	// If you change the button position here make sure to also change it in the UpdatePosition functions within the button classes
	buttons.push_back(make_unique<LoginButton>(userButtonSize, sf::Vector2f(winSize.x / 2.0f, (2.0f * winSize.y) / 5.0f), lightBlue, "ContinueIcon", *this)); // Login button
	buttons.push_back(make_unique<CreateUserButton>(userButtonSize, sf::Vector2f(winSize.x / 2.0f, (4.0f * winSize.y) / 5.0f), lightBlue, "AddUserIcon", *this)); // CreateUser button
}
bool UserSelect::ActivateUser(const string& rawUsername, bool createMode)
{
	string username = rawUsername;

	if (!IsValidUsername(username))
		return false;

	const string sampleFile = "data/sampleSRS.txt";
	const string userFile = "data/" + username + ".txt";

	if (createMode)
	{
		if (FileExists(userFile))
			return false;

		if (!FileExists(sampleFile))
			return false;

		if (!CopyFileStream(sampleFile, userFile))
			return false;
	}
	else
	{
		if (!FileExists(userFile))
			return false;
	}

	UserProgress progress;
	if (!app.storage.loadUserProgress(username, progress))
	{
		app.storage.saveUserProgress(UserProgress{ username, 0, 0, 0 });
	}

	app.currentUsername = username;
	app.currentUserFile = userFile;
	nextScreen = ScreenType::MainMenu;
	return true;
}
bool UserSelect::CopyFileStream(const string& source, const string& destination) const
{
	ifstream in(source, ios::binary);
	ofstream out(destination, ios::binary);

	if (!in || !out)
		return false;

	out << in.rdbuf();
	return true;
}
bool UserSelect::FileExists(const string& path) const
{
	ifstream in(path);
	return in.good();
}
bool UserSelect::IsValidUsername(const string& s)
{
	if (s.empty())
		return false;

	for (unsigned char c : s)
	{
		if (!(std::isalnum(c) || c == '_' || c == '-'))
			return false;
	}

	return true;
}