#include "Game.h"



Game::Game()
{
	humanObj = new Human();
	computerObj = new Computer();
	boardViewObj = new boardView();
	humanWin = 0;
	computerWin = 0;
}


Game::~Game()
{
	delete humanObj;
	delete computerObj;
	delete boardObj;
	delete boardViewObj;
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
		for (int j = 0; j < 8; j++)
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
	file << "Computer Wins: " << getComputerWins() << "\n\n";
	file << "Human Wins: " << getHumanWins() << "\n\n";
	file << "Next Player: " << nextPlayer;

	file.close();
}

bool Game::savePrompt(string nextPlayer)
{
	char input;

	do
	{
		cout << "****************************************************" << endl;
		cout << "*              ~~ Save & Exit? ~~                  *" << endl;
		cout << "*     Would you like to save and exit the game?    *" << endl;
		cout << "*     Enter 'y' for yes or 'n' for no              *" << endl;
		cout << "****************************************************" << endl;
		cout << endl;
		cout << "     Selection: ";
		cin >> input;
		cout << endl;
		tolower(input);

		if (input == 'y')
		{
			saveGame(nextPlayer);
			return true;
		}
		else if (input == 'n')
		{
			return false;
		}		
	} while (input != 'y' && input != 'n');

}



/* *********************************************************************
Function Name: round
Purpose: To execute a single round of play
Parameters:
player, a string. It refers to the player who goes first
Return Value: void
Local Variables:
Algorithm:
1) Loop through steps while private endGame variable is false
2) Display Gameboard
3) Set the board object in the player class
4) Ask if user needs help
5) Execute move in Player function
6) Set board object in Game Class
7) Check the board to see if player has won. If true, set endgame to true and break 
8) Display board
9) Ask user to save
10) Repeat steps for next player
11) Return to top of loop
Assistance Received: none
********************************************************************* */
void Game::round(string player)
{


	// Continue executing rounds until
	// the endGame bool is flipped
	while (endGame == false)
	{
		// If the human player goes first execute in this order
		if (player == "Human")
		{
			boardViewObj->ViewBoard(boardObj->GetBoard());
			if (savePrompt("Human"))
			{
				break;
			}
			humanObj->setBoard(boardObj);
			askHelp();
			setBoard(humanObj->play());
			if (setWin("H"))
			{
				boardViewObj->ViewBoard(boardObj->GetBoard());
				cout << endl << endl;
				cout << "*****************************************" << endl;
				cout << "*             You Win!                  *" << endl;
				cout << "*       Congrats, want a medal?         *" << endl;
				cout << "*****************************************" << endl;
				cout << endl;
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
			if (setWin("C"))
			{
				boardViewObj->ViewBoard(boardObj->GetBoard());
				cout << endl << endl;
				cout << "*****************************************" << endl;
				cout << "*               You lose...             *" << endl;
				cout << "*     Don't worry we won't tell anyone  *" << endl;
				cout << "*****************************************" << endl;
				cout << endl;
				setEndGame();
				break;
			}
		}
		// If the computer player goes first execute in this order
		else
		{
			boardViewObj->ViewBoard(boardObj->GetBoard());
			if (savePrompt("Computer"))
			{
				break;
			}
			computerObj->setBoard(boardObj);
			setBoard(computerObj->play());
			if (setWin("C"))
			{
				boardViewObj->ViewBoard(boardObj->GetBoard());
				cout << endl << endl;
				cout << "*****************************************" << endl;
				cout << "*        Well that's embarassing        *" << endl;
				cout << "*               You lose...             *" << endl;
				cout << "*****************************************" << endl;
				cout << endl;
				setEndGame();
				break;
			}
			boardViewObj->ViewBoard(boardObj->GetBoard());
			if (savePrompt("Human"))
			{
				break;
			}
			humanObj->setBoard(boardObj);
			askHelp();
			setBoard(humanObj->play());
			if (setWin("H"))
			{
				boardViewObj->ViewBoard(boardObj->GetBoard());
				cout << endl << endl;
				cout << "*****************************************" << endl;
				cout << "*             You Win!                  *" << endl;
				cout << "*   You haven't seen the last of me     *" << endl;
				cout << "*****************************************" << endl;
				cout << endl;
				setEndGame();
				break;
			}
		}

	}
}

void Game::startGame()
{
	// Get who's playing first
	string player = firstPlayer();
	while (!endGame)
	{
		round(player);
		setEndGame();
	}
}

/* *********************************************************************
Function Name: firstPlayer
Purpose: To randomly select first player 
Parameters:
Return Value: The player who will go first
Local Variables:
human, an int that will contain the random number for the human
computer, an int that will contain the random number for the computer
player, a string containing the player who will go first
Algorithm:
1) Seed the random function with the current time
2) Start loop which continues if there is a tie
3) Randomly select a number 1-6 for human
4) Randomly select a number 1-6 for computer
5) Compare the two numbers and return the player with highest value
Assistance Received: none
********************************************************************* */
string Game::firstPlayer()
{
	int human, computer;
	string player;
	// Seed rand() with the current time
	srand(time(NULL));

	do
	{

		// Select a random number between 1-6 whoever has the higher number goes first
		human = (rand() % 6 + 1);
		computer = (rand() % 6 + 1);
		cout << "          +=================================================+" << endl;
		cout << "          |        Roll a die to see who goes first!        |" << endl;
		cout << "          |                                                 |" << endl;
		cout << "          |        You rolled a " << human <<"                           |" << endl;
		cout << "          |        Computer rolled a " << computer <<"                      |" << endl;
		cout << "          |                                                 |" << endl;
		if (human > computer)
		{
			cout << "          |        You go first!                            |" << endl;
			cout << "          +=================================================+" << endl;
			player = "Human";
			return player;
		}

		if (computer > human)
		{
			cout << "          |        Computer goes first                      |" << endl;
			cout << "          +=================================================+" << endl;
			player = "Computer";
			return player;
		}
		if (computer == human)
		{
			cout << "          |        It's a tie!                              |" << endl;
			cout << "          |        Roll again...                            |" << endl;
			cout << "          +=================================================+" << endl;
		}

	} while (human == computer);
}

void Game::setWinLoad(int computerWins, int humanWins)
{
	computerWin = computerWins;
	humanWin = humanWins;
}

bool Game::setWin(string player)
{
	if (player == "H")
	{
		if (humanObj->checkHumanWin())
		{
			humanWin++;
			return true;
		}
	}
	else
	{
		if (computerObj->checkComputerWin())
		{
			computerWin++;
			return true;
		}
	}

	return false;
}

void Game::askHelp()
{
	char input;
	do
	{
		cout << "****************************************************" << endl;
		cout << "*                 ~~ Help? ~~                      *" << endl;
		cout << "*     Would you like some help?                    *" << endl;
		cout << "*     Enter 'y' for yes or 'n' for no              *" << endl;
		cout << "****************************************************" << endl;
		cout << endl;
		cout << "     Selection: ";
		cin >> input;
		cout << endl;
		tolower(input);

		if (input == 'y')
		{
			humanObj->help();
		}
		else if (input == 'n')
		{
			break;
		}
	} while (input != 'y');
}

void Game::setEndGame()
{
	if (endGame = false)
	{
		endGame = true;
	}
	else
	{
		endGame = false;
	}
	
}


