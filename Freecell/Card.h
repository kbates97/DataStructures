#pragma once
#ifndef CARD_H
#define CARD_H

#include "AdtException.h"
#include <windows.h>
#include <iostream>
#include <io.h> //for _setmode
#include <fcntl.h> //for _O_U16TEXT

using std::ostream;
using std::wostream;

class Card
{
public:
	Card();
	Card(size_t face, size_t suit);
	~Card() = default;

	void SetFace(size_t face);
	void SetSuit(size_t suit);
	void SetColor();
	size_t GetFace();
	size_t GetNext();
	size_t GetSuit();
	
	friend bool operator==(const Card& lhs, const Card& rhs);
	friend bool operator!=(const Card& lhs, const Card& rhs);


	friend wostream & operator<<(wostream & stream, Card & card);

private:
	enum face_value
	{
		BLANK, ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
	};
	enum suit
	{
		NONE, HEARTS, CLUBS, DIAMONDS, SPADES
	};
	char char_face_[14] = { ' ', 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K' };
	wchar_t char_suit_[5] = { L' ', L'♥', L'♣', L'♦', L'♠' };
	size_t face_;
	size_t suit_;
	WORD color_;
};

#endif // !CARD_H
