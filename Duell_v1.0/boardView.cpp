//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************

#include "boardView.h"
#include "stdafx.h"


boardView::boardView()
{
}


boardView::~boardView()
{
}

/* *********************************************************************
Function Name: ViewBoard
Purpose: Display the board
Parameters: vector<vector<die>> gameboard by reference
Return Value: void
Algorithm:
1) Loop through gameboard 
2) Print each index
3) Print the x and y indexes
Assistance Received: none
********************************************************************* */
void boardView::ViewBoard(vector<vector<Die>>& gameboard)
{
	int rowIndex = 8; // Index for y coordinates
	cout << endl << endl;
	

	cout << endl;

	// Iterate & Print 2D Vector 
	for (int i = 7; i >= 0; i--)
	{
		cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
		cout << rowIndex << " ";
		for (int j = 0; j < gameboard[i].size(); j++)
		{
			 // If the vector element is empty print empty square
			if (gameboard[i][j].displayDie() == "00")
			{
				cout << "|   ";
			}
			else
			{
				cout << "|"  << gameboard[i][j].displayDie();
			}
			
		}

		rowIndex--;
		cout << "|" << endl;
	}
	cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
	cout << "    ";
	// Print x coordinates
	for (int j = 1; j <= 9; j++)
	{
		cout << j << "   ";
	}
	cout << endl << endl;
}




