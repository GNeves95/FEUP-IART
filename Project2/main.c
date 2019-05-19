#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct _node{
    int estimate, move, numChildren;
    char *thisboard;
    struct _node *children;
} node;

typedef struct _move{
    int src, dest, rem, value;
} move;

typedef struct _possMov{
    unsigned int numberOfMoves;
    move *moves;
} possMov;

typedef struct player{
    unsigned int openingStack, midStack, poundedStack;
} player;

typedef enum boolean{true=1,false=0}bool;

char *board;

void initBoard(){
    board = (char *)malloc(24* sizeof(char));
    for (unsigned int i = 0; i < 24; i++) {
        board[i] = ' ';
    }
}

int numberOf(char *position, char token){
    int num = 0;

    for(unsigned int i=0; i < 24; i++){
        if(position[i] == token){
            num++;
        }
    }
    return num;
}

int boardValue(char *position){
    int num = 0;

    for(unsigned int i=0; i < 24; i++){
        if(position[i] == 'w') {
            //num1++;
            num++;
        }
        else if(position[i] == 'b') {
            //num2++;
            num--;
        }
    }
    return num;
}

node *initNode(int steps, char* thisboard, int estimate){
    node *ret = (node*)malloc(sizeof(node));

    ret->estimate = estimate;
    ret->move = steps;
    ret->numChildren = 0;
    ret->children = 0;

    memcpy(ret->thisboard,thisboard,24);

    return ret;
}

node *processNode(node *curr){
    return 0;
}

int *contains(char *position, char token){
    int num = 0;
    int *ret = (int*)malloc(sizeof(int));
    ret[0] = -1;

    for(unsigned int i=0; i < 24; i++){
        if(position[i] == token){
            num++;
            ret = (int*)realloc(ret, (num+1)* sizeof(int));
            ret[num-1] = i;
            ret[num] = -1;
        }
    }
    return ret;
}

int *neighbours(int pos){
    int *ret = (int*)malloc(sizeof(int));
    ret[0] = -1;
    switch (pos){
        case 0:
            ret = (int*)realloc(ret, 3* sizeof(int));
            ret[0] = 1;
            ret[1] = 9;
            ret[2] = -1;
            break;
        case 1:
            ret = (int*)realloc(ret, 4* sizeof(int));
            ret[0] = 0;
            ret[1] = 2;
            ret[2] = 4;
            ret[3] = -1;
            break;
        case 2:
            ret = (int*)realloc(ret, 3* sizeof(int));
            ret[0] = 1;
            ret[1] = 14;
            ret[2] = -1;
            break;
        case 3:
            ret = (int*)realloc(ret, 3* sizeof(int));
            ret[0] = 4;
            ret[1] = 10;
            ret[2] = -1;
            break;
        case 4:
            ret = (int*)realloc(ret, 5* sizeof(int));
            ret[0] = 1;
            ret[1] = 3;
            ret[2] = 5;
            ret[3] = 7;
            ret[4] = -1;
            break;
        case 5:
            ret = (int*)realloc(ret, 3* sizeof(int));
            ret[0] = 4;
            ret[1] = 13;
            ret[2] = -1;
            break;
        case 6:
            ret = (int*)realloc(ret, 3* sizeof(int));
            ret[0] = 7;
            ret[1] = 11;
            ret[2] = -1;
            break;
        case 7:
            ret = (int*)realloc(ret, 4* sizeof(int));
            ret[0] = 4;
            ret[1] = 6;
            ret[2] = 8;
            ret[3] = -1;
            break;
        case 8:
            ret = (int*)realloc(ret, 3* sizeof(int));
            ret[0] = 7;
            ret[1] = 12;
            ret[2] = -1;
            break;
        case 9:
            ret = (int*)realloc(ret, 4* sizeof(int));
            ret[0] = 0;
            ret[1] = 10;
            ret[2] = 21;
            ret[3] = -1;
            break;
        case 10:
            ret = (int*)realloc(ret, 5* sizeof(int));
            ret[0] = 3;
            ret[1] = 9;
            ret[2] = 11;
            ret[3] = 18;
            ret[4] = -1;
            break;
        case 11:
            ret = (int*)realloc(ret, 4* sizeof(int));
            ret[0] = 6;
            ret[1] = 10;
            ret[2] = 15;
            ret[3] = -1;
            break;
        case 12:
            ret = (int*)realloc(ret, 4* sizeof(int));
            ret[0] = 8;
            ret[1] = 13;
            ret[2] = 17;
            ret[3] = -1;
            break;
        case 13:
            ret = (int*)realloc(ret, 5* sizeof(int));
            ret[0] = 5;
            ret[1] = 12;
            ret[2] = 14;
            ret[3] = 20;
            ret[4] = -1;
            break;
        case 14:
            ret = (int*)realloc(ret, 4* sizeof(int));
            ret[0] = 2;
            ret[1] = 13;
            ret[2] = 23;
            ret[3] = -1;
            break;
        case 15:
            ret = (int*)realloc(ret, 3* sizeof(int));
            ret[0] = 11;
            ret[1] = 16;
            ret[2] = -1;
            break;
        case 16:
            ret = (int*)realloc(ret, 4* sizeof(int));
            ret[0] = 15;
            ret[1] = 17;
            ret[2] = 19;
            ret[3] = -1;
            break;
        case 17:
            ret = (int*)realloc(ret, 3* sizeof(int));
            ret[0] = 12;
            ret[1] = 16;
            ret[2] = -1;
            break;
        case 18:
            ret = (int*)realloc(ret, 3* sizeof(int));
            ret[0] = 10;
            ret[1] = 19;
            ret[2] = -1;
            break;
        case 19:
            ret = (int*)realloc(ret, 5* sizeof(int));
            ret[0] = 16;
            ret[1] = 18;
            ret[2] = 20;
            ret[3] = 22;
            ret[4] = -1;
            break;
        case 20:
            ret = (int*)realloc(ret, 3* sizeof(int));
            ret[0] = 13;
            ret[1] = 19;
            ret[2] = -1;
            break;
        case 21:
            ret = (int*)realloc(ret, 3* sizeof(int));
            ret[0] = 9;
            ret[1] = 22;
            ret[2] = -1;
            break;
        case 22:
            ret = (int*)realloc(ret, 4* sizeof(int));
            ret[0] = 19;
            ret[1] = 21;
            ret[2] = 23;
            ret[3] = -1;
            break;
        case 23:
            ret = (int*)realloc(ret, 3* sizeof(int));
            ret[0] = 14;
            ret[1] = 22;
            ret[2] = -1;
            break;
    }
    return ret;
}

int mill(char *position, int pos){
    switch (pos){
        case 0:
            return ((position[1] == position[0] && position[2] == position[0]) || (position[9] == position[0] && position[21] == position[0]));
        case 1:
            return ((position[1] == position[0] && position[2] == position[1]) || (position[4] == position[1] && position[7] == position[1]));
        case 2:
            return ((position[2] == position[0] && position[1] == position[2]) || (position[14] == position[2] && position[23] == position[2]));
        case 3:
            return ((position[4] == position[3] && position[5] == position[3]) || (position[10] == position[3] && position[18] == position[3]));
        case 4:
            return ((position[4] == position[3] && position[5] == position[4]) || (position[1] == position[4] && position[7] == position[4]));
        case 5:
            return ((position[4] == position[5] && position[3] == position[5]) || (position[13] == position[5] && position[20] == position[5]));
        case 6:
            return ((position[8] == position[6] && position[7] == position[6]) || (position[11] == position[6] && position[15] == position[6]));
        case 7:
            return ((position[6] == position[7] && position[8] == position[7]) || (position[1] == position[7] && position[4] == position[7]));
        case 8:
            return ((position[6] == position[8] && position[7] == position[8]) || (position[12] == position[8] && position[17] == position[8]));
        case 9:
            return ((position[10] == position[9] && position[11] == position[9]) || (position[0] == position[9] && position[21] == position[9]));
        case 10:
            return ((position[9] == position[10] && position[11] == position[10]) || (position[10] == position[3] && position[18] == position[10]));
        case 11:
            return ((position[9] == position[11] && position[10] == position[11]) || (position[6] == position[11] && position[15] == position[11]));
        case 12:
            return ((position[13] == position[12] && position[14] == position[12]) || (position[8] == position[12] && position[17] == position[12]));
        case 13:
            return ((position[12] == position[13] && position[14] == position[13]) || (position[5] == position[13] && position[20] == position[13]));
        case 14:
            return ((position[12] == position[14] && position[13] == position[14]) || (position[2] == position[14] && position[23] == position[14]));
        case 15:
            return ((position[16] == position[15] && position[17] == position[15]) || (position[6] == position[15] && position[11] == position[15]));
        case 16:
            return ((position[15] == position[16] && position[17] == position[16]) || (position[19] == position[16] && position[22] == position[16]));
        case 17:
            return ((position[16] == position[17] && position[15] == position[17]) || (position[8] == position[17] && position[12] == position[17]));
        case 18:
            return ((position[18] == position[3] && position[10] == position[18]) || (position[19] == position[18] && position[20] == position[18]));
        case 19:
            return ((position[18] == position[19] && position[20] == position[19]) || (position[16] == position[19] && position[22] == position[19]));
        case 20:
            return ((position[18] == position[20] && position[19] == position[20]) || (position[5] == position[20] && position[13] == position[20]));
        case 21:
            return ((position[22] == position[21] && position[23] == position[21]) || (position[0] == position[21] && position[9] == position[21]));
        case 22:
            return ((position[21] == position[22] && position[23] == position[22]) || (position[16] == position[22] && position[19] == position[22]));
        case 23:
            return ((position[21] == position[23] && position[22] == position[23]) || (position[2] == position[23] && position[14] == position[23]));
    }
}

possMov getPossibleMoves(char *position, int step, char token){
    possMov ret;
    ret.numberOfMoves = 0;
    ret.moves = (move*)malloc(sizeof(move));
    ret.moves = 0;

    if(step < 18) {
        int *empty = contains(position, ' ');
        int *i = empty;
        while (*i != -1){
            char *b2 = (char*)malloc(24* sizeof(char));
            memcpy(b2, position, 24);
            b2[*i] = token;
            move aux;
            aux.dest = *i;
            aux.value = 12345;
            aux.rem = -1;
            aux.src = -1;
            if(mill(b2,*i)){
                int *cont = contains(b2, (token == 'w') ? 'b' : 'w');
                int *j = cont;
                while (*j != -1){
                    move aux2;
                    aux2 = aux;
                    aux2.rem = *j;
                    ret.numberOfMoves++;
                    ret.moves = (move*)realloc(ret.moves, ret.numberOfMoves * sizeof(move));
                    ret.moves[ret.numberOfMoves-1] = aux2;
                    j++;
                }
                free(cont);
            } else{
                ret.numberOfMoves++;
                ret.moves = (move*)realloc(ret.moves, ret.numberOfMoves * sizeof(move));
                ret.moves[ret.numberOfMoves-1] = aux;
            }
            i++;
            free(b2);
        }
        free(empty);
    }
    else{
        int *empty = contains(position, token);
        int *i = empty;
        if (numberOf(position, token) == 3){
            int *blank = contains(position, ' ');
            while (*i != -1){
                int *k = blank;
                while (*k != -1){
                    char *b2 = (char*)malloc(24* sizeof(char));
                    memcpy(b2, position, 24);
                    b2[*k] = b2[*i];
                    b2[*i] = ' ';
                    move aux;
                    aux.src = *i;
                    aux.value = 12345;
                    aux.rem = -1;
                    aux.dest = *k;
                    if (mill(b2, *k)){
                        int *cont = contains(b2, (token == 'w') ? 'b' : 'w');
                        int *j = cont;
                        while (*j != -1){
                            move aux2;
                            aux2 = aux;
                            aux2.rem = *j;
                            ret.numberOfMoves++;
                            ret.moves = (move*)realloc(ret.moves, ret.numberOfMoves * sizeof(move));
                            ret.moves[ret.numberOfMoves-1] = aux2;
                            j++;
                        }
                        free(cont);
                    } else{
                        ret.numberOfMoves++;
                        ret.moves = (move*)realloc(ret.moves, ret.numberOfMoves * sizeof(move));
                        ret.moves[ret.numberOfMoves-1] = aux;
                    }
                    k++;
                    free(b2);
                }
                i++;
            }
            free(blank);
        }
        else{
            while (*i != -1){
                int *blank = neighbours(*i);
                int *k = blank;
                while (*k != -1){
                    if(position[*k] == ' ') {
                        char *b2 = (char*)malloc(24* sizeof(char));
                        memcpy(b2, position, 24);
                        b2[*k] = b2[*i];
                        b2[*i] = ' ';
                        move aux;
                        aux.src = *i;
                        aux.value = 12345;
                        aux.rem = -1;
                        aux.dest = *k;
                        if (mill(b2, *k)) {
                            int *cont = contains(b2, (token == 'w') ? 'b' : 'w');
                            int *j = cont;
                            while (*j != -1) {
                                move aux2;
                                aux2 = aux;
                                aux2.rem = *j;
                                ret.numberOfMoves++;
                                ret.moves = (move *) realloc(ret.moves, ret.numberOfMoves * sizeof(move));
                                ret.moves[ret.numberOfMoves - 1] = aux2;
                                j++;
                            }
                            free(cont);
                        } else {
                            ret.numberOfMoves++;
                            ret.moves = (move *) realloc(ret.moves, ret.numberOfMoves * sizeof(move));
                            ret.moves[ret.numberOfMoves - 1] = aux;
                        }
                        free(b2);
                    }
                    k++;
                }
                i++;
                free(blank);
            }
        }
        free(empty);
    }

    return ret;
}

move minimax(char *position, unsigned int depth, int alpha, int beta, int step, bool maximizingPlayer, move thisMove){
    //checking win conditions
    if(step >= 18){
        if(numberOf(position, 'w') == 2){
            thisMove.value = -1000;
            return thisMove;
        }
        if(numberOf(position, 'b') == 2){
            thisMove.value = 1000;
            return thisMove;
        }
    }

    //checking board value at bottom of tree
    if(depth == 0){
        thisMove.value = boardValue(position);
        return thisMove;
    }

    //looping through minimax tree
    if (maximizingPlayer == true){
        thisMove.value = -999999;
        possMov pm = getPossibleMoves(position, step, 'w');
        for (unsigned int i = 0; i < pm.numberOfMoves; i++) {
            char *b2 = (char*)malloc(24* sizeof(char));
            memcpy(b2,position,24);
            move aux = pm.moves[i];
            aux.value = -999999;
            if(aux.src != -1){
                b2[aux.src] = ' ';
            }
            b2[aux.dest] = 'w';
            if (aux.rem != -1){
                b2[aux.rem] = ' ';
            }
            move aux2 = minimax(b2,depth - 1,alpha,beta,step + 1, false,aux);
            aux.value = aux2.value;
            thisMove = (thisMove.value > aux.value) ? thisMove : aux;
            alpha = (alpha > aux.value) ? alpha : aux.value;
            if (alpha >= beta)
                i = 9999;
        }
        free(pm.moves);
        return thisMove;
    } else {
        thisMove.value = 999999;
        possMov pm = getPossibleMoves(position, step, 'b');
        for (unsigned int i = 0; i < pm.numberOfMoves; i++) {
            char *b2 = (char*)malloc(24* sizeof(char));
            memcpy(b2,position,24);
            move aux = pm.moves[i];
            aux.value = 999999;
            if(aux.src != -1){
                b2[aux.src] = ' ';
            }
            b2[aux.dest] = 'b';
            if (aux.rem != -1){
                b2[aux.rem] = ' ';
            }
            move aux2 = minimax(b2,depth - 1,alpha,beta,step + 1, true,aux);
            aux.value = aux2.value;
            thisMove = (thisMove.value < aux.value) ? thisMove : aux;
            beta = (beta < aux.value) ? beta : aux.value;
            if (alpha >= beta)
                i = 9999;
        }
        free(pm.moves);
        return thisMove;
    }
}

void display(){
    for (unsigned int i = 0; i < 24; i++) {
        switch (i){
            case 0:
                printf("%c", board[i]);
                printf("-----");
                break;
            case 1:
                printf("%c", board[i]);
                printf("-----");
                break;
            case 2:
                printf("%c", board[i]);
                printf("\n|     |     |\n");
                break;
            case 3:
                printf("| %c", board[i]);
                printf("---");
                break;
            case 4:
                printf("%c", board[i]);
                printf("---");
                break;
            case 5:
                printf("%c", board[i]);
                printf(" |\n| |   |   | |\n");
                break;
            case 6:
                printf("| | %c", board[i]);
                printf("-");
                break;
            case 7:
                printf("%c", board[i]);
                printf("-");
                break;
            case 8:
                printf("%c", board[i]);
                printf(" | |\n| | |   | | |\n");
                break;
            case 9:
                printf("%c", board[i]);
                printf("-");
                break;
            case 10:
                printf("%c", board[i]);
                printf("-");
                break;
            case 11:
                printf("%c", board[i]);
                printf("   ");
                break;
            case 12:
                printf("%c", board[i]);
                printf("-");
                break;
            case 13:
                printf("%c", board[i]);
                printf("-");
                break;
            case 14:
                printf("%c", board[i]);
                printf("\n| | |   | | |\n");
                break;
            case 15:
                printf("| | %c", board[i]);
                printf("-");
                break;
            case 16:
                printf("%c", board[i]);
                printf("-");
                break;
            case 17:
                printf("%c", board[i]);
                printf(" | |\n| |   |   | |\n");
                break;
            case 18:
                printf("| %c", board[i]);
                printf("---");
                break;
            case 19:
                printf("%c", board[i]);
                printf("---");
                break;
            case 20:
                printf("%c", board[i]);
                printf(" |\n|     |     |\n");
                break;
            case 21:
                printf("%c", board[i]);
                printf("-----");
                break;
            case 22:
                printf("%c", board[i]);
                printf("-----");
                break;
            case 23:
                printf("%c", board[i]);
                printf("\n");
                break;
        }
    }
}

int main() {
    printf("Hello, World!\n");
    initBoard();
    char ai1choice = ' ', ai2choice = ' ';
    char *prev1board = (char*)malloc(24* sizeof(char));
    char *prev2board = (char*)malloc(24* sizeof(char));
    int choice = -1;
    int player = 1;
    int steps = 0;
    memcpy(prev1board, board, 24);
    memcpy(prev2board, board, 24);
    int player1flight = 0, player2flight = 0;
    bool p1ai = false, p2ai = false;
    printf("Is player 1 ai?(y/n)\n");
    scanf("%c", &ai1choice);
    if (ai1choice == 'y' || ai1choice == 'Y')
        p1ai = true;
    printf("Is player 2 ai?(y/n)\n");
    scanf(" %c", &ai2choice);
    if (ai2choice == 'y' || ai2choice == 'Y')
        p2ai = true;

    int miniMaxDepth = 1;
    printf("Minimax Depth:\n");
    scanf("%d", &miniMaxDepth);
    do{
        if (((player == 1) ? p1ai : p2ai) == false) {
            display();
            printf("Player %d position:\n", player);
            possMov pm = getPossibleMoves(board, steps, (player == 1) ? 'w' : 'b');
            for (unsigned int i = 0; i < pm.numberOfMoves; i++) {
                move aux = pm.moves[i];
                if (aux.src != -1) {
                    printf("%d ---> ", aux.src);
                }
                printf("%d\n", aux.dest);
                if (aux.rem != -1) {
                    printf("Remove: %d\n", aux.rem);
                }
            }
            free(pm.moves);
            RECHOOSE:
            printf("-1 for hint, -2 to undo move or -3 to exit\n");
            scanf("%d", &choice);
            if(choice == -1){
                move aux;
                aux.rem = -1;
                aux.dest = -1;
                aux.src = -1;
                aux = minimax(board, miniMaxDepth, -999999, 999999, steps, ((player == 1) ? true : false), aux);
                if(aux.src != -1)
                    printf("Move piece at: %d ", aux.src);
                printf("Place at: %d", aux.dest);
                if(aux.src != -1)
                    printf("And remove piece at: %d ", aux.rem);
                printf("\n");
                goto RECHOOSE;
            }
            else if (choice == -2){
                printf("Not yet implemented");
                //TODO
                memcpy(board, prev2board, 24);
                //goto RECHOOSE;
            }
            system("tput reset");
            if (steps < 18) {
                if (choice >= 0 && choice < 24) {
                    memcpy(prev2board, prev1board, 24);
                    memcpy(prev1board, board, 24);
                    if (board[choice] == ' ') {
                        board[choice] = (player == 1) ? 'w' : 'b';
                        if (mill(board, choice)) {
                            int *cont = contains(board, (player == 1) ? 'b' : 'w');
                            printf("Remove which:\n");
                            int *j = cont;
                            while (*j != -1) {
                                printf("%d\n", *j);
                                j++;
                            }
                            int pos = -1;
                            scanf("%d", &pos);
                            board[pos] = ' ';
                            free(cont);
                        }
                        player = (player == 1) ? 2 : 1;
                    }
                }
            } else {
                if (choice >= 0 && choice < 24) {
                    memcpy(prev2board, prev1board, 24);
                    memcpy(prev1board, board, 24);
                    switch (player) {
                        case 1:
                            if (board[choice] == 'w') {
                                printf("Move to:\n");
                                if (player1flight == 0) {
                                    int *ret = neighbours(choice);
                                    int *i = ret;
                                    int choice2 = -1;
                                    //int possible = 0;
                                    while (*i != -1) {
                                        printf("%d\n", *i);
                                        i += 1;
                                    }
                                    scanf("%d", &choice2);
                                    i = ret;
                                    while (*i != -1) {
                                        if (*i == choice2) {
                                            if (choice2 >= 0 && choice2 <= 23) {
                                                if (board[choice2] == ' ') {
                                                    board[choice] = ' ';
                                                    board[choice2] = 'w';
                                                    if (mill(board, choice2)) {
                                                        int *cont = contains(board, 'b');
                                                        printf("Remove which:\n");
                                                        int *j = cont;
                                                        while (*j != -1) {
                                                            printf("%d\n", *j);
                                                            j++;
                                                        }
                                                        int pos = -1;
                                                        scanf("%d", &pos);
                                                        board[pos] = ' ';
                                                        if (numberOf(board, 'b') == 3) {
                                                            player2flight = 1;
                                                        } else if (numberOf(board, 'b') == 2) {
                                                            printf("Player One wins!\n");
                                                            display();
                                                            free(cont);
                                                            return 0;
                                                        }
                                                        free(cont);
                                                    }
                                                    player = 2;
                                                }
                                            }
                                        }
                                        i += 1;
                                    }
                                    free(ret);
                                } else {
                                    int choice2 = -1;
                                    scanf("%d", &choice2);
                                    if (choice2 >= 0 && choice2 <= 23) {
                                        if (board[choice2] == ' ') {
                                            board[choice] = ' ';
                                            board[choice2] = 'w';
                                            if (mill(board, choice2)) {
                                                int *cont = contains(board, 'b');
                                                printf("Remove which:\n");
                                                int *j = cont;
                                                while (*j != -1) {
                                                    printf("%d\n", *j);
                                                    j++;
                                                }
                                                int pos = -1;
                                                scanf("%d", &pos);
                                                board[pos] = ' ';
                                                if (numberOf(board, 'b') == 3) {
                                                    player2flight = 1;
                                                } else if (numberOf(board, 'b') == 2) {
                                                    printf("Player One wins!\n");
                                                    free(cont);
                                                    //free(j);
                                                    return 0;
                                                }
                                                free(cont);
                                                //free(j);
                                            }
                                            player = 2;
                                        }
                                    }
                                }
                            }
                            break;
                        case 2:
                            if (board[choice] == 'b') {
                                printf("Move to:\n");
                                if (player2flight == 0) {
                                    int *ret = neighbours(choice);
                                    int *i = ret;
                                    int choice2 = -1;
                                    //int possible = 0;
                                    while (*i != -1) {
                                        printf("%d\n", *i);
                                        i += 1;
                                    }
                                    scanf("%d", &choice2);
                                    i = ret;
                                    while (*i != -1) {
                                        if (*i == choice2) {
                                            if (choice2 >= 0 && choice2 <= 23) {
                                                if (board[choice2] == ' ') {
                                                    board[choice] = ' ';
                                                    board[choice2] = 'b';
                                                    if (mill(board, choice2)) {
                                                        int *cont = contains(board, 'w');
                                                        printf("Remove which:\n");
                                                        int *j = cont;
                                                        while (*j != -1) {
                                                            printf("%d\n", *j);
                                                            j++;
                                                        }
                                                        int pos = -1;
                                                        scanf("%d", &pos);
                                                        board[pos] = ' ';
                                                        if (numberOf(board, 'w') == 3) {
                                                            player1flight = 1;
                                                        } else if (numberOf(board, 'w') == 2) {
                                                            free(cont);
                                                            //free(j);
                                                            printf("Player Two wins!\n");
                                                            return 0;
                                                        }
                                                        free(cont);
                                                        //free(j);
                                                    }
                                                    /*memcpy(prev2board, prev1board, 24);
                                                    memcpy(prev1board, board, 24);*/
                                                    player = 1;
                                                }
                                            }
                                        }
                                        i += 1;
                                    }
                                    free(ret);
                                } else {
                                    int choice2 = -1;
                                    scanf("%d", &choice2);
                                    if (choice2 >= 0 && choice2 <= 23) {
                                        if (board[choice2] == ' ') {
                                            board[choice] = ' ';
                                            board[choice2] = 'b';
                                            if (mill(board, choice2)) {
                                                int *cont = contains(board, 'w');
                                                printf("Remove which:\n");
                                                int *j = cont;
                                                while (*j != -1) {
                                                    printf("%d\n", *j);
                                                    j++;
                                                }
                                                int pos = -1;
                                                scanf("%d", &pos);
                                                board[pos] = ' ';
                                                if (numberOf(board, 'w') == 3) {
                                                    player1flight = 1;
                                                } else if (numberOf(board, 'w') == 2) {
                                                    printf("Player Two wins!\n");
                                                    free(cont);
                                                    //free(j);
                                                    return 0;
                                                }
                                                free(cont);
                                                //free(j);
                                            }
                                            /*memcpy(prev2board, prev1board, 24);
                                            memcpy(prev1board, board, 24);*/
                                            player = 1;
                                        }
                                    }
                                }
                                break;
                            }
                    }
                }
            }
        } else {
            display();
            memcpy(prev2board, prev1board, 24);
            memcpy(prev1board, board, 24);
            sleep(1);
            move ret;
            ret.value = (player == 1) ? -999999 : 999999;
            ret.rem = -1;
            ret.dest = -1;
            ret.src = -1;
            ret = minimax(board,miniMaxDepth,-999999, 999999, steps, (player == 1) ? true : false, ret);
            if (ret.src != -1) {
                printf("%d ---> ", ret.src);
                board[ret.src] = ' ';
            }
            printf("%d\n", ret.dest);
            board[ret.dest] = (player == 1) ? 'w' : 'b';
            if (ret.rem != -1) {
                printf("rem: %d\n", ret.rem);
                board[ret.rem] = ' ';
            }
            player = (player == 1) ? 2 : 1;
            system("tput reset");
            choice = 3;
            if (numberOf(board, (player == 1) ? 'b' : 'w') == 2 && steps > 18){
                display();
                printf("Player %d wins!\n", (player == 1) ? 1 : 2);
                choice = -3;
            }
        }
        steps++;
        /*memcpy(prev2board, prev1board, 24);
        memcpy(prev1board, board, 24);*/
    }
    while (choice != -3);

    printf("Positions with ' ' token:\n");

    int *ret = contains(board, ' ');
    int *i = ret;
    while(*i != -1){
        printf("%d\n", *i);
        i += 1;
    }
    free(ret);
    free(board);
    free(prev1board);
    free(prev2board);

    return 0;
}