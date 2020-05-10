#include <stdio.h>
#include <string.h>

int main() {
  char *name;
  int age = 20;
  strcpy(name, "John");
  printf("%s %d\n", name, age);
  return 0;
}
