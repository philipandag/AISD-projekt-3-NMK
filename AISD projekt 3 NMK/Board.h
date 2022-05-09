#pragma once
#include "Field.h"
#include "time.h"

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
	Board& operator=(Board& other);
	int getN() const;
	int getM() const;
	int getK() const;
	Field* operator[](size_t index);
	const Field* operator[](size_t index) const;
	friend ostream& operator<<(ostream& os, const Board& board);
	void clearFlags(Point** winningMoves, int* counter);
	Field::Value checkWin() const;
	Field checkWinningSituations();
	Field checkWinningSituation(Point pos);
	Field::Value checkWinAt(Point pos) const;
	bool onBoard(Point p) const;
	Field operator[](Point p) const;
	Field& operator[](Point p);
	Field& at(Point p);
	int countInDirection(Point p, Direction d) const;
	Board& operator<<(istream& is);
	int getEmptyFields() const;
	Field getPlayer() const;
	void print(ostream& os) const;
	void generateMoves(ostream& os) const;
	void generateMovesCut(ostream& os) const;
	bool checkInitialWin(ostream& os) const;
	Board* copyChangePlayer();
	Field solve();
	Field solveAlphaBeta(Field alpha, Field beta);
	void solveGame(ostream& os) const;
	Board& set(Point p, Field value);
	~Board();
};