#include<stdio.h>
#define SIZE 3
void transpose(int[SIZE][SIZE]);
void swap2Rows (int M[SIZE][SIZE], int r1, int r2);
void swap2Cols (int M[SIZE][SIZE], int c1, int c2);
void display(int M[SIZE][SIZE]);
int main (void)
{   int i,j,m,n;
    int M[SIZE][SIZE]={};
    printf("Please enter nine numbers:");
    for (m=0;m<3;m++)
    {
        for(n=0;n<3;n++)
        {
            scanf("%d",M[m]+n);
        }
    }
    display(M);
    transpose(M);
    swap2Rows(M,1,2);
    swap2Cols(M,1,2);
    return 0;
}
void display(int M[SIZE][SIZE])
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            printf("%-6d",M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void transpose(int M[SIZE][SIZE])
{
    int a;
	int i,j;
	for (i=0;i<3;i++)
	{
		for (j=i+1;j<3;j++)
		{
			a=M[i][j];
			M[i][j]=M[j][i];
			M[j][i]=a;
		}
    }
    display(M);
}
void swap2Rows (int M[SIZE][SIZE], int r1, int r2)
{
    int a,i,j;
    for(j=0;j<3;j++)
    {
        a=M[r1][j];
        M[r1][j]=M[r2][j];
        M[r2][j]=a;
    }
    display(M);
}
void swap2Cols (int M[SIZE][SIZE], int c1, int c2)
{
    int a,i,j;
    for(i=0;i<3;i++)
    {
        a=M[i][c1];
        M[i][c1]=M[i][c2];
        M[i][c2]=a;
    }
    display(M);
}
