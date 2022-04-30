#include<stdio.h>

int bar(int a, int b, int c) {
    return c - a << b;
}

int foo(int m, int n, int o) {
    int p = bar(m + n, n + o, o + m); // bar(2+3,3+4,4+2) == bar (5,7,6) == 128
    int q = bar(m - o, n - m, 2 * n); // bar(2-4,3-2,2*3) == bar(-2,1,6) == 16 
    return p + q;
}

int main() {
    int x = 2, y = 3, z = 4;
    z = x + y + z + foo(x, y, z);
    printf("%d\n", z);
    return 0;
}
