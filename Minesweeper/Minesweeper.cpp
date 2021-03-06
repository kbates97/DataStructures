// Minesweeper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Minesweeper.h"

int main()
{
	Minesweeper newGame;
	newGame.PlayGame();
	newGame.EndSequence();
}

Minesweeper::Minesweeper()
{
	cout << "Select a difficulty: 1 = easy, 2 = intermediate, 3 = expert: " << endl;
	int difficulty;
	cin >> difficulty;
	board_.SetDifficulty(difficulty);
	switch (difficulty)
	{
	case 1:
		cout << "You chose Easy: 10x10, 10 bombs." << endl;
		break;
	case 2:
		cout << "You chose Intermediate: 16x16, 40 bombs" << endl;
		break;
	case 3:
		cout << "You chose Expert: 16x30, 100 bombs." << endl;
		break;
	default:
		cout << "Invalid Input. Defaulting to Easy." << endl;
		break;
	}
}

Minesweeper::Minesweeper(size_t difficulty)
{
	board_.SetDifficulty(difficulty);
	switch (difficulty)
	{
	default:
		cout << "Board set with Easy difficulty: 10x10, 10 bombs." << endl;
		break;
	case 1:
		cout << "Board set with Easy difficulty: 10x10, 10 bombs." << endl;
		break;
	case 2:
		cout << "Board set with Intermediate difficulty: 16x16, 40 bombs." << endl;
		break;
	case 3:
		cout << "Board set with Expert difficulty: 16x30, 100 bombs." << endl;
		break;
	}
}

void Minesweeper::PlayGame()
{
	int row, col;
	char selectOrMark;
	board_.PrintBoard(); 
	while (done_ == false)
	{
		cout << "Enter Coordinates(Row Col): ";
		cin >> row >> col;
		cout << "Do you want to select or mark(s = select/m = mark)? ";
		cin >> selectOrMark;
		if (selectOrMark == 'm' || selectOrMark == 'M')
		{
			board_.Mark(row, col);
		}
		else if (selectOrMark == 's' || selectOrMark == 'S' || selectOrMark == 'x' || selectOrMark == 'X')
		{
			if (board_.Select(row, col) == 'B')
			{
				done_ = true;
				win_ = false;
			}
		}
		else if (selectOrMark == '*')
			Settings();
		else
			cout << "Not a valid input." << endl;
		if (board_.AllBombsMarked())
		{
			done_ = true;
			win_ = true;
		}
		board_.PrintBoard();
	}
}

void Minesweeper::EndSequence()
{
	if (win_)
		cout << "You won!" << endl;
	else
		cout << "Dead!" << endl;
}

void Minesweeper::Settings()
{
	cout << endl << "Settings" << endl;
	cout << "Change Difficulty = c, Reset Game = r, Cancel = x: ";
	char choice;
	int difficulty;
	cin >> choice;
	switch (choice)
	{
	default:
		break;
	case 'c':
		cout << "Select Difficulty(1 = Easy, 2 = Intermediate, 3 = Expert: ";
		cin >> difficulty;
		board_.SetDifficulty(difficulty);
		break;
	case 'r':
		board_.ResetBoard();
		break;
	}
}
