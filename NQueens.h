/*
 * NQueens.h
 *
 *  Created on: Dec 10, 2019
 *      Author: Jyalu
 */

#ifndef NQUEENS_H_
#define NQUEENS_H_

int backtrack (int* board, int n, int row);
int nextLegalPosition(int* board, int n);
void printBoard(int* board, int n);

#endif /* NQUEENS_H_ */
