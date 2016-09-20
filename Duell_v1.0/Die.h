#include "stdafx.h"
#pragma once

class Die
{
public:
	Die() : die(6) {};
	~Die();
	vector<int> frontalMove(vector<int>);
	vector<int> createStartingDie(int, int);
	vector<int> lateralRightMove(vector<int>);
	string displayDie(vector<int>, string);
private:
	vector<int> die;
};

