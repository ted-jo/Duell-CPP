//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************

#include "Computer.h"



Computer::Computer()
{
}


Computer::~Computer()
{
}

/* *********************************************************************
Function Name: play
Purpose: Virtual function that executes the AI move
Parameters: None
Return Value: Pointer to a board object
Local Variables: None
Algorithm:
1) Check if AI can attack keypiece
2) Check if AI can block a keypiece attack
3) Check if AI can block a keyspace attack
4) Check if AI can overtake a piece
5) Check if AI can execute best move available
6) return the boardObj
Assistance Received: none
********************************************************************* */
Board * Computer::play()
{
	cout << "Its the Computer's Turn!" << endl;
	// First Pass
	// Try to execute attack on Human KeyPiece
	if (keyPieceAttack("C", false))
	{
		cout << "Computer has attacked your Key Piece" << endl;
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
