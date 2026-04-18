#pragma once
#include "Screens.h"
#include "Buttons.h"
#include "Textbox.h"
#include "AppState.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
using std::vector;
using std::unique_ptr;
using std::string;

struct UserSelect : public Screen
{
	/*==== Constructors / Destructors ====*/
	UserSelect(const sf::Vector2f& winSize, AppState& appState); // Create buttons here

	/*==== Main Behavior ====*/
	void HandleEvents(const sf::Event& event, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void Update(const sf::Vector2f& winSize);

	void LoginUserFromTopTextbox();
	void CreateUserFromBottomTextbox();
private:
	AppState& app;

	vector<unique_ptr<Textbox>> textboxes;

	/*==== Helper Functions ====*/
	void PushBackElements(const sf::Vector2f& winSize); // Pushes all the button objects into the buttons vector
	bool ActivateUser(const string& rawUsername, bool createMode);
	bool CopyFileStream(const string& source, const string& destination) const;
	bool FileExists(const string& path) const;
	static bool IsValidUsername(const std::string& s);
};