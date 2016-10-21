#include "Tournament.h"
#include "stdafx.h"



Tournament::Tournament()
{
	gameObj = new Game();
	boardObj = new Board();

}

Tournament::~Tournament()
{
	delete gameObj;
	delete boardObj;
}

void Tournament::displayWinner()
{
	int computerWins = gameObj->getComputerWins();
	int humanWins = gameObj->getHumanWins();
	string winner;
	if (computerWins > humanWins)
	{
		winner = "*                        You lose...                        *";
	}
	else if (computerWins < humanWins)
	{
		winner = "*                         You win!!!                        *";
	}
	else
	{
		winner = "*                        It's a tie!                        *";
	}
	cout << "*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;
	cout << "*                   ~~ End of Tournament ~~                 *" << endl;
	cout << "*     The Computer finished with " << computerWins << " wins                     *" << endl;
	cout << "*     You finished with " << humanWins << " wins                              *" << endl;
	cout << "*                                                           *" << endl;
	cout << winner << endl;
	cout << "*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;




}
void Tournament::startTournament()
{
	// Get who's playing first
	string player = gameObj->firstPlayer();
	bool endGame = false;
	gameObj->setBoard(boardObj);

	while (!endGame)
	{
		gameObj->round(player);
		endGame = true;
	}

	if (playAgain())
	{
		setBoard();
		gameObj->setEndGame();
		gameObj->setBoard(boardObj);
		startTournament();
	}
	else
	{
		endGame = false;
	}

}

bool Tournament::playAgain()
{
	char input;
	do
	{
		cout << "****************************************************" << endl;
		cout << "*     Would you like to play another round?        *" << endl;
		cout << "*     Enter 'y' for yes or 'n' for no              *" << endl;
		cout << "****************************************************" << endl;
		cout << endl;
		cout << "     Selection: ";
		cin >> input;
		cout << endl;
		tolower(input);

		if (input == 'y')
		{
			return true;
		}
		else if (input == 'n')
		{
			displayWinner();
			return false;
		}
	} while (input != 'y');
}

void Tournament::loadGame()
{
	fstream file;
	string fileName, line, nextPlayer, computerWinsStr, humanWinsStr, tmp, player, topStr, rightStr;
	int topNum, rightNum, computerWins, humanWins;
	int iter = 0;
	vector<vector<string>> fileVec;
	vector<vector<Die>> gameBoard(8, vector <Die>(9));
	bool boardLoop = true;

	do
	{
		cout << "******************************************" << endl;
		cout << "*             ~~ Load Game ~~            *" << endl;
		cout << "*        Enter file name ex. game1       *" << endl;
		cout << "******************************************" << endl;
		cout << endl;
		cout << "     File name - ";
		cin >> fileName;
		fileName += ".txt";
		file.open(fileName);
	} while (!file.is_open());

	// Skip First line containing Board:
	getline(file, line);
	while (getline(file, line, '\n'))
	{
		int n = 0;
		istringstream iss(line);
		string item, temp;
		vector<string> row;

		if (fileVec.size() == 8)
		{
			boardLoop = false;
		}
		if (boardLoop == true)
		{
			while (iss >> item)
			{
				row.push_back(item);
			}
			fileVec.push_back(row);
		}
		if (boardLoop == false)
		{
			while (iss >> item)
			{
				if (item == "Computer")
				{
					if (iss >> temp >> item)
					{
						computerWinsStr = item;
					}
				}
				else if (item == "Human")
				{
					if (iss >> temp >> item)
					{
						humanWinsStr = item;
					}
				}
				else if (item == "Next")
				{
					if (iss >> temp >> item)
					{
						nextPlayer = item;
					}
				}
			}

		}


	}

	// Loop through the 2D vector containing the 
	// gameboard of strings
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < fileVec[i].size(); j++)
		{
			// Save the full string of the Die in Temp
			tmp = fileVec[i][j];
			// If the space contains a piece
			if (tmp != "0")
			{
				// Grab the player from the first character of the string
				player = tmp.substr(0, 1);
				// Grab the top number from the second character
				topStr = tmp.substr(1, 1);
				// Grab the right number from the third character
				rightStr = tmp.substr(2, 1);
				// Convert from string to int
				istringstream(topStr) >> topNum;
				istringstream(rightStr) >> rightNum;
				// Run die switch function to create the Die* to fill the board
				gameBoard[iter][j] = *boardObj->dieSwitch(topNum, rightNum, player);
			}
		}
		iter++;
	}

	// Convert the number of wins to an int and set appropriate variables
	istringstream(computerWinsStr) >> computerWins;
	istringstream(humanWinsStr) >> humanWins;
	boardObj->setBoard(gameBoard);
	gameObj->setBoard(boardObj);
	gameObj->setWinLoad(computerWins, humanWins);

	// Start the game
	startFromLoad(nextPlayer);

}

void Tournament::startFromLoad(string player)
{
	bool endGame = false;
	while (!endGame)
	{
		gameObj->round(player);
		endGame = true;
	}
	if (playAgain())
	{
		delete boardObj;
		setBoard();
		gameObj->setEndGame();
		gameObj->setBoard(boardObj);
		startTournament();
	}
	else
	{
		endGame = false;
	}
}

void Tournament::setBoard()
{
	Board * newBoard = new Board();
	boardObj = newBoard;
}
