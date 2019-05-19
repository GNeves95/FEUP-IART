#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "utils.h"
#include "board.h"

typedef struct bchoice {
    char board[5][4];
} bchoice;

typedef struct state {
    board *b;
    struct state *prev;
    int f;
} state;

void printBoard(char board[5][4]){
    for(unsigned int i = 0; i < 5; i++){
        for(unsigned int j = 0; j < 4; j++){
            char c = board[i][j];
            printf("%c ", c);
        }
        endl;
    }
}

bool exists(vector *visited, board *state){
    for (unsigned int i = 0; i < visited->size; i++) {
        board *b = (board *)at(visited, i);
        if (compStates(b, state) == true)
            return true;
    }
    return false;
}

int main() {
    VECTOR(choices);
    FILE *fd;
    fd = fopen("klotski.txt", "r");
    char character;
    int bc[5][4] = {0};
    int i = -1, j = 0;
    while((character = getc(fd))!=EOF){
        if(character == '{'){
            i = -1;
            j = 0;
            for (unsigned int x = 0; x < 5; x++){
                for (unsigned int y = 0; y < 4; y++){
                    bc[x][y] = 0;
                }
            }
        } else if(character == '}') {
            bchoice *aux = (bchoice *)malloc(sizeof(bchoice));
            for (unsigned int x = 0; x < 5; x++){
                for (unsigned int y = 0; y < 4; y++){
                    aux->board[x][y] = bc[x][y];
                }
            }
            //memcpy(aux->board, bc, 4 * 5 * sizeof(char));
            add(&choices, aux);
        } else if(character == '\n') {
            i++;
            j=0;
        } else if(character == ' ') {
            j++;
        } else {
            if (character == 'e')
                bc[i][j] = '_';
            else
                bc[i][j] = bc[i][j] + character;
        }
    }
    fclose(fd);

    for(unsigned int i=0; i < choices.size; i++){
        printf("(%d):\n", i);
        printBoard(at(&choices, i));
    }

    board *b = BOARD();
    int choice = -1;
    printf("Please choose a board:\n");
    scanf("%d", &choice);

    if (choice < 0 || choice >= choices.size){
        printf("Board out of bounds!\n");
        return -1;
    }

    bchoice puzzle = *(bchoice *)at(&choices, choice);

    for (unsigned int x = 0; x < 5; x++) {
        for (unsigned int y = 0; y < 4; y++) {
            if (puzzle.board[x][y] != 'g' && puzzle.board[x][y] != '_')
                addBlock(b, puzzle.board[x][y], x, y);
        }
    }

    printState(b);

    vector moves = getPossibleMoves(b);

    endl;
    printf("Moves:\n");
    for (unsigned int i = 0; i < moves.size; i++){
        movement *aux = (movement *)at(&moves, i);
        printf("[%d, %c]\n", aux->bid, aux->direction);
    }

    VECTOR(visited);
    VECTOR(queue);

    state *begin = (state *)malloc(sizeof(state));

    int alg;
    printf("Please choose an algorithm: (1-bfs/2-a*): ");
    scanf("%d", &alg);
    endl;
    if(alg == 1){

        begin->b = b;
        begin->prev = 0;
        begin->f = begin->b->moveCount;

        insert(&queue, begin, 0);

        add(&visited, begin->b);

        bool win = false;

        while (queue.size > 0 && win == false){
            state *curr = (state *)rem(&queue, 0);
            moves = getPossibleMoves(curr->b);

            /*printf("(%d)\n", curr->f);
            printState(curr->b);
            endl;*/
            //endl;

            for(unsigned int i = 0; i < moves.size; i++) {
                board *newBoard = duplicate(curr->b);
                movement *aux = (movement *) at(&moves, i);
                move(newBoard, aux->bid, aux->direction);

                if (goal_test(newBoard) == true){
                    win = true;
                    printf("Win, do something!\n\tMoves: %d\n", newBoard->moveCount);

                    printf("Back tracking:\n");
                    printf("(%d)\n", newBoard->moveCount);
                    printState(newBoard);
                    state * winState = curr;
                    endl;
                    while (winState != 0){
                        printf("(%d)\n", winState->b->moveCount);
                        printState(winState->b);
                        winState = winState->prev;
                    }
                }

                bool seen = false;
                for (unsigned int k = 0; k < visited.size && seen == false; k++) {
                    board *bv = (board *)at(&visited, k);
                    if(compStates(newBoard, bv)){
                        seen = true;
                    }
                }

                if (seen == false){
                    add(&visited, newBoard);
                    unsigned int k = 0;
                    state *queueState = (state *)at(&queue, k);
                    while (k < queue.size && queueState->f <= newBoard->moveCount){
                        k++;
                        if(k < queue.size)
                            queueState = (state *)at(&queue, k);
                    }

                    state *newState = (state *)malloc(sizeof(state));
                    newState->f = newBoard->moveCount;
                    newState->b = newBoard;
                    newState->prev = curr;

                    insert(&queue, newState, k);
                }

            }
        }

        printf("(BFS): Under Construction;\n");
    } else if (alg == 2){

        begin->b = b;
        begin->prev = 0;
        begin->f = begin->b->moveCount + heuristics(begin->b);

        insert(&queue, begin, 0);

        add(&visited, begin->b);

        bool win = false;

        while (queue.size > 0 && win == false){
            state *curr = (state *)rem(&queue, 0);
            moves = getPossibleMoves(curr->b);

            /*printf("(%d)\n", curr->f);
            printState(curr->b);
            endl;*/
            //endl;

            for(unsigned int i = 0; i < moves.size; i++) {
                board *newBoard = duplicate(curr->b);
                movement *aux = (movement *) at(&moves, i);
                move(newBoard, aux->bid, aux->direction);

                if (goal_test(newBoard) == true){
                    win = true;
                    printf("Win, do something!\n\tMoves: %d\n", newBoard->moveCount);

                    printf("Back tracking:\n");
                    printf("(%d)\n", newBoard->moveCount);
                    printState(newBoard);
                    state * winState = curr;
                    endl;
                    while (winState != 0){
                        printf("(%d)\n", winState->b->moveCount);
                        printState(winState->b);
                        winState = winState->prev;
                    }
                }

                bool seen = false;
                for (unsigned int k = 0; k < visited.size && seen == false; k++) {
                    board *bv = (board *)at(&visited, k);
                    if(compStates(newBoard, bv)){
                        seen = true;
                    }
                }

                if (seen == false){
                    add(&visited, newBoard);
                    unsigned int k = 0;
                    state *queueState = (state *)at(&queue, k);
                    while (k < queue.size && queueState->f <= (newBoard->moveCount + heuristics(begin->b))){
                        k++;
                        if(k < queue.size)
                            queueState = (state *)at(&queue, k);
                    }

                    state *newState = (state *)malloc(sizeof(state));
                    newState->f = newBoard->moveCount + heuristics(begin->b);
                    newState->b = newBoard;
                    newState->prev = curr;

                    insert(&queue, newState, k);
                }

            }
        }

        printf("(A-Star): Under Construction;\n");
    } else {
        printf("Wrong value, no search algorithm selected;\n");
    }
    return 0;
}