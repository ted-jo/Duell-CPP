//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************

#include "Die.h"
#include "stdafx.h"


Die::~Die()
{
}

/* *********************************************************************
Function Name: oppositePlayer
Purpose: Check if a die belongs to the opposing player
Parameters:
	player, string containing the player
Return Value: If the starting piece is human/computer and the end piece is computer/human return true
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: setDie
Purpose: Die vector Mutator
Parameters:
	newDie, vector<int> containing all faces of the die
Return Value: void
Assistance Received: none
********************************************************************* */
void Die::setDie(vector<int> newDie)
{
	die = newDie;
}


/* *********************************************************************
Function Name: frontalMove
Purpose: Swap die faces to move forward by one space
Parameters: None
Return Value: void
Assistance Received: none
********************************************************************* */
void Die::frontalMove()
{
	// Die[top, bottom, left, right, front, back]
	// newDie[back, front, left, right, top, bottom]

	vector<int> newDie(6, 0);

	newDie[0] = die[5];
	newDie[1] = die[4];
	newDie[2] = die[2];
	newDie[3] = die[3];
	newDie[4] = die[0];
	newDie[5] = die[1];



	setDie(newDie);
}


/* *********************************************************************
Function Name: backwardMove
Purpose: Swap die faces to move backward by one space
Parameters: None
Return Value: void
Assistance Received: none
********************************************************************* */
void Die::backwardMove()
{
	// Die[top, bottom, left, right, front, back]
	// newDie[front, back, left, right, bottom, top]
	vector<int> newDie(6, 0);

	newDie[0] = die[4];
	newDie[1] = die[5];
	newDie[2] = die[2];
	newDie[3] = die[3];
	newDie[4] = die[1];
	newDie[5] = die[0];

	setDie(newDie);

}


/* *********************************************************************
Function Name: lateralRightMove
Purpose: Swap die faces to move right by one space
Parameters: None
Return Value: void
Assistance Received: none
********************************************************************* */
void Die::lateralRightMove()
{
	// Die[top, bottom, left, right, front, back]
	// newDie[left, right, bottom, top, front, back]

	vector<int> newDie(6, 0);

	newDie[0] = die[2];
	newDie[1] = die[3];
	newDie[2] = die[1];
	newDie[3] = die[0];
	newDie[4] = die[4];
	newDie[5] = die[5];

	setDie(newDie);
}


/* *********************************************************************
Function Name: lateralLeftMove
Purpose: Swap die faces to move left by one space
Parameters: None
Return Value: void
Assistance Received: none
********************************************************************* */
void Die::lateralLeftMove()
{
	// Die[top, bottom, left, right, front, back]
	// newDie[right, left, top, bottom, front, back]
	vector<int> newDie(6, 0);

	newDie[0] = die[3];
	newDie[1] = die[2];
	newDie[2] = die[0];
	newDie[3] = die[1];
	newDie[4] = die[4];
	newDie[5] = die[5];

	setDie(newDie);
}

/* *********************************************************************
Function Name: isEmpty
Purpose: Check if die is empty
Parameters: None
Return Value: return true if die is empty
Assistance Received: none
********************************************************************* */
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


/* *********************************************************************
Function Name: createStartingDie
Purpose: Create starting die based off given top number and right number
Parameters:
	d, pointer to die object
	topNum, int containing the top number
	rightNum, int containing the right number
Return Value: pointer to die object
Algorithm:
1) If topNum and rightNum are 1 Create a keypiece
2) Else calculate other faces based off given top and right
3) return d
Assistance Received: none
********************************************************************* */
Die* Die::createStartingDie(Die * d, int topNum, int rightNum, string player)
{
	// Die[top, bottom, left, right, front, back]
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


/* *********************************************************************
Function Name: createDie
Purpose: Create die based off sides
Parameters:
	d, pointer to die object
	topNum, int containing the top number
	rightNum, int containing the right number
	frontNum, int containing front number
	backNum, int containing back number
	player, string containing the player
Return Value: pointer to die object
Algorithm:
1) If topNum and rightNum are 1 Create a keypiece
2) Else calculate other faces based off given sides
3) return d
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: createBlankDie
Purpose: Create die with all 0s
Parameters:
	d, pointer to die object
Return Value: pointer to die object
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: displayDie
Purpose: Display the die in format P12
Parameters: None
Return Value: String with the player, top and right side
Assistance Received: none
********************************************************************* */
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
