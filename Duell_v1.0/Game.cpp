#include "Game.h"



Game::Game()
{
	humanObj = new Human();
	computerObj = new Computer();
	boardObj = new Board();
	boardViewObj = new boardView();
}


Game::~Game()
{
}

void Game::setBoard(Board * board)
{
	boardObj = board;
}

void Game::saveGame(string nextPlayer)
{
	vector<vector<Die>> tempBoard = boardObj->GetBoard();
	ofstream file;
	string fileName;

	cout << "Enter a file name" << endl;
	cin >> fileName;

	fileName = fileName + ".txt";
	file.open(fileName);
	file << "Board:\n";

	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < tempBoard[i].size(); j++)
		{
			if (tempBoard[i][j].isEmpty())
			{
				file << " 0  ";
			}
			else
			{
				file << tempBoard[i][j].displayDie() << " ";
			}
		}
		file << "\n";
	}

	file << "\n";
	file << "Computer Wins: " << computerObj->getWin() << "\n\n";
	file << "Human Wins: " << humanObj->getWin() << "\n\n";
	file << "Next Player: " << nextPlayer;

	file.close();
}

bool Game::savePrompt(string nextPlayer)
{
	char input;

	cout << "Would you like to save and exit the game?" << endl;
	cout << "Enter 'y' for yes or 'n' for no" << endl;
	cin >> input;
	tolower(input);

	if (input == 'y')
	{
		saveGame(nextPlayer);
		return true;
	}

	return false;
}

void Game::round()
{
	bool first = true;
	while (endGame == false)
	{
		if (first)
		{
			first = false;
			boardViewObj->ViewBoard(boardObj->GetBoard());
			humanObj->setBoard(boardObj);
			setBoard(humanObj->play());
			boardViewObj->ViewBoard(boardObj->GetBoard());
			if (savePrompt("Computer"))
			{
				break;
			}
			computerObj->setBoard(boardObj);
			setBoard(computerObj->play());
			continue;
		}
		boardViewObj->ViewBoard(boardObj->GetBoard());
		if (savePrompt("Human"))
		{
			break;
		}
		humanObj->setBoard(boardObj);
		setBoard(humanObj->play());
		if (humanObj->checkHumanWin())
		{
			cout << "You Win!" << endl;
			setEndGame();
			break;
		}
		boardViewObj->ViewBoard(boardObj->GetBoard());
		if (savePrompt("Computer"))
		{
			break;
		}
		computerObj->setBoard(boardObj);
		setBoard(computerObj->play());		
	}
}

void Game::startGame()
{
	// TODO: Add coin flip to see which player goes first
	bool first = true;
	while (!endGame)
	{
		round();
		setEndGame();
	}
}

void Game::setEndGame()
{
	endGame = true;
}


