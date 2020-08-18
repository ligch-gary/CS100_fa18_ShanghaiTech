//
// Created by dell on 2018/10/14.
//
#include <stdio.h>

#include "../include/T2.h"

void function0(void);

void function1(int h, int k);

void function2(int *h, int *k);

int T2_P2(int i, int j) {
    int h, k;
    h = 5;
    k = 15;
    printf("main 1: \th = %d, k = %d\n", h, k);
    function0();
    printf("main 2: \th = %d, k = %d\n", h, k);
    function1(h, k);
    printf("main 3: \th = %d, k = %d\n", h, k);
    function2(&h, &k);
    printf("main 4: \th = %d, k = %d\n", h, k);
    return 0;
}

void function0() {
    int h, k;
    h = k = -100;
    printf("function 0.1: \th = %d, k = %d\n", h, k);
}

void function1(int h, int k) {
    printf("function 1.1: \th = %d, k = %d\n", h, k);
    h = k = 100;
    printf("function 1.2: \th = %d, k = %d\n", h, k);
}

void function2(int *h, int *k) {
    printf("function 2.1: \th = %d, k = %d\n", *h, *k);
    *h = *k = 200;
    printf("function 2.2: \th = %d, k = %d\n", *h, *k);
}

//this is for problem--3
long groupDigits1(long);
void groupDigits2(long, long *);

int T2_P3() {
    long number, result;
    printf("Enter number (-1 to end): ");
    scanf("%d", &number);
    while (number != -1) {
        printf("GroupDigits1() = %d\n", groupDigits1(number));
        groupDigits2(number, &result);
        printf("GroupDigits2() = %d\n", result);
        printf("Enter number (-1 to end): ");
        scanf("%d", &number);
    }
    return 0;
}

long groupDigits1(long n) {
    long digit;
    int gp1power = 1;
    long gp1result = 0;
    do {
        digit = n % 10;
        if (digit < 5) {
            gp1result += digit * gp1power;
            gp1power *= 10;
        }
        n /= 10;
    } while (n > 0);
    if (gp1power == 1)
        gp1result = -1;
    return gp1result;
}

void groupDigits2(long n, long *nd) {
    long digit;
    int gp1power = 1;
    long gp1result = 0;
    do {
        digit = n % 10;
        if (digit < 5) {
            gp1result += digit * gp1power;
            gp1power *= 10;
        }
        n /= 10;
    } while (n > 0);
    if (gp1power == 1)
        gp1result = -1;
    *nd = gp1result;
}