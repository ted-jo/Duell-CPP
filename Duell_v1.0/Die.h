#include "stdafx.h"
#pragma once

class Die
{
public:
	Die() : die(6) {};
	~Die();
	vector<int> frontalMove(vector<int>, int, bool);
	vector<int> createStartingDie(int, int);
	int lateralMove(int, int, int, bool);
private:
	vector<int> die;
	bool keyPiece;
};

