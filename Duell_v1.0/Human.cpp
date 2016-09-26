#include "Human.h"
#include "Game.h"



Human::Human()
{
}


Human::~Human()
{
}

void Human::setCoordinates(int x, int y)
{
	xCoord = x;
	yCoord = y;
}

void Human::getCoordinates()
{
	int x, y;

	cout << "Choose X Coordinate of Die to move: ";
	cin >> x;
	cout << "Choose Y Coordinate of Die to move: ";
	cin >> y;

	setCoordinates(x, y);
	
}
