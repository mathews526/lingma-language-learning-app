#include "SRS.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>
#include <queue>
#include <ctime>
using namespace std;

void review()
{
	string filename = "sampleUser.txt";
	ifstream infile(filename);
	if (!infile)
	{
		cout << "Could not find the user's file" << endl;
		return;
	}

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
}
void refreshAvailable(string filename)
{
	ifstream infile(filename);
	ofstream outfile("temp.txt");

	if (!infile || !outfile)
	{
		cerr << "Could not open file" << endl;
		return;
	}

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
		int srslvl = stoi(tokens[1]);
		long long lastSeen = stoll(tokens[3]);
		if (srslvl == 0)
		{
			tokens[4] = "0";
		}
		else if (srslvl >= 5)
		{
			// Mastered cards never become available again
			tokens[4] = "0";
		}
		else if (now >= lastSeen)
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

		if (available && srslvl < 5 && srslvl > 0)
		{
			q.push(c);
		}
	}
	infile.close();
	return q;

}
// The same as getQueue but pushed unavailable cards
queue<Card> getLessonQueue(string filename)
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

		if (srslvl == 0)
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
//Using increments of 10 seconds for testing purposes
time_t setNext(time_t& now, int srsLvl)
{
	time_t next = now;
	switch (srsLvl)
	{
	case 1:
		next += 10;
		break;
	case 2:
		next += 30;
		break;
	case 3:
		next += 60;
		break;
	case 4:
		next += 120;
		break;
	case 5:
		next += 300;
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