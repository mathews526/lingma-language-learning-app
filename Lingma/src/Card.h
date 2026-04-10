#pragma once
#include <string>
using namespace std;

class Card
{
	string _word;
	int _srslvl = 0;
	int _last = 0;
	int _next = 0;
	bool _available = false;
public:
	Card() = default;
	Card(string word, int srslvl, int last, int next, bool available) : _word(word), _srslvl(srslvl), _last(last), _next(next), _available(available) {}
	string getWord() { return _word; }
	int getLvl() { return _srslvl; }
	int getLast() { return _last; }
	int getNext() { return _next; }
	bool getAvailable() { return _available; }

	void setLvl(int rating) {
		if (rating == 1 && getLvl() > 1) _srslvl -= 1;
		else if (rating == 3 && getLvl() < 11) _srslvl += 1;
	};
};