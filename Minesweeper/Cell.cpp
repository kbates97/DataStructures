#include "stdafx.h"
#include "Cell.h"

Cell::Cell()
{
	data_ = '0';
	visible_ = false;
}

Cell::Cell(char data, bool visible)
{
	data_ = data;
	visible_ = visible;
}

char Cell::GetData()
{
	return data_;
}

bool Cell::GetVisible()
{
	return visible_;
}

bool Cell::GetMarked()
{
	return marked_;
}

void Cell::SetData(const char data)
{
	data_ = data;
}

void Cell::SetVisible(const bool visible)
{
	visible_ = visible;
}

void Cell::SetMarked(const bool marked)
{
	marked_ = marked;
}

ostream & operator<<(ostream & stream, Cell& cell)
{
	stream << '[';
	if (cell.GetVisible())
	{
		if (cell.GetData() == '0')
			stream << ' ';
		else
			stream << cell.GetData();
	}
	else if (cell.GetMarked())
	{
		stream << 'M';
	}
	else
		stream << '?';
	stream << ']';
	return stream;
}
