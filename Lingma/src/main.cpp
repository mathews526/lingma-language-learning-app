#include <SFML/Graphics.hpp>
#include <memory>
#include "Screens.h"
#include "UserSelectScreen.h"
#include "MainMenuScreen.h"
#include "Card.h"
#include "TextureManager.h"
#include "SRS.h"
using namespace std;

void startProgram();

int main()
{
	startProgram();
	
	return 0;
}

void startProgram() 
{
	unsigned int width = 854;
	unsigned int height = 480;
	// Creates the window
	sf::RenderWindow window(sf::VideoMode({ width, height }), "Lingma");
	window.setFramerateLimit(60);

	// Creates a view (the camera)
	sf::View view(sf::FloatRect({ 0.0f, 0.0f }, { static_cast<float>(width), static_cast<float>(height) }));

	sf::Vector2f winSize = static_cast<sf::Vector2f>(window.getSize());
	unique_ptr<Screen> currentScreen = make_unique<UserSelect>(winSize);

	// Event Handling
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();

			// Handles resizing
			if (const auto* resized = event->getIf<sf::Event::Resized>())
			{
				float windowWidth = static_cast<float>(resized->size.x);
				float windowHeight = static_cast<float>(resized->size.y);

				view.setSize({ windowWidth, windowHeight }); // Updates the view size to match the new window size
				view.setCenter({ windowWidth / 2.0f, windowHeight / 2.0f }); // Resets the center of the view so (0,0) stays at the top-left
				window.setView(view);

				winSize = static_cast<sf::Vector2f>(window.getSize()); // Stores the new window size
			}

			// Current screen handles its own events
			if (currentScreen)
				currentScreen->HandleEvents(*event, window);
		}

		// Updates page elements (e.g. Buttons)
		if (currentScreen)
			currentScreen->Update(winSize);

		if (currentScreen->nextScreen != ScreenType::None)
		{
			// Check which screen was requested requested
			if (currentScreen->nextScreen == ScreenType::MainMenu)
				currentScreen = make_unique<MainMenu>(winSize); // Updates to MainMenu screen

			// TODO: Add more else-if blocks here later for the other screens
		}

		// RENDER SPRITES HERE

		window.clear(sf::Color(240, 240, 240)); // Light grey background

		// Draws elements based on current screen
		if (currentScreen)
			currentScreen->Draw(window);

		window.display();
	}

	TextureManager::Clear();
}
