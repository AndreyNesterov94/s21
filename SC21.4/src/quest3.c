#include <stdio.h>

int fib(int n);

int main() {
    int n, result;

    if (scanf("%d", &n) != 1 || getchar() != '\n') {
        printf("n/a");
        return 0;
    }

    result = fib(n);

    if (result < 0) {
        printf("n/a");
    } else {
        printf("%d", result);
    }

    return 0;
}

int fib(int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fib(n - 1) + fib(n - 2);
    }
}