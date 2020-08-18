#include <stdio.h>
typedef struct {
 float operand1, operand2;
 char operator;
} bexpression;
float compute1(bexpression expr);
float compute2(bexpression *expr);
int main() {
 bexpression e;
 char repeat = 'y';
 do {
 printf("Enter expression (op1 op2 op) :\n");
 scanf("%f %f %c", &e.operand1, &e.operand2, &e.operator);
 printf("compute1 = %f\n", compute1(e));
 printf("compute2 = %f\n", compute2(&e));
 getchar();
 printf("\nContinue ('y' or 'n') :\n");
 scanf("%c", &repeat);
 } while (repeat == 'y');
 return 0;
}
float compute1(bexpression expr) {
 float a;
 switch(expr.operator){
     case '+': a = expr.operand1 + expr.operand2;
     break;
     case '-': a = expr.operand1 - expr.operand2;
     break;
     case '/': a = expr.operand1 / expr.operand2;
     break;
     case '*': a = expr.operand1 * expr.operand2;
 }
 return a;
}
float compute2(bexpression *expr) {
 float a;
 switch((*expr).operator){
     case '+': a = (*expr).operand1 + (*expr).operand2;
     break;
     case '-': a = (*expr).operand1 - (*expr).operand2;
     break;
     case '/': a = (*expr).operand1 / (*expr).operand2;
     break;
     case '*': a = (*expr).operand1 * (*expr).operand2;
     break;
 }
 return a;
}