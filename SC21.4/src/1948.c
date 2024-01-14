#include <math.h>
#include <stdio.h>

int find_num(int a);
int findNpd(int a);
int div(int a, int b);
int simp(int a);

int main() {
    int a;
    if ((scanf("%d", &a) != 1 || getchar() != '\n') || a % 1 != 0) {
        printf("n/a");
        return 1;
    }

    a = find_num(a);
    int res = findNpd(a);
    printf("%d", res);
    return 0;
}

int findNpd(int a) {
    int res = 1;
    for (int i = 1; i <= a; i++) {
        if (div(a, i) && simp(i)) {
            res = i;
        }
    }
    return res;
}

int find_num(int a) { return a >= 0 ? a : -a; }

int div(int a, int b) {
    while (a > 0) {
        a -= b;
    }
    if (a == 0) {
        return 1;
    } else {
        return 0;
    }
}

int simp(int a) {
    if (a == 1 || a == 2) {
        return 1;
    }
    for (int i = 2; i < a - 1; i++) {
        if (div(a, i)) {
            return 0;
        }
    }
    return 1;
}