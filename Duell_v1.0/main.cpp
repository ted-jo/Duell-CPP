//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************


#include "stdafx.h"     // Contains the pre-compiled headers.
#include "Game.h"
#include "Tournament.h"
#include <stdio.h>

/* *********************************************************************
Function Name: main
Purpose: Start the program and ask user for start option
Parameters: None
Algorithm:
1) Ask user to select game start option
2) Create a tournament object and start the game
Assistance Received: none
********************************************************************* */
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
		cout << "          |     1. Start a New Tournament                   |" << endl;
		cout << "          |     2. Load a Saved Game                        |" << endl;
		cout << "          |     3. Quit                                     |" << endl;
		cout << "          +=================================================+" << endl;
		cout << endl;
		cout << "           Selection: ";
		cin >> choice;
		cout << endl << endl << endl << endl;

		switch (choice)
		{
		case '1' :
		{
			// Start a new Tournament
			Tournament * tournament = new Tournament();
			tournament->startTournament();
			break;
		}
		case '2' :
		{
			// Load a Saved Game
			Tournament * tournament = new Tournament();
			tournament->loadGame();
			break;
		}
		case '3' :
		{
			// Quit Game
			break;
		}
		default :
			// Return to top of loop on invalid input
			cout << "Incorrect input!" << endl;
			cout << "Please try again" << endl << endl;
			break;
		}
	} while (choice != '3');


	cout << endl;
	system("PAUSE");
	return 0;
}