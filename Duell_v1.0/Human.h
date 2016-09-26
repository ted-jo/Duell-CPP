#include "stdafx.h"
#include "Player.h"
#pragma once

class Human : public Player
{
public:
	Human();
	~Human();
	void setCoordinates(int, int);
	void getCoordinates();
	int getXCoordinate() { return xCoord; }
	int getYCoordinate() { return yCoord; }
private:
	int xCoord;
	int yCoord;
};

