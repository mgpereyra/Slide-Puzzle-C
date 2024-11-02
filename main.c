#include "SlidePuzzle.h"

int main() {
    PuzzleGame game;
    initializePuzzle(&game);

    while (!isSolved(&game)) {
        system("cls");
        printf("Welcome to the 3x3 Puzzle Game!\nArrange the numbers from 1 to 8 in order with 0 as the empty space.\n");
        displayMatrix(&game);

        int tile;
        printf("Enter the number you want to move (1-8): ");
        if (scanf("%d", &tile) != 1 || tile < 1 || tile > 8) {
            printf("Invalid input! Please enter a number between 1 and 8.\n");
            while (getchar() != '\n'); // Clear input buffer
            printf("Press any key to continue...\n");
            getchar(); // Pause until a key is pressed
            continue; // Restart the loop
        }

        if (!moveTile(&game, tile)) {
            printf("Invalid move! Tile %d is not adjacent to the empty space.\n\n", tile);
            while (getchar() != '\n'); // Clear input buffer
            printf("Press any key to continue...\n");
            getchar(); // Pause until a key is pressed
        } else {
            game.moves++;
        }
    }
    system("cls");
    printf("Congratulations! You solved the puzzle in %d moves!\n\n", game.moves);
    displayMatrix(&game);
    return 0;
}
