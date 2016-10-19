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

void Game::loadGame()
{
	fstream file;
	string fileName, line, nextPlayer, computerWins, humanWins;;
	vector<vector<string>> fileVec;
	vector<vector<Die>> gameBoard;
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
						computerWins = item;
					}
				}
				else if (item == "Human")
				{
					if (iss >> temp >> item)
					{
						humanWins = item;
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

	cout << computerWins << endl;
	cout << humanWins << endl;
	cout << nextPlayer << endl;

}


void Game::round(string player)
{
	bool first = true;
	while (endGame == false)
	{
		// If the human player goes first execute in this order
		if (player == "Human")
		{
			// Don't ask to save on the first iteration of loop
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
		else
		{
			// Don't ask to save on the first iteration of loop
			if (first)
			{
				first = false;
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
			if (computerObj->checkComputerWin())
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

void Game::setEndGame()
{
	endGame = true;
}


