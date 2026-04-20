#pragma once
#include "AppState.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

/*
STAR BUTTONS / SCROLLER:
------------------------
Displays a row of stars in the top right corner.
Before the goal is set: clicking cycles through star_row0 -> star_row1 -> ... -> star_row5 -> star_row1 and calls SetGoal on each cycle past 0.
After the goal is set: displays starsN where N = GetWordsCounted() clamped to the goal.
*/

/*==== Star Goal Buttons ====*/
class StarButton
{
public:
	/*==== Constructor ====*/
	StarButton(AppState& appState);

	/*==== Main Behaviors ====*/
	void HandleClick(sf::Vector2f mousePos);
	void ConfirmGoal();
	void Draw(sf::RenderWindow& window);
	void UpdatePosition(const sf::Vector2f& winSize);
	bool Contains(sf::Vector2f mousePos) const;

	sf::FloatRect GetGlobalBounds() const;

private:
	AppState& app;
	sf::Sprite sprite;
	int _displayIndex = 0; // 0 = no stars, 1 = 1 star, ..., 5 = 5 stars. Updated based on app.goal.GetWordsCounted() and app.goal.GetGoal()
	static constexpr float _scale = 0.45f;
	sf::Vector2f _lastWinSize{ 0.0f, 0.0f }; // Stored so refreshing the sprite doesn't reset the position; updated in UpdatePosition

	/*==== Helper Functions =====*/
	void RefreshSprite();
	static string IndexToTextureName(int index);
};