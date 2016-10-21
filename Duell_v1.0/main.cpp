/*
* Driver for the game
*/
#include "stdafx.h"     // Contains the pre-compiled headers.
#include "Game.h"
#include "Tournament.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
	// Switch Statement Choice
	char choice;

	cout << " +********************************************************************************************************+ " << endl;
	cout << " |  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.   " << " |" << endl;
	cout << " |  | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. | " << " |" << endl;
	cout << " |  | |  ________    | || | _____  _____ | || |  _________   | || |   _____      | || |   _____      | | " << " |" << endl;
	cout << " |  | | |_   ___ `.  | || ||_   _||_   _|| || | |_   ___  |  | || |  |_   _|     | || |  |_   _|     | | " << " |" << endl;
	cout << " |  | |   | |   `. \\ | || |  | |    | |  | || |   | |_  \\_|  | || |    | |       | || |    | |       | | " << " |" << endl;
	cout << " |  | |   | |    | | | || |  | '    ' |  | || |   |  _|  _   | || |    | |   _   | || |    | |   _   | | " << " |" << endl;
	cout << " |  | |  _| |___.' / | || |   \\ `--' /   | || |  _| |___/ |  | || |   _| |__/ |  | || |   _| |__/ |  | | " << " |" << endl;
	cout << " |  | | |________.'  | || |    `.__.'    | || | |_________|  | || |  |________|  | || |  |________|  | | " << " |" << endl;
	cout << " |  | |              | || |              | || |              | || |              | || |              | | " << " |" << endl;
	cout << " |  | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' | " << " |" << endl;
	cout << " |  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' " << "   |" << endl;
	cout << " |                                                                                                        |" << endl;
	cout << " |       Author: Ted Johansmeyer                                                                          |" << endl;
	cout << " |       Project: C++ Duell                                                                               |" << endl;
	cout << " |       Class: CMPS 366 Organization of Programming Languages                                            |" << endl;
	cout << " |       Date: October 21st 2016                                                                          |" << endl;
	cout << " |                                                                                                        |" << endl;
	cout << " +********************************************************************************************************+ " << endl;
	cout << endl;
	do 
	{
		cout << "          +=================================================+" << endl;
		cout << "          |                Welcome to Duell!                |" << endl;
		cout << "          |             Please Select an Option             |" << endl;
		cout << "          |                                                 |" << endl;
		cout << "          |     1. Start a New Game                         |" << endl;
		cout << "          |     2. Start a New Tournament                   |" << endl;
		cout << "          |     3. Load a Saved Game                        |" << endl;
		cout << "          |     4. Quit                                     |" << endl;
		cout << "          +=================================================+" << endl;
		cout << endl;
		cout << "           Selection: ";
		cin >> choice;
		cout << endl << endl << endl << endl;

		switch (choice)
		{
		case '1' :
		{
			// Start a new game
			Game * game = new Game();
			game->startGame();
			break;
		}
		case '2' :
		{
			// Start a new Tournament
			Tournament * tournament = new Tournament();
			tournament->startTournament();
			break;
		}
		case '3' :
		{
			// Load a Saved Game
			Game * game = new Game();
			game->loadGame();
			break;
		}
		case '4' :
			// Quit Game
			break;
		default :
			// Return to top of loop on invalid input
			cout << "Incorrect input!" << endl;
			cout << "Please try again" << endl << endl;
			break;
		}
	} while (choice != '4');


	cout << endl;
	system("PAUSE");
	return 0;
}