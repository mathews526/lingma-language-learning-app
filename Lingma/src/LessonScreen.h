#pragma once
#include "Screens.h"
#include "Card.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <queue>
#include <optional>
#include <string>
using std::queue;
using std::string;
using std::optional;

struct Lesson : public Screen
{
	/*==== Constructor ====*/
	Lesson(const sf::Vector2f& winSize, const std::string& filename);

	/*==== Main Behavior ====*/
	void Draw(sf::RenderWindow& window);
	void Update(const sf::Vector2f& winSize);

	void NextCard();
	void PlayCurrentAudio();

private:
	string filename;
	queue<Card> cardQueue;
	Card currentCard;
	bool hasCurrentCard = false;

	optional<sf::Sprite> cardImage;
	sf::SoundBuffer audioBuffer;
	optional<sf::Sound> audioPlayer;

	/*==== Helper Functions ====*/
	void PushBackElements(const sf::Vector2f& winSize); // Pushes all the button objects into the buttons vector
	void LoadCurrentCard();
	void PositionCardImage(const sf::Vector2f& winSize);
};