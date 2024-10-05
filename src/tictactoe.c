#include "../include/tictactoe.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// Gewinner Variable deklarieren
char winner = 0;  // Initialisiere den Gewinner mit 0 (kein Gewinner)

// Funktion um Board updaten
void PickField(char board[BOARD_SIZE][BOARD_SIZE], int xMove, char marker){
    int r, c;
    r = (xMove - 1) / 3;
    c = (xMove - 1) % 3;

    // Board updaten
    board[r][c] = marker;
}

void printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    // Board printen
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

char checkWinner(char board[BOARD_SIZE][BOARD_SIZE]) {
    // Checke reihe
    for (int i = 0; i < BOARD_SIZE; i++){
        if ((board[i][0]) == board[i][1] && board[i][1] == board[i][2]){
            winner = board[i][0];  // Gewinner festlegen
            return winner;
        }
    }

    // Checke Spalte
    for (int i = 0; i < BOARD_SIZE; i++){
        if ((board[0][i]) == board[1][i] && board[1][i] == board[2][i]){
            winner = board[0][i];  // Hier board[0][i] statt board[0][1]
            return winner;
        }
    }

    // Checke Diagonalen
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        winner = board[0][0];
        return winner;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        winner = board[0][2];
        return winner;
    }

    return 0;  // Kein Gewinner
}

// Funktion zum X Position abfragen + im Board updaten
void makeMove(char board[BOARD_SIZE][BOARD_SIZE]) {
    int xMove;
    char marker = 'X';
    printf("\n\nAuf welches Feld willst du setzen? (1-9): ");
    scanf("%d", &xMove);
    
    // Prüfen, ob das Feld bereits belegt ist
    if (board[(xMove - 1) / 3][(xMove - 1) % 3] == 'X' || board[(xMove - 1) / 3][(xMove - 1) % 3] == 'O') {
        printf("Dieses Feld ist bereits belegt! Bitte wähle ein anderes Feld.\n");
        makeMove(board); // Recursive call to make a valid move
    } else {
        PickField(board, xMove, marker);
    }
}

// Funktion zum den User mit dem CLI greeten
void greeter(char board[BOARD_SIZE][BOARD_SIZE]){
    printf("TicTacToe \n");
    printf("------------------------\n \n");
    printBoard(board);
}

// Funktion für random generierten Input (Bot)
void BotGuess(char board[BOARD_SIZE][BOARD_SIZE]){
    char marker = 'O';
    int random_number;

    // Schleife für zufällige Zahl, die nur auf ein freies Feld zeigt
    do {
        random_number = rand() % 9 + 1;
    } while (board[(random_number - 1) / 3][(random_number - 1) % 3] == 'X' || 
             board[(random_number - 1) / 3][(random_number - 1) % 3] == 'O');

    PickField(board, random_number, marker);
}

void clearScreen(){
    sleep(2);
    system("clear");    // screen clearen
}

int main() {
    srand(time(NULL));  // Zufallsgenerator initialisieren

    char board[BOARD_SIZE][BOARD_SIZE] = {
        {'1', '2', '3'},
        {'4', '5', '6'}, 
        {'7', '8', '9'}
    };

    greeter(board);

    //Programm wiederholen bis es einen Gewinner gibt
    while (winner != 'X' && winner != 'O'){
        makeMove(board);     // Spieler macht Zug
        winner = checkWinner(board);  // Überprüfe, ob es einen Gewinner gibt
        clearScreen();
        greeter(board);   // Board anzeigen
        if (winner != 0) break;  // Wenn es einen Gewinner gibt, Schleife verlassen

        clearScreen();
        greeter(board);   // Board anzeigen
        
        printf("\nBot is choosing next...\n");
        BotGuess(board);  // Bot macht Zug
        winner = checkWinner(board);  // Gewinner erneut prüfen
        clearScreen();
        greeter(board);   // Board anzeigen
        if (winner != 0) break;  // Wenn es einen Gewinner gibt, Schleife verlassen

        clearScreen();
        greeter(board);   // Board anzeigen
    }
    
    // Gewinner anzeigen
    printf("Spieler %c hat gewonnen!\n", winner);

    return 0;
}
