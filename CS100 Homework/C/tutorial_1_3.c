#include<stdio.h>
int main(void)
{
    int L,i = 0,n,a = 0,s = 0;
    float average=0;
    printf ("Enter the number of input lines:");
    scanf ("%d",&L);
    for (i=1;i<=L;i++)
        {
            printf("Enter input line %d:",i);
            
            while (1)
            {   
                scanf("%d",&n); 
                s += n;
                a++;   
                if(getchar()==\n)
                break;   
            }
            average = s/a;
            printf("Average:%f\n",average);
            
        }
    system("pause");
    return 0;
}