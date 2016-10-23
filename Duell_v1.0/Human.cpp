//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************

#include "Human.h"
#include "Game.h"




Human::Human()
{
}


Human::~Human()
{
}

/* *********************************************************************
Function Name: play
Purpose: Execute a round for the Human player
Parameters: None
Return Value: Pointer to board object
Assistance Received: none
********************************************************************* */
Board * Human::play()
{
	cout << "Its You're Turn!" << endl;

	getCoordinates(); 
	getPath(startX, startY, endX, endY, direction, false);
	getPath(startX, startY, endX, endY, direction, true);
	return boardObj;
}

/* *********************************************************************
Function Name: setCoordinates
Purpose: Set the coordinates mutator
Parameters:
	startXCoord, startYCood, endXCoord, endYCoord, ints containing the start and end coordinates
Return Value: void
Assistance Received: none
********************************************************************* */
void Human::setCoordinates(int startXCoord, int startYCoord, int endXCoord, int endYCoord, int directionInput)
{
	startX = startXCoord;
	startY = startYCoord;
	endX = endXCoord;
	endY = endYCoord;
	direction = directionInput;

}

/* *********************************************************************
Function Name: getCoordinates
Purpose: Ask the player for the start and end coordinates and verify selection
Parameters: None
Return Value: void
Local Variables:
	x, y, endX, endY, ints containing the start and end coordinates
	directionInput, int with the user inputted direction
Algorithm:
1) Get the coodinates from user
2) Get direction from user
3) Set all coordinates -1 to match with vector indexes 
4) Validate the input to ensure its a legal move
5) Set Coordinates
Assistance Received: none
********************************************************************* */
void Human::getCoordinates()
{
	int x, y, endX, endY, directionInput;
	bool validInput = false;

	do
	{
		cout << "Enter X Coordinate of Die to move: ";
		cin >> y;
		cout << "Enter Y Coordinate of Die to move: ";
		cin >> x;
		cout << "Enter X Coordinate of Desired End Space: ";
		cin >> endY;
		cout << "Enter Y Coordinate of Desired End Space: ";
		cin >> endX;

		// If the Y coordinates are not equal there is a lateral movement
		if (x != endX && y != endY)
		{
			do
			{
				cout << "Would you like to move Forward or Lateral first?" << endl;
				cout << "Enter '1' for Forward or '2' for Lateral: ";
				cin >> directionInput;
				cout << endl;
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

	cout << "You are moving Piece (" << y + 1 << ", " << x + 1 << ")" << " to space (" << endY + 1 << ", " << endX + 1 << ")" << endl;

	setCoordinates(x, y, endX, endY, directionInput);
	
}
