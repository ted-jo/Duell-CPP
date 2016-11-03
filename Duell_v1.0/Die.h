//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************ 

#include "stdafx.h"
#pragma once

class Die
{
public:
	Die() : die(6) {}
	~Die();

	// Mutator
	void setDie(vector<int>);

	// Accessors
	vector <int> getDie() const { return die; }
	string getPlayer() const { return player; }
	bool getKeyPiece() const { return keypiece; }

	bool oppositePlayer(string);	
	void frontalMove();
	void backwardMove();
	void lateralRightMove();
	void lateralLeftMove();
	bool isEmpty();
	Die* createStartingDie(Die *, int, int, string);
	Die* createDie(int, int, int, int, string);
	Die* createBlankDie(Die *);

	string displayDie();
private:
	vector<int> die;
	string player;
	bool keypiece;
};

