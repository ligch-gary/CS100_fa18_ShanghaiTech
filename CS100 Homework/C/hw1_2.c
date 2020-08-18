#include<stdio.h>
int main()
{
    float a1,b1,c1,a2,b2,c2,x,y;
    printf("Enter the values for a1, b1, c1, a2, b2, c2:");
    scanf("%f %f %f %f %f %f",&a1,&b1,&c1,&a2,&b2,&c2);
    x=(b2*c1-b1*c2)/(a1*b2-a2*b1);
    y=(a1*c2-a2*c1)/(a1*b2-a2*b1);
    printf("x=%f\n",x);
    printf("y=%f\n",y);
    return 0;
}
    