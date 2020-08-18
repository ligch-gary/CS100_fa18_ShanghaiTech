#include <stdio.h>
void rsquare(int, int *);
int main() {
 int x, result;
 
 printf("Enter a number:\n");
 scanf("%d", &x);
 rsquare(x, &result);
 printf("Result: %d\n", result);
 return 0;
}
void rsquare(int num, int *result)
{
    *result = 0;
    if (num==0){
        *result = *result + 0;
    }
    else
    {
        rsquare (num-1,result);
        *result = *result + 2*num-1;
    }

}