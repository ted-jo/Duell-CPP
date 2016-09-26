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
	Die* createStartingDie(Die *, int, int, string);
	vector<int> lateralRightMove(vector<int>);
	vector<int> lateralLeftMove(vector<int>);
	string displayDie();
private:
	vector<int> die;
	string player;
	bool keypiece;
};

