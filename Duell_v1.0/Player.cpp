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
	else if (!boardObj->checkPath(startX, startY, endX, endY, direction))
	{
		cout << "*****************************************************" << endl;
		cout << "*  Error: Path is Blocked                           *" << endl;
		cout << "*  Please Select New Coordinates                    *" << endl;
		cout << "*****************************************************" << endl;

		validation = false;
	}


	return validation;
}

void Player::executeMove(int startX, int startY, int endX, int endY, int direction, string player)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();

	if (player == "H")
	{
		// No Lateral Movement
		if (direction == 0)
		{
			for (startY; startY < endY; startY++)
			{
				int tempY = endY;
				if (startY == --tempY && tempBoard[endY][endX].getPlayer() == "C")
				{
					boardObj->overtakePiece(endX, endY);
				}

				boardObj->movePieceUp(startX, startY);
			}
		}
		// First movement forward
		else if (direction == 1)
		{
			// Move forward until the end Y location
			for (startY; startY < endY; startY++)
			{
				boardObj->movePieceUp(startX, startY);
			}
			// Move Lateral to the end X location
			// If start X > end X -> move left
			if (startX > endX)
			{
				for (startX; startX > endX; startX--)
				{
					int tempX = endX;
					if (startY == ++tempX && tempBoard[endY][endX].getPlayer() == "C")
					{
						boardObj->overtakePiece(endX, endY);
					}

					boardObj->movePieceLeft(startX, endY);
				}
			}
			else
			{
				for (startX; startX < endX; startX++)
				{
					int tempX = endX;
					if (startY == --tempX && tempBoard[endY][endX].getPlayer() == "C")
					{
						boardObj->overtakePiece(endX, endY);
					}

					boardObj->movePieceRight(startX, startY);
				}
			}
		}
		// First Movement Lateral
		else if(direction == 2)
		{
			// Move Lateral to the end X location
			// If start X > end X -> move left
			if (startX > endX)
			{
				for (startX; startX > endX; startX--)
				{
					boardObj->movePieceLeft(startX, endY);
				}
			}
			else
			{
				for (startX; startX < endX; startX++)
				{
					boardObj->movePieceRight(startX, startY);
				}
			}

			// Move forward until the end Y location
			for (startY; startY < endY; startY++)
			{
				int tempY = endY;
				if (startY == --tempY && tempBoard[endY][endX].getPlayer() == "C")
				{
					boardObj->overtakePiece(endX, endY);
				}

				boardObj->movePieceUp(startX, startY);
			}
		}
	}
	// Execute Computer Move
	else
	{
		// No Lateral Movement
		if (direction == 0)
		{
			for (startY; startY > endY; startY--)
			{
				int tempY = endY;
				if (startY == ++tempY && tempBoard[endY][endX].getPlayer() == "H")
				{
					boardObj->overtakePiece(endX, endY);
				}

				boardObj->movePieceDown(startX, startY);
			}
		}
		// First movement forward
		else if (direction == 1)
		{
			// Move forward until the end Y location
			for (startY; startY > endY; startY--)
			{
				boardObj->movePieceUp(startX, startY);
			}
			// Move Lateral to the end X location
			// If start X > end X -> move left
			if (startX > endX)
			{
				for (startX; startX > endX; startX--)
				{
					int tempX = endX;
					if (startY == ++tempX && tempBoard[endY][endX].getPlayer() == "H")
					{
						boardObj->overtakePiece(endX, endY);
					}

					boardObj->movePieceLeft(startX, endY);
				}
			}
			else
			{
				for (startX; startX < endX; startX++)
				{
					int tempX = endX;
					if (startY == --tempX && tempBoard[endY][endX].getPlayer() == "H")
					{
						boardObj->overtakePiece(endX, endY);
					}

					boardObj->movePieceRight(startX, startY);
				}
			}
		}
		// First Movement Lateral
		else if (direction == 2)
		{
			// Move Lateral to the end X location
			// If start X > end X -> move left
			if (startX > endX)
			{
				for (startX; startX > endX; startX--)
				{
					boardObj->movePieceLeft(startX, endY);
				}
			}
			else
			{
				for (startX; startX < endX; startX++)
				{
					boardObj->movePieceRight(startX, startY);
				}
			}

			// Move forward until the end Y location
			for (startY; startY > endY; startY--)
			{
				int tempY = endY;
				if (startY == ++tempY && tempBoard[endY][endX].getPlayer() == "H")
				{
					boardObj->overtakePiece(endX, endY);
				}

				boardObj->movePieceDown(startX, startY);
			}
		}
	}
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

// TODO: check against key space
bool Player::keyPieceAttack(string player)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	vector<int> KeyPieceLocation = getKeypieceLoc(player);
	int endX = KeyPieceLocation[0];
	int endY = KeyPieceLocation[1];

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
					if (boardObj->checkNumSpaces(x, y, endX, endY) == true)
					{
						if (boardObj->checkPath(x, y, endX, endY, 0) == true)
						{
							executeMove(x, y, endX, endY, 0, "C");
							return true;
						}
						else if (boardObj->checkPath(x, y, endX, endY, 1) == true)
						{
							executeMove(x, y, endX, endY, 1, "C");
							return true;
						}
						else if (boardObj->checkPath(x, y, endX, endY, 2) == true)
						{
							executeMove(x, y, endX, endY, 2, "C");
							return true;
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
					if (boardObj->checkNumSpaces(x, y, endX, endY) == true)
					{
						if (boardObj->checkPath(x, y, endX, endY, 0) == true)
						{
							return true;
						}
						else if (boardObj->checkPath(x, y, endX, endY, 1) == true)
						{
							return true;
						}
						else if (boardObj->checkPath(x, y, endX, endY, 2) == true)
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
	vector<int> KeyPieceLocation = getKeypieceLoc("C");
	int endX = KeyPieceLocation[0];
	int endY = KeyPieceLocation[1];

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
				if (boardObj->checkNumSpaces(x, y, endX, endY) == true)
				{
					// If check path is true, then Human has a winning move
					// Execute block and return true
					if (boardObj->checkPath(x, y, endX, endY, 0) || boardObj->checkPath(x, y, endX, endY, 2))
					{
						// For a forward or lateral->forward attack set --endY
						// So block manuever is executed one space below keypiece
						if (executeBlock(endX, --endY))
						{
							return true;
						}
					}
					// For a forward->lateral attack
					// Check if Human will be attacking from left or right 
					// Execute Block on appropriate space
					else if (boardObj->checkPath(x, y, endX, endY, 1) == true)
					{
						// Block Space to left of Keypiece
						if (endX > x)
						{
							--endX;
							if (checkOOB(endX, endY))
							{
								if (executeBlock(endX, endY))
								{
									return true;
								}
							}
						}
						else
						{
							++endX;
							if (checkOOB(endX, endY))
							{
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
	}

	return false;
}

// TODO: Check against Keyspace
bool Player::executeBlock(int endX, int endY)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();

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
					if (boardObj->checkPath(x, y, endX, endY, 0) == true)
					{
						executeMove(x, y, endX, endY, 0, "C");
						return true;
					}
					else if (boardObj->checkPath(x, y, endX, endY, 1) == true)
					{
						executeMove(x, y, endX, endY, 1, "C");
						return true;
					}
					else if (boardObj->checkPath(x, y, endX, endY, 2) == true)
					{
						executeMove(x, y, endX, endY, 2, "C");
						return true;
					}
				}
			}
		}
	}

	// If there are no possible blocking moves return false
	return false;
}

void Player::findBestMove()
{
	vector<int> location;
	vector<int> tempLocation;
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	vector<int> KeyPieceLocation = getKeypieceLoc("C");
	int endX = KeyPieceLocation[0];
	int endY = KeyPieceLocation[1];
	int startX = 0;
	int startY = 0;
	int score = 100;
	int direction;

	for (int y = 0; y <= 7; y++)
	{
		for (int x = 0; x <= 8; x++)
		{
			if (tempBoard[y][x].getPlayer() == "C")
			{
				location = checkBestMove(x, y);
				if (location[0] < score)
				{
					score = location[0];
					startX = x;
					startY = y;
					tempLocation = location;
				}
			}
		}
	}

	endX = tempLocation[1];
	endY = tempLocation[2];
	direction = executeClosestMove(startX, startY, endX, endY);

	int displayX = startX;
	int displayY = startY;

	cout << "The Computer has Picked " << tempBoard[startY][startX].displayDie() << " at (" << ++displayX << "," << ++displayY << ") to roll because this Die can move closest to the Human KeyPiece" << endl;

	// Find type of roll and number of spaces for display
	if (direction == 0)
	{
		int numSpacesY = abs(startY - endY);
		cout << "It rolled " << numSpacesY << " frontally because it was the most direct clear path" << endl;
	}
	else if (direction == 1)
	{
		int numSpacesY = abs(startY - endY);
		int numSpacesX = abs(startX - endX);
		cout << "It rolled " << numSpacesY << " frontally and " << numSpacesX << " laterally because a frontal move was blocked" << endl;
	}
	else if (direction == 2)
	{
		int numSpacesY = abs(startY - endY);
		int numSpacesX = abs(startX - endX);
		cout << "It rolled " << numSpacesX << " laterally and " << numSpacesY << " frontally because a straight frontal and frontal -> lateral move were blocked" << endl;
	}

}

vector<int> Player::checkBestMove(int startX, int startY)
{
	vector<int> location;
	vector<int> KeyPieceLocation = getKeypieceLoc("C");
	int endX = KeyPieceLocation[0];
	int endY = KeyPieceLocation[1];
	int tempScore;

	for (int y = 0; y <= 7; y++)
	{
		for (int x = 0; x <= 8; x++)
		{
			if (boardObj->checkNumSpaces(startX, startY, x, y))
			{
				tempScore = (abs(x - endX) + abs(y - endY));
				location.push_back(tempScore);
				location.push_back(x);
				location.push_back(y);				
			}
		}
	}
	//cout << endl;
	//cout << "Temp Score: " << score << endl;
	//cout << "Computer has chosen " << ++startX << " " << ++startY << endl;
	//cout << "To space " << ++tempX << " " << ++tempY << endl;

	return location;
}

int Player::executeClosestMove(int startX, int startY, int endX, int endY)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	string player = tempBoard[startY][startX].getPlayer();

	if (boardObj->checkPath(startX, startY, endX, endY, 0))
	{
		executeMove(startX, startY, endX, endY, 0, player);
		return 0;
	}
	else if (boardObj->checkPath(startX, startY, endX, endY, 1))
	{
		executeMove(startX, startY, endX, endY, 1, player);
		return 1;
	}
	else if (boardObj->checkPath(startX, startY, endX, endY, 2))
	{
		executeMove(startX, startY, endX, endY, 2, player);
		return 2;
	}

	return -1;
}




