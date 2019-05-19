//
// Created by linuxlite on 06-04-2019.
//

#include "block.h"

void Block(block *b, int bid, unsigned int x, unsigned int y){
    b->width = 1;
    b->height = 1;
    b->bid = bid;
    b->x = x;
    b->y = y;
}

void makeHorizontal(block *b){
    b->width=2;
    b->height=1;
}

void makeVertical(block *b){
    b->width=1;
    b->height=2;
}

void makeSquare(block *b){
    b->height=2;
    b->width=2;
}

unsigned int getX(block *b){ return b->x;}

unsigned int getY(block *b){ return b->y;}

unsigned int getWidth(block *b){ return b->width;}

unsigned int getHeight(block *b){ return b->height;}

bool moveUp(block *b){
    if(b->x > 0){
        b->x--;
        return true;
    } else
        return false;
}

bool moveDown(block *b){
    if(b->x < 4){
        b->x++;
        return true;
    } else
        return false;
}

bool moveLeft(block *b){
    if(b->y > 0){
        b->y--;
        return true;
    } else
        return false;
}

bool moveRight(block *b){
    if(b->y < 3){
        b->y++;
        return true;
    } else
        return false;
}

int getBid(block *b){ return b->bid;}

block copy(block *b){
    block ret;
    ret.bid = b->bid;
    ret.x = b->x;
    ret.y = b->y;
    ret.height = b->height;
    ret.width = b->width;
    return ret;
}