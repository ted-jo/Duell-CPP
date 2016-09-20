#include "Die.h"
#include "stdafx.h"


Die::~Die()
{
}

// Move forward by one space
// Die[top, bottom, left, right, front, back]
// newDie[back, front,left, right, top, bottom]
Die* Die::frontalMove(Die *d)
{
	Die * newDie = new Die();
		
		newDie->die[0] = d->die[5];
		newDie->die[1] = d->die[4];
		newDie->die[2] = d->die[2];
		newDie->die[3] = d->die[3];
		newDie->die[4] = d->die[0];
		newDie->die[5] = d->die[1];
		newDie->player = d->player;

		return newDie;
	
}

// Move Right One Space
// Die[top, bottom, left, right, front, back]
// newDie[left, right, bottom, top, front, back]
vector<int> Die::lateralRightMove(vector<int> die)
{
	vector<int> newDie;

	newDie[0] = die[2];
	newDie[1] = die[3];
	newDie[2] = die[1];
	newDie[3] = die[0];
	newDie[4] = die[4];
	newDie[5] = die[5];

	return newDie;
}

// Move Left One Space
// Die[top, bottom, left, right, front, back]
// newDie[right, left, top, bottom, front, back]
vector<int> Die::lateralLeftMove(vector<int> die)
{
	vector<int> newDie;

	newDie[0] = die[3];
	newDie[1] = die[2];
	newDie[2] = die[0];
	newDie[3] = die[1];
	newDie[4] = die[4];
	newDie[5] = die[5];

	return newDie;
}

// Create starting die based off given top number
// Die[top, bottom, left, right, front, back]
Die* Die::createStartingDie(Die * d, int topNum, int rightNum, string player)
{
	d->die[0] = topNum;
	d->die[1] = 7 - topNum;
	d->die[2] = 7 - rightNum;
	d->die[3] = rightNum;
	d->die[4] = 4;
	d->die[5] = 3;
	d->player = player;

	return d;
}


string Die::displayDie()
{
	int top, right;
	string sTop, sRight;
	top = die[0];
	right = die[3];

	sTop = to_string(top);
	sRight = to_string(right);
	



	return player + sTop + sRight;
}
