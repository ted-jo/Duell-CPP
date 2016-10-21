#include "Die.h"
#include "stdafx.h"


Die::~Die()
{
}

// If the starting piece is human/computer and the end piece is computer/human return true
bool Die::oppositePlayer(string stPlayer)
{
	if ((stPlayer == "C" && player == "H") || (stPlayer == "H" && player == "C"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Die::setDie(vector<int> newDie)
{
	die = newDie;
}

// Move forward by one space
// Die[top, bottom, left, right, front, back]
// newDie[back, front, left, right, top, bottom]
void Die::frontalMove()
{
	vector<int> newDie(6, 0);

	newDie[0] = die[5];
	newDie[1] = die[4];
	newDie[2] = die[2];
	newDie[3] = die[3];
	newDie[4] = die[0];
	newDie[5] = die[1];



	setDie(newDie);
}

// Move backward by one space
// Die[top, bottom, left, right, front, back]
// newDie[front, back, left, right, bottom, top]
void Die::backwardMove()
{
	vector<int> newDie(6, 0);

	newDie[0] = die[4];
	newDie[1] = die[5];
	newDie[2] = die[2];
	newDie[3] = die[3];
	newDie[4] = die[1];
	newDie[5] = die[0];

	setDie(newDie);

}

// Move Right One Space
// Die[top, bottom, left, right, front, back]
// newDie[left, right, bottom, top, front, back]
void Die::lateralRightMove()
{
	vector<int> newDie(6, 0);

	newDie[0] = die[2];
	newDie[1] = die[3];
	newDie[2] = die[1];
	newDie[3] = die[0];
	newDie[4] = die[4];
	newDie[5] = die[5];

	setDie(newDie);
}

// Move Left One Space
// Die[top, bottom, left, right, front, back]
// newDie[right, left, top, bottom, front, back]
void Die::lateralLeftMove()
{
	vector<int> newDie(6, 0);

	newDie[0] = die[3];
	newDie[1] = die[2];
	newDie[2] = die[0];
	newDie[3] = die[1];
	newDie[4] = die[4];
	newDie[5] = die[5];

	setDie(newDie);
}

bool Die::isEmpty()
{
	if (die[0] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Create starting die based off given top number
// Die[top, bottom, left, right, front, back]
Die* Die::createStartingDie(Die * d, int topNum, int rightNum, string player)
{
	// When creating a key piece set the keypiece bool to true
	if (topNum == 1 && rightNum == 1)
	{
		d->die[0] = topNum;
		d->die[1] = topNum;
		d->die[2] = topNum;
		d->die[3] = topNum;
		d->die[4] = topNum;
		d->die[5] = topNum;
		d->player = player;
		d->keypiece = true;
	}
	else
	{	
		d->die[0] = topNum;
		d->die[1] = 7 - topNum;
		d->die[2] = 7 - rightNum;
		d->die[3] = rightNum;
		d->die[4] = 4;
		d->die[5] = 3;
		d->player = player;
		d->keypiece = false;
	}

	return d;
}



Die * Die::createDie(int topNum, int rightNum, int frontNum, int backNum, string player)
{
	Die * d = new Die();

	// When creating a key piece set the keypiece bool to true
	if (topNum == 1 && rightNum == 1)
	{
		d->die[0] = topNum;
		d->die[1] = topNum;
		d->die[2] = topNum;
		d->die[3] = topNum;
		d->die[4] = topNum;
		d->die[5] = topNum;
		d->player = player;
		d->keypiece = true;
	}
	else
	{
		d->die[0] = topNum;
		d->die[1] = 7 - topNum;
		d->die[2] = 7 - rightNum;
		d->die[3] = rightNum;
		d->die[4] = frontNum;
		d->die[5] = backNum;
		d->player = player;
		d->keypiece = false;
	}

	return d;
}

Die* Die::createBlankDie(Die * d)
{
		d->die[0] = 0;
		d->die[1] = 0;
		d->die[2] = 0;
		d->die[3] = 0;
		d->die[4] = 0;
		d->die[5] = 0;
		d->player = "";
		d->keypiece = false;
	

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
