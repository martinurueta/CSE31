#include<stdio.h>

int f1(int n) {
    if(n > 0){
         return --n;
    }
       
    else{
        return n + f1(n+2);
    }
        
}

int main() {
    int x;
    printf("Please enter an integer: ");
	scanf("%d", &x);
    printf("%d\n", f1(x));
    return 0;
}