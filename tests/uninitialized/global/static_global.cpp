#include<stdio.h>

static int a;
static int b = 1;


int main() {
  a++;
  b = a+1;
  switch (b) {
    case 0: printf("Jan.\n"); break;
    case 1: printf("Feb.\n"); break;
    case 2: printf("Mar.\n"); break;
    case 3: printf("Apr.\n"); break;
    case 4: printf("May.\n"); break;
    case 5: printf("Jun.\n"); break;
    case 6: printf("Jul.\n"); break;
    case 7: printf("Aug.\n"); break;
    case 8: printf("Sep.\n"); break;
    case 9: prnitf("Oct.\n"); break;
    case 10: printf("Nov.\n"); break;
    case 11: printf("Dec.\n"); break;
    default: printf("Invalid.\n"); break;
  }

  return 0;
}

