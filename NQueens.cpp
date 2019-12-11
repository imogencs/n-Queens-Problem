//============================================================================
// Name        : NQueens.cpp
// Author      : Imogen Cleaver-Stigum & Jyalu Wu
// Version     :
// Copyright   : ©2019 IMOLU
// Description :
//============================================================================

#include <iostream>
#include "NQueens.h"

using namespace std;

/*
 * Runs the program for the n-Queens project. It finds the first complete
 * boards for n=4 to n=20, then finds all the solutions for a particular
 * n-Queens problem, for which the n is specified by the user.
 *
 * The boards start from index 0 instead of 1 like they do in the directions.
 */
int main() {

	int n = 8;
	int numSols = 0;


	findCompleteBoards();

	cout << "Enter in a number 4 <= n <= 20: ";
	cin >> n;

	numSols = findAllSolutions(n);
	cout << "total number of solutions: " << numSols << endl;

	return 0;
}



/*
 * Returns true if no two queens attack each other in the given board.
 * @param board, The given board
 * @param n, The size of the board
 * @return 1 if no two queens attack each other, 0 otherwise
 */
int isLegalPosition (int* board, int n) {
	int isLegal = 1;

	// assume there are no same-row queens since the queens are places row-by-row
	for (int row = 0; row < n; row++) {

		for (int j = 0; j < n; j++) { // check for same-column queens
			if (board[row] == board[j] && board[row] != -1 && row != j) {
				isLegal = 0;
			}
		}

		// check for positive slope diagonal queens
		for (int i = 0; i < row; i++) {
			if (i + board[i] == row + board[row] && board[row] != -1 && board[i] != -1) {
				return 0;
			}
		}

		// check for negative slope diagonal queens
		for (int i = 0; i < row; i++) {
			if (i - board[i] == row - board[row] && board[row] != -1 && board[i] != -1) {
				return 0;
			}
		}
	}
	return isLegal;
}




/*
 * This function performs a backtrack for the given board.
 * @param board, The given board
 * @param n, The size of the board
 * @param row, The last full row
 * @return 1 if a legal solution was found, 0 otherwise.
 */
int backtrack (int* board, int n, int row) {
	// the current row is in the last column - backtrack previous row
	if (board[row] == n - 1) {
		for (int i = row; i < n; i++) {
			board[i] = -1;
		}
		if (row == 0) {
			return 0;
		}
		return backtrack(board, n, row-1);
	}

	// find legal solution for the current row
	for (int col = board[row]+1; col < n; col++) {
		board[row] = col;
		if (isLegalPosition(board, n)) {
			return 1;
		}
	}

	// reset the rest of the board after the current row
	for (int i = row; i < n; i++) {
		board[i] = -1;
	}

	return backtrack(board, n, row-1);
}




/*
 * Finds the next legal position for the board by either adding a queen
 * into the next empty row or by backtracking.
 * @param board, The given board
 * @param n, The size of the board
 * @return 0 if no legal position could be found, 1 otherwise
 */
int nextLegalPosition(int* board, int n) {
	int row = -1;

	// find out which row was the last row filled
	for (int i = 0; i < n; i++) {
		if (board[i] != -1) {
			row = i;
		}
	}

	// case 1: full, legal solution
	if (isLegalPosition(board, n) && row == n-1) {
		return backtrack(board, n, row);

	}

	// case 2: partial legal solution
	else if (isLegalPosition(board, n)) {

		// try to add a queen to the next empty row
		for (int col = 0; col < n; col++) {
			board[row+1] = col;
			if (isLegalPosition(board, n)) {
				return 1;
			}
		}

		// if it wasn't possible, backtrack
		board[row+1] = -1;
		return backtrack(board, n, row);
	}

	// case 3: partial illegal solution
	else {
		if (board[row] < n-1) {
			board[row]++;
			//printBoard(board, n);
			if (isLegalPosition(board, n)) {
				return 1;
			}
			else {
				return nextLegalPosition(board, n);
			}
		}
		else {
			return backtrack(board, n, row);
		}
	}
	return 0;
}




/*
 * Finds the first complete board for all the n-Queens problems
 * from n=4 to n=20. It becomes extremely slow after about n=22
 * so please make sure that your computer does not work too hard!
 */
void findCompleteBoards () {
	for (int boardSize = 4; boardSize <= 20; boardSize++) {
		int* board = new int[boardSize];
		for (int i = 0; i < boardSize; i++) {
			board[i] = -1;
		}
		while (!isFull(board, boardSize)) {
			nextLegalPosition(board, boardSize);
		}
		cout << "First complete board for n = " << boardSize << endl;
		printBoard(board, boardSize);
	}
}


/*
 * Finds all solutions to the n-Queens Problem for a particular n and
 * prints them out in lexicographical order.
 * @n, The size of the board
 * @return The number of solutions
 */
int findAllSolutions(int n) {
	int allSolutionsFound = 0;
	int numSolutions = 0;
	int* board = new int[n];

	for (int i = 0; i < n; i++) {
		board[i] = -1;
	}

	while (!allSolutionsFound) {
		while (!allSolutionsFound && !isFull(board, n)) {
			allSolutionsFound =	!nextLegalPosition(board, n);
		}

		if (isLegalPosition(board, n) && !allSolutionsFound) {
			numSolutions++;
			printBoard(board, n);
			allSolutionsFound = !nextLegalPosition(board, n);
		}
	}
	return numSolutions;
}



/*
 * Checks to see whether or not the given board is full.
 * @param board, The given board
 * @param n, The size of the board
 * @return 1 if the board is full, 0 otherwise
 */
int isFull (int* board, int n) {
	int boardIsFull = 1;

	for (int i = 0; i < n; i++) {
		if (board[i] == -1) {
			boardIsFull = 0;
		}
	}
	return boardIsFull;
}


/*
 * In the given board, for each row, the function prints out the column
 * that the queen is in. If there is no queen in that column, it prints -1.
 * @param board, The given board
 * @param n, The size of the board
 */
void printBoard(int* board, int n) {
	cout << "(";
	for (int i = 0; i < n; i++) {

		cout << board[i];
		if (i != n-1)
			cout << " " ;
	}
	cout << ")" << endl;
}
