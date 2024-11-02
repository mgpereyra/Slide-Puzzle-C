#include "SlidePuzzle.h"

void initializePuzzle(PuzzleGame *game) {
    int value = 1;
    srand(time(NULL)); // Doing some tests and some research, if we don't use this function it will always show the same matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            game->matrix[i][j] = (value < 9) ? value++ : 0;
        }
    }
    game->emptyRow = SIZE - 1;
    game->emptyCol = SIZE - 1;
    game->moves = 0;

    // Shuffle until solvable
    do {
        shuffleMatrix(game);
    } while (!isSolvable(game->matrix));
}

void shuffleMatrix(PuzzleGame *game) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int i1 = rand() % SIZE;
            int j1 = rand() % SIZE;
            swap(&game->matrix[i][j], &game->matrix[i1][j1]);
        }
    }
    // Update empty space position after shuffle
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game->matrix[i][j] == 0) {
                game->emptyRow = i;
                game->emptyCol = j;
                return;
            }
        }
    }
}

// Another thing I noticed is that if we don't check the inversions, the game might be unsolvable!
int isSolvable(int matrix[SIZE][SIZE]) {
    int flat[SIZE * SIZE];
    int k = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            flat[k++] = matrix[i][j];
        }
    }
    int inversions = countInversions(flat, SIZE * SIZE);
    return (inversions % 2 == 0);
}

int countInversions(int arr[], int n) {
    int invCount = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] && arr[j] && arr[i] > arr[j])
                invCount++;
        }
    }
    return invCount;
}

// Shows the matrix
void displayMatrix(PuzzleGame *game) {
    printf("Current puzzle state (Moves: %d):\n", game->moves);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game->matrix[i][j] == 0)
                printf("   ");
            else
                printf("%2d ", game->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int isSolved(PuzzleGame *game) {
    int value = 1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == SIZE - 1 && j == SIZE - 1)
                return game->matrix[i][j] == 0;
            if (game->matrix[i][j] != value++)
                return 0;
        }
    }
    return 1;
}

int moveTile(PuzzleGame *game, int tile) {
    int tileRow, tileCol;
    if (!findTile(game, tile, &tileRow, &tileCol))
        return 0;

    // Check if tile is adjacent to the empty space
    if ((tileRow == game->emptyRow && abs(tileCol - game->emptyCol) == 1) ||
        (tileCol == game->emptyCol && abs(tileRow - game->emptyRow) == 1)) {
        swap(&game->matrix[tileRow][tileCol], &game->matrix[game->emptyRow][game->emptyCol]);
        game->emptyRow = tileRow;
        game->emptyCol = tileCol;
        return 1;
    }
    return 0;
}

int findTile(PuzzleGame *game, int tile, int *tileRow, int *tileCol) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game->matrix[i][j] == tile) {
                *tileRow = i;
                *tileCol = j;
                return 1;
            }
        }
    }
    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
