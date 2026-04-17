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
*/

class LearningGoal
{
public:
	static constexpr int reviewsRequiredForGoal = 3; // Number of times a word must be rated green to count towards the goal
	static constexpr int wordsPerStar = 1; // 1 star = 1 word, 2 stars = 2 words, etc.

	/*==== Constructor ====*/
	// Pass the user's save filename so the goal can persist.
	LearningGoal(const string& userFilename);

	/*==== Goal Setting ====*/
	// Set goal to starCount words. Does nothing if goal already set this session.
	void SetGoal(int starCount);
	bool IsGoalSet() const;
	int GetGoal() const;

	/*==== Session Tracking ====*/
	// Call this function when a word is rated green. If the word reaches the required number of green ratings, it counts towards the goal.
	void RecordGreenRating(const string& word);
	int GetWordsCounted() const;
	bool IsGoalMet() const;

	/*==== Persistence ====*/
	// Save the current goal and progress to the user's save file. Call this when the user logs out or exits the program.
	void SaveProgress();
	int LoadProgress() const;

private:
	string _filename;
	int _goal = 0;
	bool _goalSet = false;
	unordered_map<string, int> _wordGreenCounts; // Maps word -> how many times each word has been rated green
	static constexpr const char* goalPrefix = "##GOAL="; // Prefix used in save file to identify goal
};