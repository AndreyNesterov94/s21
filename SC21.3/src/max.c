#include <stdio.h>

int max(int x, int y) { return (x > y) ? x : y; }

int main() {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2 || getchar() != '\n') {
        printf("n/a");
        return -1;
    }

    printf("%d", max(a, b));
    return 0;
}
