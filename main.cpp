#include <iostream>
#include <algorithm>

int N = 3;
int pl = 1;
int ai = -1;

int MAX = 1000;
int MIN = -1000;

int hFunc(int b[][3]);
int minimax(int board[][3],int alpha, int beta, int moves, bool isMaxPl);
void AImove(int board[][3], int alpha, int beta, int moves, bool isMaxPl);
int checkForWinner(int b[][3]);
void printBoard(int board[][3]);
bool isFree(int board[][3], int m1, int m2);

int checkH1Max(int board[][3], int bestH, int bestMove[2], int i, int j, int newI, int newJ, int &r1, int &r2);
int checkH2Max(int board[][3], int bestH, int bestMove[2], int i, int j, int j1, int j2, int &r1, int &r2);
int checkH3Max(int board[][3], int bestH, int bestMove[2], int i, int j, int i1, int i2, int &r1, int &r2);

int checkH1Min(int board[][3], int bestH, int bestMove[2], int i, int j, int newI, int newJ, int &r1, int &r2);
int checkH2Min(int board[][3], int bestH, int bestMove[2], int i, int j, int j1, int j2, int &r1, int &r2);
int checkH3Min(int board[][3], int bestH, int bestMove[2], int i, int j, int i1, int i2, int &r1, int &r2);


void playerMove1(int board[][3], int& m1, int& m2, int &moves);
void playerMove2(int board[][3], int& m1, int& m2, int& m3, int &m4);
void AI1(int board[][3], int& alpha, int& beta, int& moves, bool isMaxPl);
void AI2(int board[][3], bool isMaxPl);

void AImove2(int board[][3], bool isMaxPl);


int main()
{
	bool plIsFirst = false;
	std::cout << "Wanna be first?(1 for yes and 0 for no)" << std::endl;
	std::cin >> plIsFirst;
	
	if (!plIsFirst)
	{
		pl = -1;
		ai = 1;
	}

	int alpha = MIN;
	int beta = MAX;

	int winner = 0;
	int board[3][3] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	int m1 = 0;
	int m2 = 0;
	int m3 = 0;
	int m4 = 0;
	int moves = 0;

	printBoard(board);
	//putting the balls on the board
	while (moves < 6)
	{
		//if the player plays first(player is the MaxPlayer)
		if (plIsFirst)
		{
			
			playerMove1(board, m1, m2, moves);
			AI1(board, alpha, beta, moves, false);
			
		}
		//if the ai plays first(player is the MinPlayer)
		else
		{
			AI1(board, alpha, beta, moves, true);
			playerMove1(board, m1, m2, moves);
		}
	}
	//now all the balls are on the board and is time to move them
	while(checkForWinner(board) == 0)
	{
		if (plIsFirst)
		{

			playerMove2(board, m1, m2, m3, m4);
			AI2(board, false);
		}
		else
		{

			AI2(board, true);
			playerMove2(board, m1, m2, m3, m4);

		}
	}
	system("pause");
}
void AI1(int board[][3], int& alpha, int& beta, int& moves, bool isMaxPl)
{
	std::cout << "AI move:" << std::endl;
	if (moves == 0)
	{
		int i = rand() % 3;
		int j = rand() % 3;
		moves++;
		board[i][j] = ai;
				
	}
	else
	{
		
		AImove(board, alpha, beta, moves, isMaxPl);

		moves++;

		if (checkForWinner(board) != 0)
		{

			std::cout << "Game over." << std::endl;
		}
	}
	printBoard(board);

}
void AI2(int board[][3], bool isMaxPl)
{
	std::cout << "AI move:" << std::endl;
	AImove2(board, isMaxPl);
	if (checkForWinner(board) != 0)
	{

		std::cout << "Game over." << std::endl;
	}
	printBoard(board);
}
void playerMove1(int board[][3], int& m1, int& m2, int &moves)
{

	int currm = moves - 1;
	std::cout << "Where do you want to put?" << std::endl;
	while (currm != moves)
	{
		std::cin >> m1 >> m2;
		if (isFree(board, m1, m2))
		{

			board[m1][m2] = pl;
			currm++;
		}
		else
		{
			std::cout << "This spot is  not available. Please choose another one." << std::endl;
		}


	}
	moves++;

	if (checkForWinner(board) != 0)
	{

		std::cout << "Game over." << std::endl;
	}
	printBoard(board);
}
void playerMove2(int board[][3], int& m1, int& m2, int& m3, int& m4)
{
	std::cout << "Move ";
	std::cin >> m1;
	std::cin >> m2;
	//while(board[m1][m2] != pl)
	//{
	//	/*std::cout << "Please select a spot with " << pl <<"."<<  std::endl
	//		<< "Move ";
	//	std::cin >> m1;
	//	std::cin >> m2;*/
	//	
	//	
	//}

	std::cout << "to position ";
	std::cin >> m3;
	std::cin >> m4;
	std::cout << std::endl;
	/*while(!(isFree(board, m3, m4)))
	{
		std::cout<< "This spot is  not available. Please choose another one." << std::endl;
	}*/
	board[m1][m2] = 0;
	board[m3][m4] = pl;

	if (checkForWinner(board) != 0)
	{

		std::cout << "Game over." << std::endl;
	}
	printBoard(board);

}
//checks for 00, 02, 20, 22(corners)
int checkH1Max(int board[][3], int bestH, int bestMove[2], int i, int j, int newI, int newJ, int &r1, int &r2)
{
	int currH;
	if (isFree(board, newI, j))
	{
		board[newI][j] = ai;
		currH = hFunc(board);
		if (currH > bestH)
		{
			bestH = currH;
			bestMove[0] = newI;
			bestMove[1] = j;
			r1 = i;
			r2 = j;
		}
		board[newI][j] = 0;
	}
	if (isFree(board, i, newJ))
	{
		board[i][newJ] = ai;
		currH = hFunc(board);
		if (currH > bestH)
		{
			bestH = currH;
			bestMove[0] = i;
			bestMove[1] = newJ;
			r1 = i;
			r2 = j;
		}
		board[i][newJ] = 0;
	}
	if (isFree(board, 1, 1))
	{
		board[1][1] = ai;
		currH = hFunc(board);
		if (currH > bestH)
		{
			bestH = currH;
			bestMove[0] = 1;
			bestMove[1] = 1;
			r1 = i;
			r2 = j;
		}
		board[1][1] = 0;
	}
	return bestH;
}
//check for 01, 21
int checkH2Max(int board[][3], int bestH, int bestMove[2], int i, int j, int j1, int j2, int &r1, int &r2)
{
	int currH;
	
	if (isFree(board, i, j1))
	{
		board[i][j1] = ai;
		currH = hFunc(board);
		if (currH > bestH)
		{
			bestH = currH;
			bestMove[0] = i;
			bestMove[1] = j1;
			r1 = i;
			r2 = j;
		}
		board[i][j1] = 0;
	}
	if (isFree(board, i, j2))
	{
		board[i][j2] = ai;
		currH = hFunc(board);
		if (currH > bestH)
		{
			bestH = currH;
			bestMove[0] = i;
			bestMove[1] = j2;
			r1 = i;
			r2 = j;
		}
		board[i][j2] = 0;
	}
	if (isFree(board, 1, 1))
	{
		board[1][1] = ai;
		currH = hFunc(board);
		if (currH > bestH)
		{
			bestH = currH;
			bestMove[0] = 1;
			bestMove[1] = 1;
			r1 = i;
			r2 = j;
		}
		board[1][1] = 0;
	}

	return bestH;
}
//check for 10, 12
int checkH3Max(int board[][3], int bestH, int bestMove[2], int i, int j, int i1, int i2, int &r1, int &r2)
{
	int currH;
	if (isFree(board, i1, j))
	{
		board[i1][j] = ai;
		currH = hFunc(board);
		if (currH > bestH)
		{
			bestH = currH;
			bestMove[0] = i1;
			bestMove[1] = j;
			r1 = i;
			r2 = j;
		}
		board[i1][j] = 0;
	}
	if (isFree(board, i2, j))
	{
		board[i2][j] = ai;
		currH = hFunc(board);
		if (currH > bestH)
		{
			bestH = currH;
			bestMove[0] = i2;
			bestMove[1] = j;
			r1 = i;
			r2 = j;
		}
		board[i2][j] = 0;
	}
	if (isFree(board, 1, 1))
	{
		board[1][1] = ai;
		currH = hFunc(board);
		if (currH > bestH)
		{
			bestH = currH;
			bestMove[0] = 1;
			bestMove[1] = 1;
			r1 = i;
			r2 = j;
		}
		board[1][1] = 0;
	}
	return bestH;
}
int checkH1Min(int board[][3], int bestH, int bestMove[2], int i, int j, int newI, int newJ, int &r1, int &r2)
{
	int currH;
	if (isFree(board, newI, j))
	{
		board[newI][j] = ai;
		currH = hFunc(board);
		if (currH < bestH)
		{
			bestH = currH;
			bestMove[0] = newI;
			bestMove[1] = j;
			r1 = i;
			r2 = j;
		}
		board[newI][j] = 0;
	}
	if (isFree(board, i, newJ))
	{
		board[i][newJ] = ai;
		currH = hFunc(board);
		if (currH < bestH)
		{
			bestH = currH;
			bestMove[0] = i;
			bestMove[1] = newJ;
			r1 = i;
			r2 = j;
		}
		board[i][newJ] = 0;
	}
	if (isFree(board, 1, 1))
	{
		board[1][1] = ai;
		currH = hFunc(board);
		if (currH < bestH)
		{
			bestH = currH;
			bestMove[0] = 1;
			bestMove[1] = 1;
			r1 = i;
			r2 = j;
		}
		board[1][1] = 0;
	}
	return bestH;
}
int checkH2Min(int board[][3], int bestH, int bestMove[2], int i, int j, int j1, int j2, int &r1, int &r2)
{
	int currH;

	if (isFree(board, i, j1))
	{
		board[i][j1] = ai;
		currH = hFunc(board);
		if (currH < bestH)
		{
			bestH = currH;
			bestMove[0] = i;
			bestMove[1] = j1;
		}
		board[i][j1] = 0;
	}
	if (isFree(board, i, j2))
	{
		board[i][j2] = ai;
		currH = hFunc(board);
		if (currH < bestH)
		{
			bestH = currH;
			bestMove[0] = i;
			bestMove[1] = j2;
		}
		board[i][j2] = 0;
	}
	if (isFree(board, 1, 1))
	{
		board[1][1] = ai;
		currH = hFunc(board);
		if (currH < bestH)
		{
			bestH = currH;
			bestMove[0] = 1;
			bestMove[1] = 1;
		}
		board[1][1] = 0;
	}

	return bestH;
}
int checkH3Min(int board[][3], int bestH, int bestMove[2], int i, int j, int i1, int i2, int &r1, int &r2)
{
	int currH;
	if (isFree(board, i1, j))
	{
		board[i1][j] = ai;
		currH = hFunc(board);
		if (currH < bestH)
		{
			bestH = currH;
			bestMove[0] = i1;
			bestMove[1] = j;
			r1 = i;
			r2 = j;
		}
		board[i1][j] = 0;
	}
	if (isFree(board, i2, j))
	{
		board[i2][j] = ai;
		currH = hFunc(board);
		if (currH < bestH)
		{
			bestH = currH;
			bestMove[0] = i2;
			bestMove[1] = j;
			r1 = i;
			r2 = j;
		}
		board[i2][j] = 0;
	}
	if (isFree(board, 1, 1))
	{
		board[1][1] = ai;
		currH = hFunc(board);
		if (currH < bestH)
		{
			bestH = currH;
			bestMove[0] = 1;
			bestMove[1] = 1;
			r1 = i;
			r2 = j;
		}
		board[1][1] = 0;
	}
	return bestH;
}
void AImove2(int board[][3], bool isMaxPl)
{
	int currH;
	int bestH;
	int bestMove[2];


	int r1, r2;

	if (isMaxPl)
		bestH = MIN;
	else
		bestH = MAX;

	if (isMaxPl)
	{
		if (board[0][0] == ai)
		{
			bestH = checkH1Max(board,bestH, bestMove, 0, 0, 1, 1, r1, r2);
		}
		if (board[0][2] == ai)
		{
			bestH = checkH1Max(board, bestH, bestMove, 0, 2, 1, 1, r1, r2);
		}
		if (board[2][0] == ai)
		{
			bestH = checkH1Max(board, bestH, bestMove, 2, 0, 1, 1, r1, r2);
		}
		if (board[2][2] == ai)
		{
			bestH = checkH1Max(board, bestH, bestMove, 2, 2, 1, 1, r1, r2);
		}

		if (board[1][0] == ai)
		{
			checkH3Max(board, bestH, bestMove, 1, 0, 0, 2, r1, r2);
		}
		if(board[1][2] == ai)
		{
			checkH3Max(board, bestH, bestMove, 1, 2, 0, 2, r1, r2);
		}
		if (board[0][1] == ai)
		{
			checkH2Max(board, bestH, bestMove, 0, 1, 0, 2, r1, r2);
		}
		if (board[2][1] == ai)
		{
			checkH2Max(board, bestH, bestMove, 2, 1, 0, 2, r1,r2);
		}

		
		if (board[1][1] == ai)
		{
			for (int l = 0; l < N; l++)
			{
				for (int k = 0; k < N; k++)
				{
					if (isFree(board, l, k))
					{
						board[l][k] = ai;
						currH = hFunc(board);
						if (currH > bestH)
						{
							bestH = currH;
							bestMove[0] = l;
							bestMove[1] = k;
							r1 = 1;
							r2 = 1;
						}
						board[l][k] = 0;
					}
				}
			}
		}



	}
	else
	{
		//same but for min <
		if (board[0][0] == ai)
		{
			bestH = checkH1Min(board, bestH, bestMove, 0, 0, 1, 1, r1, r2);
		}
		if (board[0][2] == ai)
		{
			bestH = checkH1Min(board, bestH, bestMove, 0, 2, 1, 1, r1, r2);
		}
		if (board[2][0] == ai)
		{
			bestH = checkH1Min(board, bestH, bestMove, 2, 0, 1, 1, r1, r2);
		}
		if (board[2][2] == ai)
		{
			bestH = checkH1Min(board, bestH, bestMove, 2, 2, 1, 1, r1, r2);
		}

		if (board[1][0] == ai)
		{
			checkH3Min(board, bestH, bestMove, 1, 0, 0, 2, r1, r2);
		}
		if (board[1][2] == ai)
		{
			checkH3Min(board, bestH, bestMove, 1, 2, 0, 2, r1, r2);
		}
		if (board[0][1] == ai)
		{
			checkH2Min(board, bestH, bestMove, 0, 1, 0, 2, r1, r2);
		}
		if (board[2][1] == ai)
		{
			checkH2Min(board, bestH, bestMove, 2, 1, 0, 2, r1, r2);
		}
		if (board[1][1] == ai)
		{
			for (int l = 0; l < N; l++)
			{
				for (int k = 0; k < N; k++)
				{
					if (isFree(board, l, k))
					{
						board[l][k] = ai;
						currH = hFunc(board);
						if (currH < bestH)
						{
							bestH = currH;
							bestMove[0] = l;
							bestMove[1] = k;
							r1 = 1;
							r2 = 1;
						}
						board[l][k] = 0;
					}
				}
			}
		}
		
	}
	
	int i = bestMove[0];
	int j = bestMove[1];
	board[r1][r2] = 0;
	board[i][j] = ai;
	
}

void AImove(int board[][3],int alpha, int beta, int moves,bool isMaxPl)
{
	int bestH =0;
	int currH = 0;

	int bestMove[2];

	if (isMaxPl)
		bestH = MIN;
	else
		bestH = MAX;
	
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (board[i][j] == 0)
				{
					board[i][j] = ai;

					if (isMaxPl)
					{
						currH = minimax(board, alpha, beta, moves, false);
						board[i][j] = 0;
						if (currH > bestH)
						{
							bestH = currH;
							bestMove[0] = i;
							bestMove[1] = j;
							
						}

					}
					else
					{
						currH = minimax(board, alpha, beta, moves, true);
						board[i][j] = 0;
						if (currH < bestH)
						{
							bestH = currH;
							bestMove[0] = i;
							bestMove[1] = j;

						}
					}
				}
			}
		}
	
	int i = bestMove[0];
	int j = bestMove[1];
	board[i][j] = ai;
}
int minimax(int board[][3],int alpha, int beta, int moves, bool isMaxPl)
{
	int result = checkForWinner(board);
	if (result != 0)
	{
		return result;
	}
	int currH;
	int bestH = MIN;
	
	if (isMaxPl)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (board[i][j] == 0)
				{
					board[i][j] = 1;
					moves++;
					currH = hFunc(board);
					minimax(board, alpha, beta, moves, false);
					board[i][j] = 0;
					moves--;
					bestH = std::max(bestH, currH);
					alpha = std::max(alpha, currH);
					if (beta <= alpha)
						return bestH;

				}
			}
		}
		return bestH;
	}
	else
	{
		int currH;
		int bestH = MAX;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (board[i][j] == 0)
				{
					board[i][j] = -1;
					moves++;
					currH = hFunc(board);
					minimax(board, alpha, beta, moves, true);
					board[i][j] = 0;
					moves--;
					bestH = std::min(bestH, currH);
					beta = std::min(beta, currH);
					if (beta <= alpha)
						return bestH;
				}
			}
		}
		return bestH;
		
	}
}

int checkForWinner(int b[][3])
{
	//check diagonals
	if (((b[0][0] == b[1][1] && b[1][1] == b[2][2]) ||
		(b[0][2] == b[1][1] && b[1][1] == b[2][0])) && b[1][1] !=0)
	{
		return b[1][1];
	}
	//check corners
	if (b[1][0] == b[0][0] && b[0][0] == b[0][1] && b[0][0] != 0)
	{
		return b[0][0];
	}

	if (b[0][1] == b[0][2] && b[0][2] == b[1][2] && b[0][2] != 0)
	{
		return b[0][2];
	}

	if (b[1][2] == b[2][2] && b[2][2] == b[2][1] && b[2][2] != 0)
	{
		return b[2][2];
	}
	if (b[2][1] == b[2][0] && b[2][0] == b[1][0] && b[2][0] != 0)
	{
		return b[2][0];
	}

	//check rows and cols
	for (int i = 0; i < N; i++)
	{
		if (b[i][0] == b[i][1] && b[i][1] == b[i][2] && b[i][1] != 0)
		{
			return b[i][1];
		}

	}
	for (int i = 0; i < N; i++)
	{
		if (b[0][i] == b[1][i] && b[1][i] == b[2][i] && b[1][i] != 0)
		{
			return b[0][i];
		}

	}
	return 0;
}
int hFunc(int b[][3])
{
	int h = 0;
	//sum of d1
	if((b[0][0] == 0 || b[1][1] == 0 || b[2][2] == 0) || 
		(b[0][0] == b[1][1] && b[1][1] == b[2][2]))
		h += b[0][0] + b[1][1] + b[2][2];
	//sum of d1
	if ((b[0][2] == 0 || b[1][1] == 0 || b[2][0] == 0) ||
		(b[0][2] == b[1][1] && b[1][1]== b[2][0]))
		h += b[0][2] + b[1][1] + b[2][0];

	//sum of rows
	for (int i = 0; i < N; i++)
	{
		if((b[i][0] == 0 || b[i][1] == 0 || b[i][2] == 0) ||
			(b[i][0] == b[i][1] && b[i][1] == b[i][2]))
			h += b[i][0] + b[i][1] + b[i][2];
		
	}
	//sum of cols
	for (int i = 0; i < N; i++)
	{
		if ((b[0][i] == 0 || b[1][i] == 0 || b[2][i] == 0) ||
			(b[0][i] == b[1][i] && b[1][i] == b[2][i]))
			h += b[0][i] + b[1][i] + b[2][i];

	}
	//sum of edge 1
	if ((b[0][0] == 0 || b[0][1] == 0 || b[1][0] == 0) ||
		(b[0][0] == b[0][1] && b[0][1] == b[1][0]))
		h += b[0][0] + b[0][1] + b[1][0];
	//sum of edge 2
	if ((b[1][0] == 0 || b[2][0] == 0 || b[2][1] == 0) ||
		(b[1][0] == b[2][0] && b[2][0] == b[2][1]))
		h += b[1][0] + b[2][0] + b[2][1];
	//sum of edge 3
	if ((b[2][1] == 0 || b[2][2] == 0 || b[1][2] == 0) ||
		(b[2][1] == b[2][2] && b[2][2] == b[1][2]))
		h += b[2][1] + b[2][2] + b[1][2];
	//sum of edge 4
	if ((b[0][1] == 0 || b[0][2] == 0 || b[1][2] == 0) ||
		(b[0][1] == b[0][2] && b[0][2] == b[1][2]))
		h += b[0][1] + b[0][2] + b[1][2];

	return h;

}
void printBoard(int board[][3])
{
	std::cout << "   " << board[0][1] << std::endl;
	std::cout << " " << board[0][0] << "   " << board[0][2] << std::endl;
	std::cout << board[1][0] << "  " << board[1][1] << "  " << board[1][2];
	std::cout << std::endl; 
	std::cout << " " << board[2][0] << "   " << board[2][2] << std::endl;
	std::cout << "   " << board[2][1] << std::endl;
	
}
bool isFree(int board[][3], int m1, int m2)
{
	if (board[m1][m2] == 0)
		return true;
	else
		return false;
}





