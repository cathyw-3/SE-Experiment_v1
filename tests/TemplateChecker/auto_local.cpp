#include<stdio.h>

int main() {
  int a = 1;
  int b, c;
  scanf("%d", &b);
  if (b == a) {
    int a = 1;
    c = a;
  }
  a = c + b;
  printf("%d\n", c);

  return 0;
}
