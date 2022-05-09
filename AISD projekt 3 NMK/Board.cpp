#include "Board.h"

int GAMES_SOLVED = 0;

Board::Board(int n, int m, int k, Field player):
	n(n), m(m), k(k), player(player), fields(createFields(n, m)), emptyFields(0)
{}



Board::Board():
	n(0), m(0), k(0), player(Field::EMPTY), fields(nullptr), emptyFields(0)
{}

Field::Value Board::checkWin() const
{
	Field::Value win = Field::EMPTY;

	for (int y = 0; y < n; y++)
		for (int x = 0; x < m; x++)
		{
			win = checkWinAt({ x, y });
			if (win == Field::P1 || win == Field::P2)
				return win;
		}
	return Field::EMPTY;
}


Field::Value Board::checkWinAt(Point pos) const
{
	if ((*this)[pos] == Field::EMPTY)
		return Field::EMPTY;

	for (Direction d = Direction::E; d < Direction::W; ++d) // >, _\, \/, /_
		if (countInDirection(pos, d) >= k)
			 return (*this)[pos].value;
			

	return Field::EMPTY;
}

bool Board::onBoard(Point p) const
{
	return p.x >= 0 && p.x < m && p.y >= 0 && p.y < n;
}

int Board::countInDirection(Point p, Direction d) const
{
	if (!onBoard(p))
		return 0;

	int counter = 1;
	Point delta = d.getP();

	Field first = fields[p.y][p.x];
	while (onBoard(p + delta) && (*this)[p + delta] == first)
	{
		p += delta;
		counter++;
	}
	return counter;
}

Board& Board::operator=(Board& other)
{
	if (this != &other)
	{
		this->emptyFields = other.emptyFields;

		if (this->n != other.getN() || this->m != other.getM())
		{
			delete this->fields;
			this->fields = createFields(other.getN(), other.getM());
		}

		for (int y = 0; y < n; y++)
			for (int x = 0; x < m; x++)
				fields[y][x] = other[y][x];
	}
	return *this;
}

int Board::getN() const {
	return n;
}

int Board::getM() const {
	return m;
}

int Board::getK() const {
	return k;
}

Field* Board::operator[](size_t index) {
	return fields[index];
}

const Field* Board::operator[](size_t index) const {
	return fields[index];
}

ostream& operator<<(ostream& os, const Board& board)
{
	for (int y = 0; y < board.getN(); y++)
	{
		for (int x = 0; x < board.getM(); x++)
			printf("%d ", board[y][x]);
		printf("\n");
	}
	return os;
}

Board& Board::operator<<(istream& is)
{
	if (fields != nullptr)
		deleteFields();
	is >> n >> m >> k >> player;

	fields = createFields(n, m);
	emptyFields = 0;

	for (int y = 0; y < n; y++)
		for (int x = 0; x < m; x++)
		{
			is >> fields[y][x];
			if (fields[y][x].empty())
				emptyFields++;
		}

	return *this;
}

int Board::getEmptyFields() const
{
	return emptyFields;
}

Field Board::getPlayer() const
{
	return player;
}

void Board::deleteFields()
{
	for (int i = 0; i < n; i++)
		delete fields[i];
	delete fields;
}

void Board::generateMoves(ostream& os) const
{
	if (checkInitialWin(os))
		return;

	os << "\n" << emptyFields << "\n";

	Board copy = (*this);
	for (int y = 0; y < n; y++)
		for (int x = 0; x < m; x++)
			if (copy[y][x].empty())
			{
				copy[y][x] = player;
				os << copy << endl;
				copy[y][x].value = Field::EMPTY;
			}
}

Board::~Board()
{
	deleteFields();
}

Field Board::operator[](Point p) const
{
	return fields[p.y][p.x];
}
Field& Board::operator[](Point p)
{
	return fields[p.y][p.x];
}
Field& Board::at(Point p) 
{
	return fields[p.y][p.x];
}

bool Board::checkInitialWin(ostream& os) const
{
	if (checkWin() != Field::EMPTY)
	{
		os << 0 << "\n";
		return true;
	}
	return false;
}

void Board::generateMovesCut(ostream& os) const
{
	if (checkInitialWin(os))
		return;

	Board copy = (*this);

	for (int y = 0; y < n; y++)
		for (int x = 0; x < m; x++)
			if (copy[y][x].empty())
			{
				copy[y][x] = player;
				if (copy.checkWin())
				{
					os << 1 << endl << copy;
					return;
				}
				copy[y][x].value = Field::EMPTY;
			}

	generateMoves(os);
}

void Board::solveGame(ostream& os) const
{
	Board copy = (*this);
	Field result = copy.solve();
	os << RESULTS[result.value] << endl;
	GAMES_SOLVED++;
}

Board* Board::copyChangePlayer()
{
	Board* copy = new Board((*this));
	copy->player = player.getOtherPlayer();
	return copy;
}

Board& Board::set(Point p, Field value)
{
	if ((*this)[p] != value)
	{
		if (value == Field::EMPTY)
			emptyFields++;
		else
			emptyFields--;
	}
	(*this)[p] = value;

	return *this;
}

Field Board::solve()
{
	Field win = checkWinningSituations();
	if (win == Field::P1 || win == Field::P2)
		return win;

	if (emptyFields == 0)
		return Field::EMPTY;

	Field otherPlayer = player.getOtherPlayer();
	Field best = otherPlayer; // other player wins - the worst scenario

	int resultNumber = 0;
	for (int y = 0; y < n; y++)
		for (int x = 0; x < m; x++)
			if (fields[y][x] == Field::EMPTY && resultNumber < emptyFields)
			{
				Point pos = { x, y };
				set(pos, player);
				player = player.getOtherPlayer();
				Field result = solve();
				set({ x, y }, Field::EMPTY);
				player = player.getOtherPlayer();

				if (result == player) // quick optimisation - if its the best option - it would be chosen no matter what the others would be, so don't bother checking them
					return player;

				if (result == Field::EMPTY)
				{
					if (best == otherPlayer)
						best = Field::EMPTY;
				}

				resultNumber++;
			}

	return best;
}

Field Board::checkWinningSituations()
{
	Point pos;
	Point delta;
	int winningMovesCount[2];
	winningMovesCount[Field::P1] = 0;
	winningMovesCount[Field::P2] = 0;

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			pos = { x,y };
			if (at(pos).empty())
			{
				for (Direction d = Direction::E; d < Direction::W; ++d)
				{
					delta = d.getP();
					int backCount, frontCount;

					if (onBoard(pos-delta) && !at(pos-delta).empty())
					{
						backCount = 1;
						for (int i = 2; i <= k; i++)
							if (onBoard(pos-delta*i) && at(pos - delta * i) == at(pos-delta))
								backCount++;
							else
								break;

						if (backCount == k)
							return at(pos-delta);
					}
					else
						backCount = 0;
			
					if (onBoard(pos + delta) && !at(pos+delta).empty())
					{
						frontCount = 1;
						for (int i = 2; i <= k; i++)
							if (onBoard(pos - delta * i) && at(pos - delta * i) == at(pos+delta))
								frontCount++;
							else
								break;

						if (frontCount == k)
							return at(pos+delta);
					}else
						frontCount = 0;

					if (onBoard(pos-delta) && onBoard(pos+delta) && at(pos-delta) == at(pos+delta) && backCount + frontCount + 1 >= k)
						winningMovesCount[at(pos-delta).value]++;
					else if(onBoard(pos-delta) && backCount + 1 >= k)
						winningMovesCount[at(pos - delta).value]++;
					else if(onBoard(pos + delta) && frontCount + 1 >= k)
						winningMovesCount[at(pos + delta).value]++;

				}
			}
		}
	}

	Field win = Field::EMPTY;
	if (winningMovesCount[Field::P1] >= 2)
	{
		if (winningMovesCount[Field::P2] >= 1)
			win = player;
		else
			win = Field::P1;
	}
	else if (winningMovesCount[Field::P2] >= 2)
	{
		if (winningMovesCount[Field::P1] >= 1)
			win = player;
		else
			win = Field::P2;
	}

	return win;
}