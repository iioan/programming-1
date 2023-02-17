// nume: Ioan Teodorescu
// grupa: 313CB
#include <stdio.h>

#define MAX 10

unsigned int cbin(unsigned int n, unsigned x, unsigned poz) {
    unsigned int fin = 0, i = 0;
    for (i = 0; i < n; i++) {
        fin = fin | ((x >> poz) & 1);
        poz--;
        if (i != n - 1)
            fin = fin * 2;
    }
    return fin;
}

int main() {
    unsigned int n = 0, N = 0, dim = 0, i = 0, nr = 0;
    unsigned int b1 = 28, b2 = 27, x = 0, y = 0, operatie[MAX] = {0};
    const int shift = 29;
    scanf("%u", & n);
    N = (n >> shift) + 1;
    // determin N
    printf("%d ", N);
    for (i = 0; i < N; i++) {
        x = ((n >> b1) & 1);
        y = ((n >> b2) & 1);
        operatie[nr] = ((operatie[nr] | x) * 2) | y;
        nr++;
        b1 -= 2;
        b2 -= 2;
    }
    for (i = 0; i < nr; i++) {
        if (operatie[i] == 0)
            printf("+ ");
        if (operatie[i] == 1)
            printf("- ");
        if (operatie[i] == 2)
            printf("* ");
        if (operatie[i] == 3)
            printf("/ ");
    }
    // aflu instructiunile si le afisez
    dim = cbin(4, n, b1);
    dim++;
    // determin dimensiunea unui operand
    printf("%d\n", dim);
    return 0;
}