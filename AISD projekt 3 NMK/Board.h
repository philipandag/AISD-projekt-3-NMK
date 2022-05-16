#pragma once
#include "Field.h"

class Board
{
public:
	int n, m, k;
	Field player;
	Field** fields;
	int emptyFields;

	void deleteFields();
public:
	Board(int n, int m, int k, Field player);
	Board();
	Field* operator[](size_t index);
	const Field* operator[](size_t index) const;
	void print();
	void clearFlags(Point** winningMoves, int* counter);
	Field checkWin();
	Field checkWinningSituations();
	Field checkWinAt(Point pos);
	bool onBoard(Point p) const;
	Field operator[](Point p) const;
	Field& operator[](Point p);
	Field& at(Point p);
	int countInDirection(Point p, Point delta);
	Board& read();
	int getEmptyFields() const;
	Field getPlayer() const;
	void generateMoves();
	void generateMovesCut();
	Field solve();
	void solveGame();
	Board& set(Point p, Field value);
	void km1SequencesIncrementer(Field front, int frontCounter, Field back, int backCounter, int& P1Sequences, int& P2Sequences) const;
	Field km1SequencesGetWinner(int P1Sequences, int P2Sequences) const;
	~Board();
};