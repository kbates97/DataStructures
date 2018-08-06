#include "stdafx.h"
#include "Board.h"

Board::Board()
{
	board_.SetRow(10);
	board_.SetColumn(10);
	bombs_ = 10;
	ResetBoard();
}

Board::Board(size_t difficulty)
{
	switch (difficulty)
	{
	default:
		board_.SetRow(10);
		board_.SetColumn(10);
		bombs_ = 10;
		ResetBoard();
		break;
	case 1:
		board_.SetRow(10);
		board_.SetColumn(10);
		bombs_ = 10;
		ResetBoard();
		break;
	case 2:
		board_.SetRow(16);
		board_.SetColumn(16);
		bombs_ = 40;
		ResetBoard();
		break;
	case 3:
		board_.SetRow(16);
		board_.SetRow(30);
		bombs_ = 100;
		ResetBoard();
		break;
	}
}

Board::Board(const Array2D<Cell>& board, const size_t bombs)
{
	board_ = board;
	bombs_ = bombs;
}

Board::Board(const Board& board)
{
	board_ = board.board_;
	bombs_ = board.bombs_;
}

void Board::SetDifficulty(const size_t difficulty)
{
	switch (difficulty)
	{
	default:
		board_.SetRow(10);
		board_.SetColumn(10);
		bombs_ = 10;
		ResetBoard();
		break;
	case 1:
		board_.SetRow(10);
		board_.SetColumn(10);
		bombs_ = 10;
		ResetBoard();
		break;
	case 2:
		board_.SetRow(16);
		board_.SetColumn(16);
		bombs_ = 40;
		ResetBoard();
		break;
	case 3:
		board_.SetRow(16);
		board_.SetColumn(30);
		bombs_ = 100;
		ResetBoard();
		break;
	}
}

void Board::ResetBoard()
{
	ClearBoard();
	size_t bombsPlaced = 0;
	while (bombsPlaced < bombs_)
	{
		int row = rand() % board_.GetRow();
		int col = rand() % board_.GetColumn();
		if (board_[row][col].GetData() != 'B')
		{
			board_[row][col].SetData('B');
			bombsPlaced += 1;
			IncrementNumbersAroundBomb(row, col);
		}
	}
	for (size_t i = 0; i < board_.GetRow(); ++i)
	{
		for (size_t k = 0; k < board_.GetColumn(); ++k)
		{
			board_[i][k].SetVisible(false);
		}
	}
}

void Board::IncrementNumbersAroundBomb(int row, int col)
{
	if (row > 0)
	{
		if (board_[row - 1][col].GetData() != 'B')
			board_[row - 1][col].SetData(board_[row - 1][col].GetData()+1);
		if (col > 0)
		{
			if (board_[row - 1][col - 1].GetData() != 'B')
				board_[row - 1][col - 1].SetData(board_[row - 1][col - 1].GetData()+1);
		}
		if (col < board_.GetColumn() - 1)
		{
			if (board_[row - 1][col + 1].GetData() != 'B')
				board_[row - 1][col + 1].SetData(board_[row - 1][col + 1].GetData()+1);
		}
	}
	if (row < board_.GetRow() - 1)
	{
		if (board_[row + 1][col].GetData() != 'B')
			board_[row + 1][col].SetData(board_[row + 1][col].GetData()+1);
		if (col > 0)
		{
			if (board_[row + 1][col - 1].GetData() != 'B')
				board_[row + 1][col - 1].SetData(board_[row + 1][col - 1].GetData()+1);
		}
		if (col < board_.GetColumn() - 1)
		{
			if (board_[row + 1][col + 1].GetData() != 'B')
				board_[row + 1][col + 1].SetData(board_[row + 1][col + 1].GetData()+1);
		}
	}
	if (col > 0)
	{
		if (board_[row][col - 1].GetData() != 'B')
			board_[row][col - 1].SetData(board_[row][col - 1].GetData()+1);
	}
	if (col < board_.GetColumn() - 1)
	{
		if (board_[row][col + 1].GetData() != 'B')
			board_[row][col + 1].SetData(board_[row][col + 1].GetData()+1);
	}
}

void Board::PrintBoard()
{
	system("CLS");
	for (size_t i = 0; i < board_.GetRow(); ++i)
	{
		for (size_t k = 0; k < board_.GetColumn(); ++k)
		{
			std::cout << board_[i][k];
		}
		std::cout << std::endl;
	}
}

bool Board::AllBombsMarked()
{
	return (bombsMarked_ == bombs_);
}

char Board::Select(const int row, const int col)
{
	if (!board_[row][col].GetMarked())
	{
		board_[row][col].SetVisible(true);
		if (board_[row][col].GetData() == '0')
			ClearBlanks(row, col);
		return board_[row][col].GetData();
	}
	else
		return 'M';
}

void Board::Mark(const int row, const int col)
{
	if (board_[row][col].GetMarked())
	{
		board_[row][col].SetMarked(false);
		if (board_[row][col].GetData() == 'B')
			--bombsMarked_;
	}
	else
	{
		board_[row][col].SetMarked(true);
		if (board_[row][col].GetData() == 'B')
			++bombsMarked_;
		else
			--bombsMarked_;
	}
}

void Board::ClearBlanks(const int row, const int col)
{
	if (board_[row][col].GetVisible() == false)
		board_[row][col].SetVisible(true);
	if (row > 0)
	{
		if (board_[row - 1][col].GetData() == '0' && board_[row - 1][col].GetVisible() == false)
			ClearBlanks(row - 1, col);
		board_[row - 1][col].SetVisible(true);
		if (col > 0)
		{
			if (board_[row - 1][col - 1].GetData() == '0' && board_[row - 1][col - 1].GetVisible() == false)
				ClearBlanks(row - 1, col - 1);
			board_[row - 1][col - 1].SetVisible(true);
		}
		if (col < board_.GetColumn() - 1)
		{
			if (board_[row - 1][col + 1].GetData() == '0' && board_[row - 1][col + 1].GetVisible() == false)
				ClearBlanks(row - 1, col + 1);
			board_[row - 1][col + 1].SetVisible(true);
		}
	}
	if (row < board_.GetRow() - 1)
	{
		if (board_[row + 1][col].GetData() == '0' && board_[row + 1][col].GetVisible() == false)
			ClearBlanks(row + 1, col);
		board_[row + 1][col].SetVisible(true);
		if (col > 0)
		{
			if (board_[row + 1][col - 1].GetData() == '0' && board_[row + 1][col - 1].GetVisible() == false)
				ClearBlanks(row + 1, col - 1);
			board_[row + 1][col - 1].SetVisible(true);
		}
		if (col < board_.GetColumn() - 1)
		{
			if (board_[row + 1][col + 1].GetData() == '0' && board_[row + 1][col + 1].GetVisible() == false)
				ClearBlanks(row + 1, col + 1);
			board_[row + 1][col + 1].SetVisible(true);
		}
	}
	if (col > 0)
	{
		if (board_[row][col - 1].GetData() == '0' && board_[row][col - 1].GetVisible() == false)
			ClearBlanks(row, col - 1);
		board_[row][col - 1].SetVisible(true);
	}
	if (col < board_.GetColumn() - 1)
	{
		if (board_[row][col + 1].GetData() == '0' && board_[row][col + 1].GetVisible() == false)
			ClearBlanks(row, col + 1);
		board_[row][col + 1].SetVisible(true);
	}
}

void Board::ClearBoard()
{
	for (size_t i = 0; i < board_.GetRow(); ++i)
	{
		for (size_t k = 0; k < board_.GetColumn(); ++k)
		{
			board_[i][k].SetData('0');
		}
	}
}
