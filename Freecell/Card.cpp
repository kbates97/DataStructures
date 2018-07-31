#include "stdafx.h"
#include "Card.h"

Card::Card():face_(ACE), suit_(HEARTS)
{
	SetColor();
}

Card::Card(size_t face, size_t suit)
{
	SetFace(face);
	SetSuit(suit);
}

void Card::SetFace(size_t face)
{
	if (face > 13 || face < 0)
		throw AdtException("Out Of Bounds");
	face_ = face;
}

void Card::SetSuit(size_t suit)
{
	if (suit > 4 || suit < 0)
		throw AdtException("Out Of Bounds");
	suit_ = suit;
	SetColor();
}

void Card::SetColor()
{
	if (suit_ % 2)
		color_ = FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
	else
		color_ = FOREGROUND_RED & FOREGROUND_BLUE & FOREGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
}

size_t Card::GetFace()
{
	return face_;
}

size_t Card::GetNext()
{
	return face_ + 1;
}

size_t Card::GetSuit()
{
	return suit_;
}

bool operator==(const Card& lhs, const Card& rhs)
{
	return lhs.face_ == rhs.face_ && lhs.suit_ == rhs.suit_;
}

bool operator!=(const Card& lhs, const Card& rhs)
{
	return !(lhs == rhs);
}

wostream & operator<<(wostream & stream, Card & card)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	HANDLE hStdout = 0;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, card.color_);
	stream << card.char_face_[card.face_] << card.char_suit_[card.suit_];
	SetConsoleTextAttribute(hStdout, DEFAULT_PALETTE);

	return stream;
}
