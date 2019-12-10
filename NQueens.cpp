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
	int board[8] = {1, 3, 0, 2, 4, 7, 5, -1};

	cout << "start board:" << endl;
	printBoard(board, n);

	nextLegalPosition(board, n);
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
 *
 */

int backtrack (int* board, int n, int row) {

	cout << "in backtrack for row: " << row << endl;
	printBoard(board, n);

	// the current row is in the last column - backtrack previous row
	if (board[row] == n - 1) {
		for (int i = row; i < n; i++) {
			board[i] = -1;
		}
		return backtrack(board, n, row-1);
	}

	// find legal solution for the current row
	for (int col = board[row]+1; col < n; col++) {
		board[row] = col;
		cout << "trying new board in backtrack:" << endl;
		printBoard(board, n);
		if (isLegalPosition(board, n)) {
			return 1;
		}
	}

	cout << "after backtrack:" << endl;
	printBoard(board, n);

	// reset the rest of the board after the current row
	for (int i = row; i < n; i++) {
		board[i] = -1;
	}

	return backtrack(board, n, row-1);
}



/*
 * TODO
 *
 * case 1: full legal solution
 * 	backtrack until a legal board is found
 *
 * case 2: partial legal solution
 * 	add queen to next empty row
 * 	if not possible, backtrack until a legal board is found
 *
 * case 3: partial illegal solution
 * 	change queen in the last full row
 * 	if not possible, backtrack until a legal board is found
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
		cout << "found legal full board" << endl;
		return backtrack(board, n, row);
	}

	// case 2: partial legal solution
	else if (isLegalPosition(board, n)) {
		cout << "partial legal solution for row: " << row << endl;

		// try to add a queen to the next empty row
		for (int col = 0; col < n; col++) {
			board[row+1] = col;
			if (isLegalPosition(board, n)) {
				printBoard(board, n);
				return 1;
			}
		}

		// if it wasn't possible, backtrack
		board[row+1] = -1;
		printBoard(board, n);
		cout << "calling backtrack for row: " << row << endl;
		return backtrack(board, n, row);
	}

	// case 3: partial illegal solution
	else {
		cout << "partial illegal solution" << endl;
		if (board[row] < n-1) {
			board[row]++;
			printBoard(board, n);
			if (isLegalPosition(board, n)) {
				return 1;
			}
			else
				return nextLegalPosition(board, n);
		}
		else {
			return backtrack(board, n, row);
		}
	}
	return 0;
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
