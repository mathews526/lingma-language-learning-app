#include "LocalStorage.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Constructor
LocalStorage::LocalStorage(const string& file) {
    filename = "data/" + file;
}

// Check if file exists
bool LocalStorage::fileExists() const {
    ifstream inFile(filename);
    return inFile.good();
}

// Load all users from file
vector<UserProgress> LocalStorage::loadAllProgress() const {
    vector<UserProgress> users;
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        return users;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        UserProgress user;

        ss >> user.username >> user.lessonNumber >> user.completionPercent >> user.streak;

        if (!ss.fail()) {
            users.push_back(user);
        }
    }

    inFile.close();
    return users;
}

// Save all users to file
void LocalStorage::saveAllProgress(const vector<UserProgress>& users) const {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cout << "Error: Could not open file for writing." << endl;
        return;
    }

    for (size_t i = 0; i < users.size(); i++) {
        outFile << users[i].username << " "
            << users[i].lessonNumber << " "
            << users[i].completionPercent << " "
            << users[i].streak << endl;
    }

    outFile.close();
}

// Save or update one user's progress
void LocalStorage::saveUserProgress(const UserProgress& newUser) const {
    vector<UserProgress> users = loadAllProgress();
    bool found = false;

    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].username == newUser.username) {
            users[i] = newUser;
            found = true;
            break;
        }
    }

    if (!found) {
        users.push_back(newUser);
    }

    saveAllProgress(users);
}



// Load one user by username
bool LocalStorage::loadUserProgress(const string& username, UserProgress& result) const {
    vector<UserProgress> users = loadAllProgress();

    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].username == username) {
            result = users[i];
            return true;
        }
    }

    return false;
}


/* Notes from meeting : Create a function that creates a new user string and create the text file with all the vocab words
   and default it to SRS level 1, and dummy timestamps and set the variable Boolean to false = 0 with all the words */

   //Saving vocab words for a new user to a separate file with Default SRS level 1
bool LocalStorage::createNewUserVocabFile(const string& username) const {
    string userFileName = username + ".txt";
    ofstream outFile(userFileName);

    if (!outFile.is_open()) {
        cout << "Error: Could not create vocab file for user " << username << endl;
        return false;
    }

    // Format:
    // word,srsLevel,lastReviewed,nextReview,availablity


    const auto& vocabRef = this->vocab;
    for (size_t i = 0; i < vocabRef.size(); i++) {
        outFile << vocabRef[i] << ","
            << 1 << ","
            << "1767225600" << ","
            << "1767225600" << ","
            << 0 << endl;
    }

    outFile.close();
    return true;
}

vector<string> LocalStorage::getVocab() const
{
    return vocab;
}