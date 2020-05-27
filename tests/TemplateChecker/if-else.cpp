#include <stdio.h>
#include <iostream>
using namespace std;

int main() {
    int c = (int)random();
    c = c + 1;
    int a = c;
    int b = 0;
    if (c != 1) {
        a = 1;
        b = -1;
    }
    if (c != 2) {
        c = a + b;
    }
    printf("%d\n", c);
    for (int i = 0; i < 3; ++i) {
        ++c;
    }
    //return 0;
}