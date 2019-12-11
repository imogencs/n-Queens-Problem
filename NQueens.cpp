//============================================================================
// Name        : NQueens.cpp
// Author      : Imogen Cleaver-Stigum & Jyalu Wu
// Version     :
// Copyright   : 2019 IMOLU
// Description :
//============================================================================

#include <iostream>
#include "NQueens.h"

using namespace std;

int main() {

	int n = 8;
	int numSols = 0;


//	findCompleteBoards();

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
		if (row < n-1) { // check for same-diagonal queens on negative-slope diagonals
			if (board[row] == board[row+1]-1 && board[row]!= -1 && board[row+1] != -1) {
				isLegal = 0;
			}
		}
		if (row > 0) { // check for same-diagonal queens on positive-slope diagonals
			if (board[row] == board[row-1]-1 && board[row]!= -1 && board[row-1] != -1) {
				isLegal = 0;
			}
		}
	}
	return isLegal;
}




/*
 * Returns 1 if a legal solution was found, 0 otherwise.
 */

int backtrack (int* board, int n, int row) {

	//cout << "in backtrack for row: " << row << endl;
	//printBoard(board, n);

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
		//cout << "trying new board in backtrack:" << endl;
		//printBoard(board, n);
		if (isLegalPosition(board, n)) {
			return 1;
		}
	}

	//cout << "after backtrack:" << endl;
	//printBoard(board, n);

	// reset the rest of the board after the current row
	for (int i = row; i < n; i++) {
		board[i] = -1;
	}

	return backtrack(board, n, row-1);
}





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
		//cout << "found legal full board" << endl;
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
		//cout << "partial illegal solution" << endl;
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





void findCompleteBoards () {
	int* board;

	for (int boardSize = 4; boardSize <= 100; boardSize++) {
		board = new int[boardSize];
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
 * Finds all solutions to then-Queens Problem for a particular n and
 * prints them out in lexicographical order.
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

		if (!allSolutionsFound) {
			numSolutions++;
			printBoard(board, n);
			allSolutionsFound = !nextLegalPosition(board, n);
		}
	}
	return numSolutions;
}




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
		cout << board[i] << " " ;
	}
	cout << ")" << endl;
}




