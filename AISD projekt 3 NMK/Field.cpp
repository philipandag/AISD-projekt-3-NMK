#include "Field.h"

extern const char* RESULTS[3] = {
	"BOTH_PLAYERS_TIE",
	"FIRST_PLAYER_WINS",
	"SECOND_PLAYER_WINS"
};

Field** createFields(int n, int m)
{
	Field** board = new Field*[n];
	for (int i = 0; i < n; i++)
		board[i] = new Field[m];
	return board;
}

istream& operator>>(istream& is, Field& f)
{
	int a;
	if (is >> a)
		f.value = static_cast<Field::Value>(a==0?2:(a-1));
	return is;
}

Field Field::getOtherPlayer()
{
	Field p = *this;
	p.value = value == Field::Value::P1 ? Field::Value::P2 : Field::Value::P1;
	return p;
}

bool Field::operator<(Field than)
{
	if (value == Value::P1 && than.value == Value::EMPTY)
		return false;
	if (value == Value::EMPTY && than.value == Value::P1)
		return true;
	return value < than.value;
}

bool Field::operator>(Field than)
{
	if (value == Value::P1 && than.value == Value::EMPTY)
		return true;
	if (value == Value::EMPTY && than.value == Value::P1)
		return false;
	return value < than.value;
}

bool Field::operator<=(Field than)
{
	return value == than.value || value < than.value;
}
bool Field::operator>=(Field than)
{
	return value == than.value || value > than.value;
}

bool Field::empty()
{
	return this->value == Value::EMPTY;
}

bool Field::notChecked(Field player)
{
	return value == Value::EMPTY && winningMove[(int)player.value] == false;
}

bool Field::operator==(Field f)
{
	return value == f.value;
}

bool Field::operator!=(Field f)
{
	return value != f.value;
}