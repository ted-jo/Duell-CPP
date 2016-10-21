#include "stdafx.h"
#include "Player.h"
#pragma once

class Human : public Player
{
public:
	Human();
	~Human();
	Board * play();
	void setCoordinates(int, int, int, int, int);
	void getCoordinates();
	int getStartXCoordinate() const { return startX; }
	int getStartYCoordinate() const { return startY; }
private:
	int startX, startY, endX, endY, direction;
};

