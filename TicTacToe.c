#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

char board[9];
char PLAYER = 'X';
char COMPUTER = 'O';

void restartBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char winner);
void printChoiceFormat();

int main(void) {
    char winner = ' ';
    char replayResponse;

    do {
        restartBoard();
        printChoiceFormat();

        while (winner == ' ' && checkFreeSpaces() != 0) {
            printBoard();

            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }

            computerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
        }

        printBoard();
        printWinner(winner);
        
        // incase if player wants to play again and by this there is no need to rerun the code
        printf("\n\nDo you want to play again(Y/N): ");
        scanf("%c", &replayResponse);
        replayResponse = toupper(replayResponse);
    }
    while (replayResponse == 'Y');

    return 0;
}

void restartBoard() {
    for (int i = 0; i < 9; i++) {
        board[i] = ' ';
    }
}

void printBoard() {
    printf("\n");
    printf(" %c | %c | %c\n", board[0], board[1], board[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[3], board[4], board[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", board[6], board[7], board[8]);
    printf("\n");
}


int checkFreeSpaces() {
    int freeSpaces = 9;
    for (int i = 0; i < 9; i++) {
        if (board[i] != ' ') {
            freeSpaces--;
        }
    }

    return freeSpaces;
}

void printChoiceFormat() {
    printf("\n\n 1 | 2 | 3 \n---|---|---\n 4 | 5 | 6\n---|---|---\n 7 | 8 | 9 \n");
}

void playerMove() {
    int playerChoice = 0;

    do {
        redirect: printf("select a choice based on the format: ");
        scanf("%d", &playerChoice);

        if (board[playerChoice - 1] != ' ') {
            printf("Invalid Move!!");
            goto redirect;
        } else {
            board[playerChoice - 1] = PLAYER;
            break;
        }
    } while (board[playerChoice - 1] != ' ');
}


// Strategic AI
void computerMove() {
    srand(time(0));
    int computerRandomChoice;


    // Check for winning moves 
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = COMPUTER;
            if (checkWinner() == COMPUTER) {
                return;  // Computer has a winning move
            }
            board[i] = ' ';  // Undo the move
        }
    }

    // Check for blocking player's winning moves
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = PLAYER;
            if (checkWinner() == PLAYER) {
                board[i] = COMPUTER;  // Block player's winning move
                return;
            }
            board[i] = ' ';  // Undo the move
        }
    }

    // If no winning or blocking moves, make a random move
    do {
        computerRandomChoice = rand() % 9;
    } while (board[computerRandomChoice] != ' ');

    board[computerRandomChoice] = COMPUTER;
}



//  ---Make Random Computer Moves--- //

// void computerMove() {
//     srand(time(0));
//     int computerRandomChoice;

//     if (checkFreeSpaces() > 0) {
//         do {
//             computerRandomChoice = rand() % 9;
//         } while (board[computerRandomChoice] != ' ');

//         board[computerRandomChoice] = COMPUTER;
//     } else {
//         printWinner(' ');
//     }
// }

char checkWinner() {
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == board[i + 1] && board[i] == board[i + 2] && board[i] != ' ') {
            return board[i];
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[i] == board[i + 3] && board[i] == board[i + 6] && board[i] != ' ') {
            return board[i];
        }
    }

    // Check diagonals
    if (board[0] == board[4] && board[0] == board[8] && board[0] != ' ') {
        return board[0];
    }

    if (board[2] == board[4] && board[2] == board[6] && board[2] != ' ') {
        return board[2];
    }

    return ' ';
}

void printWinner(char winner) {
    if (winner == PLAYER) {
        printf("\n\nYou Win!!.");
    } else if (winner == COMPUTER) {
        printf("\n\nYou Lose;");
    } else {
        printf("\n\nIt's a Tie.");
    }
}



