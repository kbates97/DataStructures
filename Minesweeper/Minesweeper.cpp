// Minesweeper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Array2D.h"
#include "Minesweeper.h"
#include "Board.h"
using std::cout;
using std::endl;

void printBoard(Array2D<char>& minefield);

int main()
{
	Board board;
	board.Select(4, 8);
	board.Mark(5, 5);
	board.printBoard();
}

void printBoard(Array2D<char>& minefield)
{
	printf("\033[1;1H");
	for (size_t i = 0; i < minefield.GetRow(); ++i)
	{
		for (size_t k = 0; k < minefield.GetColumn(); ++k)
		{
			printf("[%c]", minefield[i][k]);
		}
		printf("\n");
	}
}