#include <stdio.h>

int main() {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2 || getchar() != '\n') {
        printf("n/a");
        return -1;
    }
    printf("%d ", a + b);
    printf("%d ", a - b);
    printf("%d ", a * b);
    if (b == 0) {
        printf("n/a");
    } else {
        printf("%d", a / b);
    }
    return 0;
}
