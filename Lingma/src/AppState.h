#pragma once
#include <string>
#include "LocalStorage.h"
using std::string;

struct AppState
{
	string currentUsername;
	string currentUserFile = "data/sampleSRS.txt";
	LocalStorage storage;

	UserProgress progress;

	AppState();
};