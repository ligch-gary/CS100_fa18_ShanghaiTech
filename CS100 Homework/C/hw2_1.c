#include <stdio.h>
int digitvalue(int n,int k);
int main(void)
{
   int n,k;
   printf("enter number n:");
   scanf("%d",&n);
   printf("enter number k:");
   scanf("%d",&k);
   printf("%d",digitvalue(n,k));
   return 0; 
}
int digitvalue(int n,int k)
{
    int i,j,mod;
    for(i=0;i<k;i++)
        {
            mod = n % 10;
            n = n/10;
        }    
     if(n=0)
     return 0;
     else
     return mod;
}