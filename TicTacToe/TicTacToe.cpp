

#include <iostream>

bool gameOver_chk(char* board, char turn);
void printBoard(char* board);

using namespace std;

void main()
{

	char board[9] = {0};

	bool gameOver = 0;
	char turn = 'X';
	int numTurns = 0;

	while ( (!gameOver) && (numTurns < 9))
	{
		int play;

		// Get turn input
		cout << turn << " plays:  ";
		cin >> play;
		cout << endl;

		if (play-- <= 9)
			if (board[play] == 0)
				board[play] = turn;
			else
			{
				cout << "Square not empty!" << endl;
				continue;
			}
		else
		{
			cout << "Out of range!" << endl;
			continue;
		}


		gameOver = gameOver_chk(board, turn);

		printBoard(board);

		// prepare for next turn
		turn = (turn == 'O') ? 'X' : 'O' ;

		numTurns++;

	}


	if (gameOver)
		cout << "Game over!" << endl << turn << " loses!" << endl;
	else
		cout << "Tie game!" << endl;

}


bool gameOver_chk(char* board, char turn)
{

	// check horizontal cases
	for(int i = 0; i < 3; i++)
		if ( (board[i*3] == turn) && (board[i*3 + 1] == turn) && (board[i*3 + 2] == turn) ) 
			return true;

	// check vertical cases
	for(int j = 0; j < 3; j++)
		if ( (board[j] == turn) && (board[3+j] == turn) && (board[6+j] == turn) ) 
			return true;

	// check diagonal cases
	if ( (board[0] == turn) && (board[4] == turn) && (board[8] == turn) ) 
			return true;

	if ( (board[2] == turn) && (board[4] == turn) && (board[6] == turn) ) 
			return true;

	return false;

}


void printBoard(char* board)
{
	cout << endl;
	cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
	cout << "---|---|---" << endl;
	cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
	cout << "---|---|---" << endl;
	cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
	cout << endl;

}
