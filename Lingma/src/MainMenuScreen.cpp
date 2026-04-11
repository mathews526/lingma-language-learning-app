#include "MainMenuScreen.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
using namespace std;

MainMenu::MainMenu(const sf::Vector2f& winSize)
{
	// TODO: Call the pushBackButtons function
}
void MainMenu::Draw(sf::RenderWindow& window)
{
	Screen::Draw(window);

	// Draw unique screen-specific elements below
}
void MainMenu::PushBackButtons(const sf::Vector2f& winSize)
{
	// TODO: Push the buttons related to this screen to the buttons vector
}