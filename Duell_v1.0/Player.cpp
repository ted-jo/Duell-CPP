#include "Player.h"




Player::~Player()
{
}

// Function checks to make sure coordinates are not out of bounds
bool Player::checkOOB(int x, int y)
{
	// Check if x or y coordinate is out of the 2D vector bounds on the upper end
	if (x > 9 || y > 8)
	{
		cout << endl << "Chosen Coordinates Out of Bounds" << endl;
		cout << "Please Choose again!" << endl;
		return false;
	}
	// Check if x or y is out of the 2D vector bounds on the low end
	else if (x < 1 || y < 1)
	{
		cout << endl << "Chosen Coordinates Out of Bounds" << endl;
		cout << "Please Choose again!" << endl;
		return false;
	}

	return true;
}
