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
	// Try to execute attack on Human KeyPiece
	if (keyPieceAttack() == true)
	{
		// TODO: Set Win Game
		cout << "Computer has attacked your Key Piece" << endl;
		cout << "Computer Wins!" << endl;

	}
	else
	{
		cout << "No keypiec attack moves" << endl;
	}

	return boardObj;
}
