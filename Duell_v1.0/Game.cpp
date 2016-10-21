#include "Game.h"



Game::Game()
{
	humanObj = new Human();
	computerObj = new Computer();
	boardObj = new Board();
	boardViewObj = new boardView();
	humanWin = 0;
	computerWin = 0;
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

void Game::loadGame()
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
		cout << "Enter file name ex. game1" << endl;
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
	setBoard(boardObj);
	setWinLoad(computerWins, humanWins);

	// Start the game
	round(nextPlayer);

}

/* *********************************************************************
Function Name: round
Purpose: To execute a single round of play
Parameters:
player, a string. It refers to the player who goes first
Return Value: void
Local Variables:
first, a bool that flips after first execution of loop since the first round 
has a different order of steps
Algorithm:
1) Loop through steps while private endGame variable is false
2) Display Gameboard
3) Set the board object in the player class
4) Execute move in Player function
5) Set board object in Game Class
6) Check the board to see if player has won. If true, set endgame to true and break 
7) Display board
8) Ask user to save
9) Repeat steps for next player
10) Return to top of loop
Assistance Received: none
********************************************************************* */
void Game::round(string player)
{
	// Bool flips after first loop
	// Used to not prompt for save 
	// Before any player goes
	bool first = true;

	// Continue executing rounds until
	// the endGame bool is flipped
	while (endGame == false)
	{
		// If the human player goes first execute in this order
		if (player == "Human")
		{
			// Don't ask to save on the first iteration of loop
			if (first)
			{
				first = false;

				// Display the untouched board
				boardViewObj->ViewBoard(boardObj->GetBoard());
				// Set the board variable in the player class
				// So the player has access to it
				humanObj->setBoard(boardObj);
				// Execute a human move
				// Set the master board object of the Game class
				setBoard(humanObj->play());
				// Display the board after first move
				boardViewObj->ViewBoard(boardObj->GetBoard());
				// Ask user to Save game passing the next player
				if (savePrompt("Computer"))
				{
					break;
				}
				// Set the changed board to the Player class
				computerObj->setBoard(boardObj);
				// Execute a Computer move
				// Set the master board object of the Game class
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
			if (setWin("H"))
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
		else
		{
			// Don't ask to save on the first iteration of loop
			if (first)
			{
				first = false;
				// Display first instance of gameboard
				boardViewObj->ViewBoard(boardObj->GetBoard());
				computerObj->setBoard(boardObj);
				setBoard(computerObj->play());
				boardViewObj->ViewBoard(boardObj->GetBoard());
				if (savePrompt("Human"))
				{
					break;
				}
				humanObj->setBoard(boardObj);
				setBoard(humanObj->play());
				continue;
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
				cout << "Computer Wins!" << endl;
				setEndGame();
				break;
			}
			boardViewObj->ViewBoard(boardObj->GetBoard());
			if (savePrompt("Human"))
			{
				break;
			}
			humanObj->setBoard(boardObj);
			setBoard(humanObj->play());
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

void Game::setEndGame()
{
	endGame = true;
}


