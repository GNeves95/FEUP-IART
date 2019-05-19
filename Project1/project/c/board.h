//
// Created by linuxlite on 05-04-2019.
//

#ifndef KLOTSKI_BOARD_H
#define KLOTSKI_BOARD_H

#include "block.h"
#include "vector.h"

typedef struct board {
    char board[5][4];
    unsigned int moveCount;
    vector blocks;
}board;

void addBlock(board *self, int bid, int x, int y);

bool goal_test(board *self);

bool canMove(board *self, unsigned int bid, char direction);

void update(board *self);

bool move(board *self, unsigned int piece, char direction);

unsigned int heuristics(board *self);

void printState(board *self);

bool compStates(board *self, board *other);

vector getPossibleMoves(board *self);

board *duplicate(board *self);

board * BOARD();

//#define BOARD(X) board X = {.board = {{' ', '0', '0', ' '},{' ', '0', '0', ' '},{' ', ' ', ' ', ' '},{' ', ' ', ' ', ' '},{' ', ' ', ' ', ' '}}, .moveCount = 0}

#endif //KLOTSKI_BOARD_H
