import copy
import sys

from klotski import board
from Vector import vector
from klotski import block
import tkinter
from tkinter import ttk as tk
import re


sys.setrecursionlimit(99999)


def copy_node(node):
    return node


def exists(node, cont):
    if node[1] == cont:
        return True
    else:
        i = 0
        while i < len(node[2]):
            if exists(node[2][i], cont) is True:
                return True
            i += 1
    return False


def itrBFS(queue):
    """curr = queue.pop(0)[0]
    moves = curr[1].getPossibleMoves()
    i = 0
    while i < len(moves):
        newBoard = board.Board()
        newBoard.board = curr[1].board[:]
        newBoard.moveCount = curr[1].moveCount
        newBoard.blocks = copy.deepcopy(curr[1].blocks)
        j = 0
        while j < len(curr[1].blocks):
            newBoard.blocks[j] = copy.deepcopy(curr[1].blocks[j])
            j += 1
        newBoard.move(moves[i][0], moves[i][1])
        newNode = [curr, newBoard, []]
        if newBoard.goal_test() is True:
            return newNode
        curr[2].append(newNode)
        k = 0
        while k < len(queue) and queue[k][1] <= newBoard.moveCount:
            k += 1
        queue.insert(k, [newNode, newBoard.moveCount])
        i += 1
    return itrBFS(queue)"""
    print(f'Building')


file = open('klotski.txt')

file_contents = file.read()

i = 1
state = 0

curr_board = 0

boards = re.findall(r'\{\n(.*?)\n\}', file_contents, re.MULTILINE + re.DOTALL)

i = 0

while i < len(boards):
    print(f'{i}:\n{boards[i]}\n')
    i += 1

choice = int(input("Please choose a board: "))

puzzle = boards[choice]

print(f'\t\tPuzzle:\n{puzzle}\n\n')

lines = puzzle.splitlines()

boar = board.Board()

i = 0

while i < len(lines):
    curr_line = lines[i].split(' ')
    j = 0
    while j < len(curr_line):
        if curr_line[j] is not 'g' and curr_line[j] is not 'e':
            boar.addBlock(curr_line[j], i, j)
        j += 1
    i += 1

print(boar)

moves = boar.getPossibleMoves()

i = 0

while i < len(moves):
    print(f'bid:{moves[i][0]}\nmove:{moves[i][1]}')
    i += 1

graph = ["", boar, []]

alg = int(input('Please choose algorithm (1-bfs/2-a*)\n?-'))

visited = ""

if alg is 1:
    queue = [[graph, graph[1].moveCount]]
    win = False
    while len(queue) != 0 and win is False:
        curr = queue.pop(0)[0]
        moves = curr[1].getPossibleMoves()
        i = 0
        while i < len(moves):
            #aux = [curr[0] + str(curr[1]), ]
            #print(f'print: {aux[0]}')

            newBoard = board.Board()
            newBoard.board = curr[1].board[:]
            newBoard.moveCount = curr[1].moveCount
            newBoard.blocks = copy.deepcopy(curr[1].blocks)
            j = 0
            """while j < len(curr[1].blocks):
                newBoard.blocks[j] = copy.deepcopy(curr[1].blocks[j])
                j += 1"""
            newBoard.move(moves[i][0], moves[i][1])
            if newBoard.goal_test() is True:
                win = True
                i = len(moves)
                print(curr[0] + newBoard)
            if visited.find(str(newBoard)) is -1:
                #print(f'({newBoard.moveCount}):\n{newBoard}')
                k = 0
                while k < len(queue) and queue[k][1] <= newBoard.moveCount:
                    k += 1
                aux = [curr[0] + '(' + str(curr[1].moveCount) + '):\n' + str(curr[1]), newBoard]
                visited += str(curr[1])
                queue.insert(k, [aux, newBoard.moveCount])
            i += 1

    print(f'Under Construction')

elif alg is 2:
    queue = [[graph, int(graph[1].moveCount) + int(graph[1].heuristics())]]
    win = False
    while len(queue) != 0 and win is False:
        curr = queue.pop(0)[0]
        moves = curr[1].getPossibleMoves()
        i = 0
        while i < len(moves):
            # aux = [curr[0] + str(curr[1]), ]
            # print(f'print: {aux[0]}')

            newBoard = board.Board()
            newBoard.board = curr[1].board[:]
            newBoard.moveCount = curr[1].moveCount
            newBoard.blocks = copy.deepcopy(curr[1].blocks)
            j = 0
            """while j < len(curr[1].blocks):
                newBoard.blocks[j] = copy.deepcopy(curr[1].blocks[j])
                j += 1"""
            newBoard.move(moves[i][0], moves[i][1])
            if newBoard.goal_test() is True:
                win = True
                i = len(moves)
                print(curr[0] + newBoard)
            if visited.find(str(newBoard)) is -1:
                #print(f'({newBoard.moveCount}):\n{newBoard}')
                k = 0
                while k < len(queue) and queue[k][1] <= newBoard.moveCount:
                    k += 1
                aux = [curr[0] + '(' + str(curr[1].moveCount) + '):\n' + str(curr[1]), newBoard]
                visited += str(curr[1])
                queue.insert(k, [aux, int(newBoard.moveCount) + int(newBoard.heuristics())])
            i += 1

    print(f'Under Construction')
else:
    print(f'Wrong value inserted')

"""app = tk.Panedwindow()

app.update()

app.mainloop()"""
