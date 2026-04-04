#include "MainMenuScreen.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
using namespace std;

MainMenu::MainMenu(const sf::Vector2f& winSize)
{
	// TODO: Call the pushBackButtons function
}
void MainMenu::HandleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	if (const auto* mousePress = event.getIf<sf::Event::MouseButtonPressed>())
	{
		// TODO: Call the mouse press function for the respective button if clicked on.
	}
}
void MainMenu::Draw(sf::RenderWindow& window)
{

}
void MainMenu::Update(const sf::Vector2f& winSize)
{

}
void MainMenu::PushBackButtons(const sf::Vector2f& winSize)
{
	// TODO: Push the buttons related to this screen to the buttons vector
}