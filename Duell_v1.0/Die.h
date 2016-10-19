#include "stdafx.h"
#pragma once

class Die
{
public:
	Die() : die(6) {}
	~Die();
	vector <int> getDie() { return die; }
	string getPlayer() { return player; }
	bool oppositePlayer(string);
	bool getKeyPiece() { return keypiece; }
	void setDie(vector<int>);
	void frontalMove();
	void backwardMove();
	void lateralRightMove();
	void lateralLeftMove();
	bool isEmpty();
	Die* createStartingDie(Die *, int, int, string);
	Die* dieSwitch(int, int, string);
	Die* createDie(int, int, int, int, string);
	Die* createBlankDie(Die *);

	string displayDie();
private:
	vector<int> die;
	string player;
	bool keypiece;
};

