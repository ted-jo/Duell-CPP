//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************

#include "stdafx.h"
#include "Player.h"
#pragma once
class Computer : public Player
{
public:
	Computer();
	~Computer();
	Board * play();
};

