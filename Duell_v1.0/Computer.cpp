#include "Computer.h"



Computer::Computer()
{
}


Computer::~Computer()
{
}

void Computer::play()
{
	cout << "Its the Computer's Turn!" << endl;
	// Display Board
	boardViewObj->ViewBoard(boardObj->GetBoard());
	// Try to execute attack on Human KeyPiece
	if (keyPieceAttack() == true)
	{
		// TODO: Set Win Game
		cout << "Computer has attacked your Key Piece" << endl;
		cout << "Computer Wins!" << endl;

	}
}
