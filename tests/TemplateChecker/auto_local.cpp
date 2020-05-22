#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;

int main() {
  int a = 1;
  int b, c;
  b = (int)random();
  if (b == a) {
    int a = 1;
    c = a;
  }
  a = c + b;
  printf("%d\n", c);

  return 0;
}
