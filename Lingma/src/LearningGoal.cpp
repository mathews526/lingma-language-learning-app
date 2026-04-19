#include "LearningGoal.h"
#include <fstream>
#include <iostream>
using namespace std;

/*==== Constructor ====*/
LearningGoal::LearningGoal() {}

/*==== Setup ====*/
void LearningGoal::SetUsername(const string& username)
{
	_goalFilename = BuildGoalFilename(username);
	_goal = 0;
	_goalSet = false;
	_wordGreenCounts.clear();
}

void LearningGoal::SetGoal(int starCount)
{
	if (_goalSet) return; // Goal already set this session, do nothing
	_goal = starCount * wordsPerStar;
	_goalSet = true;
	SaveProgress();
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
	for (const auto& [word, ratings] : _wordGreenCounts)
	{
		if (ratings >= reviewsRequiredForGoal)
			count++;
	}
	return count;
}

bool LearningGoal::IsGoalMet() const
{
	if (!_goalSet || _goal <= 0) return false; // No goal set or invalid goal) 
	return GetWordsCounted() >= _goal;
}

/*==== Persistence ====*/
int LearningGoal::LoadProgress() 
{
	ifstream inFile(_goalFilename);
	if (!inFile.is_open()) return 0;
	string line;
	while (getline(inFile, line))
	{
		if (line.find(goalPrefix) == 0) {
			string numStream = line.substr(string(goalPrefix).size());
			try
			{
				_goal = stoi(numStream);
				_goalSet = (_goal > 0);
				inFile.close();
				return _goal;

			}
			catch (const invalid_argument&)
			{
				cerr << "Error: Invalid goal format in save file: " << numStream << endl;
			}
		}
	}
	inFile.close();
	return 0;
}

void LearningGoal::SaveProgress() const
{
	if (_goalFilename.empty()) 
	{
		cerr << "Error: LearningGoal has no filename set. Call SetUsername first." << endl;
		return;
	}
	ofstream outFile(_goalFilename, ios::trunc);
	if (!outFile.is_open()) 
	{
		cerr << "Error: Could not open goal file for saving: " << _goalFilename << endl;
		return;
	}
	outFile << goalPrefix << _goal << "\n";
	outFile.close();
}

/*==== Private Helpers ====*/
string LearningGoal::BuildGoalFilename(const string& username)
{
	return "data/" + username + "_goal.txt";
}