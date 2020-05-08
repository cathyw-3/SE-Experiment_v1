#include<stdio.h>

int global;

void increase() {
  int tmp = global;
  for(int i = 0; i < tmp+1; i++){
    global++;
  }
}

int main() {

  global++;
  
  for(int j = 0; j < 2; j++)
    increase();
  
  printf("%d\n", global);
  return 0;
}
