//============================================================================
// Name        : nQueens.cpp
// Author      : Imogen Cleaver-Stigum & Jyalu Wu
// Version     :
// Copyright   : 2019 IMOLU
// Description : 
//============================================================================

#include <iostream>

using namespace std;

// this is not a header file 
int isLegalPosition (int* board, int n);
int main();



int main() {
	int n = 8;
	int board[8] = {1, 0, -1, -1, -1, -1, -1, -1};

	return 0;
}


int isLegalPosition (int* board, int n) {
	int isLegal = 1;
	// assume there are no same-row queens since the queens are places row-by-row
	for (int i = 0; i < n; i++) {
		
		for (int j = 0; j < n; j++) { // check for same-column queens
			if (board[i] == board[j] && board[i] != -1 && i != j) { 
				isLegal = 0;
			}
		}
		if (i < n-1) { // check for same-diagonal queens on negative-slope diagonals
			if (board[i] == board[i+1]-1 && board[i]!= -1 && board[i+1] != -1) { 
				isLegal = 0;
			}
		}
		if (i > 0) { // check for same-diagonal queens on positive-slope diagonals
			if (board[i] == board[i-1]-1 && board[i]!= -1 && board[i-1] != -1) {
				isLegal = 0;
			}
		}
	}
	return isLegal;
}
		
