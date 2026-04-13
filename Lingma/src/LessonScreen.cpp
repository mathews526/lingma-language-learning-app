#include "LessonScreen.h"
#include "CardButtons.h"
#include "SRS.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

/*==== Constructor ====*/
Lesson::Lesson(const sf::Vector2f& winSize, const string& filename)
	: filename(filename)
{
	cardQueue = getLessonQueue(filename);

	PushBackElements(winSize);
	LoadCurrentCard();
	PositionCardImage(winSize);
}

/*==== Main Behavior ====*/
void Lesson::Draw(sf::RenderWindow& window)
{
	Screen::Draw(window);

	// Draw unique screen-specific elements below
	if (cardImage)
		window.draw(*cardImage);
}
void Lesson::Update(const sf::Vector2f& winSize)
{

}
void Lesson::NextCard()
{
	if (cardQueue.empty())
		return;
	cardQueue.pop();
	LoadCurrentCard();
}
void Lesson::PlayCurrentAudio()
{
	if (hasCurrentCard && audioPlayer)
		audioPlayer->play();
}

/*==== Helper Functions ====*/
void Lesson::PushBackElements(const sf::Vector2f& winSize)
{
	sf::Vector2f audioButtonSize({ 50.0f, 50.0f });
	sf::Vector2f navigationButtonSize({ 50.0f, 50.0f });
	sf::Color gray(200, 200, 200);

	// If you change the button position here make sure to also change it in the UpdatePosition functions within the button classes
	buttons.push_back(make_unique<AudioButton>(audioButtonSize, sf::Vector2f(winSize.x / 2.0f, (5.0f * winSize.y) / 8.0f), gray, "audioicon", *this)); // Audio Button
	buttons.push_back(make_unique<NextButton>(navigationButtonSize, sf::Vector2f((7.0f * winSize.x) / 8.0f, (7.0f * winSize.y) / 8.0f), gray, "ContinueIcon", *this)); // Next Button
	buttons.push_back(make_unique<BackButton>(navigationButtonSize, sf::Vector2f(winSize.x / 8.0f, winSize.y / 8.0f), gray, "BackIcon", *this)); // Back Button
}
void Lesson::LoadCurrentCard()
{
	if (cardQueue.empty())
	{
		hasCurrentCard = false;
		cardImage.reset();

		if (audioPlayer)
			audioPlayer->stop();

		nextScreen = ScreenType::MainMenu;
		return;
	}

	hasCurrentCard = true;
	currentCard = cardQueue.front();

	const string& name = currentCard.getWord();

	cardImage.emplace(TextureManager::GetTexture(name));

	if (audioBuffer.loadFromFile("audio/wordbatch1/" + name + ".flac"))
	{
		if (!audioPlayer)
			audioPlayer.emplace(audioBuffer);
		else
			audioPlayer->setBuffer(audioBuffer);
	}
	else
		audioPlayer.reset();
}
void Lesson::PositionCardImage(const sf::Vector2f& winSize)
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