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

void stergere(unsigned short v[], unsigned n, unsigned poz) {
    unsigned int i = 0;
    for (i = poz; i < n - 1; i++)
        v[i] = v[i + 1];
    n--;
}

void stergereint(int v[], int n, int poz) {
    for (int i = poz; i < n - 1; i++)
        v[i] = v[i + 1];
    n--;
}

int main() {
    unsigned int n = 0, N = 0, dim = 0, b1 = 28, b2 = 27;
    unsigned int x = 0, y = 0, nr_opi = 0, nr_print = 0;
    unsigned short operanzi_short[MAX] = {0}, numar = 0, operatie[MAX] = {0};
    int i = 0, j = 0, operanzi[MAX] = {0}, Dim = 0, opN = 0;
    const int shift = 29, lastbit = 15, nobits = 16;
    double nr_printrest = 0;
    scanf("%u", & n);
    N = (n >> shift) + 1;
    // determin N
    for (i = 0; i < N; i++) {
        x = ((n >> b1) & 1);
        y = ((n >> b2) & 1);
        operatie[nr_opi] = (((operatie[nr_opi] | x) * 2) | y) + 1;
        nr_opi++;
        b1 -= 2;
        b2 -= 2;
    }
    // aflu instructiunile
    dim = cbin(4, n, b1);
    dim++;
    // dimensiunea unui operand
    Dim = (int) dim;
    nr_print = ((N + 1) * Dim) / nobits;
    nr_printrest = (double)((N + 1) * Dim) / nobits;
    if (nr_printrest != nr_print)
        nr_print++;

    for (i = 0; i < nr_print; i++) {
        scanf("%hu", & numar);
        j = lastbit;
        while (j >= 0) {
            operanzi_short[opN] = cbin(dim, numar, j);
            opN++;
            j = j - Dim;
            if (opN == N + 1)
                break;
        }
    }
    // compun operanzii
    for (i = 0; i < opN; i++) {
        operanzi[i] = (int) operanzi_short[i];
    }
    i = 0;
    while (i < nr_opi) {
        if (operatie[i] == 3) {
            operanzi[i] = operanzi[i] * operanzi[i + 1];
            stergereint(operanzi, opN, i + 1);
            opN--;
            stergere(operatie, nr_opi, i);
            nr_opi--;
        } else if (operatie[i] == 4) {
            operanzi[i] = operanzi[i] / operanzi[i + 1];
            stergereint(operanzi, opN, i + 1);
            opN--;
            stergere(operatie, nr_opi, i);
            nr_opi--;
        } else
            i++;
    }
    // calculez operatiile de inmultire si impartire mai intai
    i = 0;
    while (i < nr_opi) {
        if (operatie[i] == 1) {
            operanzi[i] = operanzi[i] + operanzi[i + 1];
            stergereint(operanzi, opN, i + 1);
            opN--;
            stergere(operatie, nr_opi, i);
            nr_opi--;
        } else if (operatie[i] == 2) {
            operanzi[i] = operanzi[i] - operanzi[i + 1];
            stergereint(operanzi, opN, i + 1);
            opN--;
            stergere(operatie, nr_opi, i);
            nr_opi--;
        } else
            i++;
    }
    // calculez restul instructiunilor
    printf("%d\n", operanzi[0]);
    return 0;
}