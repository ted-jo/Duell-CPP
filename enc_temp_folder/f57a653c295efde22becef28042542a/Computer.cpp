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

	}
	// Check to see if the Human has any moves that 
	// will overtake the AI's keypiece
	// Initiate a block if true
	else if (keyPieceAttack("H"))
	{
		cout << "Human has finishing move initiate block" << endl;
	}
	else
	{
		// No winning or blocking moves
		// Execute best move available
		findBestMove();
	}



	return boardObj;
}
