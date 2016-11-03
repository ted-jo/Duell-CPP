//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************

#include "Tournament.h"
#include "stdafx.h"


/* *********************************************************************
Function Name: Tournament
Purpose: Construct Tournament Object
Algorithm:
1) Create new game object
2) Create new board object
Assistance Received: none
********************************************************************* */
Tournament::Tournament()
{
	gameObj = new Game();
	boardObj = new Board();

}

/* *********************************************************************
Function Name: ~Tournament
Purpose: destruct Tournament Object
Algorithm:
1) delete game object
2) delete board object
Assistance Received: none
********************************************************************* */
Tournament::~Tournament()
{
	delete gameObj;
	delete boardObj;
}

/* *********************************************************************
Function Name: displayWinner
Purpose: Display the winner of the tournament
Parameters: None
Return Value: void
Local Variables:
	computerWins, an int containing the total number of computer wins
	humanWins, an int containing the total number of human wins
	winner, string containing the winner message
Algorithm:
1) Check if computerWins > humanWins or vice versa
2)	Set appropriate winner string
3) Display the total number of wins each and the winner string
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: startTournament
Purpose: Start a round of the tournament
Parameters: None
Return Value: void
Local Variables:
	player, string containing the player who goes first
	endGame, bool flipped at end of game to break from loop
Algorithm:
1) Run firstPlayer function to get player who goes first
2) Set the boardObj to the game class
3) Loop until endGame is true
4)		execute a round in the player class
5) At end of round, ask player if they would like to play again
6) Reset the board
7) Recursively run startTournament again
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: playAgain
Purpose: Ask the player if they would like to play again, if not display winner
Parameters: None
Return Value: return true to start another game
Assistance Received: none
********************************************************************* */
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


/* *********************************************************************
Function Name: loadGame
Purpose: Load a game from a save file
Parameters: None
Return Value: void
Local Variables:
	file, fstream object which contains the loaded file
	fileVec, 2D vector of strings which holds all the loaded gameboard in string form
	gameBoard, 2D vector of die which holds all the loaded gameboard in die form
	nextPlayer, string holding next player from the file
	fileName, string containing the file name to open
	iss, istringstream to parse out the file
Algorithm:
1) Get Filename
2) Open File
3) Loop until end of file
4) Using istringstream push each position on the board to the fileVec
5) When the board is complete get the number of wins and the next player
6) Loop through the fileVec parsing out the die
7) Using that data calculate all sides and create a new die
8) Push that to the correct position on the gameboard
9) Set the board in the game class
10) Call startFromLoad
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: startFromLoad
Purpose: Start the round from a loaded state
Parameters:
	player, string containing the player who goes first
Return Value: void
Local Variables: None
Algorithm:
1) Set the boardObj to the game class
2) Loop until endGame is true
3)		execute a round in the player class with the given nextPlayer
4) At end of round, ask player if they would like to play again
5) Reset the board
6) Recursively run startTournament again
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: setBoard
Purpose: Create a new board obj and set for new game
Return Value: void
Assistance Received: none
********************************************************************* */
void Tournament::setBoard()
{
	Board * newBoard = new Board();
	boardObj = newBoard;
}
