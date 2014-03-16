#include <stdio.h>
#include <stdbool.h>

int B(int a, int b, int c) 
{ 
 int x; 
 int y; 
 // x = a * b + c; 
if(4<4)
	y = 77777;
else
	y = 999999;
 return y; 
} 
 
int A(int a, int b) 
{ 
 int x; 
 int y; 
 int z; 
 int r; 
 
 x = 2; 
 y = 5; 
 z = a+b; 
 r = B(x,y,z); 
 return r; 
} 
int main() 
{ 
 int r = 5; 
 r = A(0,12); 
 printf("%d\n",r); 
} 
