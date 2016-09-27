#include "stdafx.h"
#include "Player.h"
#pragma once

class Human : public Player
{
public:
	Human();
	~Human();
	void play();
	void setCoordinates(int, int, int, int, char);
	void getCoordinates();
	int getStartXCoordinate() { return startX; }
	int getStartYCoordinate() { return startY; }
private:
	int startX, startY, endX, endY;
	char direction;
};

