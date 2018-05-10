#include<bits/stdc++.h>
#include<iostream>


using namespace std;

#define SMALL 0
#define MEDIUM 1
#define LARGE 2
#define MAXSIDE 25
#define MAXMINES 99
#define MOVESIZE 526

int SIDE ;
int MINES ;

// check cell validity
bool isValid(int row, int col)
{
	// returns true if (r,c) is valid
	return (row >= 0) && (row < SIDE) &&
		(col >= 0) && (col < SIDE);
}

// check whether mine is in cell
bool isMine (int row, int col, char board[][MAXSIDE])
{
	if (board[row][col] == '*')
		return (true);
	else
		return (false);
}

// get user's move
void makeMove(int *x, int *y)
{
	// Take the input move
	printf("Enter the coordinates of your move: ");
	scanf("%d %d", x, y);
	return;
}

// print updated board
void printBoard(char myBoard[][MAXSIDE])
{
	int i, j;

	printf (" ");

	for (i=0; i<SIDE; i++)
		printf ("%d ", i);

	printf ("\n\n");

	for (i=0; i<SIDE; i++)
	{
		printf ("%d ", i);

		for (j=0; j<SIDE; j++)
			printf ("%c ", myBoard[i][j]);
		printf ("\n");
	}
	return;
}

// count nearby mines
int countMines(int row, int col, int mines[][2], 
					char realBoard[][MAXSIDE])
{

	int i;
	int count = 0;


//check northern neighbor

		if (isValid (row-1, col) == true)
		{
			if (isMine (row-1, col, realBoard) == true)
			count++;
		}

//check southern neighbor

		if (isValid (row+1, col) == true)
		{
			if (isMine (row+1, col, realBoard) == true)
			count++;
		}

//check eastern neighbor

		if (isValid (row, col+1) == true)
		{
			if (isMine (row, col+1, realBoard) == true)
			count++;
		}

//check western neighbor

		// Only process this cell if this is a valid one
		if (isValid (row, col-1) == true)
		{
			if (isMine (row, col-1, realBoard) == true)
			count++;
		}

//check northeastern neighbor

		if (isValid (row-1, col+1) == true)
		{
			if (isMine (row-1, col+1, realBoard) == true)
			count++;
		}

//check northwestern neighbor

		if (isValid (row-1, col-1) == true)
		{
			if (isMine (row-1, col-1, realBoard) == true)
			count++;
		}

//check southeastern neighbor

		if (isValid (row+1, col+1) == true)
		{
			if (isMine (row+1, col+1, realBoard) == true)
			count++;
		}

//check southwestern neighbor

		if (isValid (row+1, col-1) == true)
		{
			if (isMine (row+1, col-1, realBoard) == true)
			count++;
		}

	return (count);
}

//did you step on a mine? no? yes?
bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE],
			int mines[][2], int row, int col, int *movesLeft)
{

	if (myBoard[row][col] != '-')
		return (false);

	int i, j;

    //opened a mine?
	if (realBoard[row][col] == '*')
	{
		myBoard[row][col]='*';

		for (i=0; i<MINES; i++)
			myBoard[mines[i][0]][mines[i][1]]='*';

        system("clear"); // clear the screen
		printBoard (myBoard);
        //source of ascii mushroom: https://stackoverflow.com/questions/37765925/ascii-art-in-c
        std::cout << R"(
                     _.-^^---....,,--
                 _--                  --_
                <         B O O M!       >)
                |        GAME OVER!       |
                 \._                   _./
                    ```--. . , ; .--'''
                          | |   |
                       .-=||  | |=-.
                       `-=#$%&%$#=-'
                          | ;  :|
                 _____.,-#%&$@%#&#~,._____ 

)" << '\n';
		return (true) ;
	}

	else
	{
		//find number of mine neighbors
		int count = countMines(row, col, mines, realBoard);
		(*movesLeft)--;

		myBoard[row][col] = count + '0';

		if (!count) {

//northern neighbor
			if (isValid (row-1, col) == true)
			{
				if (isMine (row-1, col, realBoard) == false)
				playMinesweeperUtil(myBoard, realBoard, mines, row-1, col, movesLeft);
			}

//southern neighbor

			if (isValid (row+1, col) == true)
			{
				if (isMine (row+1, col, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col, movesLeft);
			}

//eastern neighbor
			if (isValid (row, col+1) == true)
			{
				if (isMine (row, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col+1, movesLeft);
			}

//western neighbor
			if (isValid (row, col-1) == true)
			{
				if (isMine (row, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col-1, movesLeft);
			}

//northeastern neighbor
			if (isValid (row-1, col+1) == true)
			{
				if (isMine (row-1, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col+1, movesLeft);
			}

//northwestern neighbor
			if (isValid (row-1, col-1) == true)
			{
				if (isMine (row-1, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col-1, movesLeft);
			}

//southeastern neighbor
			if (isValid (row+1, col+1) == true)
			{
				if (isMine (row+1, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col+1, movesLeft);
			}

//southwestern neighbor
			if (isValid (row+1, col-1) == true)
			{
				if (isMine (row+1, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col-1, movesLeft);
			}
		}

		return (false);
	}
}

// put mines somewhere
void placeMines(int mines[][2], char realBoard[][MAXSIDE])
{
	bool mark[MAXSIDE*MAXSIDE];

	memset (mark, false, sizeof (mark));

	//make some mines
	for (int i=0; i<MINES; )
	{
		int random = rand() % (SIDE*SIDE);
		int x = random / SIDE;
		int y = random % SIDE;

		//add a mine
		if (mark[random] == false)
		{
			//mine row
			mines[i][0]= x;
			//mine column
			mines[i][1] = y;

			//display the mine
			realBoard[mines[i][0]][mines[i][1]] = '*';
			mark[random] = true;
			i++;
		}
	}

	return;
}

//initialize the game
void initialise(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE])
{

	srand(time (NULL));

	//clear board
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
		{
			myBoard[i][j] = realBoard[i][j] = '-';
		}
	}

	return;
}

//replace some mines
void replaceMine (int row, int col, char board[][MAXSIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
			{
				if (board[i][j] != '*')
				{
					board[i][j] = '*';
					board[row][col] = '-';
					return;
				}
			}
	}
	return;
}

//implement the sweeping of mines!
void playMinesweeper ()
{

	bool gameOver = false;


	char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE];

	int movesLeft = SIDE * SIDE - MINES, x, y;
	int mines[MAXMINES][2];

	initialise (realBoard, myBoard);


	placeMines (mines, realBoard);

	int currentMoveIndex = 0;
	while (gameOver == false)
	{
                system("clear"); // clear the screen before re-drawing board

		printf ("Open a space. The number tells you how many mines there are in adjacent spaces. \n");
		printBoard (myBoard);
		makeMove (&x, &y);


		if (currentMoveIndex == 0)
		{
			if (isMine (x, y, realBoard) == true)
				replaceMine (x, y, realBoard);
		}

		currentMoveIndex ++;

		gameOver = playMinesweeperUtil (myBoard, realBoard, mines, x, y, &movesLeft);

		if ((gameOver == false) && (movesLeft == 0))
		{
			printf ("\nYou won !\n");
			gameOver = true;
		}
	}
	return;
}

//choose board size
void boardSize ()
{

	int level;

	printf ("Choose Your Board Size\n");
	printf ("Enter 0: 9 x 9 Cells and 10 Mines\n");
	printf ("Enter 1: 16 x 16 Cells and 40 Mines\n");
	printf ("Enter 2: 24 x 24 Cells and 99 Mines\n");

	scanf ("%d", &level);

	if (level == SMALL)
	{
		SIDE = 9;
		MINES = 10;
	}

	if (level == MEDIUM)
	{
		SIDE = 16;
		MINES = 40;
	}

	if (level == LARGE)
	{
		SIDE = 24;
		MINES = 99;
	}

	return;
}

//sweep some mines!
int main()
{

	boardSize();

	playMinesweeper();

	return (0);
}
