#ifndef LOCALSTORAGE_H
#define LOCALSTORAGE_H

#include <string>
#include <vector>

using namespace std;

// Struct to hold one user's progress
struct UserProgress {
    string username;
    int lessonNumber;
    int completionPercent;
    int streak;
};

// Class for saving/loading progress locally from a text file
class LocalStorage {
private:
    string filename;

public:
    // Constructor
    LocalStorage(const string& file);

    // Confirm if file exists
    bool fileExists() const;

    // Loads all user progress from the file
    vector<UserProgress> loadAllProgress() const;

    // Saves user progress records to the file
    void saveAllProgress(const vector<UserProgress>& users) const;

    // Saves or updates one user's progress
    void saveUserProgress(const UserProgress& newUser) const;

    // Loads one user's progress by username
    bool loadUserProgress(const string& username, UserProgress& result) const;
};

#endif