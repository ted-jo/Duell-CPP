#include "Die.h"
#include "stdafx.h"



Die::Die()
{
}


Die::~Die()
{
}

// Move forward by one space
// Die[top, bottom, left, right, front, back]
// newDie[back, front,left, right, top, bottom]
vector<int> Die::frontalMove(vector<int> die, int move, bool keyPiece)
{
	vector<int> newDie;
	if (keyPiece == false)
	{
		newDie[0] = die[5];
		newDie[1] = die[4];
		newDie[2] = die[2];
		newDie[3] = die[3];
		newDie[4] = die[0];
		newDie[5] = die[1];

		return newDie;


	}
	
}

// Create starting die based off given top number
// Die[top, bottom, left, right, front, back]
vector<int> Die::createStartingDie(int topNum, int rightNum)
{
	vector<int> die;

	die[0] = topNum;
	die[1] = 7 - topNum;
	die[2] = 7 - rightNum;
	die[3] = rightNum;
	die[4] = 4;
	die[5] = 3;

	return die;
}

string Die::displayDie(vector<int> die)
{
	int top, right;
	string sTop, sRight;
	top = die[0];
	right = die[3];

	sTop = to_string(top);
	sRight = to_string(right);
	



	return sTop + sRight;
}
