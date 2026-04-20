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
	: app(appState), starButton(appState)
{
	LoadFont("Verdana");
	levelLabelText.emplace(font, "", 16);
	countText.emplace(font, "", 16);

	// UPDATE: Goal bar elements
	goalBarLabel.emplace(font, "", 13);

	levelLabelText->setFillColor(sf::Color::Black);
	countText->setFillColor(sf::Color::Black);

	// UPDATE: Goal bar elements
	goalBarLabel->setFillColor(sf::Color::Black);
	
	LoadDashboardData();
	PushBackElements(winSize);

	BuildDashboardVisuals(winSize);
	PositionDashboard(winSize);

	// UPDATE: Add goal buttons
	BuildGoalVisuals(winSize);
	PositionGoalVisuals(winSize);
	starButton.UpdatePosition(winSize);
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

	// UPDATE: Draw goal bar elements
	if (app.goal.IsGoalSet())
	{
		window.draw(goalBarBack);
		window.draw(goalBarFill);
		if (goalBarLabel)
			window.draw(*goalBarLabel);
	}
	starButton.Draw(window);
}
void MainMenu::Update(const sf::Vector2f& winSize)
{
	Screen::Update(winSize);
	PositionDashboard(winSize);

	// UPDATE: Position goal bar elements
	BuildGoalVisuals(winSize);
	PositionGoalVisuals(winSize);
	starButton.UpdatePosition(winSize);
}

// UPDATE: Handle click and enter for star goal elements; keeps MouseClick from getting too messy
void MainMenu::HandleEvents(const sf::Event& event, sf::RenderWindow& window)
{
	Screen::HandleEvents(event, window);
	if (const auto* mousePress = event.getIf<sf::Event::MouseButtonPressed>()) 
	{
		if (mousePress->button == sf::Mouse::Button::Left) 
		{
			sf::Vector2f mousePos = window.mapPixelToCoords(mousePress->position);
			starButton.HandleClick(mousePos);
		}
	}

	if (const auto* keyPress = event.getIf<sf::Event::KeyPressed>()) 
	{
		if (keyPress->code == sf::Keyboard::Key::Enter) 
		{
			starButton.ConfirmGoal();
		}
	}
}

/*==== Helper Functions ====*/
void MainMenu::PushBackElements(const sf::Vector2f& winSize)
{
	sf::Vector2f largeButtonSize({ 325.0f, 125.0f });
	sf::Color cloudBlue(215, 235, 255);
	sf::Color pastelTeal(200, 240, 240);

	// If you change the button position here make sure to also change it in the UpdatePosition functions within the button classes
	buttons.push_back(make_unique<LessonButton>(largeButtonSize, sf::Vector2f(winSize.x / 4.0f, winSize.y / 4.0f), pastelTeal, "learn", *this));
	buttons.push_back(make_unique<ReviewButton>(largeButtonSize, sf::Vector2f((3.0f * winSize.x) / 4.0f, winSize.y / 4.0f), cloudBlue, "review", *this));
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
		sf::Color(255, 180, 180),
		sf::Color(255, 210, 180),
		sf::Color(255, 255, 190),
		sf::Color(210, 245, 190),
		sf::Color(180, 235, 200)
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

// UPDATE: Goal bar helper functions
void MainMenu::BuildGoalVisuals(const sf::Vector2f& winSize)
{
	goalBarBack.setSize({ 120.0f, 14.0f });
	goalBarBack.setFillColor(sf::Color(220, 220, 220));
	goalBarFill.setOutlineThickness(1.0f);
	goalBarFill.setOutlineColor(sf::Color(160, 160, 160));

	float ratio = 0.0f;
	if (app.goal.IsGoalSet() && app.goal.GetGoal() > 0)
		ratio = static_cast<float>(app.goal.GetWordsCounted()) / static_cast<float>(app.goal.GetGoal());
	if (ratio > 1.0f) 
		ratio = 1.0f;

	goalBarFill.setSize({ goalBarBack.getSize().x * ratio, goalBarBack.getSize().y });
	goalBarFill.setFillColor(app.goal.IsGoalMet() ? sf::Color(100, 200, 100) : sf::Color(100, 160, 220));
}

void MainMenu::PositionGoalVisuals(const sf::Vector2f& winSize)
{
	if (!app.goal.IsGoalSet())
		return;

	sf::FloatRect starBounds = starButton.GetGlobalBounds();
	float barHeight = goalBarBack.getSize().y;
	float barWidth = goalBarBack.getSize().x;
	float gap = 15.0f;
	
	// Align bar vertically to center of the star sprite
	float barX = starBounds.position.x - barWidth - gap; 
	float topY = starBounds.position.y + (starBounds.size.y / 2.0f) - (barHeight / 2.0f);

	goalBarBack.setPosition({ barX, topY });
	goalBarFill.setPosition({ barX, topY });

	if (goalBarLabel)
	{
		string labelStr = to_string(min(app.goal.GetWordsCounted(), app.goal.GetGoal())) + " / " + to_string(app.goal.GetGoal()) + " words";
		goalBarLabel->setString(labelStr);
		sf::FloatRect bounds = goalBarLabel->getLocalBounds();
		goalBarLabel->setOrigin({ bounds.position.x + bounds.size.x / 2.0f, 0.0f });
		goalBarLabel->setPosition({ barX + (barWidth / 2.0f), topY + goalBarBack.getSize().y + 4.0f });
	}
}