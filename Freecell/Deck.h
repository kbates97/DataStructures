#pragma once
#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "ListStack.h"

class Deck
{
public:
	Deck();
	~Deck() = default;

	void Shuffle();
	Card& Deal();

	void Restack();

private:
	ListStack<Card> deck_;
};

#endif // !DECK_H
