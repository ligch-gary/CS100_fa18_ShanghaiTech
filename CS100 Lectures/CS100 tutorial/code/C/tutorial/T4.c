//
// Created by dell on 2018/10/28.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "../include/T4.h"

/* --------------------------------------------------------------------------- */
/* --------------------- This is designed for Question 1 --------------------- */

int T4_P1_intersect(struct circle c1, struct circle c2) {
    double a, b;
    a = c1.x - c2.x;
    b = c1.y - c2.y;
    return (sqrt(a * a + b * b) <= (c1.radius + c2.radius));
}

int T4_P1_contain(struct circle *c1, struct circle *c2) {
    double a, b;
    a = c1->x - c2->x;
    b = c1->y - c2->y;
    return (c1->radius >= (c2->radius + sqrt(a * a + b * b)));
}

void T4_P1() {
    struct circle c1 = {0, 0, 1};
    struct circle c2 = {1, 0, 1};
    int b1 = T4_P1_intersect(c1, c2);
    int b2 = T4_P1_contain(&c1, &c2);
    printf("if intersect: %d\n", b1);
    printf("if contain: %d\n", b2);
}

/* --------------------------------------------------------------------------- */
/* --------------------- This is designed for Question 2 --------------------- */

void getInput(leaveRecord *list, int *n) {
    *n = 0;

    while (~scanf("%d %d %d", &list[*n].id, &list[*n].totalLeave, &list[*n].leaveTaken)!=EOF) { // on my laptop (Windows) this is OK, yours may need some change
        (*n)++;
    }
    getchar();
}

int mayTakeLeave(leaveRecord list[], int id, int leave, int n) {
    int p;
    for (p = 0; p < n; p++)
        if (list[p].id == id)
            return (list[p].totalLeave >= list[p].leaveTaken + leave);
    return -1;
}

void T4_P2() {
    leaveRecord list[100];
    int n;
    getInput(list, &n);
    printf("the total id is: %d\nPlease input the id and ask_for_leave_days: ", n);
    int idd,ask_days;
    scanf("%d %d",&idd,&ask_days);
    int if_allowed = mayTakeLeave(list, idd, ask_days, n);
    printf("The application result is: %d\n", if_allowed);
}

/* --------------------------------------------------------------------------- */
/* --------------------- This is designed for Question 3 --------------------- */

int sumUp(int n) {
    if (n == 1)
        return 1;
    else
        return n + sumUp(n - 1);
}

int sumUp2(int n) {
    int i, sum;
    sum = 0;
    for (i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

void T4_P3() {
    int result1 = sumUp(4);
    int result2 = sumUp2(4);
    printf("the result1 is: %d\n", result1);
    printf("the result2 is: %d\n", result2);
}

/* --------------------------------------------------------------------------- */
/* --------------------- This is designed for Question 4 --------------------- */

float power1(float x, int n) {
    if (n == 0)
        return 1;
    else if (n < 0)
        return power1(x, n + 1) / x;
    else
        return power1(x, n - 1) * x;
}

void power2(float x, int n, float *y) {
    if (n == 0) {
        *y = 1;
    } else if (n < 0) {
        power2(x, n + 1, y);
        *y /= x;
    } else {
        power2(x, n - 1, y);
        *y *= x;
    }
}

void T4_P4() {
    float result1 = power1(2, -3); //注意负数的处理
    float result2;
    power2(2, -3, &result2);
    printf("the result1 is: %f\n", result1);
    printf("the result2 is: %f\n", result2);
}

/* --------------------------------------------------------------------------- */
/* ------------------- This is designed for Tower of Hanoi ------------------- */

void Hanoi(int n, char from, char to, char buffer){
    if(n==1){
        printf("This is Hanoi depth We move the %d-th disk from %c to %c via %c\n", n, from, to, buffer);
        return;
    }

    Hanoi(n-1,from,buffer,to);
    printf("This is Hanoi depth We move the %d-th disk from %c to %c\n", n, from, to);
    Hanoi(n-1, buffer, to,from);
}

