#include "Human.h"
#include "Game.h"




Human::Human()
{
}


Human::~Human()
{
}

void Human::play()
{
	cout << "Its You're Turn!" << endl;
	// Display Board
	boardViewObj->ViewBoard(boardObj->GetBoard());

	getCoordinates();
}

void Human::setCoordinates(int startXCoord, int startYCoord, int endXCoord, int endYCoord, char directionInput)
{
	startX = startXCoord;
	startY = startYCoord;
	endX = endXCoord;
	endY = endYCoord;
	direction = directionInput;

}

void Human::getCoordinates()
{
	int x, y, endX, endY, directionInput;
	bool validInput = false;

	do
	{
		cout << "Enter X Coordinate of Die to move: ";
		cin >> x;
		cout << "Enter Y Coordinate of Die to move: ";
		cin >> y;
		cout << "Enter X Coordinate of Desired End Space: ";
		cin >> endX;
		cout << "Enter Y Coordinate of Desired End Space: ";
		cin >> endY;

		// If the Y coordinates are not equal there is a lateral movement
		if (x != endX)
		{
			do
			{
				cout << "Would you like to move Forward or Lateral first?" << endl;
				cout << "Enter '1' for Forward or '2' for Lateral: ";
				cin >> directionInput;
			} while (!((directionInput != 1) || (directionInput != 2)));
			
		}
		else
		{
			// Set direction to n if there's no rotation 
			directionInput = 0;
			
		}

		// Sets the x, y index - 1 since vector starts at index 0
		x--;
		y--;
		endX--;
		endY--;

		// Send the coordinates, direction, and player to the validation function
		validInput = validateMove(x, y, endX, endY, directionInput, "H");

		
	} while (!validInput);

	cout << "You are moving Piece (" << x + 1 << ", " << y + 1 << ")" << " to space (" << endX + 1 << ", " << endY + 1 << ")" << endl;
	


	setCoordinates(x, y, endX, endY, directionInput);
	
}
