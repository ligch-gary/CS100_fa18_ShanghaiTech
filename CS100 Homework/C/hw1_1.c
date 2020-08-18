#include<stdio.h>
int main(void)
{
   float C,F;
   printf("Enter the temperature in degree F: ");
   scanf("%f",&F);
   C = (5.0 / 9.0) *(F-32);
   printf("Converted degree in C: %f\n",C);
   return 0;
}
