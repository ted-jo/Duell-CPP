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
	if (keyPieceAttack("C", false))
	{
		cout << "Computer has attacked your Key Piece" << endl;
		cout << "Computer Wins!" << endl;
	}
	// Check to see if the Human has any moves that 
	// will overtake the AI's keypiece
	// Initiate a block if true
	else if (keyPieceAttack("H", false) && protectKeyPiece("C", false))
	{
		cout << "Human has finishing move on key piece, initiate block" << endl;
	}
	// Check to see if the Human has any moves that 
	// will overtake the AI's keyspace
	// Initiate a block if true
	else if (keyPieceAttack("H", false) && protectKeyPiece("C", true))
	{
		cout << "Human has finishing move on key space, initiate block" << endl;
	}
	else if (checkOvertake("C"))
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
