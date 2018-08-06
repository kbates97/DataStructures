#pragma once
#ifndef FREECELL_H
#define FREECELL_H
#include "ArrayStack.h"
#include "Deck.h"
#include <string>

using std::cin;
using std::wstring;

class Freecell
{
public:
	Freecell();
	~Freecell() = default;

	void Start();
	void SetBoard();
	void Move();
	void SetCursor(int x, int y);
	bool Win();

	void PrintBoard();
	void ClearError();

private:
	Array<Card> free_cells_;
	Array<ArrayStack<Card>> home_cells_;
	Array<ListStack<Card>> play_area_;
	Deck deck;
	wstring error;
};

#endif // !FREECELL_H
