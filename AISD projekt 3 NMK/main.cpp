#include "Board.h"
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
using namespace std;

const int INPUT_BUFFER_SIZE = 100;

int main()
{
	clock_t t1 = clock();
	char* command = new char[INPUT_BUFFER_SIZE];
	while (cin >> command)
	{
		if (strcmp(command, "GEN_ALL_POS_MOV") == 0)
		{
			Board board;
			board.read();
			board.generateMoves();
		} 
		else if (strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0)
		{
			Board board;
			board.read();
			board.generateMovesCut();
		}
		else if (strcmp(command, "SOLVE_GAME_STATE") == 0)
		{
			Board board;
			board.read();
			board.solveGame();

		}

	}
	delete[] command;
	printf("%fs", ((double)(clock() - t1) / (double)CLOCKS_PER_SEC));
}