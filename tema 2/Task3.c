// nume: Ioan Teodorescu
// grupa: 313CB
#include "utils.h"

#define MAX1 500001
#define MAX2 600000
#define matrix1 800
#define matrix2 100

void SolveTask3() {
   getc(stdin);
   char m[matrix1][matrix2];
   char s[MAX1] = "\0", str[MAX2] = "\0", c = 0;
   int i = 0, v[matrix1] = {0}, j = 0, k = 0;
   // citim textul
   while (scanf("%s", s) == 1) {
      strncat(s, " ", 1);
      strncat(str, s, strlen(s) + 1);
   }
   char * l = strtok(str, " ");
   char * p = strtok(NULL, " ");
   while (p != NULL) {
      if (strchr(",.!;", *(p + strlen(p) - 1)))
         *(p + strlen(p) - 1) = '\0';
      strncpy(m[i], l, strlen(l) + 1);
      strncat(m[i], " ", 1);
      strncat(m[i], p, strlen(p) + 1);
      i++;
      strncpy(l, p, strlen(p) + 1);
      p = strtok(NULL, " ");
   }
   int n = i;
   for (i = 0; i < n; i++) {
      int frequency = 1;
      for (j = i + 1; j < n; j++) {
         if (strcmp(m[i], m[j]) == 0) {
            frequency++;
            for (int k = j; k < n - 1; k++)
               strncpy(m[k], m[k + 1], strlen(m[k + 1]) + 1);
            n--;
         }
      }
      v[i] = frequency;
   }
   printf("%d\n", n);

   for (i = 0; i < n; i++) {
      printf("%s %d\n", m[i], v[i]);
   }
}