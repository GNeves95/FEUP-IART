//
// Created by linuxlite on 06-04-2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"

void addBlock(board *self, int nbid, int x, int y) {
    int bid = -1;
    if (nbid > '9'){
        bid = 10 + (nbid - '1' - '0');
    } else {
        bid = nbid - '0';
    }
    bool exists = false;
    unsigned int i = 0;
    self->board[x][y] = bid;
    block *bl = (block *)at(&(self->blocks), bid);
    if(bl != 0) {
        if (bl->bid == bid) {
            if (x > bl->x) {
                makeVertical(bl);
            } else {
                makeHorizontal(bl);
            }
            exists = true;
        }
    }
    if(!exists) {
        block *aux = (block *)malloc(sizeof(block));
        Block(aux, bid, x, y);
        insert(&(self->blocks), aux, bid);
    }
}

bool goal_test(board *self) {
    block *bl = (block *)at(&(self->blocks), 0);
    if (bl->x == 3 && bl->y == 1)
        return true;
    else
        return false;
}

bool canMove(board *self, unsigned int bid, char direction) {
    if(bid < 0 || bid >= self->blocks.size)
        return false;
    block *bl = (block *)at(&(self->blocks), bid);
    if (bl == 0)
        return false;

    if (direction == 'w') {
        if (bl->x > 0) {
            if (self->board[bl->x - 1][bl->y] == ' ') {
                if (bl->width == 2) {
                    if (self->board[bl->x - 1][bl->y + 1] == ' ')
                        return true;
                    else
                        return false;
                } else {
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    else if(direction == 'a') {
        if (bl->y > 0) {
            if (self->board[bl->x][bl->y - 1] == ' ') {
                if (bl->height == 2) {
                    if (self->board[bl->x + 1][bl->y - 1] == ' ')
                        return true;
                    else
                        return false;
                } else {
                    return true;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else if (direction == 's'){
        if ((bl->height + bl->x < 5) && self->board[(bl->height + bl->x)][bl->y] == ' ') {
            if (bl->width == 2) {
                if (self->board[(bl->height + bl->x)][bl->y + 1] == ' ')
                    return true;
                else
                    return false;
            } else {
                return true;
            }
        } else {
            return false;
        }
    } else if (direction == 'd') {
        if ((bl->width + bl->y < 4) && self->board[bl->x][bl->width + bl->y] == ' ') {
            if (bl->height == 2) {
                if (self->board[(bl->x + 1)][bl->width + bl->y] == ' ')
                    return true;
                else
                    return false;
            } else {
                return true;
            }
        } else {
            return false;
        }
    }
}

void update(board *self) {
    char aux[5][4] = {{' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' '}};
    memcpy(&(self->board), &aux, 5*4* sizeof(char));
    for(unsigned int i=0; i < self->blocks.size; i++) {
        block *curr = (block *) at(&(self->blocks), i);
        if (curr->width == 2) {
            self->board[curr->x][curr->y] = curr->bid;
            self->board[curr->x][curr->y + 1] = curr->bid;
            if (curr->height == 2) {
                self->board[curr->x + 1][curr->y] = curr->bid;
                self->board[curr->x + 1][curr->y + 1] = curr->bid;
            }
        } else if (curr->height == 2) {
            self->board[curr->x][curr->y] = curr->bid;
            self->board[curr->x + 1][curr->y] = curr->bid;
        } else {
            self->board[curr->x][curr->y] = curr->bid;
        }
    }
}

bool move(board *self, unsigned int piece, char direction){
    if (canMove(self, piece, direction) == true){
        block *bl = (block *)at(&(self->blocks), piece);
        if (direction == 'w'){
            moveUp(bl);
        } else if (direction == 's'){
            moveDown(bl);
        } else if (direction == 'a'){
            moveLeft(bl);
        } else if (direction == 'd'){
            moveRight(bl);
        }
        update(self);
        self->moveCount++;
        return true;
    } else
        return false;
}

unsigned int heuristics(board *self){
    block *bl = (block *)at(&(self->blocks), 0);
    return abs(3 - bl->x) + abs(1 - bl->y);
}

void printState(board *self){
    for(unsigned int i = 0; i < 5; i++){
        for(unsigned int j = 0; j < 4; j++){
            char c;
            if (self->board[i][j] == ' ')
                printf("  ");
            else
                printf("%x ", self->board[i][j]);
        }
        endl;
    }
}

bool compStates(board *self, board *other){
    for (unsigned int x = 0; x < 5; x++){
        for (unsigned int y = 0; y < 4; y++){
            if (self->board[x][y] != other->board[x][y])
                return false;
        }
    }
    return true;
}

vector getPossibleMoves(board *self) {
    VECTOR(moves);
    for(unsigned int i = 0; i < 5; i++){
        for(unsigned int j = 0; j < 4; j++){
            if(self->board[i][j] == ' '){
                if(i > 0 && self->board[i - 1][j] != ' '){
                    if(canMove(self, self->board[i - 1][j], 's')) {
                        movement *mov = (movement *)malloc(sizeof(movement));
                        mov->bid = self->board[i - 1][j];
                        mov->direction = 's';
                        add(&moves, mov);
                    }
                }
                if(i < 4 && self->board[i + 1][j] != ' '){
                    if(canMove(self, self->board[i + 1][j], 'w')) {
                        movement *mov = (movement *)malloc(sizeof(movement));
                        mov->bid = self->board[i + 1][j];
                        mov->direction = 'w';
                        add(&moves, mov);
                    }
                }
                if(j > 0 && self->board[i][j - 1] != ' '){
                    if(canMove(self, self->board[i][j - 1], 'd')) {
                        movement *mov = (movement *)malloc(sizeof(movement));
                        mov->bid = self->board[i][j - 1];
                        mov->direction = 'd';
                        add(&moves, mov);
                    }
                }
                if(j < 3 && self->board[i][j + 1] != ' '){
                    if(canMove(self, self->board[i][j + 1], 'a')) {
                        movement *mov = (movement *)malloc(sizeof(movement));
                        mov->bid = self->board[i][j + 1];
                        mov->direction = 'a';
                        add(&moves, mov);
                    }
                }
            }
        }
    }
    return moves;
}

board * duplicate(board *self) {
    board *newone = (board *)malloc(sizeof(board));

    newone->moveCount = self->moveCount;

    //memcpy(&(newone.board), &(self->board), 4*5* sizeof(char));

    for (unsigned int x = 0; x < 5; x++){
        for (unsigned int y = 0; y < 4; y++){
            newone->board[x][y] = self->board[x][y];
        }
    }

    newone->blocks.size = 0;

    for (unsigned int i = 0; i < self->blocks.size; i++) {
        block *bl = (block *)malloc(sizeof(block));
        (*bl) = copy((block *)at(&(self->blocks), i));
        add(&(newone->blocks), bl);
    }
    return newone;
}

board * BOARD(){
    board *ret = (board *)malloc(sizeof(board));
    char arr[5][4] = {{' ', 0, 0, ' '},{' ', 0, 0, ' '},{' ', ' ', ' ', ' '},{' ', ' ', ' ', ' '},{' ', ' ', ' ', ' '}};
    memcpy(&(ret->board), arr, 5*4* sizeof(char));
    ret->moveCount = 0;
    VECTOR(bl);
    block *bc = (block *)malloc(sizeof(block));
    Block(bc, 0, 0, 1);
    makeSquare(bc);
    add(&bl, bc);
    ret->blocks = bl;
    return ret;
}