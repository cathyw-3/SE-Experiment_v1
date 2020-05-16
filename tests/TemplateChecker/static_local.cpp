#include<stdio.h>
#include<string.h>

int main() {
  static char* i;
  strcpy(i, "ast");
  if (i != nullptr)
    printf("%s\n", i);

  return 0;
}
