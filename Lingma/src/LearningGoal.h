#pragma once
#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

/*
LEARNING GOAL FUNCTIONALITY:
----------------------------
Track the learning goal for one login session.
Goal = N words, where a word "counts" if it was rated green (rating 3) at least 3 times this session.
Once set, the goal cannot be changed for the remainder of the session.
UPDATE: Goal data is saved to a separate file.
*/

class LearningGoal
{
public:
	static constexpr int reviewsRequiredForGoal = 1; // Number of times a word must be rated green to count towards the goal
	static constexpr int wordsPerStar = 1; // 1 star = 1 word, 2 stars = 2 words, etc.

	/*==== Constructor ====*/
	LearningGoal();

	/*==== Setup ====*/
	void SetUsername(const string& username); 

	// Set goal to starCount words. Does nothing if goal already set this session.
	void SetGoal(int starCount);
	bool IsGoalSet() const;
	int GetGoal() const;

	/*==== Session Tracking ====*/
	void RecordGreenRating(const string& word);
	int GetWordsCounted() const;
	bool IsGoalMet() const;

	/*==== Persistence ====*/
	int LoadProgress(); 
	void SaveProgress() const;

private:
	string _goalFilename; // e.g. "username_goal.txt"
	int _goal = 0;
	bool _goalSet = false;
	unordered_map<string, int> _wordGreenCounts; // Maps word -> how many times each word has been rated green
	static constexpr const char* goalPrefix = "GOAL="; // Prefix used in save file to identify goal
	static string BuildGoalFilename(const string& username);
};