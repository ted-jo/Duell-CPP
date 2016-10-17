#include "stdafx.h"
#include "Player.h"
#pragma once
class Computer : public Player
{
public:
	Computer();
	~Computer();
	Board * play();
	int getWin() { return computerWin; }
};

