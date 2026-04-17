#include "LearningGoal.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

/*==== Constructor ====*/
LearningGoal::LearningGoal(const string& userFilename)
	: _filename(userFilename)
{
}

/*==== Goal Setting ====*/
void LearningGoal::SetGoal(int starCount)
{
	if (_goalSet) return; // Goal already set this session, do nothing
	_goal = starCount * wordsPerStar; // Convert stars to words
	_goalSet = true;
	SaveProgress(); // Save the goal immediately so it persists even if the user doesn't log out properly
}

bool LearningGoal::IsGoalSet() const
{
	return _goalSet;
}

int LearningGoal::GetGoal() const
{
	return _goal;
}

/*==== Session Tracking ====*/
void LearningGoal::RecordGreenRating(const string& word)
{
	_wordGreenCounts[word]++;
}

int LearningGoal::GetWordsCounted() const
{
	int count = 0;
	for (const auto& [word, ratings] :_wordGreenCounts)
	{
		if (ratings >= reviewsRequiredForGoal)
			count++;
	}
	return count;
}

bool LearningGoal::IsGoalMet() const
{
	if (!_goalSet || _goal <= 0) return false; // No valid goal set
	return GetWordsCounted() >= _goal;
}

/*==== Persistence ====*/
void LearningGoal::SaveProgress()
{
	// Read existing data to preserve it
	ifstream inFile(_filename);
	if (!inFile.is_open())
	{
		cerr << "Error: Could not open file for saving learning goal: " << _filename << endl;
		return;
	}

	vector<string> lines;
	string line;
	while (getline(inFile, line))
	{
		// Strip out any existing goal lines
		if (line.find(goalPrefix) == string::npos)
			lines.push_back(line);
	}
	inFile.close();

	// Append the current goal and progress
	ofstream outFile(_filename, ios::trunc);
	if (!outFile.is_open())
	{
		cerr << "Error: Could not open file for saving learning goal: " << _filename << endl;
		return;
	}

	for (const auto& l : lines)
		outFile << l << "\n"; // Write back preserved lines

	outFile << goalPrefix << _goal << "\n";
	outFile.close();
}

int LearningGoal::LoadProgress() const
{
	ifstream inFile(_filename);
	if (!inFile.is_open())
		return 0;

	string line;
	int found = 0;
	string prefix(goalPrefix);
	while (getline(inFile, line))
	{
		if (line.find(goalPrefix) == 0)
		{
			string numStr = line.substr(prefix.size());
			try
			{
				found = stoi(numStr);
			}
			catch (const invalid_argument&)
			{
				cerr << "Error: Invalid goal format in save file: " << numStr << endl;
				return 0;
			}
		}
	}
	inFile.close();
	return found;
}