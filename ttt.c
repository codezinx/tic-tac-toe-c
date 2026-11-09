#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int row;
    int column;
} coord;

coord getPlayerInput(char grid[3][3]);
coord getComputerInput(char grid[3][3]);
void drawGrid(char grid[3][3]);
int getPlayer(char mark);
int checkWinner(char grid[3][3]);

int main() {
    // Seed random number generator
    srand(time(NULL));

    // Define grid and key variables
    char grid[3][3] = {{' ', ' ', ' '},
                       {' ', ' ', ' '},
                       {' ', ' ', ' '}};
    
    int playerTurn = 1;
    int playComputer = 0; // 1 = player, 2 = computer
    int winner = 0;
    int freeSquares = 9;

    // Show grid positions to aid player

    puts("TIC TAC TOE\n");
    printf(" 1 | 2 | 3 \n");
    printf("-----------\n");
    printf(" 4 | 5 | 6 \n");
    printf("-----------\n");
    printf(" 7 | 8 | 9 \n\n");

    // Ask user whether they want to play against a friend or the computer repeatedly

    int ch;

    while (playComputer != 1 && playComputer != 2 && playComputer != 3) {
        // Play against a friend or the computer

        puts("Do you want to play against a friend or the computer?\n");
        puts("1. Friend (person)");
        puts("2. Computer");
        puts("3. Quit\n");
        printf("Enter your selection: ");

        // Collect input and validate correct data type
    
        if (scanf("%d", &playComputer) != 1) {
            // Invalid input. Clear buffer.
            while ((ch = getchar()) != '\n' && ch != EOF) ;
            puts("Invalid input. Please try again.\n");
        }

        puts("");

        // Validate if input is correct

        if (playComputer != 1 && playComputer != 2 && playComputer != 3)
            puts("Invalid input. Please try again.\n");
        else if (playComputer == 3)
            exit(1);
    }

    // Get player input

    while (freeSquares > 0 && winner == 0) {
        drawGrid(grid);
        printf("\nPlayer %d's turn\n", playerTurn);
        coord selection;

        if (playComputer == 1 || playerTurn == 1)
            selection = getPlayerInput(grid);
        else
            selection = getComputerInput(grid);

        puts(""); // Print a newline to fix formatting issues

        if (selection.row == -1 && selection.column == -1) {
            puts("Invalid input\n");
            continue;
        }
       
        // Place mark, switch turn, check for win or draw

        if (playerTurn == 1) {
            grid[selection.row][selection.column] = 'X';
            playerTurn = 2;
        }
        else {
            grid[selection.row][selection.column] = 'O';
            playerTurn = 1;
        }

        freeSquares--;
        winner = checkWinner(grid);
    }

    // Draw the grid again to see the glorious victory

    drawGrid(grid);
    puts("");

    // Who won?

    switch (winner) {
        case 1:
            puts("Player 1 wins");
            break;
        case 2:
            puts("Player 2 wins");
            break;
        case 0:
            puts("Draw");
            break;
    }

    return 0;
}

coord getPlayerInput(char grid[3][3]) {
    // Value gotten
    int value = 0;
    int ch;

    // Make error variable in advance in cases of invalid input
    coord error;
    error.row = -1;
    error.column = -1;

    // Ask for input with validation
    printf("Enter a value between 1-9: ");

    // Collect input
    if (scanf("%d", &value) != 1) {
        // Invalid input. Clear buffer.
        while ((ch = getchar()) != '\n' && ch != EOF) ;
        puts("");
        return error;
    }

    puts("");

    // Validate input 
    if (value < 1 || value > 9)
        return error;

    // Convert input to list coordinates {row, column}
    int rowVals[] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
    int colVals[] = {0, 1, 2, 0, 1, 2, 0, 1, 2};

    coord result;
    result.row = rowVals[value - 1];
    result.column = colVals[value - 1];

    // Validate input again, make sure spot isn't taken

    if (grid[result.row][result.column] != ' ')
        return error;

    return result;
}

coord getComputerInput(char grid[3][3]) {
    // Store tic-tac-toe list coordinates 
    int rowVals[] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
    int colVals[] = {0, 1, 2, 0, 1, 2, 0, 1, 2};

    // Generate a random row and column value until a free square is found. Set hard limit to 9 attempts (max number of squares).
    
    int attempts = 1;
    int index = rand() % 9;

    while (grid[rowVals[index]][colVals[index]] != ' ' && attempts < 9) {
        index = rand() % 9;
        attempts++;
    }

    // Successful index

    if (grid[rowVals[index]][colVals[index]] == ' ') {
        coord result;
        result.row = rowVals[index];
        result.column = colVals[index];
        return result;
    }
    
    // Failed index (should theoretically never occur)

    else {
        coord error;
        error.row = -1;
        error.column = -1;
        return error;
    }
}

void drawGrid(char grid[3][3]) {
    printf(" %c | %c | %c \n", grid[0][0], grid[0][1], grid[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", grid[1][0], grid[1][1], grid[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", grid[2][0], grid[2][1], grid[2][2]);
}

int getPlayer(char mark) {
    switch (mark) {
        case 'X': return 1;
        case 'O': return 2;
        default: return 0;
    }
}

int checkWinner(char grid[3][3]) {
    /*
    Return values:
    0 -> no winner
    1 -> player 1 wins
    2 -> player 2 wins
    utilizing getPlayer()
    */

    // Validate row

    for (int r = 0; r < 3; r++) {
        if (grid[r][0] != ' ' && grid[r][0] == grid[r][1] && grid[r][1] == grid[r][2])
            return getPlayer(grid[r][1]);
    }

    // Validate column

    for (int c = 0; c < 3; c++) {
        if (grid[1][c] != ' ' && grid[0][c] == grid[1][c] && grid[1][c] == grid[2][c])
            return getPlayer(grid[1][c]);
    }

    // Validate diagonal

    if (grid[1][1] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
        return getPlayer(grid[1][1]);
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
        return getPlayer(grid[1][1]);

    // Did all tests fail?
    return 0;
}