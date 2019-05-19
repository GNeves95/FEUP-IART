//
// Created by linuxlite on 05-04-2019.
//

#ifndef KLOTSKI_UTILS_H
#define KLOTSKI_UTILS_H

typedef enum bool {true= 1, false= 0} bool;

typedef struct movement {
    int bid;
    char direction;
} movement;

#define endl printf("\n")

#endif //KLOTSKI_UTILS_H
