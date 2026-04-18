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