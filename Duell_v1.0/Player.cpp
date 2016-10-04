#include "Player.h"




Player::Player()
{
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
	// TODO: Add Computer Move
	if (player == "H")
	{
		// No Lateral Movement
		if (direction == 0)
		{
			for (startY; startY < endY; startY++)
			{
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
				boardObj->movePieceUp(startX, startY);
			}
		}
	}

}

vector<int> Player::getHumanKeypieceLoc()
{
	vector<int> location;
	vector<vector<Die>> tempBoard = boardObj->GetBoard();

	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < tempBoard[i].size(); j++)
		{
			// If Die piece is a Human keypiece add coordinates
			// to to vector and return
			if (tempBoard[i][j].getPlayer() == "H" && tempBoard[i][j].getKeyPiece() == true)
			{
				location.push_back(j);
				location.push_back(i);
			}
		}
	}

	return location;
}

bool Player::checkHumanAttack()
{
	return false;
}

bool Player::keyPieceAttack()
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	vector<int> HumanKeyPieceLocation = getHumanKeypieceLoc();
	int endX = HumanKeyPieceLocation[0];
	int endY = HumanKeyPieceLocation[1];

	for (int y = 0; y <= 7; y++)
	{
		for (int x = 0; x <= 8; x++)
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
	}

	return false;
}

// Second Pass of AI
// Check if Human player can strike Computer KeyPiece
// Execute blocking 
bool Player::protectKeyPiece()
{
	return false;
}



