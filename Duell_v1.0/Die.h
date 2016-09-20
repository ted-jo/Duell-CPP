#include "stdafx.h"
#pragma once

class Die
{
public:
	Die() : die(6) {}
	~Die();
	Die* frontalMove(Die *);
	Die* createStartingDie(Die *, int, int, string);
	vector<int> lateralRightMove(vector<int>);
	vector<int> lateralLeftMove(vector<int>);
	string displayDie();
private:
	vector<int> die;
	string player;
};

