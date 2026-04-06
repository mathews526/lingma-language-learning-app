#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <queue>
#include <filesystem>
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

void refreshAvailable(string filename);
queue<Card> getQueue(string filename);
int getRating();
time_t setNext(time_t& now, int srsLvl);
void updateFile(string filename, Card& card);


int main()
{
	//user should be able to see available words on command line
	//rating 1, 2, or 3 should change timestamp in txt file

	string filename = "sampleSRS.txt";

	refreshAvailable(filename);

	queue<Card> q = getQueue(filename);

	while (!q.empty())
	{
		cout << "quizzing \"" << q.front().getWord() << "\"" << endl;

		//But actually access the images folder through SFML

		//Get familiarity rating
		int rating = getRating();
		q.front().setLvl(rating);

		//Get timestamp
		int srsLvl = q.front().getLvl();
		time_t now = time(nullptr);
		time_t next = setNext(now, srsLvl);

		//Set availability to 0
		int available = false;

		cout << "\"" << q.front().getWord() << "\" was quizzed at " << now << " and the next time has been set to " << next << "\n" << endl;

		//Write new file
		Card c(q.front().getWord(), srsLvl, now, next, available);
		updateFile(filename, c);

		q.pop();
		refreshAvailable(filename);
	}
	cout << "\nYou're study queue's empty for now! Check back later.";
	return 0;
}

void refreshAvailable(string filename)
{
	ifstream infile(filename);
	ofstream outfile("temp.txt");
	string line;
	time_t now = time(nullptr);

	while (getline(infile, line))
	{
		stringstream ss(line);
		vector<string> tokens;
		string token;

		while (getline(ss, token, ','))
		{
			tokens.push_back(token);
		}
		long long lastSeen = stoll(tokens[3]);
		if (now >= lastSeen)
		{
			tokens[4] = "1";
		}
		for (size_t i = 0; i < tokens.size(); i++)
		{
			outfile << tokens[i];
			if (i < tokens.size() - 1)
			{
				outfile << ",";
			}
		}
		outfile << "\n";
	}
	outfile.close();
	infile.close();

	filesystem::remove(filename);
	filesystem::rename("temp.txt", filename);
}
queue<Card> getQueue(string filename)
{
	queue<Card> q;

	ifstream infile(filename);
	if (!infile)
	{
		cerr << "Couldn't find file";
		return q;
	}

	string line;

	//should append all the true values to the queue
	while (getline(infile, line))
	{
		stringstream ss(line);
		string word, srslevel, boolStr;
		//should use ctime library
		int srslvl = 0, ts1 = 0, ts2 = 0;
		string timestamp1, timestamp2;
		bool available = false;

		getline(ss, word, ',');
		getline(ss, srslevel, ',');
		srslvl = stoi(srslevel);
		getline(ss, timestamp1, ',');
		ts1 = stoi(timestamp1);
		getline(ss, timestamp2, ',');
		ts2 = stoi(timestamp2);
		getline(ss, boolStr, ',');
		if (boolStr == "1")
		{
			available = true;
		}
		else
		{
			available = false;
		}

		Card c(word, srslvl, ts1, ts2, available);

		if (available)
		{
			q.push(c);
		}
	}
	infile.close();
	return q;

}
int getRating()
{
	string rating;
	cout << "Give a rating 1-3" << endl;
	cin >> rating;
	int lvl = stoi(rating);
	return lvl;
}
time_t setNext(time_t& now, int srsLvl)
{
	time_t next = now;
	switch (srsLvl)
	{
	case 2:
		next += 10;
		break;
	case 3:
		next += 20;
		break;
	case 4:
		next += 30;
		break;
	case 5:
		next += 40;
		break;
	case 6:
		next += 50;
		break;
	case 7:
		next += 60;
		break;
	case 8:
		next += 70;
		break;
	case 9:
		next += 80;
		break;
	case 10:
		next += 90;
		break;
	case 11:
		next += 100;
		break;
	default:
		next += 10;
	}
	return next;
}
void updateFile(string filename, Card& card)
{
	ifstream infile(filename);
	ofstream outfile("temp.txt");

	string line;

	while (getline(infile, line))
	{
		size_t pos = line.find(',');

		string name = (pos == string::npos) ? line : line.substr(0, pos);

		if (name == card.getWord())
		{
			outfile << name << "," << card.getLvl() << "," << card.getLast() << "," << card.getNext() << "," << card.getAvailable() << endl;
		}
		else
		{
			outfile << line << "\n";
		}
	}
	outfile.close();
	infile.close();

	filesystem::remove(filename);
	filesystem::rename("temp.txt", filename);
}