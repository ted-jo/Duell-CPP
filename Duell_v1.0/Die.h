#include "stdafx.h"
#pragma once

class Die
{
public:
	Die() : die(6) {};
	~Die();
	vector<int> frontalMove(vector<int>, int, bool);
	vector<int> createStartingDie(int, int);
	vector<int> lateralMove(vector<int>, int, bool);
	string displayDie(vector<int>);
private:
	vector<int> die;
	bool keyPiece;
};

