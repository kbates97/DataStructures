#pragma once

#ifndef Minesweeper_H
#define Minesweeper_H

#include "Board.h"

using std::cout;
using std::endl;
using std::cin;

class Minesweeper
{
public:
	Minesweeper();
	Minesweeper(size_t difficulty);

	void PlayGame();
	void EndSequence();
	void Settings();

private:
	Board board_;
	bool done_ = false;
	bool win_;
};

#endif