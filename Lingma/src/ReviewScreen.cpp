#include "ReviewScreen.h"
#include "CardButtons.h"
#include "SRS.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

/*==== Constructor ====*/
Review::Review(const sf::Vector2f& winSize, AppState& appState)
	: app(appState), filename(appState.currentUserFile)
{
	refreshAvailable(filename);
	cardQueue = getQueue(filename);

	PushBackElements(winSize);
	LoadCurrentCard();
	PositionCardImage(winSize);
}

/*==== Main Behavior ====*/
void Review::Draw(sf::RenderWindow& window)
{
	Screen::Draw(window);

	// Draw unique screen-specific elements below
	if (hasCurrentCard)
		window.draw(*cardImage);
}
void Review::Update(const sf::Vector2f& winSize)
{
	Screen::Update(winSize);
	PositionCardImage(winSize);
}
void Review::RateCurrentCard(int rating)
{
	if (!hasCurrentCard)
		return;

	// UPDATE: Record green rating for goal tracking
	if (rating == 3)
		app.goal.RecordGreenRating(currentCard.getWord());


	currentCard.setLvl(rating);

	time_t now = time(nullptr); // returns current time

	// If mastered, do not schedule it for review anymore
	if (currentCard.getLvl() >= 5)
	{
		Card updated(currentCard.getWord(), currentCard.getLvl(), static_cast<int>(now), 0, false);

		updateFile(filename, updated);
		cardQueue.pop();
		LoadCurrentCard();
		return;
	}

	time_t next = setNext(now, currentCard.getLvl());

	Card updated(currentCard.getWord(), currentCard.getLvl(), static_cast<int>(now), static_cast<int>(next), false);

	updateFile(filename, updated);

	cardQueue.pop();
	LoadCurrentCard();
}

/*==== Helper Functions ====*/
void Review::PushBackElements(const sf::Vector2f& winSize)
{
	sf::Vector2f coloredButtonsSize({ 100.0f, 50.0f });
	sf::Vector2f audioButtonSize({ 50.0f, 50.0f });
	sf::Vector2f navigationButtonSize({ 50.0f, 50.0f });
	sf::Color gray(200, 200, 200);

	// If you change the button position here make sure to also change it in the UpdatePosition functions within the button classes
	buttons.push_back(make_unique<RedButton>(coloredButtonsSize, sf::Vector2f(winSize.x / 3.0f, (7.0f * winSize.y) / 8.0f), sf::Color::Red, *this)); // Red Button
	buttons.push_back(make_unique<YellowButton>(coloredButtonsSize, sf::Vector2f(winSize.x / 2.0f, (7.0f * winSize.y) / 8.0f), sf::Color::Yellow, *this)); // Yellow Button
	buttons.push_back(make_unique<GreenButton>(coloredButtonsSize, sf::Vector2f((2.0f * winSize.x) / 3.0f, (7.0f * winSize.y) / 8.0f), sf::Color::Green, *this)); // Green Button
	buttons.push_back(make_unique<BackButton>(navigationButtonSize, sf::Vector2f(winSize.x / 8.0f, winSize.y / 8.0f), gray, "BackIcon", *this)); // Back Button
}
void Review::LoadCurrentCard()
{
	if (cardQueue.empty())
	{
		hasCurrentCard = false;
		cardImage.reset();

		nextScreen = ScreenType::MainMenu;
		return;
	}

	hasCurrentCard = true;
	currentCard = cardQueue.front();

	const string& name = currentCard.getWord();

	cardImage.emplace(TextureManager::GetTexture(name));
}
void Review::PositionCardImage(const sf::Vector2f& winSize)
{
	if (!hasCurrentCard || !cardImage)
		return;

	const sf::Texture* texture = &cardImage->getTexture();
	sf::Vector2u textureSize = texture->getSize();
	
	float maxWidth = winSize.x * 0.45f;
	float maxHeight = winSize.y * 0.35f;

	float scaleX = maxWidth / static_cast<float>(textureSize.x);
	float scaleY = maxHeight / static_cast<float>(textureSize.y);
	float scale = std::min(scaleX, scaleY);

	cardImage->setScale({ scale, scale });

	sf::FloatRect bounds = cardImage->getLocalBounds();
	cardImage->setOrigin({ bounds.position.x + (bounds.size.x / 2.0f), bounds.position.y + (bounds.size.y / 2.0f) });
	cardImage->setPosition({ winSize.x / 2.0f, (3.0f * winSize.y) / 10.0f });
}