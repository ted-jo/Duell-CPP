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
}
