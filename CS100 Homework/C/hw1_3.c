#include<stdio.h>
int main()
{
    float x,Result,sum,t=1;
    int n,i;
    sum=0;
    printf("Please enter the value of n:");
    scanf("%d",&n);
    printf("Please enter the value of x:");
    scanf("%f",&x);
    for ( i=1;i<=n;i++)
    {
    	t *= x/i;
    	sum += t;
    }    
    Result = 1+sum;
    printf("Result= %f",Result);
    system("pause");
    return 0;  
}
