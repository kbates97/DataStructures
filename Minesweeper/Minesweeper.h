#pragma once

#ifndef Minesweeper_H
#define Minesweeper_H

#include "Board.h"

class Minesweeper
{
public:
	Minesweeper();
	Minesweeper(size_t difficulty);

private:
	Board board_;
	bool done_ = false;
	bool win_;
};

#endif