//
// Created by dell on 2018/10/28.
//

#ifndef C_CODE_T4_H
#define C_CODE_T4_H
struct circle {
    double radius;
    double x;
    double y;
};
typedef struct {
    int id; /* staff identifier */
    int totalLeave; /* the total number of days of leave allowed */
    int leaveTaken; /* the number of days of leave taken so far */
} leaveRecord;

void T4_P1();
void T4_P2();
void T4_P3();
void T4_P4();
void Hanoi(int n, char from, char buffer, char to);

#endif //C_CODE_T4_H
