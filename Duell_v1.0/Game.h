#include "stdafx.h"
#include "Board.h"
#include "boardView.h"
#pragma once

class Game
{
public:
	Game();
	~Game();
private:
	Board boardObj;
	boardView boardViewObj;
};

