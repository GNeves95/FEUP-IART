//
// Created by linuxlite on 05-04-2019.
//

#ifndef KLOTSKI_BLOCK_H
#define KLOTSKI_BLOCK_H

#include "utils.h"

typedef struct block {
    int bid;
    unsigned int x, y, height, width;
} block;

void Block(block *b, int bid, unsigned int x, unsigned int y);

void makeHorizontal(block *b);

void makeVertical(block *b);

void makeSquare(block *b);

unsigned int getX(block *b);

unsigned int getY(block *b);

unsigned int getWidth(block *b);

unsigned int getHeight(block *b);

bool moveUp(block *b);

bool moveDown(block *b);

bool moveLeft(block *b);

bool moveRight(block *b);

int getBid(block *b);

block copy(block *b);

#endif //KLOTSKI_BLOCK_H
