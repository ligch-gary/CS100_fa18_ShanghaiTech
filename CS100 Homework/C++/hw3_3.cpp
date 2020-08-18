#include <stdlib.h>
#include <iostream>
class FibonacciGenerator {
private:
    int num1, num2;
public:
    void PrintAndAdvance();
    FibonacciGenerator(){
        num1=0;
        num2=1;
    }
    FibonacciGenerator(int x,int y){
        num1=x;
        num2=y;
    }
};

void FibonacciGenerator :: PrintAndAdvance() {
    int a = num1,num3;
    std::cout << "The next number is "<<a<<std::endl;
    num3 = num1 + num2;
    num1 = num2;
    num2 = num3;

}
int main() {
    FibonacciGenerator fg1;
    for( int i = 0; i < 10; i++ )
        fg1.PrintAndAdvance();
    std::cout << "\n";

    int number1;
    int number2;
    std::cin >> number1 >> number2;
    FibonacciGenerator fg2(number1, number2);
    for( int i = 0; i < 10; i++ )
        fg2.PrintAndAdvance();
    std::cout << "\n";

    return 0;
}