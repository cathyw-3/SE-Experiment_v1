#include<stdio.h>

int main() {
  int a, b, c;
  scanf("%d %d", &a, &b);
  if (b == a) {
    c = a;
  }
  a = c + b;
  printf("%d\n", c);

  return 0;
}
