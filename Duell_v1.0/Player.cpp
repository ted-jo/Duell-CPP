#include "Player.h"




Player::Player()
{
	humanWin = 0;
	computerWin = 0;
}

Player::~Player()
{
}

void Player::setBoard(Board * board)
{
	boardObj = board;
}

// Function checks to make sure coordinates are not out of bounds
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

bool Player::validateMove(int startX, int startY, int endX, int endY, int direction, string player)
{
	bool validation = true;

	// Check if starting coordinates are out of bounds
	if (!checkOOB(startX, startY))
	{
		cout << "**************************************************" << endl;
		cout << "*  Error: Starting Coordinates Out of Bounds     *" << endl;
		cout << "*  Please Select New Coordinates                 *" << endl;
		cout << "**************************************************" << endl;
		validation = false;
	}
	// Check if ending coordinates are out of bounds
	else if (!checkOOB(endX, endY))
	{
		cout << "**************************************************" << endl;
		cout << "*  Error: Ending Coordinates Out of Bounds       *" << endl;
		cout << "*  Please Select New Coordinates                 *" << endl;
		cout << "**************************************************" << endl;
		validation = false;
	}
	// Check if theres a valid die piece on the starting location
	else if (!boardObj->checkOccupiedSpace(startX, startY, player))
	{
		cout << "**************************************************" << endl;
		cout << "*  Error: No Valid Piece on Starting Coordinates *" << endl;
		cout << "*  Please Select New Coordinates                 *" << endl;
		cout << "**************************************************" << endl;
		validation = false;
	}
	// Check if the end coordinates are the correct number of spaces 
	// away from the starting coordinates
	else if (!boardObj->checkNumSpaces(startX, startY, endX, endY))
	{
		cout << "*****************************************************" << endl;
		cout << "*  Error: End Coordinates Out of Range of Movement  *" << endl;
		cout << "*  Please Select New Coordinates                    *" << endl;
		cout << "*****************************************************" << endl;

		validation = false;
	}
	// Check if there are any pieces blocking move
	//else if (!boardObj->checkPath(startX, startY, endX, endY, direction))
	else if(!getPath(startX, startY, endX, endY, direction, false))
	{
		cout << "*****************************************************" << endl;
		cout << "*  Error: Path is Blocked                           *" << endl;
		cout << "*  Please Select New Coordinates                    *" << endl;
		cout << "*****************************************************" << endl;

		validation = false;
	}


	return validation;
}

// Function finds either the Human or computer keypiece and
// stores the coordinates in a vector
vector<int> Player::getKeypieceLoc(string player)
{
	vector<int> location;
	vector<vector<Die>> tempBoard = boardObj->GetBoard();

	for (int y = 0; y <= 7; y++)
	{
		for (int x = 0; x <= 8; x++)
		{
			if (player == "C")
			{
				if (tempBoard[y][x].getPlayer() == "H" && tempBoard[y][x].getKeyPiece() == true)
				{
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

void Player::setWin(string player)
{
	if (player == "C")
	{
		computerWin++;
	}
	else
	{
		humanWin++;
	}
}

bool Player::checkHumanWin()
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();

	// Check if the key square has been overtaken set win for Human
	if (tempBoard[7][4].getPlayer() == "H")
	{
		setWin("H");
		return true;
	}
	else if (getKeypieceLoc("C").size() == 0)
	{
		setWin("H");
		return true;
	}

	return false;
}

int Player::getDirection(int startX, int startY, int endX, int endY)
{
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
	// Check  lateral then forward and return 2
	if (checkHorizontalPath(startX, startY, endX, endY, false))
	{
		if (checkVerticalPath(endX, startY, endX, endY, false))
		{
			return 2;
		}
	}
	return -1;
}

// Checks and executes path
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
				// If the end space is on an opposing die overtake end space
				if (startX == endX && startY == tempY && oppositePlayer)
				{
					return true;
				}
				// Return False if path is blocked
				if (!tempBoard[startY][startX].isEmpty())
				{
					return false;
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
	else if(startY < endY)
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
				// If the end space is on an opposing die overtake end space
				if (startX == endX && startY == tempY && oppositePlayer)
				{
					return true;
				}
				// Return False if path is blocked
				if (!tempBoard[startY][startX].isEmpty())
				{
					return false;
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
				// If the end space is on an opposing die overtake end space
				if (startX == tempX && startY == endY && oppositePlayer)
				{
					return true;
				}
				// Return False if path is blocked
				if (!tempBoard[startY][startX].isEmpty())
				{
					return false;
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
				// If the end space is on an opposing die overtake end space
				if (startX == tempX && startY == endY && oppositePlayer)
				{
					return true;
				}
				// Return False if path is blocked
				if (!tempBoard[startY][startX].isEmpty())
				{
					return false;
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
		cout << "The Computer has Picked " << tempBoard[startY][startX].displayDie() << " at (" << displayY << "," << displayX << ") to roll because this Die can win the game" << endl;

	}
	else if (moveType == 2)
	{
		// Display results for keypiece block algorithm
		cout << "The Computer has Picked " << tempBoard[startY][startX].displayDie() << " at (" << displayY << "," << displayX << ") to roll because this Die can block an attack on the keypiece" << endl;

	}
	else if (moveType == 3)
	{
		// Display results for overtake piece
		cout << "The Computer has Picked " << tempBoard[startY][startX].displayDie() << " at (" << displayY << "," << displayX << ") to roll because this Die can overtake a Human piece" << endl;

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

// TODO: check against key space fore human
bool Player::keyPieceAttack(string player)
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
					if (boardObj->checkNumSpaces(x, y, endX, endY))
					{
						direction = getDirection(x, y, endX, endY);
						if (direction != -1)
						{
							if (getPath(x, y, endX, endY, direction, true))
							{
								return true;
							}
						}
					}
					// Check against the key space
					else if ((boardObj->checkNumSpaces(x, y, 4, 0)))
					{
						direction = getDirection(x, y, endX, endY);
						// If direction != -1 path is clear in that direction
						if (direction != -1)
						{
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
				// If Die piece is a human piece check all possible moves
				// to either overtake the computer keypiece or the keyspace
				if (tempBoard[y][x].getPlayer() == "H")
				{
					// Check if the Computer Piece is the correct
					// number of spaces from the Human Key Piece
					if (boardObj->checkNumSpaces(x, y, endX, endY))
					{
						direction = getDirection(x, y, endX, endY);
						if (direction != -1)
						{
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

// Second Pass of AI
// Check if Human player can strike Computer KeyPiece
// Execute blocking 
bool Player::protectKeyPiece()
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	vector<int> KeyPieceLocation = getKeypieceLoc("H");
	int endX = KeyPieceLocation[0];
	int endY = KeyPieceLocation[1];
	int direction;

	for (int y = 0; y <= 7; y++)
	{
		for (int x = 0; x <= 8; x++)
		{
			// If Die piece is a human piece check all possible moves
			// that can overtake the computer keypiece or the keyspace
			if (tempBoard[y][x].getPlayer() == "H")
			{
				// Check if the Human Piece is the correct
				// number of spaces from the Computer Key Piece
				if (boardObj->checkNumSpaces(x, y, endX, endY))
				{
					// If check path is true, then Human has a winning move
					// Execute block and return true
					if (getPath(x, y, endX, endY, 0, false) || getPath(x, y, endX, endY, 2, false))
					{
						if (endY > y)
						{
							endY--;
							// For a forward or lateral->forward attack set --endY
							// So block manuever is executed one space below keypiece
							if (executeBlock(endX, endY))
							{
								return true;
							}
						}
						else if (endY < y)
						{
							endY++;
							if (executeBlock(endX, endY))
							{
								return true;
							}
						}

					}
					// For a forward->lateral attack
					// Check if Human will be attacking from left or right 
					// Execute Block on appropriate space
					else if (getPath(x, y, endX, endY, 1, false))
					{
						// Block Space to left of Keypiece
						if (endX > x)
						{
							--endX;
							if (executeBlock(endX, endY))
							{
								return true;
							}
						}
						else if (endX < x)
						{
							++endX;
							if (executeBlock(endX, endY))
							{
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

// TODO: Check against Keyspace
bool Player::executeBlock(int endX, int endY)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	int direction;

	// Coordinates (endX, endY) is the Computer Keypiece
	// To find a candidate to block from below
	// find a Computer piece that can move to endX--

	for (int y = 0; y <= 7; y++)
	{
		for (int x = 0; x <= 8; x++)
		{
			if (tempBoard[y][x].getPlayer() == "C")
			{
				if (boardObj->checkNumSpaces(x, y, endX, endY))
				{
					direction = getDirection(x, y, endX, endY);
					if (direction != 0)
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
	}

	// If there are no possible blocking moves return false
	return false;
}

bool Player::checkOvertake()
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	int direction;

	for (int y = 0; y <= 7; y++)
	{
		for (int x = 0; x <= 8; x++)
		{
			// If Die piece is a computer piece check all possible moves
			// to either overtake a Human Piece
			if (tempBoard[y][x].getPlayer() == "C")
			{
				for (int endY = 0; endY <= 7; endY++)
				{
					for (int endX = 0; endX <= 8; endX++)
					{
						if (tempBoard[endY][endX].getPlayer() == "H")
						{
							if (boardObj->checkNumSpaces(x, y, endX, endY))
							{
								direction = getDirection(x, y, endX, endY);
								if (direction != 0)
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
	}
	return false;
}

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
						if (boardObj->checkNumSpaces(x, y, endX, endY))
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





