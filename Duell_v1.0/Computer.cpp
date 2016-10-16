#include "Computer.h"



Computer::Computer()
{
}


Computer::~Computer()
{
}

Board * Computer::play()
{
	cout << "Its the Computer's Turn!" << endl;
	// First Pass
	// Try to execute attack on Human KeyPiece
	if (keyPieceAttack("C"))
	{
		// TODO: Set Win Game
		cout << "Computer has attacked your Key Piece" << endl;
		cout << "Computer Wins!" << endl;
		setWin("C");

	}
	// Check to see if the Human has any moves that 
	// will overtake the AI's keypiece
	// Initiate a block if true
	else if (keyPieceAttack("H") && protectKeyPiece())
	{
		cout << "Human has finishing move, initiate block" << endl;
	}
	else if (checkOvertake())
	{
		cout << "Computer executed a move to overtake a human piece";
	}
	else if(executeBestMove())
	{
		// No winning or blocking moves
		// Execute best move available
		cout << "Computer excecuted best possible move" << endl;
	}



	return boardObj;
}
