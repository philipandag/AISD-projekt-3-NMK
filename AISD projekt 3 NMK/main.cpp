#include <iostream>
#include "Board.h"
#include <stdlib.h>
#include <time.h>
using namespace std;

const int INPUT_BUFFER_SIZE = 100;

int main()
{
	char* command = new char[INPUT_BUFFER_SIZE];
	while (cin >> command)
	{
		if (strcmp(command, "GEN_ALL_POS_MOV") == 0)
		{
			Board board;
			board << cin;
			board.generateMoves(cout);
		} 
		else if (strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0)
		{
			Board board;
			board << cin;
			board.generateMovesCut(cout);
		}
		else if (strcmp(command, "SOLVE_GAME_STATE") == 0)
		{
			Board board;
			board << cin;
			board.solveGame(cout);
		}

	}
	delete[] command;
}