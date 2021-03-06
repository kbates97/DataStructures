// Freecell.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Freecell.h"

using namespace std;

int main()
{
	Freecell game;
}

Freecell::Freecell()
{
	Start();
}

void Freecell::Start()
{
	SetBoard();
	while (!Win())
	{
		PrintBoard();
		Move();
	}
	PrintBoard();
	SetCursor(3, 0);
	wcout << L"*\\|/* You Win!!! *\\|/*";
	SetCursor(0, 11);
}

void Freecell::SetBoard()
{
	deck.Shuffle();
	free_cells_.SetLength(4);
	for (size_t i = 0; i < 4; ++i)
	{
		free_cells_[i] = Card(0, 0);
	}
	home_cells_.SetLength(4);
	for (size_t i = 0; i < 4; ++i)
	{
		home_cells_[i].Push(Card(0, 0));
	}
	play_area_.SetLength(8);
	for (size_t i = 0; i < 8; ++i)
	{
		play_area_[i].Push(Card(0, 0));
	}
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t k = 0; k < 7; ++k)
		{
			play_area_[i].Push(deck.Deal());
		}
	}
	for (size_t i = 4; i < 8; ++i)
	{
		for (size_t k = 0; k < 6; ++k)
		{
			play_area_[i].Push(deck.Deal());
		}
	}
}

void Freecell::Move()
{
	Card temp1, temp2;
	size_t select, cell;
	wcout << L"Where do you want to move from? 1 = free cell, 2 = play area: ";
	cin >> select;
	ClearError();
	switch (select)
	{
	default:
		error = L"Can't Move There.";
		break;
	case 1:
		wcout << L"Which Cell? [0...3]: ";
		cin >> cell;
		if (cell > 3 || cell < 0)
		{
			error = L"Invalid Cell!";
			break;
		}
		temp1 = free_cells_[cell];
		if (temp1.GetFace() == 0)
		{
			error = L"Nothing There.";
			break;
		}
		wcout << L"Where do you want to move this to? 1 = play area, 2 = home: ";
		cin >> select;
		switch (select)
		{
		default:
			error = L"Can't Move There.";
			break;
		case 1:
			wcout << L"Which Stack? [0...7]: ";
			cin >> select;
			if (select > 7 || select < 0)
			{
				error = L"Invalid Stack!";
				break;
			}
			temp2 = play_area_[select].Peek();
			if (((temp2.GetFace() - temp1.GetFace() == 1) && ((temp2.GetSuit() - temp1.GetSuit()) % 2)) || temp2.GetFace() == 0)
			{
				play_area_[select].Push(temp1);
				free_cells_[cell].SetFace(0);
				free_cells_[cell].SetSuit(0);
			}
			else
				error = L"Can't Move There.";
			break;
		case 2:
			temp2 = home_cells_[temp1.GetSuit() - 1].Peek();
			if (temp1.GetFace() - temp2.GetFace() == 1)
			{
				home_cells_[temp1.GetSuit() - 1].Push(temp1);
				free_cells_[cell].SetFace(0);
				free_cells_[cell].SetSuit(0);
			}
			else
				error = L"Can't Move There.";
			break;
		}
		break;
	case 2:
		wcout << L"Which Stack? [0...7]: ";
		cin >> cell;
		if (cell > 7 || cell < 0)
		{
			error = L"Invalid Stack!";
			break;
		}
		temp1 = play_area_[cell].Peek();
		if (temp1.GetFace() == 0)
		{
			error = L"Nothing There.";
			break;
		}
		wcout << L"Where do you want to move this to? 1 = free cell, 2 = play area, 3 = home: ";
		cin >> select;
		switch (select)
		{
		default:
			error = L"Can't Move There.";
			break;
		case 1:
			for (size_t i = 0; i < 4; ++i)
			{
				if (free_cells_[i].GetFace() == 0)
				{
					error = L" ";
					free_cells_[i] = play_area_[cell].Pop();
					break;
				}
				else
					error = L"Can't Move There.";
			}
			break;
		case 2:
			wcout << L"Which Stack? [0...7]: ";
			cin >> select;
			if (select > 7 || select < 0)
			{
				error = L"Invalid Stack!";
				break;
			}
			temp2 = play_area_[select].Peek();
			if (((temp2.GetFace() - temp1.GetFace() == 1) && ((temp2.GetSuit() - temp1.GetSuit()) % 2)) || temp2.GetFace() == 0)
			{
				play_area_[select].Push(play_area_[cell].Pop());
			}
			else
				error = L"Can't Move There.";
			break;
		case 3:
			temp2 = home_cells_[temp1.GetSuit() - 1].Peek();
			if (temp1.GetFace() - temp2.GetFace() == 1)
			{
				home_cells_[temp1.GetSuit() - 1].Push(play_area_[cell].Pop());
			}
			else
				error = L"Can't Move There.";
			break;
		}
		break;
	}
}

void Freecell::SetCursor(int x, int y)
{
	HANDLE hStdout = 0;
	COORD cursor;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(hStdout, cursor);
}

bool Freecell::Win()
{
	bool win = true;
	for (size_t i = 0; i < 4; i++)
	{
		Card temp = home_cells_[i].Peek();
		win *= temp.GetFace() == 13;
	}
	return win;
}

void Freecell::PrintBoard()
{
	system("CLS");
	SetCursor(0, 0);
	wcout << error;
	SetCursor(0, 2);
	wcout << '|';
	for (size_t i = 0; i < 4; ++i)
	{
		wcout << free_cells_[i] << '|';
	}
	SetCursor(16, 2);
	wcout << '|';
	for (size_t i = 0; i < 4; ++i)
	{
		Card temp = home_cells_[i].Peek();
		wcout << temp << '|';
	}
	SetCursor(2, 5);
	wcout << '|';
	for (size_t i = 0; i < 8; ++i)
	{
		Card temp = play_area_[i].Peek();
		wcout << temp << '|';
	}
	wcout << "\n" << endl;
}

void Freecell::ClearError()
{
	error = L"                                                 ";
	SetCursor(0, 0);
	wcout << error;
	SetCursor(0, 8);
}
