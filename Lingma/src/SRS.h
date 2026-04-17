#pragma once
#include <string>
#include <queue>
#include <ctime>
#include "Card.h"
using std::string;
using std::queue;
using std::time_t;

void review();
void refreshAvailable(string filename);
queue<Card> getQueue(string filename);
queue<Card> getLessonQueue(string filename);
int getRating();
time_t setNext(time_t& now, int srsLvl);
void updateFile(string filename, Card& card);