#include "MainMenuScreen.h"
#include "MainMenuButtons.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
using namespace std;

/*==== Constructor ====*/
MainMenu::MainMenu(const sf::Vector2f& winSize, AppState& appState)
	: app(appState)
{
	LoadFont("Verdana");
	levelLabelText.emplace(font, "", 16);
	countText.emplace(font, "", 16);

	levelLabelText->setFillColor(sf::Color::Black);
	countText->setFillColor(sf::Color::Black);
	
	LoadDashboardData();
	PushBackElements(winSize);

	BuildDashboardVisuals(winSize);
	PositionDashboard(winSize);
}

/*==== Main Behavior ====*/
void MainMenu::Draw(sf::RenderWindow& window)
{
	Screen::Draw(window);

	// Draw unique screen-specific elements below
	window.draw(dashboardBox);
	window.draw(progressBack);
	window.draw(progressFill);

	for (int i = 0; i < 6; i++)
	{
		window.draw(levelTiles[i]);

		if (levelLabelText)
		{
			string text = "LVL ";
			levelLabelText->setString(to_string(i));
			text += levelLabelText->getString();
			levelLabelText->setString(text);
			levelLabelText->setPosition({ levelTiles[i].getPosition().x - (levelTiles[i].getSize().x / 2.0f) + 8.0f, levelTiles[i].getPosition().y - (levelTiles[i].getSize().y / 2.0f) + 4.0f});
			window.draw(*levelLabelText);
		}

		if (countText)
		{
			countText->setString(to_string(levelCounts[i]));
			countText->setPosition({ levelTiles[i].getPosition().x - 4.0f, levelTiles[i].getPosition().y - 8.0f});
			window.draw(*countText);
		}
	}
}
void MainMenu::Update(const sf::Vector2f& winSize)
{
	Screen::Update(winSize);
	PositionDashboard(winSize);
}

/*==== Helper Functions ====*/
void MainMenu::PushBackElements(const sf::Vector2f& winSize)
{
	sf::Vector2f largeButtonSize({ 325.0f, 125.0f });
	sf::Color lightBlue(0xcc, 0xff, 0xff);
	sf::Color limeGreen(0xccff66ff);

	// If you change the button position here make sure to also change it in the UpdatePosition functions within the button classes
	buttons.push_back(make_unique<LessonButton>(largeButtonSize, sf::Vector2f(winSize.x / 4.0f, winSize.y / 4.0f), lightBlue, "learn", *this));
	buttons.push_back(make_unique<ReviewButton>(largeButtonSize, sf::Vector2f((3.0f * winSize.x) / 4.0f, winSize.y / 4.0f), limeGreen, "review", *this));
}
void MainMenu::LoadDashboardData()
{
	levelCounts.fill(0);
	totalCards = 0;

	ifstream infile(app.currentUserFile);
	if (!infile)
		return;

	string line;
	while (getline(infile, line))
	{
		stringstream ss(line);
		string word, srslevel, lastStr, nextStr, availableStr;

		getline(ss, word, ',');
		getline(ss, srslevel, ',');
		getline(ss, lastStr, ',');
		getline(ss, nextStr, ',');
		getline(ss, availableStr, ',');

		if (srslevel.empty())
			continue;

		int lvl = stoi(srslevel);
		if (lvl < 0)
			lvl = 0;
		if (lvl > 5)
			lvl = 5;

		levelCounts[lvl]++;
		totalCards++;
	}
}
void MainMenu::BuildDashboardVisuals(const sf::Vector2f& winSize)
{
	dashboardBox.setSize({ 750.0f, 200.0f });
	dashboardBox.setFillColor(sf::Color(240, 240, 240));
	dashboardBox.setOutlineThickness(2.0f);
	dashboardBox.setOutlineColor(sf::Color(180, 180, 180));

	progressBack.setSize({ 660.0f, 18.0f });
	progressBack.setFillColor(sf::Color(220, 220, 220));

	float masteredRatio = 0.0f;
	if (totalCards > 0)
		masteredRatio = static_cast<float>(levelCounts[5]) / static_cast<float>(totalCards);

	progressFill.setSize({ progressBack.getSize().x * masteredRatio, progressBack.getSize().y });
	progressFill.setFillColor(sf::Color(120, 200, 120));

	sf::Vector2f tileSize(100.0f, 100.0f);
	float startX = 90.0f;
	float startY = 495.0f;
	float gap = 15.0f;

	sf::Color tileColors[6] = {
		sf::Color(200, 200, 200),
		sf::Color(120, 180, 255),
		sf::Color(120, 220, 160),
		sf::Color(255, 220, 120),
		sf::Color(255, 180, 120),
		sf::Color(240, 200, 80)
	};

	for (int i = 0; i < 6; i++)
	{
		levelTiles[i].setSize({ tileSize.x, tileSize.y });
		levelTiles[i].setFillColor(tileColors[i]);
		levelTiles[i].setOutlineThickness(2.0f);
		levelTiles[i].setOutlineColor(sf::Color(100, 100, 100));
	}
}
void MainMenu::PositionDashboard(const sf::Vector2f& winSize)
{
	sf::Vector2f dashboardPos(winSize.x / 2.0f, (4.0f * winSize.y) / 6.0f);

	dashboardBox.setOrigin(dashboardBox.getGeometricCenter());
	dashboardBox.setPosition({ dashboardPos.x , dashboardPos.y });
	progressBack.setOrigin(progressBack.getGeometricCenter());
	progressBack.setPosition({ winSize.x / 2.0f, dashboardPos.y - (dashboardBox.getSize().y / 3.0f)});
	progressFill.setPosition({ progressBack.getPosition().x - (progressBack.getSize().x / 2.0f), progressBack.getPosition().y - (progressBack.getSize().y / 2.0f) });

	sf::Vector2f tileSize(100.0f, 100.0f);
	float startX = dashboardBox.getPosition().x - ((dashboardBox.getSize().x / 2.0f) - (tileSize.x / 2.0f) - 25.0f);
	float startY = dashboardBox.getPosition().y + ((dashboardBox.getSize().y / 3.0f) - (tileSize.x / 2.0f));
	float gap = 20.0f;

	for (int i = 0; i < 6; i++)
	{
		levelTiles[i].setOrigin(levelTiles[i].getGeometricCenter());
		levelTiles[i].setPosition({ startX + i * (tileSize.x + gap), startY });
	}
}