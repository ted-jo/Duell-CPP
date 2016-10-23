#include "Board.h"
#include "Die.h"
#include "stdafx.h"




/* *********************************************************************
Function Name: Board Constructor
Purpose: Construct a Board Object
Parameters:
Return Value: 
Local Variables:
gameboard, a 2D vector of Die objects
C1-C9, new die pointers for Computer die
H1-H9, new die pointers for Human die
Algorithm:
1) Inline initialize the vector<vector<Die>> gameboard to the correct size
2) Create 9 new dies for the computer and 9 new dies for the human
3) Set each of the Dies to the proper starting values and store them in the proper location on the gameboard
Assistance Received: none
********************************************************************* */
Board::Board() : gameboard(8, vector <Die>(9))
{
	// Create New Dice Instances for Computer Player
	Die * C1 = new Die();
	Die * C2 = new Die();
	Die * C3 = new Die();
	Die * C4 = new Die();
	Die * C5 = new Die();
	Die * C6 = new Die();
	Die * C7 = new Die();
	Die * C8 = new Die();
	Die * C9 = new Die();

	// Create New Dice Instances for Human Player
	Die * H1 = new Die();
	Die * H2 = new Die();
	Die * H3 = new Die();
	Die * H4 = new Die();
	Die * H5 = new Die();
	Die * H6 = new Die();
	Die * H7 = new Die();
	Die * H8 = new Die();
	Die * H9 = new Die();
	
	// Computer Starting Postions
	gameboard[0][0] = *C1->createStartingDie(C1, 5, 6, "H");
	gameboard[0][1] = *C2->createStartingDie(C2, 1, 5, "H");
	gameboard[0][2] = *C3->createStartingDie(C3, 2, 1, "H");
	gameboard[0][3] = *C4->createStartingDie(C4, 6, 2, "H");
	gameboard[0][4] = *C5->createStartingDie(C5, 1, 1, "H");
	gameboard[0][5] = *C6->createStartingDie(C6, 6, 2, "H");
	gameboard[0][6] = *C7->createStartingDie(C7, 2, 1, "H");
	gameboard[0][7] = *C8->createStartingDie(C8, 1, 5, "H");
	gameboard[0][8] = *C9->createStartingDie(C9, 5, 6, "H");



	// Computer Starting Postions
	gameboard[7][0] = *H1->createStartingDie(H1, 5, 6, "C");
	gameboard[7][1] = *H2->createStartingDie(H2, 1, 5, "C");
	gameboard[7][2] = *H3->createStartingDie(H3, 2, 1, "C");
	gameboard[7][3] = *H4->createStartingDie(H4, 6, 2, "C");
	gameboard[7][4] = *H5->createStartingDie(H5, 1, 1, "C");
	gameboard[7][5] = *H6->createStartingDie(H6, 6, 2, "C");
	gameboard[7][6] = *H7->createStartingDie(H7, 2, 1, "C");
	gameboard[7][7] = *H8->createStartingDie(H8, 1, 5, "C");
	gameboard[7][8] = *H9->createStartingDie(H9, 5, 6, "C");
}

Board::~Board()
{
}

void Board::setBoard(vector<vector<Die>> board)
{
	gameboard = board;
}
/* *********************************************************************
Function Name: movePieceUp
Purpose: Move the Die from gameboard[y][x] --> gameboard[y+1][x]
Parameters:
x, y, ints containing the x and y coordinates
Return Value: void
Local Variables:
player, string that gets player based off gameboard[y][x]
newDie, pointer to a new Die object used to replace the previous piece
Algorithm:
1) Get player from gameboard[y][x].getPlayer();
2) The player determines if the Die is going to roll forward or backward when moving Up
3) If it's a human die, roll Die forward one roll, move Up one space, replace old space with a new empty die
4) If it's a computer die, roll Die backward one roll, move Up one space, replace old space with a new empty die
5) set the gameboard to the Board class
Assistance Received: none
********************************************************************* */
void Board::movePieceUp(int x, int y)
{
	string player = gameboard[y][x].getPlayer();
	Die * newDie = new Die();

	if (player == "H")
	{
		gameboard[y][x].frontalMove();
		gameboard[y + 1][x] = gameboard[y][x];
		gameboard[y][x] = *newDie->createBlankDie(newDie);
	}
	else
	{
		gameboard[y][x].frontalMove();
		gameboard[y + 1][x] = gameboard[y][x];
		gameboard[y][x] = *newDie->createBlankDie(newDie);
	}


	setBoard(gameboard);
}
/* *********************************************************************
Function Name: movePieceDown
Purpose: Move the Die from gameboard[y][x] --> gameboard[y-1][x]
Parameters:
x, y, ints containing the x and y coordinates
Return Value: void
Local Variables:
player, string that gets player based off gameboard[y][x]
newDie, pointer to a new Die object used to replace the previous piece
Algorithm:
1) Get player from gameboard[y][x].getPlayer();
2) The player determines if the Die is going to roll foward or backward when moving down
3) If it's a human die, roll Die backward one roll, move down one space, replace old space with a new empty die
4) If it's a computer die, roll Die forward one roll, move down one space, replace old space with a new empty die
5) set the gameboard to the Board class
Assistance Received: none
********************************************************************* */
void Board::movePieceDown(int x, int y)
{
	string player = gameboard[y][x].getPlayer();
	Die * newDie = new Die();

	if (player == "H")
	{
		gameboard[y][x].backwardMove();
		gameboard[y - 1][x] = gameboard[y][x];
		gameboard[y][x] = *newDie->createBlankDie(newDie);
	}
	else
	{
		gameboard[y][x].frontalMove();
		gameboard[y - 1][x] = gameboard[y][x];
		gameboard[y][x] = *newDie->createBlankDie(newDie);

	}

	setBoard(gameboard);
}
/* *********************************************************************
Function Name: movePieceLeft
Purpose: Move the Die from gameboard[y][x] --> gameboard[y][x-1]
Parameters:
x, y, ints containing the x and y coordinates
Return Value: void
Local Variables:
player, string that gets player based off gameboard[y][x]
newDie, pointer to a new Die object used to replace the previous piece
Algorithm:
1) Get player from gameboard[y][x].getPlayer();
2) The player determines if the Die is going to roll left or right when moving right
3) If it's a human die, roll Die left one roll, move left one space, replace old space with a new empty die
4) If it's a computer die, roll Die right one roll, move right one space, replace old space with a new empty die
5) set the gameboard to the Board class
Assistance Received: none
********************************************************************* */
void Board::movePieceLeft(int x, int y)
{
	string player = gameboard[y][x].getPlayer();
	Die * newDie = new Die();

	if (player == "H")
	{
		gameboard[y][x].lateralLeftMove();
		gameboard[y][x - 1] = gameboard[y][x];
		gameboard[y][x] = *newDie->createBlankDie(newDie);
	}
	else
	{
		gameboard[y][x].lateralRightMove();
		gameboard[y][x - 1] = gameboard[y][x];
		gameboard[y][x] = *newDie->createBlankDie(newDie);
	}

	setBoard(gameboard);
}



/* *********************************************************************
Function Name: movePieceRight
Purpose: Move the Die from gameboard[y][x] --> gameboard[y][x+1]
Parameters:
x, y, ints containing the x and y coordinates
Return Value: void
Local Variables:
player, string that gets player based off gameboard[y][x]
newDie, pointer to a new Die object used to replace the previous piece
Algorithm:
1) Get player from gameboard[y][x].getPlayer();
2) The player determines if the Die is going to roll left or right when moving right
3) If it's a human die, roll Die right one roll, move right one space, replace old space with a new empty die
4) If it's a computer die, roll Die left one roll, move right one space, replace old space with a new empty die
5) set the gameboard to the Board class
Assistance Received: none
********************************************************************* */
void Board::movePieceRight(int x, int y)
{
	string player = gameboard[y][x].getPlayer();
	Die * newDie = new Die();

	if (player == "H")
	{
		gameboard[y][x].lateralRightMove();
		gameboard[y][x + 1] = gameboard[y][x];
		gameboard[y][x] = *newDie->createBlankDie(newDie);
	}
	else
	{
		gameboard[y][x].lateralLeftMove();
		gameboard[y][x + 1] = gameboard[y][x];
		gameboard[y][x] = *newDie->createBlankDie(newDie);
	}

	setBoard(gameboard);
}



/* *********************************************************************
Function Name: dieSwitch
Purpose: To create the Die pieces on load game
Parameters:
topNum, an int containing the top number
rightNum, an int containing the right number
player, a string containing the player
Return Value: A Die pointer to the newly created Die
Local Variables:
d, a pointer to a new Die()
Algorithm:
1) Create pointer to a new die, d
2) Enter switch statement with value of top number
3) Execute nested switch statement with value of the right number
4) Create a Die with the given top, right, and front back from switch statement
and set to d
5) break out of switches
6) Return d
Assistance Received: none
********************************************************************* */
Die * Board::dieSwitch(int topNum, int rightNum, string player)
{
	// Die[top, bottom, left, right, front, back]
	Die * d = new Die();

	switch (topNum)
	{
	case 1:
		switch (rightNum)
		{
		case 1:
			d = d->createDie(topNum, rightNum, 1, 1, player);
			break;
		case 2:
			d = d->createDie(topNum, rightNum, 3, 4, player);
			break;
		case 3:
			d = d->createDie(topNum, rightNum, 5, 2, player);
			break;
		case 4:
			d = d->createDie(topNum, rightNum, 2, 5, player);
			break;
		case 5:
			d = d->createDie(topNum, rightNum, 4, 3, player);
			break;
		}
		break;
	case 2:
		switch (rightNum)
		{
		case 1:
			d = d->createDie(topNum, rightNum, 4, 3, player);
			break;
		case 3:
			d = d->createDie(topNum, rightNum, 1, 6, player);
			break;
		case 4:
			d = d->createDie(topNum, rightNum, 6, 1, player);
			break;
		case 6:
			d = d->createDie(topNum, rightNum, 3, 4, player);
			break;
		}
		break;
	case 3:
		switch (rightNum)
		{
		case 1:
			d = d->createDie(topNum, rightNum, 2, 5, player);
			break;
		case 2:
			d = d->createDie(topNum, rightNum, 6, 1, player);
			break;
		case 5:
			d = d->createDie(topNum, rightNum, 1, 6, player);
			break;
		case 6:
			d = d->createDie(topNum, rightNum, 5, 2, player);
			break;
		}
		break;
	case 4:
		switch (rightNum)
		{
		case 1:
			d = d->createDie(topNum, rightNum, 5, 2, player);
			break;
		case 2:
			d = d->createDie(topNum, rightNum, 1, 6, player);
			break;
		case 5:
			d = d->createDie(topNum, rightNum, 6, 1, player);
			break;
		case 6:
			d = d->createDie(topNum, rightNum, 2, 5, player);
			break;
		}
		break;
	case 5:
		switch (rightNum)
		{
		case 1:
			d = d->createDie(topNum, rightNum, 3, 4, player);
			break;
		case 3:
			d = d->createDie(topNum, rightNum, 6, 1, player);
			break;
		case 4:
			d = d->createDie(topNum, rightNum, 1, 6, player);
			break;
		case 6:
			d = d->createDie(topNum, rightNum, 4, 3, player);
			break;
		}
		break;
	case 6:
		switch (rightNum)
		{
		case 2:
			d = d->createDie(topNum, rightNum, 4, 3, player);
			break;
		case 3:
			d = d->createDie(topNum, rightNum, 2, 5, player);
			break;
		case 4:
			d = d->createDie(topNum, rightNum, 5, 2, player);
			break;
		case 5:
			d = d->createDie(topNum, rightNum, 3, 4, player);
			break;
		}
		break;
	}

	return d;
}






