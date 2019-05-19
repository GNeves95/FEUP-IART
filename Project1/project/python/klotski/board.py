import copy

from Vector import vector
from klotski import block


class Board:
    blocks = []
    board = [[' ', '0', '0', ' '],
             [' ', '0', '0', ' '],
             [' ', ' ', ' ', ' '],
             [' ', ' ', ' ', ' '],
             [' ', ' ', ' ', ' ']]

    moveCount = 0

    def __init__(self):
        self.addBlock(0, 0, 1)
        self.blocks[0].width = 2
        self.blocks[0].height = 2

    def addBlock(self, bid, x, y):
        exists = 0
        i = 0
        self.board[x][y] = bid
        while i < len(self.blocks):
            if self.blocks[i].bid is bid:
                if x > self.blocks[i].x:
                    self.blocks[i].makeVertical()
                else:
                    self.blocks[i].makeHorizontal()
                exists = 1
            i += 1

        if exists is 0:
            aux = block.Block(bid, x, y)
            self.blocks.append(aux)

    def goal_test(self):
        if self.blocks[0].getCoords() is [3, 1]:
            return True
        else:
            return False

    def canMove(self, bid, direction):
        bid = int(bid)
        if 0 > bid <= len(self.blocks):
            return False
        block = self.blocks[bid]
        if block is None:
            return False

        if direction is 'w':
            if block.getX() > 0:
                if self.board[int(block.getX()) - 1][int(block.getY())] is ' ':
                    if block.getWidth() is 2:
                        if self.board[int(block.getX()) - 1][int(block.getY()) + 1] is ' ':
                            return True
                        else:
                            return False
                    else:
                        return True
                else:
                    return False
            else:
                return False
        elif direction is 'a':
            if block.getY() > 0:
                if self.board[int(block.getX())][int(block.getY()) - 1] is ' ':
                    if block.getHeight() is 2:
                        if self.board[int(block.getX()) + 1][int(block.getY()) - 1] is ' ':
                            return True
                        else:
                            return False
                    else:
                        return True
                else:
                    return False
            else:
                return False
        elif direction is 's':
            if block.getHeight() is 1:
                if block.getX() < 4:
                    if self.board[int(block.getX()) + 1][int(block.getY())] is ' ':
                        if block.getWidth() is 2:
                            if self.board[int(block.getX()) + 1][int(block.getY()) + 1] is ' ':
                                return True
                            else:
                                return False
                        else:
                            return True
                    else:
                        return False
                else:
                    return False
            else:
                if block.getX() < 3:
                    if self.board[int(block.getX()) + 2][int(block.getY())] is ' ':
                        if block.getWidth() is 2:
                            if self.board[int(block.getX()) + 2][int(block.getY()) + 1] is ' ':
                                return True
                            else:
                                return False
                        else:
                            return True
                    else:
                        return False
                else:
                    return False
        elif direction is 'd':
            if block.getWidth() is 1:
                if block.getY() < 3:
                    if self.board[int(block.getX())][int(block.getY()) + 1] is ' ':
                        if block.getHeight() is 2:
                            if self.board[int(block.getX()) + 1][int(block.getY()) + 1] is ' ':
                                return True
                            else:
                                return False
                        else:
                            return True
                    else:
                        return False
                else:
                    return False
            else:
                if block.getY() < 2:
                    if self.board[int(block.getX())][int(block.getY()) + 2] is ' ':
                        if block.getHeight() is 2:
                            if self.board[int(block.getX()) + 1][int(block.getY()) + 2] is ' ':
                                return True
                            else:
                                return False
                        else:
                            return True
                    else:
                        return False
                else:
                    return False

    def update(self):
        self.board = [[' ', ' ', ' ', ' '],
                      [' ', ' ', ' ', ' '],
                      [' ', ' ', ' ', ' '],
                      [' ', ' ', ' ', ' '],
                      [' ', ' ', ' ', ' ']]
        i = 0
        while i < len(self.blocks):
            curr = self.blocks[i]
            #print(f'bid: {curr.bid}, x: {curr.getX()}, y: {curr.getY()}, Height: {curr.getHeight()}, Width: {curr.getWidth()}')
            if curr.getWidth() is 2:
                coords = curr.getCoords()
                self.board[coords[0]][coords[1]] = str(curr.getBid())
                self.board[coords[0]][coords[1] + 1] = str(curr.getBid())
                if curr.getHeight() is 2:
                    self.board[coords[0] + 1][coords[1]] = str(curr.getBid())
                    self.board[coords[0] + 1][coords[1] + 1] = str(curr.getBid())
            elif curr.getHeight() is 2:
                coords = curr.getCoords()
                self.board[coords[0]][coords[1]] = str(curr.getBid())
                self.board[coords[0] + 1][coords[1]] = str(curr.getBid())
            else:
                coords = curr.getCoords()
                self.board[coords[0]][coords[1]] = str(curr.getBid())

            i += 1

    def move(self, piece, direction):
        piece = int(piece)
        if self.canMove(piece, direction) is True:
            if direction is 'w':
                self.blocks[piece].moveUp()
            elif direction is 's':
                self.blocks[piece].moveDown()
            elif direction is 'a':
                self.blocks[piece].moveLeft()
            elif direction is 'd':
                self.blocks[piece].moveRight()
            self.update()
            self.moveCount += 1
            return True
        else:
            return False

    def heuristics(self):
        return abs(3 - self.blocks[0].getX()) + abs(1 - self.blocks[0].getY())

    def __str__(self):
        string = ''
        i = 0

        while i < 5:
            j = 0
            while j < 4:
                string += str(self.board[i][j]) + ' '
                j += 1
            string += '\n'
            i += 1
        return string

    def __eq__(self, other):
        return self.board == other.board

    def getPossibleMoves(self):
        i = 0
        moves = []
        while i < 5:
            j = 0
            while j < 4:
                if self.board[i][j] is ' ':
                    if i > 0 and self.board[i-1][j] is not ' ':
                        if self.canMove(self.board[i-1][j], 's'):
                            moves.append([self.board[i-1][j], 's'])
                    if i < 4 and self.board[i+1][j] is not ' ':
                        if self.canMove(self.board[i+1][j], 'w'):
                            moves.append([self.board[i+1][j], 'w'])
                    if j > 0 and self.board[i][j-1] is not ' ':
                        if self.canMove(self.board[i][j-1], 'd'):
                            moves.append([self.board[i][j-1], 'd'])
                    if j < 3 and self.board[i][j+1] is not ' ':
                        if self.canMove(self.board[i][j+1], 'a'):
                            moves.append([self.board[i][j+1], 'a'])
                j += 1
            i += 1
        #moves.append([13, 'd'])
        return moves

    def copy_blocks(self):
        newone = type(self)
        newone.blocks[0] = self.blocks[0].copy()
        i = 1
        while i < len(self.blocks):
            aux_block = self.blocks[i].copy()
            newone.blocks.append(aux_block)
            i += 1
        newone.board = self.board[:]
        newone.moveCount = copy.copy(self.moveCount)
        return newone
