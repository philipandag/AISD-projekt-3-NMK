#pragma once
#include <iostream>
#include "Direction.h"
#include "Point.h"

using namespace std;

extern const char* RESULTS[3];

struct Field{

	enum Value {
	P1 = 0,
	P2 = 1,
	EMPTY = 2,
	};

	Value value;
	bool winningMove[2];

	Field() {
		value = Value::EMPTY;
		winningMove[static_cast<int>(Value::P1)] = false;
		winningMove[static_cast<int>(Value::P2)] = false;
	}

	Field(Field::Value v) {
		value = v;
		winningMove[static_cast<int>(Value::P1)] = false;
		winningMove[static_cast<int>(Value::P2)] = false;
	}
	friend istream& operator>>(istream& is, Field& f);
	Field changePlayer();
	Field findInArray(Field* array, int size, Field toFind);
	Field getOtherPlayer();
	Field getWinMove(Field player);
	bool empty();
	bool notChecked(Field player);
	bool operator<(Field than);
	bool operator>(Field than);
	bool operator<=(Field than);
	bool operator>=(Field than);
	bool operator==(Field f);
	bool operator!=(Field f);


};

Field** createFields(int n, int m);


