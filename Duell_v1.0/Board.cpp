#include "Board.h"
#include "Die.h"
#include "stdafx.h"




// Board Constructor
// New Board is created when board object is created
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



// TODO: implement this during coodinate entry.
bool Board::checkOccupiedSpace(int x, int y, string player)
{
	if (gameboard[y][x].isEmpty())
	{
		return false;
	}
	// Check if Player is moving correct Die
	else if (player != gameboard[y][x].getPlayer())
	{
		return false;
	}

	return true;
}

// Function to make sure the end coordinates are the correct
// number of spaces away from the start coordinates
bool Board::checkNumSpaces(int startX, int startY, int endX, int endY)
{
	int tempX, tempY, tempXY;
	vector<int> die = gameboard[startY][startX].getDie();
	// Get number of moves allowed
	int move = die[0];

	// Subtract the end point by the starting point and take absolute value
	// When added together it equals the total number of moves allowed
	tempX = endX - startX;
	tempY = endY - startY;
	tempX = abs(tempX);
	tempY = abs(tempY);
	tempXY = tempX + tempY;
	if (tempXY == move)
	{
		return true;
	}
	else
	{
		return false;
	}
}


// Create die based off given top number for loading game
// Die[top, bottom, left, right, front, back]
Die * Board::dieSwitch(int topNum, int rightNum, string player)
{
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






