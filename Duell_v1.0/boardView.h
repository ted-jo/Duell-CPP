//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************

#pragma once
#include "Board.h"

class boardView
{
public:
	boardView();
	~boardView();
	void ViewBoard(vector <vector<Die> > & gameboard);
};

