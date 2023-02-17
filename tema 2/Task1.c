// nume: Ioan Teodorescu
// grupa: 313CB
#include "utils.h"

#define MAX 200

void reverse(int * v1, int n) {
   int * left = v1, * right = v1 + n - 1;
   while (left < right) {
      int aux = * left;
      * left = * right;
      * right = aux;
      left++;
      right--;
   }
}

int chartoint(char * str) {
   int i = 0, value = 0, r = 0;
   for (i = 0; i < strlen(str); i++) {
      r = str[i] - '0';
      value = value * 10 + r;
   }
   return value;
}

int palindrom(int n) {
   int r = 0, sum = 0, temp = n;
   while (n > 0) {
      r = n % 10;
      sum = (sum * 10) + r;
      n = n / 10;
   }
   if (temp == sum)
      return 1;
   else
      return 0;
}

int primalitate(int a) {
   int i = 0;
   if (a <= 1)
      return 0;
   if (a == 2)
      return 1;
   if (a % 2 == 0)
      return 0;
   else {
      for (i = 3; i * i <= a; i = i + 2) {
         if (a % i == 0)
            return 0;
      }
      return 1;
   }
}

long long cifre(long long str) {
   long long i = 0, value = 1;
   while (str) {
      str = str / 10;
      value = value * 10;
   }
   return value / 10;
}

int caz_c(long long nr, long long pow10, int n, int k) {
   int sum = 0, fact = 0;
   int cif = nr % (pow10 / 10);
   int cifre[MAX] = {0}, i = 0;
   while (cif != 0) {
      cifre[i] = cif % 10;
      cif = cif / 10;
      i++;
   }
   reverse(cifre, n);

   for (int i = 0; i < k; i++) {
      sum = sum + cifre[fact % n];
      fact = fact + k;
   }
   return sum % 4;
}

void SolveTask1() {
   char str[MAX];
   int M[MAX][MAX] = {0}, i = 0, j = 0, steps = 1, n = 0, m = 0;
   scanf("%d%d", & n, & m);
   getc(stdin);
   fgets(str, MAX, stdin);
   M[i][j] = steps;
   steps++;
   char * token;
   token = strtok(str, " ");
   while (token != NULL) {
      if ( * (token) == 'a') {
         int x1 = (int) * (token + 1) - '0';
         int x2 = (int) * (token + 2) - '0';
         int x3 = (int) * (token + 3) - '0';
         int x4 = (int) * (token + 4) - '0';
         int x = fmax(x1, fmax(x2, fmax(x3, x4)));
         if (x == x1)
            j++;
         else if (x == x2)
            i--;
         else if (x == x3)
            j--;
         else if (x == x4)
            i++;
      } else if ( * (token) == 'b') {
         int nr_pal = atoi(token + 1);
         int nr_prim = 10 * ((nr_pal / 10) % 10) + (nr_pal) % 10;
         int pal = palindrom(nr_pal);
         int prim = primalitate(nr_prim);
         if (pal == 1 && prim == 1)
            j--;
         else if (pal == 1 && prim == 0)
            j++;
         else if (pal == 0 && prim == 1)
            i--;
         else if (pal == 0 && prim == 0)
            i++;
      } else if ( * (token) == 'c') {
         long long nr_sum = atoll(token + 1);
         long long pow10 = cifre(nr_sum);
         int n = nr_sum / pow10;
         int k = (nr_sum / (pow10 / 10)) % 10;
         int sum = caz_c(nr_sum, pow10, n, k);
         if (sum == 0)
            j--;
         else if (sum == 1)
            i--;
         else if (sum == 2)
            j++;
         else if (sum == 3)
            i++;
      }
      M[i][j] = steps;
      steps++;
      token = strtok(NULL, " ");
   }
   for (i = 0; i < n; i++) {
      for (j = 0; j < m; j++)
         printf("%d ", M[i][j]);
      printf("\n");
   }
}