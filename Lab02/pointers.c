#include <stdio.h> 
 
 int main() { 
  int x, y, *px, *py; 
  int arr[10]; 
  printf("%d \n", x);
  printf("%d \n", y);
  printf("%d \n", px);
  printf("%d \n", py);
  printf("%d \n", arr[0]);
  px = &x;
  py = &y;
  printf("%d \n", py);
  printf("%d \n", px);
  printf("%d \n", &y);
  printf("%d \n", &x);
  printf("%d \n", &py);
  printf("%d \n", &px);
  for(int i = 0; i < 10; i++){
      printf("%d ", *(arr + i));
  }


  return 0; 
 }