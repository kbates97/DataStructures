#pragma once

#ifndef Cell_H
#define Cell_H

#include <ostream>

using std::ostream;

class Cell
{
public:
	Cell();
	Cell(char data, bool visible);

	friend ostream& operator<<(ostream& stream, Cell& cell);

	char GetData();
	bool GetVisible();
	bool GetMarked();

	void SetData(const char data);
	void SetVisible(const bool visible);
	void SetMarked(const bool marked);
private:
	char data_;
	bool visible_ = false;
	bool marked_ = false;
};

#endif // !
