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
	gameboard[0][0] = *C1->createStartingDie(C1, 5, 6, "C");
	gameboard[0][1] = *C2->createStartingDie(C2, 1, 5, "C");
	gameboard[0][2] = *C3->createStartingDie(C3, 2, 1, "C");
	gameboard[0][3] = *C4->createStartingDie(C4, 6, 2, "C");
	gameboard[0][4] = *C5->createStartingDie(C5, 1, 1, "C");
	gameboard[0][5] = *C6->createStartingDie(C6, 6, 2, "C");
	gameboard[0][6] = *C7->createStartingDie(C7, 2, 1, "C");
	gameboard[0][7] = *C8->createStartingDie(C8, 1, 5, "C");
	gameboard[0][8] = *C9->createStartingDie(C9, 5, 6, "C");



	// Computer Starting Postions
	gameboard[7][0] = *H1->createStartingDie(H1, 5, 6, "H");
	gameboard[7][1] = *H2->createStartingDie(H2, 1, 5, "H");
	gameboard[7][2] = *H3->createStartingDie(H3, 2, 1, "H");
	gameboard[7][3] = *H4->createStartingDie(H4, 6, 2, "H");
	gameboard[7][4] = *H5->createStartingDie(H5, 1, 1, "H");
	gameboard[7][5] = *H6->createStartingDie(H6, 6, 2, "H");
	gameboard[7][6] = *H7->createStartingDie(H7, 2, 1, "H");
	gameboard[7][7] = *H8->createStartingDie(H8, 1, 5, "H");
	gameboard[7][8] = *H9->createStartingDie(H9, 5, 6, "H");
}

Board::~Board()
{
}

void Board::setBoard(vector<vector<Die>> board)
{
	gameboard = board;
}

void Board::movePieceDown(int x, int y, vector<vector<Die>> &gameboard)
{
	// TODO: Change name to downward move, only allow movement if space has an active Die, Change to void and set gameboard instead of return?
	// TODO: OUT OF BOUNDS CHECKING!!!
	int newXCoord = x;
	x--;
	y--;
	Die * newDie = &gameboard[x][y];
	Die * replacementDie = new Die();
	gameboard[newXCoord][y] = *gameboard[x][y].frontalMove(&gameboard[x][y]);
	// Set prior position to a blank die
	gameboard[x][y] = *replacementDie;

	setBoard(gameboard);
}

// Function checks to make sure coordinates are not out of bounds
bool Board::legalMove(int x, int y)
{
	// Check if x or y coordinate is out of the 2D vector bounds on the upper end
	if (x > 8 || y > 7)
	{
		cout << endl << "Selected coordinates out of range" << endl;
		cout << "Please select a new set of coordinates" << endl;
		return false;
	}
	// Check if x or y is out of the 2D vector bounds on the low end
	else if (x < 1 || y < 1)
	{
		cout << endl << "Selected coordinates out of range" << endl;
		cout << "Please select a new set of coordinates" << endl;
		return false;
	}

	return true;
}







