#include "boardView.h"
#include "stdafx.h"


boardView::boardView()
{
}


boardView::~boardView()
{
}

void boardView::ViewBoard(vector<vector<Die>>& gameboard)
{
	int rowIndex = 8; // Index for y coordinates
	cout << "    ";
	// Print x coordinates
	for (int j = 1; j <= 9; j++)
	{
		cout << j << "   ";
	}
	cout << endl;

	// Iterate & Print 2D Vector 
	for (int i = 0; i < gameboard.size(); i++)
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
}



