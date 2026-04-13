#pragma once
#include "Screens.h"
#include "Card.h"
#include <SFML/Graphics.hpp>
#include <queue>
#include <string>
#include <optional>
using std::queue;
using std::string;
using std::optional;

struct Review : public Screen
{
	/*==== Constructor ====*/
	Review(const sf::Vector2f& winSize, const std::string& fileName);

	/*==== Main Behavior ====*/
	void Draw(sf::RenderWindow& window);
	void Update(const sf::Vector2f& winSize);

	void RateCurrentCard(int rating);
	void PlayCurrentAudio();

private:
	string filename;
	queue<Card> cardQueue;
	Card currentCard;
	bool hasCurrentCard = false;

	optional<sf::Sprite> cardImage;

	/*==== Helper Functions ====*/
	void PushBackElements(const sf::Vector2f& winSize); // Pushes all the button objects into the buttons vector
	void LoadCurrentCard();
	void PositionCardImage(const sf::Vector2f& winSize);
};