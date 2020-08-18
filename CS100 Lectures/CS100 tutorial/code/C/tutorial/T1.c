//
// Created by dell on 2018/10/14.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXIMUM 13
#define MINIMUM 1

#include "../include/T1.h"

int T1_P3() {
    int total, count, lines, input;
    int i;
    printf("Enter the number of input lines: ");
    scanf("%d", &lines);
    getchar();

    for (i = 0; i < lines; i++) {
        total = 0;
        count = 0;
        printf("Enter line %d: ", i);
        scanf("%d", &input);
        while (input != -1) {
            total += input;
            count++;
            scanf("%d", &input);
        }
        double average = (double) total / (double) count;
        printf("Average: %f\n", average);
    }
    return 0;

}

int T1_P4() {
    int card1 = 0, card2 = 0;
    int i;
    char reply;
    srand((unsigned int)time(NULL));
    card1 = (rand() % MAXIMUM) + MINIMUM;
    printf("The first card (between 1 and 13): %d\n", card1);
    for (i = 0; i < 4; i++) {
        printf("Guess Higher(H) or Lower(L): ");

        scanf("%c", &reply);
        getchar(); // something needs to change
        srand((unsigned int)time(NULL));
        card2 = (rand() % MAXIMUM) + MINIMUM;
        printf("The next card (between 1 and 13): %d\n", card2);
        if ((card1 > card2 && reply == 'H') ||
            (card1 < card2 && reply == 'L'))
            break;
        card1 = card2;
    }
    if (i == 4)
        printf("You win\n");
    else
        printf("You lose\n");
    return 0;

}