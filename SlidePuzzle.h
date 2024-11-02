#ifndef SLIDEPUZZLE_H_INCLUDED
#define SLIDEPUZZLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

typedef struct {
    int matrix[SIZE][SIZE];
    int emptyRow;
    int emptyCol;
    int moves;
} PuzzleGame;

void initializePuzzle(PuzzleGame *game);
void shuffleMatrix(PuzzleGame *game);
int isSolvable(int matrix[SIZE][SIZE]);
int countInversions(int arr[], int n);
void displayMatrix(PuzzleGame *game);
int isSolved(PuzzleGame *game);
int moveTile(PuzzleGame *game, int tile);
void swap(int *a, int *b);
int findTile(PuzzleGame *game, int tile, int *tileRow, int *tileCol);

#endif // SLIDEPUZZLE_H_INCLUDED
