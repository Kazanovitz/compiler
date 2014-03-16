#include <stdio.h>

extern int Tester(int a, int b);

int main() {
    // These parameters will be avilable to your ASM code
    // Change them to whatever value you want
    int parameter1 = 10;
    int parameter2 = 3;
    
    int result = Tester(parameter1, parameter2);
    printf("Start returned %d.\n", result);
}