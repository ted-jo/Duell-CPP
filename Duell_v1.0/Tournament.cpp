#include "Tournament.h"
#include "stdafx.h"



Tournament::Tournament()
{
	gameObj = new Game();
	//computerWins = 0;
	//humanWins = 0;
}


//void Tournament::setComputerWins(int computerScore)
//{
//	computerWins = computerScore;
//}
//
//void Tournament::setHumanWins(int humanScore)
//{
//	humanWins = humanScore;
//
//}

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
	cout << "*                      End of Tournament                    *" << endl;
	cout << "*     The Computer finished with " << computerWins << " wins      *" << endl;
	cout << "*     You finished with " << humanWins << " wins                      *" << endl;
	cout << "*                                                           *" << endl;
	cout << winner << endl;
	cout << "*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;




}
void Tournament::startTournament()
{
	// Get who's playing first
	string player = gameObj->firstPlayer();
	bool endGame = false;
	while (!endGame)
	{
		gameObj->round(player);
		endGame = true;
	}
	if (playAgain())
	{
		startTournament();
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
		}
	} while (input != 'y');
}

