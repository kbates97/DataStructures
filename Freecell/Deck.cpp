#include "stdafx.h"
#include "Deck.h"

Deck::Deck()
{
	Restack();
}

void Deck::Shuffle()
{
	deck_.Shuffle();
}

Card & Deck::Deal()
{
	Card temp = deck_.Pop();
	return temp;
}

void Deck::Restack()
{
	deck_.Clear();
	for (size_t i = 1; i < 5; i++)
	{
		for (size_t k = 1; k < 14; k++)
		{
			deck_.Push(Card(k, i));
		}
	}
}
