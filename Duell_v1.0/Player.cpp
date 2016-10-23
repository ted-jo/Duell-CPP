//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************

#include "Player.h"


Player::Player()
{
}

/* *********************************************************************
Function Name: setBoard
Purpose: Board Object Mutator
Parameters:
Pointer to a board object
Return Value: void
Algorithm:
1) Set boardObj
Assistance Received: none
********************************************************************* */
void Player::setBoard(Board * board)
{
	boardObj = board;
}


/* *********************************************************************
Function Name: checkOOB
Purpose: Function checks to make sure coordinates are not out of bounds
Parameters:
	x & y, ints containing the coordinates of the piece to move
Return Value: return true if move is in bounds
Local Variables: None
Assistance Received: none
********************************************************************* */
bool Player::checkOOB(int x, int y)
{
	// Check if x or y coordinate is out of the 2D vector bounds on the upper end
	if (x > 8 || y > 7)
	{
		return false;
	}
	// Check if x or y is out of the 2D vector bounds on the low end
	else if (x < 0 || y < 0)
	{
		return false;
	}

	return true;
}


/* *********************************************************************
Function Name: validateMove
Purpose: Function takes all the data about the pending move and prints 
			an error if it is not a legal move
Parameters:
	startX, startY, endX, endY, ints containing the start and end coordinates
	direction, int signifying the direction the piece will travel
	player, string containing the player
Return Value: return true if it's a legal move
Local Variables: None
Algorithm:
1) If startX and startY coordinates are out of bounds return false
2) If endX and endY coordinates are out of bound return false
3) If there's no valid piece on the space return false
4) If the start coordinates are not the correct number of moves away
from the end coordinates return false
5) If the path is blocked return false
6) return true
Assistance Received: none
********************************************************************* */
bool Player::validateMove(int startX, int startY, int endX, int endY, int direction, string player)
{
	// Check if starting coordinates are out of bounds
	if (!checkOOB(startX, startY))
	{
		cout << "**************************************************" << endl;
		cout << "*  Error: Starting Coordinates Out of Bounds     *" << endl;
		cout << "*  Please Select New Coordinates                 *" << endl;
		cout << "**************************************************" << endl;
		return false;
	}
	// Check if ending coordinates are out of bounds
	else if (!checkOOB(endX, endY))
	{
		cout << "**************************************************" << endl;
		cout << "*  Error: Ending Coordinates Out of Bounds       *" << endl;
		cout << "*  Please Select New Coordinates                 *" << endl;
		cout << "**************************************************" << endl;
		return false;
	}
	// Check if theres a valid die piece on the starting location
	else if (!checkOccupiedSpace(startX, startY, player))
	{
		cout << "**************************************************" << endl;
		cout << "*  Error: No Valid Piece on Starting Coordinates *" << endl;
		cout << "*  Please Select New Coordinates                 *" << endl;
		cout << "**************************************************" << endl;
		return false;
	}
	// Check if the end coordinates are the correct number of spaces 
	// away from the starting coordinates
	else if (!checkNumSpaces(startX, startY, endX, endY))
	{
		cout << "*****************************************************" << endl;
		cout << "*  Error: End Coordinates Out of Range of Movement  *" << endl;
		cout << "*  Please Select New Coordinates                    *" << endl;
		cout << "*****************************************************" << endl;

		return false;
	}
	// Check if there are any pieces blocking move
	else if(!getPath(startX, startY, endX, endY, direction, false))
	{
		cout << "*****************************************************" << endl;
		cout << "*  Error: Path is Blocked                           *" << endl;
		cout << "*  Please Select New Coordinates                    *" << endl;
		cout << "*****************************************************" << endl;

		return false;
	}


	return true;
}

/* *********************************************************************
Function Name: checkNumSpaces
Purpose: To check if start (x, y) is correct number of spaces from end (x, y)
			based off the top number of the starting piece
Parameters:
	startX & startY, integers containing the start X/Y positions
	endx & endY, integers containing the end X/Y positions
Return Value: bool, return true if they are the correct number of spaces away
Local Variables:
	vector<int> die, a temp holder for the positions of a die
	int move, takes the [0] index of die which is topNum == number of moves
	int tempX, tempY, tempXY, used to store the value of the start X/Y - endX/Y
		which shows us how many spaces they are from each other
Algorithm:
1) Fill in vector<int> die with the die from the [startY][startX] location on the gameboard
2) Set int move to the [0] location on the die
3) Subtract the end point by the starting point and take absolute value
4) Add together to get total number of spaces away
5) If number of moves allowed == number of spaces away --> return true
6) else return false
Assistance Received: none
********************************************************************* */
// Function to make sure the end coordinates are the correct
// number of spaces away from the start coordinates
bool Player::checkNumSpaces(int startX, int startY, int endX, int endY)
{
	int tempX, tempY, tempXY;
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	vector<int> die = tempBoard[startY][startX].getDie();
	// Get number of moves allowed
	int move = die[0];

	// Subtract the end point by the starting point and take absolute value
	// When added together it equals the total number of moves allowed
	tempX = endX - startX;
	tempY = endY - startY;
	tempX = abs(tempX);
	tempY = abs(tempY);
	tempXY = tempX + tempY;
	if (tempXY == move)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* *********************************************************************
Function Name: checkOccupiedSpace
Purpose: Check if the start coordinates contains a die of the correct player
Parameters:
x, y, two ints containing the start x/y coordinates
player, a string containing the player who called it
Local Variables: None
Algorithm:
1) Check if the gameboard is empty at [y][x]
2)		If true return false
3) If it's not empty check to make sure it's one of your pieces
4) Return true if its not empty and it is one of your Dies
Assistance Received: none
********************************************************************* */
bool Player::checkOccupiedSpace(int x, int y, string player)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();

	if (tempBoard[y][x].isEmpty())
	{
		return false;
	}
	// Check if Player is moving correct Die
	else if (player != tempBoard[y][x].getPlayer())
	{
		return false;
	}

	return true;
}

/* *********************************************************************
Function Name: getKeyPieceLoc
Purpose: Given the player find its opponent's keypiece
Parameters:
	player, string containing player who's executing the function
Return Value: vector<int> with vec[0] = x coord and vec[1] = y coord
Local Variables:
	tempBoard, vector<vector<Die>> which is filled with the current state of the board
	location, vector<int> which is the return vector
Algorithm:
1) Loop through the board
2) if the current position contains an opponent's die and it's the keypiece
3)		push the x & y coord to location
4) return location
Assistance Received: none
********************************************************************* */
vector<int> Player::getKeypieceLoc(string player)
{
	vector<int> location;
	vector<vector<Die>> tempBoard = boardObj->GetBoard();

	// Loop through board
	for (int y = 0; y <= 7; y++)
	{
		for (int x = 0; x <= 8; x++)
		{
			if (player == "C")
			{
				// If the location is an opponents die and it's the keypiece
				if (tempBoard[y][x].getPlayer() == "H" && tempBoard[y][x].getKeyPiece() == true)
				{
					// push the x & y coord to location
					location.push_back(x);
					location.push_back(y);
				}
			}
			else
			{
				if (tempBoard[y][x].getPlayer() == "C" && tempBoard[y][x].getKeyPiece() == true)
				{
					location.push_back(x);
					location.push_back(y);
				}
			}
		}
	}

	return location;
}

/* *********************************************************************
Function Name: checkHumanWin
Purpose: Check if Human player won the game
Parameters: None
Return Value: return true if Human win conditions are met
Local Variables:
		tempBoard, vector<vector<Die>> which is filled with the current state of the board
Algorithm:
1) return true if the Computer's keyspace is taken by the human key piece
2) return true if the vector returned by getKeypieceLoc is size 0
		this occurs when the opponents keypiece has been eliminated
Assistance Received: none
********************************************************************* */
bool Player::checkHumanWin()
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();

	// Check if the key square has been overtaken with keypiece
	if (tempBoard[7][4].getPlayer() == "H" && tempBoard[7][4].getKeyPiece())
	{
		return true;
	}
	else if (getKeypieceLoc("H").size() == 0)
	{
		return true;
	}

	return false;
}

/* *********************************************************************
Function Name: checkComputerWin
Purpose: return true if Computer win conditions are met
Parameters: None
Return Value: return true if Computer win conditions are met
Local Variables:
	tempBoard, vector<vector<Die>> which is filled with the current state of the board
Algorithm:
1) return true if the Human's keyspace is taken by the human key piece
2) return true if the vector returned by getKeypieceLoc is size 0
		this occurs when the opponents keypiece has been eliminated
Assistance Received: none
********************************************************************* */
bool Player::checkComputerWin()
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();

	// Check if the key square has been overtaken with keypiece
	if (tempBoard[0][4].getPlayer() == "C" && tempBoard[0][4].getKeyPiece())
	{
		return true;
	}
	else if (getKeypieceLoc("C").size() == 0)
	{
		return true;
	}

	return false;
}

/* *********************************************************************
Function Name: checkVerticalPath
Purpose: This function either checks or executes the move in the vertical direction
Parameters:
startX, startY, endX, endY, ints containing the start and end coordinates
execute, a bool that determines if the function will actually move the die
Return Value: returns true if the check or move is complete
Local Variables:
tempBoard, vector<vector<Die>> which is filled with the current state of the board
player, string containing the player at the start location
oppositePlayer, a bool signifying if an opponents die is at the end location
first, a bool that flips after the first loop iteration to skip it
tempY, an int set to 1 +- endY so the check stops before the end space
Algorithm:
1) If startY > endY, check the downward movement of the starting piece
2)		set tempY to 1 above the endX
3)		Loop starting from StartY as long as startY > endY
4)			If execute is false, check board at every StartY in loop to see if space is empty
5)				If the end space is an opposing die on return true so it can overtake
6)			If execute is true, call the movePieceDown function every iteration of the loop
7)		return true on successful completion
8) If startY < endY do opposite and call movePieceUp to move the die up on the board
Assistance Received: none
********************************************************************* */
bool Player::checkVerticalPath(int startX, int startY, int endX, int endY, bool execute)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	string player = tempBoard[startY][startX].getPlayer();
	bool first = true;
	bool oppositePlayer = tempBoard[endY][endX].oppositePlayer(player);
	int tempY;
	tempY = endY;


	if (startY > endY)
	{
		tempY++;
		for (startY; startY > endY; startY--)
		{
			// Only check path no execution of move
			if (!execute)
			{
				if (first)
				{
					first = false;
					continue;
				}
				// Return False if path is blocked
				if (!tempBoard[startY][startX].isEmpty())
				{
					return false;
				}
				// If the end space is on an opposing die overtake end space
				if (startX == endX && startY == tempY && oppositePlayer)
				{
					return true;
				}

			}
			else
			{
				if (startX == endX && startY == tempY && !tempBoard[endY][endX].isEmpty())
				{
					cout << tempBoard[endY][endX].displayDie() << " has been overtaken and removed from play" << endl;
				}
				boardObj->movePieceDown(startX, startY);
			}

		}
		// Path is clear or move is executed return true
		return true;
	}
	else if (startY < endY)
	{
		tempY--;
		for (startY; startY < endY; startY++)
		{
			if (!execute)
			{
				if (first)
				{
					first = false;
					continue;
				}
				// Return False if path is blocked
				if (!tempBoard[startY][startX].isEmpty())
				{
					return false;
				}
				// If the end space is on an opposing die overtake end space
				if (startX == endX && startY == tempY && oppositePlayer)
				{
					return true;
				}



			}
			else
			{
				if (startX == endX && startY == tempY && !tempBoard[endY][endX].isEmpty())
				{
					cout << tempBoard[endY][endX].displayDie() << " has been overtaken and removed from play" << endl;
				}
				boardObj->movePieceUp(startX, startY);
			}

		}
		// Path is clear return true
		return true;
	}
	// Error
	return false;
}

/* *********************************************************************
Function Name: checkHorizontalPath
Purpose: This function either checks or executes the move in the horizontal direction
Parameters:
startX, startY, endX, endY, ints containing the start and end coordinates
execute, a bool that determines if the function will actually move the die
Return Value: returns true if the check or move is complete
Local Variables:
tempBoard, vector<vector<Die>> which is filled with the current state of the board
player, string containing the player at the start location
oppositePlayer, a bool signifying if an opponents die is at the end location
first, a bool that flips after the first loop iteration to skip it
tempX, an int set to 1 +- endX so the check stops before the end space
Algorithm:
1) If startX > endX, check the lateral left movement of the starting piece
2)		set tempX to 1 above the endX
3)		Loop starting from StartY as long as startY > endY
4)			If execute is false, check board at every StartX in loop to see if space is empty
5)				If the end space is an opposing die on return true so it can overtake
6)			If execute is true, call the movePieceLeft function every iteration of the loop
7)		return true on successful completion
8) If startX < endX do opposite and call movePieceRight to move the die right on the board
Assistance Received: none
********************************************************************* */
bool Player::checkHorizontalPath(int startX, int startY, int endX, int endY, bool execute)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	string player = tempBoard[startY][startX].getPlayer();
	bool oppositePlayer = tempBoard[endY][endX].oppositePlayer(player);
	bool first = true;
	int tempX;
	tempX = endX;

	if (startX > endX)
	{
		tempX++;
		for (startX; startX > endX; startX--)
		{
			if (!execute)
			{
				if (first)
				{
					first = false;
					continue;
				}
				// Return False if path is blocked
				if (!tempBoard[startY][startX].isEmpty())
				{
					return false;
				}
				// If the end space is on an opposing die overtake end space
				if (startX == tempX && startY == endY && oppositePlayer)
				{
					return true;
				}

			}
			else
			{
				if (startX == tempX && startY == endY && !tempBoard[endY][endX].isEmpty())
				{
					cout << tempBoard[endY][endX].displayDie() << " has been overtaken and removed from play" << endl;
				}
				boardObj->movePieceLeft(startX, startY);
			}

		}
		// Path is clear return true
		return true;
	}
	else if (startX < endX)
	{
		tempX--;
		for (startX; startX < endX; startX++)
		{
			if (!execute)
			{
				if (first)
				{
					first = false;
					continue;
				}
				// Return False if path is blocked
				if (!tempBoard[startY][startX].isEmpty())
				{
					return false;
				}
				// If the end space is on an opposing die overtake end space
				if (startX == tempX && startY == endY && oppositePlayer)
				{
					return true;
				}

			}
			else
			{
				if (startX == tempX && startY == endY && !tempBoard[endY][endX].isEmpty())
				{
					cout << tempBoard[endY][endX].displayDie() << " has been overtaken and removed from play" << endl;
				}
				boardObj->movePieceRight(startX, startY);
			}

		}
		// Path is clear return true
		return true;
	}
	// Error
	return false;
}


/* *********************************************************************
Function Name: getDirection()
Purpose: This function finds direction to move with a clear path
Parameters:
	startX, startY, endX, endY, ints containing the start and end coordinates
Return Value: an int which signifies the direction chosen
Local Variables: None
Algorithm:
1) If startX = endX, return 0 if the vertical path is clear
2) If startY = endY, return 0 if the horizontal path is clear
3) If the vertical path then the horizontal path is clear, return 1
4) If the horizontal path then the vertical path is clear, return 2
5) If no path is clear return -1
Assistance Received: none
********************************************************************* */
int Player::getDirection(int startX, int startY, int endX, int endY)
{
	// Return 0 if strictly vertical or strictly horizontal move
	if (startX == endX)
	{
		if (checkVerticalPath(startX, startY, endX, endY, false))
		{
			return 0;
		}
	}
	else if(startY == endY)
	{
		if (checkHorizontalPath(startX, startY, endX, endY, false))
		{
			return 0;
		}
	}
	// Check forward then horizontal path and return 1
	else if (checkVerticalPath(startX, startY, endX, endY, false))
	{
		if (checkHorizontalPath(startX, endY, endX, endY, false))
		{
			return 1;
		}
	}
	// Check lateral then forward and return 2
	if (checkHorizontalPath(startX, startY, endX, endY, false))
	{
		if (checkVerticalPath(endX, startY, endX, endY, false))
		{
			return 2;
		}
	}
	// Return -1 if no paths are clear
	return -1;
}

/* *********************************************************************
Function Name: getPath
Purpose: This function has two purposes depending on the execute parameter
1) If execute is false, simply check the path
2) If execute is true, the function executes the move to the end coordinates
Parameters:
	startX, startY, endX, endY, ints containing the start and end coordinates
	direction, int signifying the direction the piece will travel
	execute, a bool that determines if the function will actually move the die
Return Value:
	bool, return true at successful completion of path checking or path execution
Local Variables:
	tempBoard, vector<vector<Die>> which is filled with the current state of the board
	player, string containing the player at the start coordinates
	endPlayer, string containing the player at the end coordinates
Algorithm:
1) If player = endPlayer, the move is invalid since the end space is occupied by
		a piece of the same player. Return false
2) If startX == endX, the path is strictly vertical
3)		If checkVerticalPath(...false) is true, the vertical path is clear. return true
4)			If execute is true and checkVerticalPath(...true) is true, move executed successfully
5) If startY == endY, repeat steps 3-4 with checkHorizontalPath instead
6) If direction == 1 check/execute vertical then horizontal path, return true if successful
7) If direction == 2 check/execute horizontal then vertical path, return true if successful
8) return false paths are not clear
Assistance Received: none
********************************************************************* */
bool Player::getPath(int startX, int startY, int endX, int endY, int direction, bool execute)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	string player = tempBoard[startY][startX].getPlayer();
	string endPlayer = tempBoard[endY][endX].getPlayer();


	// If endspace is occupied by Die of same player path is blocked
	if (player == endPlayer)
	{
		return false;
	}
	// If move is strictly forward
	if (startX == endX)
	{
		// If path is clear, execute move and return true
		if (checkVerticalPath(startX, startY, endX, endY, false))
		{
			if (execute)
			{
				if (checkVerticalPath(startX, startY, endX, endY, true))
				{
					return true;
				}
			}	
			return true;
		}
	}
	// If move is strictly lateral
	else if (startY == endY)
	{
		// If path is clear, execute move and return true
		if (checkHorizontalPath(startX, startY, endX, endY, false))
		{
			if (execute)
			{
				if (checkHorizontalPath(startX, startY, endX, endY, true))
				{
					return true;
				}
			}
			return true;
		}
	}
	// If move is forward then lateral
	else if (direction == 1)
	{
		// Check if path is clear
		if (checkVerticalPath(startX, startY, endX, endY, false))
		{
			if (checkHorizontalPath(startX, endY, endX, endY, false))
			{
				if (execute)
				{
					// Execute Move
					if (checkVerticalPath(startX, startY, endX, endY, true))
					{
						if (checkHorizontalPath(startX, endY, endX, endY, true))
						{
							return true;
						}
					}
				}
				return true;
			}
		}
	}
	// If move is lateral then forward
	else if (direction == 2)
	{
		// Check if path is clear
		if (checkHorizontalPath(startX, startY, endX, endY, false))
		{
			if (checkVerticalPath(endX, startY, endX, endY, false))
			{
				if (execute)
				{
					// Execute Move
					if (checkHorizontalPath(startX, startY, endX, endY, true))
					{
						if (checkVerticalPath(endX, startY, endX, endY, true))
						{
							return true;
						}
					}
				}
				return true;
			}
		}
	}

	// No clear path return false
	return false;
}

/* *********************************************************************
Function Name: displayMove
Purpose: Display the Computer's move and explain the reasoning behind it
Parameters:
	startX, startY, endX, endY, ints containing the start and end coordinates
	direction, int signifying the direction the piece will travel
	moveType, an int signifying the reason behind the move
Return Value: void
Local Variables:
	displayX/Y = used to hold the modifyable coordinates for display
	tempBoard, vector<vector<Die>> which is filled with the current state of the board
Algorithm:
1) If moveType = 1, Display start die, coords, and key piece attack reasoning
2) If moveType = 2, Display start die, coords, and block attack reasoning
3) If moveType = 3, Display start die, coords, and overtake human die reasoning
4) If not 1, 2, or 3, Display start die, coords and last case reasoning
5) Then depending on the direction value
6) Calculate the number of spaces moved in a direction
7) Print the number of spaces moved in that direction and why it chose that path
Assistance Received: none
********************************************************************* */
void Player::displayMove(int startX, int startY, int endX, int endY, int moveType, int direction)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	int displayX = startX;
	int displayY = startY;
	displayX++;
	displayY++;

	if (moveType == 1)
	{
		// Display results for keypiece attack algorithm
		cout << "*The Computer has Picked " << tempBoard[startY][startX].displayDie() << " at (" << displayY << "," << displayX << ") to roll because this Die can win the game" << endl;

	}
	else if (moveType == 2)
	{
		// Display results for keypiece block algorithm
		cout << "*The Computer has Picked " << tempBoard[startY][startX].displayDie() << " at (" << displayY << "," << displayX << ") to roll because this Die can block an attack on the keypiece" << endl;

	}
	else if (moveType == 3)
	{
		// Display results for overtake piece
		cout << "*The Computer has Picked " << tempBoard[startY][startX].displayDie() << " at (" << displayY << "," << displayX << ") to roll because this Die can overtake a Human piece" << endl;

	}
	else
	{
		// Display results of best move algorithm
		cout << "The Computer has Picked " << tempBoard[startY][startX].displayDie() << " at (" << displayY << "," << displayX << ") to roll because this Die can move closest to the Human KeyPiece" << endl;

	}

	// Find type of roll and number of spaces for display
	if (direction == 0)
	{
		if (startX == endX)
		{
			int numSpacesY = abs(startY - endY);
			cout << "It rolled " << numSpacesY << " frontally because it was the most direct clear path" << endl;
		}
		else
		{
			int numSpacesX = abs(startX - endX);
			cout << "It rolled " << numSpacesX << " laterally because it was the most direct clear path" << endl;
		}

	}
	else if (direction == 1)
	{
		int numSpacesY = abs(startY - endY);
		int numSpacesX = abs(startX - endX);
		cout << "It rolled " << numSpacesY << " frontally and " << numSpacesX << " laterally because a frontal then lateral path was clear" << endl;
	}
	else if (direction == 2)
	{
		int numSpacesY = abs(startY - endY);
		int numSpacesX = abs(startX - endX);
		cout << "It rolled " << numSpacesX << " laterally and " << numSpacesY << " frontally because a straight frontal and frontal -> lateral move were blocked" << endl;
	}
}

/* *********************************************************************
Function Name: keyPieceAttack
Purpose: First pass of AI algorithm
	Determines and excutes m a move overtaking the keypiece or keyspace
Parameters:
	player, string containing the player
	display, bool if true it will display help for human player
Return Value: return true if successful
Local Variables:
	tempBoard, vector<vector<Die>> which is filled with the current state of the board
	KeyPieceLocation, vector<int> the vector holding the coords of the keypiece
	endX, endY, ints containing the coordinates of the keypiece
	direction, int signifying the direction the piece will travel
Algorithm:
1) Loop through each space on the board looking for a computer die
2) Check if that die is the correct number of spaces away from the end coords
3) Check if a move in any direction is clear
4) Display the chosen move and reasoning
5) Execute the move and return true
6) Do steps 1-5 except make the keyspace the end coords
7) If a human calls help()
8) Run steps 2-4 and display results for the human
Assistance Received: none
********************************************************************* */
bool Player::keyPieceAttack(string player, bool display)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	vector<int> KeyPieceLocation = getKeypieceLoc(player);
	int endX = KeyPieceLocation[0];
	int endY = KeyPieceLocation[1];
	int direction;

	for (int y = 0; y <= 7; y++)
	{
		for (int x = 0; x <= 8; x++)
		{			
			if (player == "C")
			{
				// If Die piece is a computer piece check all possible moves
				// to either overtake the Human keypiece or the keyspace
				if (tempBoard[y][x].getPlayer() == "C")
				{
					// Check if the Computer Piece is the correct
					// number of spaces from the Human Key Piece
					if (checkNumSpaces(x, y, endX, endY))
					{
						direction = getDirection(x, y, endX, endY);
						if (direction != -1)
						{
							displayMove(x, y, endX, endY, 1, direction);
							if (getPath(x, y, endX, endY, direction, true))
							{
								return true;
							}
						}
					}
					// Check against the key space
					else if ((checkNumSpaces(x, y, 4, 0)))
					{
						direction = getDirection(x, y, 4, 0);
						// If direction != -1 path is clear in that direction
						if (direction != -1)
						{
							displayMove(x, y, endX, endY, 1, direction);
							if (getPath(x, y, 4, 0, direction, true))
							{
								return true;
							}
						}
					}
				}				
			}
			else
			{
				// If Die piece is a human piece check all possible moves
				// to either overtake the computer keypiece or the keyspace
				if (tempBoard[y][x].getPlayer() == "H")
				{
					// Check if the Computer Piece is the correct
					// number of spaces from the Human Key Piece
					if (checkNumSpaces(x, y, endX, endY))
					{
						direction = getDirection(x, y, endX, endY);
						if (direction != -1)
						{
							if (display)
							{
								displayHelp(x, y, endX, endY, direction, "attackPiece");
							}
							return true;
						}
					}
					else if ((checkNumSpaces(x, y, 4, 7)))
					{
						direction = getDirection(x, y, 4, 7);
						// If direction != -1 path is clear in that direction
						if (direction != -1)
						{
							if (display)
							{
								displayHelp(x, y, 4, 7, direction, "attackSpace");
							}
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

/* *********************************************************************
Function Name: protectKeyPiece
Purpose: Second Pass of AI algorithm, move to protect keypiece
Parameters:
	player, string containing the player
	keySpace, bool if true it will block keyspace
Return Value: return true if successful
Local Variables:
	tempBoard, vector<vector<Die>> which is filled with the current state of the board
	KeyPieceLocation, vector<int> the vector holding the coords of the keypiece
	endX, endY, ints containing the coordinates of the keypiece
	direction, int signifying the direction the piece will travel
Algorithm:
1) Set the end coords based on player and if they're checking the keyspace or keypiece
2) Loop through each space of the board looking for an opponents die
3) Check if that die is the correct number of moves away from your keyPiece/Space
4) Check if any path is clear to the end space meaning you're vulnerable for attack
5) Depending on the direction call executeBlock on the proper end coordinates
		to check if any of the players pieces can block
Assistance Received: none
********************************************************************* */
bool Player::protectKeyPiece(string player, bool keySpace)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	int direction, endX, endY;

	// If its a computer move and we're trying to protect the key piece
	if (player == "C" && !keySpace)
	{
		vector<int> KeyPieceLocation = getKeypieceLoc("H");
		endX = KeyPieceLocation[0];
		endY = KeyPieceLocation[1];
	}
	// If its a computer move and we're trying to protect the key space
	else if (player == "C" && keySpace)
	{
		endX = 4;
		endY = 7;	
	}
	// If its a human move and we're trying to protect the key piece
	else if(player == "H" && !keySpace)
	{
		vector<int> KeyPieceLocation = getKeypieceLoc("C");
		endX = KeyPieceLocation[0];
		endY = KeyPieceLocation[1];
	}
	// If its a human move and we're trying to protect the key space
	else
	{
		endX = 4;
		endY = 0;
	}

	for (int y = 7; y >= 0; y--)
	{
		for (int x = 0; x <= 8; x++)
		{
			// Computer Move
			if (player == "C")
			{
				// If Die piece is a human piece check all possible moves
				// that can overtake the computer keypiece or the keyspace
				if (tempBoard[y][x].getPlayer() == "H")
				{
					// Check if the Human Piece is the correct
					// number of spaces from the Computer Key Piece
					if (checkNumSpaces(x, y, endX, endY))
					{
						direction = getDirection(x, y, endX, endY);
						// If check path is true, then Human has a winning move
						// Execute block and return true
						if (direction != -1)
						{
							if (direction == 0)
							{
								// If its a vertical attack and end is higher than start
								if (x == endX && endY > y)
								{
									endY--;
									// For a forward attack set --endY
									// So block manuever is executed one space below keypiece
									if (executeBlock(endX, endY, true))
									{
										return true;
									}
								}
								// If its a vertical attack and end is lower than start
								else if (x == endX && endY < y)
								{
									endY++;
									if (executeBlock(endX, endY, true))
									{
										return true;
									}
								}
								// If its a Horizontal attack and end is higher than start
								else if (y == endY && endX > x)
								{
									// Block Space to left of Keypiece
									if (endX > x)
									{
										--endX;
										if (executeBlock(endX, endY, true))
										{
											return true;
										}
									}
								}
								// If its a Horizontal attack and end is lower than start
								else if (y == endY && endX < x)
								{
									++endX;
									if (executeBlock(endX, endY, true))
									{
										return true;
									}
								}
							}
							// If its a forward -> lateral attack
							else if (direction == 1)
							{
								// Block Space to left of Keypiece
								if (endX > x)
								{
									--endX;
									if (executeBlock(endX, endY, true))
									{
										return true;
									}
								}
								else if (endX < x)
								{
									++endX;
									if (executeBlock(endX, endY, true))
									{
										return true;
									}
								}
							}
							// If its a lateral -> forward
							else if (direction == 2)
							{
								if (endY > y)
								{
									endY--;
									// For a forward or lateral->forward attack set --endY
									// So block manuever is executed one space below keypiece
									if (executeBlock(endX, endY, true))
									{
										return true;
									}
								}
								else if (endY < y)
								{
									endY++;
									if (executeBlock(endX, endY, true))
									{
										return true;
									}
								}
							}
						}
					}
				}
			}
			// Human move
			else
			{
				// If Die piece is a Computer piece check all possible moves
				// that can overtake the human keypiece or the keyspace
				if (tempBoard[y][x].getPlayer() == "C")
				{
					// Check if the Computer Piece is the correct
					// number of spaces from the Human Key Piece
					if (checkNumSpaces(x, y, endX, endY))
					{
						direction = getDirection(x, y, endX, endY);
						// If check path is true, then Human has a winning move
						// Execute block and return true
						if (direction != -1)
						{
							if (direction == 0)
							{
								// If its a vertical attack and end is higher than start
								if (x == endX && endY > y)
								{
									endY--;
									// For a forward attack set --endY
									// So block manuever is executed one space below keypiece
									if (executeBlock(endX, endY, false))
									{
										return true;
									}
								}
								// If its a vertical attack and end is lower than start
								else if (x == endX && endY < y)
								{
									endY++;
									if (executeBlock(endX, endY, false))
									{
										return true;
									}
								}
								// If its a Horizontal attack and end is higher than start
								else if (y == endY && endX > x)
								{
									// Block Space to left of Keypiece
									if (endX > x)
									{
										--endX;
										if (executeBlock(endX, endY, false))
										{
											return true;
										}
									}
								}
								// If its a Horizontal attack and end is lower than start
								else if (y == endY && endX < x)
								{
									++endX;
									if (executeBlock(endX, endY, false))
									{
										return true;
									}
								}
							}
							// If its a forward -> lateral attack
							else if (direction == 1)
							{
								// Block Space to left of Keypiece
								if (endX > x)
								{
									--endX;
									if (executeBlock(endX, endY, false))
									{
										return true;
									}
								}
								else if (endX < x)
								{
									++endX;
									if (executeBlock(endX, endY, false))
									{
										return true;
									}
								}
							}
							// If its a lateral -> forward
							else if (direction == 2)
							{
								if (endY > y)
								{
									endY--;
									// For a forward or lateral->forward attack set --endY
									// So block manuever is executed one space below keypiece
									if (executeBlock(endX, endY, false))
									{
										return true;
									}
								}
								else if (endY < y)
								{
									endY++;
									if (executeBlock(endX, endY, false))
									{
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

/* *********************************************************************
Function Name: executeBlock
Purpose: If it is found an opponent can attack, check for a possible candidate to block
Parameters:
	endX, endY, ints containing the end coordinates
	bool, true if function should execute the move
Return Value: return true if successful
Local Variables:
	tempBoard, vector<vector<Die>> which is filled with the current state of the board
	direction, int signifying the direction the piece will travel
Algorithm:
1) Loop through board looking for one of your own die
2) Check to see if the piece is the correct distance from the end space
3) Get a direction with a clear path
4) Display the move
5) Execute move
6) Do steps 1-4 if Human is player
7) Send data to the help function
Assistance Received: none
********************************************************************* */
bool Player::executeBlock(int endX, int endY, bool execute)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	int direction;

	// Coordinates (endX, endY) is the Computer Keypiece
	// To find a candidate to block from below
	// find a Computer piece that can move to endX--
	for (int y = 7; y >= 0; y--)
	{
		for (int x = 0; x <= 8; x++)
		{
			if (execute)
			{
				if (tempBoard[y][x].getPlayer() == "C")
				{
					if (checkNumSpaces(x, y, endX, endY))
					{
						direction = getDirection(x, y, endX, endY);
						if (direction != -1)
						{
							displayMove(x, y, endX, endY, 2, direction);
							if (getPath(x, y, endX, endY, direction, true))
							{
								return true;
							}

						}
					}
				}
			}
			else
			{
				if (tempBoard[y][x].getPlayer() == "H")
				{
					if (checkNumSpaces(x, y, endX, endY))
					{
						direction = getDirection(x, y, endX, endY);
						if (direction != -1)
						{
							displayHelp(x, y, endX, endY, direction, "block");
							return true;
						}
					}
				}
			}
		}
	}

	// If there are no possible blocking moves return false
	return false;
}


/* *********************************************************************
Function Name: checkOvertake
Purpose: Third pass of AI algorithm, Check if theres a die to overtake
Parameters:
	player, string containing the player
Return Value: return true if successful overtake
Local Variables:
	tempBoard, vector<vector<Die>> which is filled with the current state of the board
	direction, int signifying the direction the piece will travel
Algorithm:
1) Loop through board looking for a die owned by player
2) Once found, loop through board again looking for die owned by opponent
3) Check the distance between the two die
4) Find a direction with a clear path 
5) Execute move and overtake piece
Assistance Received: none
********************************************************************* */
bool Player::checkOvertake(string player)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	int direction;

	for (int y = 7; y >= 0; y--)
	{
		for (int x = 0; x <= 8; x++)
		{
			// Computer Move
			if (player == "C")
			{
				// If Die piece is a computer piece check all possible moves
				// to overtake a Human Piece
				if (tempBoard[y][x].getPlayer() == "C")
				{
					for (int endY = 0; endY <= 7; endY++)
					{
						for (int endX = 0; endX <= 8; endX++)
						{
							if (tempBoard[endY][endX].getPlayer() == "H")
							{
								if (checkNumSpaces(x, y, endX, endY))
								{
									direction = getDirection(x, y, endX, endY);
									if (direction != -1)
									{
										displayMove(x, y, endX, endY, 3, direction);
										if (getPath(x, y, endX, endY, direction, true))
										{
											return true;
										}

									}
								}
							}
						}
					}
				}
			}
			// Human move
			else
			{
				// If Die piece is a Human piece check all possible moves
				// to overtake a Computer Piece
				if (tempBoard[y][x].getPlayer() == "H")
				{
					for (int endY = 7; endY >= 0; endY--)
					{
						for (int endX = 0; endX <= 8; endX++)
						{
							if (tempBoard[endY][endX].getPlayer() == "C")
							{
								if (checkNumSpaces(x, y, endX, endY))
								{
									direction = getDirection(x, y, endX, endY);
									if (direction != -1)
									{
										displayHelp(x, y, endX, endY, direction, "overtake");
										return true;
									}
								}
							}
						}
					}
				}
			}

		}
	}
	return false;
}


/* *********************************************************************
Function Name: executeBestMove
Purpose: Fourth pass of AI algorithm; Blitz tactic
	Find a piece that can move closest to the Human's keypiece
Parameters: None
Return Value: return true if piece has been moved to the best location available
Local Variables:
	tempBoard, vector<vector<Die>> which is filled with the current state of the board
	direction, int signifying the direction the piece will travel
	temp, score, int that holds the best score for all the moves available
	KeyPieceLocation, vector<int> the vector holding the coords of the keypiece
	keyX, keyY, ints storing the coords for the opponents keypiece
	startX, startY, finalX, finalY, ints containing the start and end coordinates
Algorithm:
1) Loop through board looking for Computer die
2) Loop through board again checking every possible end location for the die
3) Check direction and if path is clear for an endpoint
4) Calculate the distance of that valid endpoint to the keypiece, save to tempScore
5) If the tempScore < score this move will be closer to the keypiece
6) Display move with the lowest score
7) Execute the move with the lowest score
Assistance Received: none
********************************************************************* */
bool Player::executeBestMove()
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	vector<int> KeyPieceLocation = getKeypieceLoc("C");
	int keyX = KeyPieceLocation[0];
	int keyY = KeyPieceLocation[1];
	int score = 100;
	int direction, tempDirection, tempScore, startX, startY, finalX, finalY;

	// Loop through board finding every C piece
	for (int y = 0; y <= 7; y++)
	{
		for (int x = 0; x <= 8; x++)
		{
			if (tempBoard[y][x].getPlayer() == "C")
			{
				// When C piece is found loop through board again
				// Checking all possible end locations
				for (int endY = 0; endY <= 7; endY++)
				{
					for (int endX = 0; endX <= 8; endX++)
					{
						// If end point is proper number of spaces
						// Check path and get direction and calculate score
						if (checkNumSpaces(x, y, endX, endY))
						{
							tempDirection = getDirection(x, y, endX, endY);
							// If getDirection != -1 path is clear
							if (tempDirection != -1)
							{
								tempScore = (abs(endX - keyX) + abs(endY - keyY));

								if (tempScore < score)
								{
									score = tempScore;
									direction = tempDirection;
									startX = x;
									startY = y;
									finalX = endX;
									finalY = endY;
								}
							}
						}
					}
				}
			}
		}
	}
	// Display Results
	displayMove(startX, startY, finalX, finalY, 4, direction);
	// If move is executed return true;
	if (getPath(startX, startY, finalX, finalY, direction, true))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* *********************************************************************
Function Name: help
Purpose: This function calls all the AI components as a human player
			to generate the help prompts
Parameters: None
Return Value: void
Local Variables: None
Algorithm:
1) Check if a human die can attack the computer's keypiece
2) Check if a human die can defend the keypiece
3) Check if a human die can defend the keyspace
4) Check is a human die can overtake a computer die
5) If none of these scenarios are true, prompt the player to move any piece they choose
Assistance Received: none
********************************************************************* */
void Player::help()
{
	// Check if Human has winning move
	if (keyPieceAttack("H", true));
	// Check if 
	else if (protectKeyPiece("H", false));
	else if (protectKeyPiece("H", true));
	else if (checkOvertake("H"));
	else
	{
		cout << "***********************************************************************************" << endl;
		cout << "*                               ~~ Help ~~                                        *" << endl;
		cout << "*     There are no critical moves to execute, move any die of your choosing       *" << endl;
		cout << "***********************************************************************************" << endl;

	}


}

/* *********************************************************************
Function Name: displayHelp
Purpose: Displays the help results for the human player
Parameters:
	startX, startY, endX, endY, ints containing the start and end coordinates
	direction, int signifying the direction the piece will travel
	moveType, string signifying the type of move to display
Return Value: void
Local Variables:
	tempBoard, vector<vector<Die>> which is filled with the current state of the board
	message, a string containing message to display
Algorithm:
1) Depending on the moveType set the message to explain what the move will accomplish
2) Depending on the direction display the start die, the location, end location, and which direction to move first
Assistance Received: none
********************************************************************* */
void Player::displayHelp(int startX, int startY, int endX, int endY, int direction, string moveType)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	string message;
	int displayX = startX;
	int displayY = startY;

	if (moveType == "attackPiece")
	{
		message = "To attack the key piece and win the game";
	}
	else if (moveType == "attackSpace")
	{
		message = "To attack the key space and win the game";
	}
	else if (moveType == "block")
	{
		message = "To perform blocking move                ";
	}
	else if (moveType == "overtake")
	{
		message = "To overtake a computer piece            ";
	}
	else
	{

	}


	if (direction == 0)
	{
		if (startX == endX)
		{
			cout << "*******************************************************************************************************" << endl;
			cout << "*                                           ~~ Help ~~                                                *" << endl;
			cout << "*     " << message << "                                                        *" << endl;
			cout << "*     Choose die " << tempBoard[displayY][displayX].displayDie() << " at location (" << ++startY << "," << ++startX << ")                                                                *" << endl;
			cout << "*     Roll it to location (" << ++endY << "," << ++endX << ") frontally because it is the most direct clear path                    *" << endl;
			cout << "*******************************************************************************************************" << endl;


		}
		else
		{
			cout << "*******************************************************************************************************" << endl;
			cout << "*                                           ~~ Help ~~                                                *" << endl;
			cout << "*     " << message << "                                                        *" << endl;
			cout << "*     Choose die " << tempBoard[displayY][displayX].displayDie() << " at location (" << ++startY << "," << ++startX << ")                                                                *" << endl;
			cout << "*     Roll it to location (" << ++endY << "," << ++endX << ") laterally because it is the most direct clear path          *" << endl;
			cout << "*******************************************************************************************************" << endl;

		}

	}
	else if (direction == 1)
	{
		cout << "*******************************************************************************************************" << endl;
		cout << "*                                           ~~ Help ~~                                                *" << endl;
		cout << "*     " << message << "                                                        *" << endl;
		cout << "*     Choose die " << tempBoard[displayY][displayX].displayDie() << " at location (" << ++startY << "," << ++startX << ")                                                                *" << endl;
		cout << "*     Roll it to location (" << ++endY << "," << ++endX << ") frontally first because a frontal then lateral path is clear          *" << endl;
		cout << "*******************************************************************************************************" << endl;
	}
	else if (direction == 2)
	{
		cout << "*******************************************************************************************************" << endl;
		cout << "*                                           ~~ Help ~~                                                *" << endl;
		cout << "*     " << message << "                                                        *" << endl;
		cout << "*     Choose die " << tempBoard[displayY][displayX].displayDie() << " at location (" << ++startY << "," << ++startX << ")                                                                *" << endl;
		cout << "*     Roll it to location (" << ++endY << "," << ++endX << ") laterally first because a lateral then frontal path is clear          *" << endl;
		cout << "*******************************************************************************************************" << endl;

	}
	
}



