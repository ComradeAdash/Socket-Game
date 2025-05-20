#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "raylib.h"
#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define CELL_HEIGHT_WIDTH (SCREEN_WIDTH / 3)

/*

Tic Tac Toe

Ensure raylib is installed before running. 

gcc main.c -o test $(pkg-config --cflags --libs raylib) -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio && ./test

*/

typedef struct {    
    char boardArray[3][3];
    int  openSpaces[9];
} Board;

Board* createBoard(){
    Board *board = (Board*)malloc(sizeof(Board));
    if (board != NULL){
        for (int i = 0;i<3;i++){
            for (int j = 0;j<3;j++){
                board->boardArray[i][j] = '-';
            }
        }
        //a zero will mean the slot is available. 
        for (int i = 0;i<9;i++){
            board->openSpaces[i] = 0;
        }
    }
    return board;
};

void displayBoard(Board* theboard){
    for (int i = 0;i<3;i++){
        for (int j = 0;j<3;j++){
            printf("%c ",theboard->boardArray[i][j]);
        }
        printf("\n");
    }
};

bool checkWinner(Board* b,char sym){
    for (int i = 0; i < 3; i++) {

        // check the rows
        if (b->boardArray[i][0] == sym &&
            b->boardArray[i][1] == sym &&
            b->boardArray[i][2] == sym)
            return true;

        // check the columns
        if (b->boardArray[0][i] == sym &&
            b->boardArray[1][i] == sym &&
            b->boardArray[2][i] == sym)
            return true;
    }

    // Check diagonals
    if ((b->boardArray[0][0] == sym &&  // first diagonal
         b->boardArray[1][1] == sym &&
         b->boardArray[2][2] == sym) ||
        (b->boardArray[0][2] == sym &&  // second diagonal
         b->boardArray[1][1] == sym &&
         b->boardArray[2][0] == sym))
        return true;

    return false;
}

// returns false to continue the game
bool updateBoard(Board* theBoard,char symbol,int x, int y){
    bool theresult = false;
    if (theBoard != NULL && x >= 0 && x < 3 && y >= 0 && y < 3){
        theBoard->boardArray[y][x] = symbol;

        theresult = checkWinner(theBoard,symbol);
    }
    if (theresult == true){
        printf("Game Over! %c Wins\n",symbol);
    }
    return theresult;
}

int main(){

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tic Tac Toe");
    Color colour = RED;
    Vector2 mousePos;
    Board* theBoard = createBoard();
    int CellArray[3][3] = {0}; // gui grid
    bool status = false; // the game status, true = game is running, false = game is over / stopped
    char symbol;
    int turn = 0; //RED = 0, BLUE = 1
    int num_turns = 0;

    while ((status == false) && !WindowShouldClose() && (num_turns < 9)){
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0;i<3;i++){ 
            DrawLine(i*CELL_HEIGHT_WIDTH,0,i*CELL_HEIGHT_WIDTH,SCREEN_HEIGHT,BLACK);
        }
        for (int i = 0;i<3;i++){
            DrawLine(0,i*CELL_HEIGHT_WIDTH,SCREEN_WIDTH,i*CELL_HEIGHT_WIDTH,BLACK);
        }
        mousePos = GetMousePosition();
        int col = (int)(mousePos.x / CELL_HEIGHT_WIDTH);
        int row = (int)(mousePos.y / CELL_HEIGHT_WIDTH);


        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            printf("Mouse_X = %f and Mouse_Y = %f \n", mousePos.x,mousePos.y);
            if (col >= 0 && col < 3 && row >= 0 && row < 3 && theBoard->boardArray[row][col] == '-'){
                num_turns++;
                if ( CellArray[row][col] == 0){
                    CellArray[row][col] = 1;
                }

                if (turn == 0){
                    status = updateBoard(theBoard,'X',col,row);
                    turn = 1;
                }
                else {
                    status = updateBoard(theBoard,'O',col,row);
                    turn = 0;
                }
            }
            displayBoard(theBoard);
        }

        // find where to draw / fill in 

        for (int i = 0;i<3;i++){
            for (int j = 0;j<3;j++){
                if (CellArray[i][j]){
                    if (theBoard->boardArray[i][j] == 'X'){
                        colour = RED;
                    }
                    else{
                        colour = BLUE;
                    }
                    DrawRectangle(j * CELL_HEIGHT_WIDTH ,i * CELL_HEIGHT_WIDTH, CELL_HEIGHT_WIDTH, CELL_HEIGHT_WIDTH, colour);
                }
            }
        }
        EndDrawing();
    }

    free(theBoard);
    CloseWindow();
    return 0;
}