#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;

void mem_leak1(int n) {
  new int;
  int *p;
  int *q = (int *)malloc(sizeof(int)*n);
}


void mem_leak1_fix(int n) {
  int *p;
  p = new int;
  delete p;
  int *q = (int *)malloc(sizeof(int)*n);
  free(q);
}


void mem_leak3(int n) {
  int *o;
  o = (int *)malloc(sizeof(int)*(n+1));
  int *a = o;

}


void mem_leak3_fix(int n) {
  int *o;
  o = (int *)malloc(sizeof(int)*(n+1));
  int *a = o;
  free(a);
}
