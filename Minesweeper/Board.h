#pragma once

#ifndef Board_H
#define Board_H

#include "Cell.h"
#include "Array2D.h"
#include <iostream>

class Board
{
public:
	Board();
	Board(const size_t difficulty);
	Board(const Array2D<Cell>& board, const size_t bombs);
	Board(const Board& board);

	void SetDifficulty(const size_t difficulty);

	char Select(const int row, const int col);
	void Mark(const int row, const int col);

	void resetBoard();
	void printBoard();


private:
	Array2D<Cell> board_;
	size_t bombs_;

	void incrementNumbersAroundBomb(int row, int col);
	void ClearBlanks(const int row, const int col);
};

#endif // !Board_H
