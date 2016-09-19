/*
* Driver for the game
*/
#include "stdafx.h"     // Contains the pre-compiled headers.
#include "Board.h"
#include "boardView.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
	Board b;
	boardView v;
	vector<vector<string>> gameboard = b.GetBoard();
	cout << "Start Game" << endl << endl;
	b.ResetBoard(gameboard);
	v.ViewBoard(gameboard);



	cout << endl;
	system("PAUSE");
	return 0;
}