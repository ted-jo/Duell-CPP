//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************

#include "stdafx.h"
#include "Player.h"
#pragma once

class Human : public Player
{
public:
	Human();
	~Human();
	// Mutator
	void setCoordinates(int, int, int, int, int);
	// Accessors
	int getStartXCoordinate() const { return startX; }
	int getStartYCoordinate() const { return startY; }

	void getCoordinates();
	Board * play();
private:
	int startX, startY, endX, endY, direction;
};

