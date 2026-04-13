#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <ctime>
#include "Card.h"
using namespace std;

void review();
void refreshAvailable(string filename);
queue<Card> getQueue(string filename);
queue<Card> getLessonQueue(string filename);
int getRating();
time_t setNext(time_t& now, int srsLvl);
void updateFile(string filename, Card& card);