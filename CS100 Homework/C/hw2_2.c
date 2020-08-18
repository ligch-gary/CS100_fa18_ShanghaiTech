#include <stdio.h>
void extOddDigits(long n, long *nd);
int main(void)
{
    long n,result;
    printf("enter a number n:");
    scanf("%ld",&n);
    extOddDigits(n, &result);
    printf("%d",result);
    return 0;
}
void extOddDigits(long n, long *nd)
{
   long digit;
   int power=1;
   long result=0;
   do
   {
       digit = n % 10;
       if (digit % 2 != 0)
       {
           result += digit * power;
           power *=10;
       }
       n /= 10;
   }while(n>0);
   if (power==1)
     result = -1;
    *nd = result;
}