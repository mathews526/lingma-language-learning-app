#pragma once
#include "LocalStorage.h"
#include <string>
using std::string;

struct AppState
{
	string currentUsername;
	string currentUserFile = "data/sampleSRS.txt";
	LocalStorage storage;

	AppState();
};