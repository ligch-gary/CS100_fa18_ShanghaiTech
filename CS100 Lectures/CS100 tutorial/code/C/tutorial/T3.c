#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/T3.h"

/* --------------------- This is designed for Question 1 --------------------- */
void getFrequency(int histogram[10], int n);
void printFrequency(int histogram[10]);

void T3_P1(){
    int frequencies[10];
    int total;
    printf("Please input the number of random numbers: ");
    scanf("%d", &total);
    srand(time(NULL));
    getFrequency(frequencies, total);
    printFrequency(frequencies);
}
void getFrequency(int histogram[10], int n)
{
    int count;
    for (count = 0; count < 10; count++)
        histogram[count] = 0; // initialize the array
    for (count = 0; count < n; count++)
        histogram[(rand() % 100)/10]++; // allocate value randomly
}
void printFrequency(int histogram[10])
{
    int count, index;
    for (count = 0; count < 10; count++) {
        printf("%2d -- %2d |", count*10, count*10+9);
        for (index = 0; index < histogram[count]; index++ ) {
            putchar('*');
        }
        putchar('\n');
    }
}

/* --------------------- This is designed for Question 2 --------------------- */

void add1(int ar[], int size);
void display(int ar[3][4]);
int T3_P2(){
    int h, k;
    int ar[3][4] = {
            {5, 10, 15, 20},
            {10, 20, 30, 40},
            {20, 40, 60, 80}
    };
    display(ar);
//    for (h = 0; h < 3; h++) { add1(ar[h], 4); } /* line a */
    add1(ar[1], 3*4); /* line a */
    printf("After line a: \n");
    display(ar);
    return 0;
}
void add1(int ar[], int size){
    int k;
    for (k = 0; k < size; k++)
        ar[k]++;
}

void display(int ar[3][4]){
    int l,m;
    for (l=0; l<3; l++) {
        for (m = 0; m < 4; m++) {
            printf("%5d",ar[l][m]);
        }
        printf("\n");
    }
}

/* --------------------- This is designed for Question 3 --------------------- */

#define M1 "How are ya, sweetie?"
char M2[40] = "Beat the clock.";
char *M3 = "chat";
int T3_P3()
{
    char words[80];
    printf(M1);
    puts(M1);
    puts(M2);
    puts(M2+1);
    gets(words); /* user inputs : win a toy. */
    puts(words);
    scanf("%s", words+6); /* user inputs : snoopy. */
    puts(words);
    words[3] = '\0';
    puts(words);
    while (*M3) puts(M3++);
    puts(--M3);
    puts(--M3);
    M3 = M1;
    puts(M3);
    return 0;
}

/* --------------------- This is designed for const test! ------------------ */

extern int global_const;
//extern int static_const; //error, extern static int also wrong!!!

void T3_const_test(){
    printf("%d",global_const);
//    printf("%d",static_const); //error!!!
}

/* --------------------- This is designed for storage test! ------------------ */
static char * str_const = "change all of a to *";
void Replace(char*,char old_char, char new_char);

void T3_storage_test(){
    printf("Before: ");
    puts(str_const);
    char str_local_array[]="change all of a to *";
    char* str_local_const="change all of a to *";
//    Replace(str_const,'a','*');
//    Replace(str_local_const,'a','*');
    Replace(str_local_array,'a','*');
}

void Replace(char* str, char old_char, char new_char){
    printf("After:  ");
    int i;
    int length = strlen(str);
    for (i = 0; i < length; ++i) {
        if(str[i]==old_char){
            str[i]=new_char;
        }
    }
    puts(str);
}

/* --------------------- This is designed for char test! ------------------ */
void T3_char_test(){
    char a[]="abc";//"abc" is copied first (in stack), then the copy is given to a
    char* b="abc";  //b is in stack, it points to the address of "abc" in 文字常量区
//    char* c=new char[3]; //c++
    char* c=(char*) malloc(3); //c
    c="abc"; // Terribly wrong! This assignment means you make c redirect to the address of "abc",
//                in such case you will lose the address that allocate memory before, and then you cannot free c!
    strcpy(c,"abc"); //make a copy of "abc" into the memory (in heap) allocated to c before

    printf("%p\n",a); //also: printf("%p",&a)
    printf("%p\n",&b);
    printf("%p\n",&c);

    printf("%p ### %p\n", &a, a);//这两个值是一样的,应该都是栈中数组a的起始地址
    printf("%p ### %p\n", &b, b);//不一样, &b是栈中指针b的地址,b是b指向的文字常量区中"abc"所在的地址
    printf("%p ### %p\n", &c, c);//不一样, &c是栈中指针c的地址,c是c指向的堆中"abc"所在的地址
    //注意！从显示得到的地址结果中可以看出：“栈、堆、文字常量区”三者在不同的区域！
//    delete c; //c++
    free(c);
}






