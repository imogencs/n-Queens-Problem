//============================================================================
// Name        : NQueens.h
// Author      : Imogen Cleaver-Stigum & Jyalu Wu
// Version     :
// Copyright   : 2019 IMOLU
// Description :
//============================================================================

#ifndef NQUEENS_H_
#define NQUEENS_H_

int isLegalPosition (int* board, int n);
int backtrack (int* board, int n, int row);
int nextLegalPosition(int* board, int n);
void findCompleteBoards ();
int findAllSolutions(int n);
int isFull (int* board, int n);
void printBoard(int* board, int n);


#endif /* NQUEENS_H_ */
