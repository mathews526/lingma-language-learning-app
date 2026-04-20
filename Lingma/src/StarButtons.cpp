#include "StarButtons.h"
#include "TextureManager.h"
#include <algorithm>
#include <string>
using namespace std;

/*==== StarButton Functions ====*/
StarButton::StarButton(AppState& appState) : app(appState), sprite(TextureManager::GetTexture(IndexToTextureName(0)))
{
	if (app.goal.IsGoalSet()) 
	{
		int progress = min(app.goal.GetWordsCounted(), app.goal.GetGoal());
		_displayIndex = progress;
	}
	sprite.setTexture(TextureManager::GetTexture(IndexToTextureName(_displayIndex)), true);
}

/*==== Main Behaviors ====*/
void StarButton::HandleClick(sf::Vector2f mousePos)
{
	if (app.goal.IsGoalSet())
		return;
	if (!Contains(mousePos))
		return;

	// Figure out which star was clicked based on mouse position and update display index accordingly
	sf::FloatRect bounds = sprite.getGlobalBounds();
	float relX = mousePos.x - bounds.position.x;
	float starWidth = bounds.size.x / 5.0f; // Each star takes up 1/5 of the total width
	int clickedStar = static_cast<int>(relX / starWidth) + 1; // +1 because star index starts at 1
	if (clickedStar < 1)
		clickedStar = 1;
	if (clickedStar > 5)
		clickedStar = 5;
	
	_displayIndex = clickedStar;
	RefreshSprite();
}

void StarButton::ConfirmGoal()
{
	if (app.goal.IsGoalSet())
		return;
	if (_displayIndex > 0)
		app.goal.SetGoal(_displayIndex);
}

void StarButton::Draw(sf::RenderWindow& window)
{
	if (app.goal.IsGoalSet())
	{
		int progress = min(app.goal.GetWordsCounted(), app.goal.GetGoal());
		if (progress != _displayIndex)
		{
			_displayIndex = progress;
			RefreshSprite();
		}
	}
	window.draw(sprite);
}

void StarButton::UpdatePosition(const sf::Vector2f& winSize)
{
	_lastWinSize = winSize;
	sprite.setScale({ _scale, _scale });

	sf::FloatRect bounds = sprite.getGlobalBounds();
	sprite.setOrigin({ 0.0f, 0.0f });
	sprite.setPosition({ winSize.x - bounds.size.x, 0.0f });
}

bool StarButton::Contains(sf::Vector2f mousePos) const
{
	return sprite.getGlobalBounds().contains(mousePos);
}

sf::FloatRect StarButton::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

/*==== Helper Functions ====*/
void StarButton::RefreshSprite()
{
	// Swap texture
	sprite.setTexture(TextureManager::GetTexture(IndexToTextureName(_displayIndex)), true);
	if (_lastWinSize.x > 0.0f)
		UpdatePosition(_lastWinSize);
}

string StarButton::IndexToTextureName(int index)
{
	return "star_row" + to_string(index); // e.g. "star_row0.png", "star_row1.png", ..., "star_row5.png"
}

