#include "stdafx.h"
#pragma once

class Die
{
public:
	Die() : die(6) {}
	~Die();
	vector <int> getDie() { return die; }
	string getPlayer() { return player; }
	void setDie(vector<int>);
	void frontalMove();
	void backwardMove();
	void lateralRightMove();
	void lateralLeftMove();
	bool isEmpty();
	Die* createStartingDie(Die *, int, int, string);

	string displayDie();
private:
	vector<int> die;
	string player;
	bool keypiece;
};

