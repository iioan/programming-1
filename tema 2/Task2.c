// nume: Ioan Teodorescu
// grupa: 313CB
#include "utils.h"

#define addition 10001
#define caesar 1001

void rm_0(char * str) {
   while (str[0] == '0') {
      int j = 0;
      for (j = 0; j < (int) strlen(str); j++) {
         str[j] = str[j + 1];
      }
   }
}

void reverse_char(char * v1) {
   int n = (int) strlen(v1) - 1;
   char * left = v1, * right = v1 + n;
   while (left < right) {
      int aux = * left;
      * left = * right;
      * right = aux;
      left++;
      right--;
   }
}

void swap(char ** str1, char ** str2) {
   char * temp = * str1;
   * str1 = * str2;
   * str2 = temp;
}

void decript_c(char * input, int X) {
   const int char_a = 97, alphabet = 26, char_A = 65, char_0 = 48, numbers = 10;
   int i = 0, length = (int) strlen(input);
   for (i = 0; i < length; i++) {

      if (input[i] >= 'a' && input[i] <= 'z') {
         int decriptare = (int) input[i] - char_a - (X % alphabet);
         if (decriptare < 0)
            decriptare = alphabet + decriptare;
         input[i] = (char) char_a + decriptare;

      } else if (input[i] >= 'A' && input[i] <= 'Z') {
         int decriptare = (int) input[i] - char_A - (X % alphabet);
         if (decriptare < 0)
            decriptare = alphabet + decriptare;
         input[i] = (char) char_A + decriptare;

      } else if (input[i] >= '0' && input[i] <= '9') {
         int decriptare = (int) input[i] - char_0 - (X % numbers);
         if (decriptare < 0)
            decriptare = numbers + decriptare;
         input[i] = (char) char_0 + decriptare;
      }
   }
}

void decript_c_numbers(char * input, int X) {
   int i = 0, length = (int) strlen(input);
   const int char_0 = 48, numbers = 10;
   for (i = 0; i < length; i++) {
      int decriptare = (int) input[i] - char_0 - (X % 10);
      if (decriptare < 0)
         decriptare = numbers + decriptare;
      input[i] = (char) char_0 + decriptare;
   }
}

void decript_v(char * input, int key[], int lengthK) {
   int i = 0, length = (int) strlen(input), j = 0;
   const int char_a = 97, alphabet = 26, char_A = 65, char_0 = 48, numbers = 10;
   for (i = 0; i < length; i++) {
      if (j == lengthK)
         j = 0;
      if (input[i] >= 'a' && input[i] <= 'z') {
         int decriptare = (int) input[i] - char_a - (key[j] % alphabet);
         if (decriptare < 0)
            decriptare = alphabet + decriptare;
         input[i] = (char) char_a + decriptare;
      } else if (input[i] >= 'A' && input[i] <= 'Z') {
         int decriptare = (int) input[i] - char_A - (key[j] % alphabet);
         if (decriptare < 0)
            decriptare = alphabet + decriptare;
         input[i] = (char) char_A + decriptare;
      } else if (input[i] >= '0' && input[i] <= '9') {
         int decriptare = (int) input[i] - char_0 - (key[j] % numbers);
         if (decriptare < 0)
            decriptare = numbers + decriptare;
         input[i] = (char) char_0 + decriptare;
      }
      j++;
   }
}

void findsum(char * str1, char * str2) {
   if (strlen(str1) < strlen(str2))
      swap( & str1, & str2);
   char str[addition] = "\0";
   int n1 = (int) strlen(str1), n2 = (int) strlen(str2);
   int diff = n1 - n2;
   int carry = 0, j = 0;
   // incep de la capatul ambelor sirur
   for (int i = n1 - 1; i >= n1 - n2; i--) {
      int sum = ((int)(str1[i] - '0') + (int)(str2[i - diff] - '0') + carry);
      str[j] = (char)(sum % 10 + '0');
      j++;
      carry = sum / 10;
   }
   // adaug caracterele ramase din str3
   for (int i = n1 - n2 - 1; i >= 0; i--) {
      int sum = ((int)(str1[i] - '0') + carry);
      str[j] = (char)(sum % 10 + '0');
      j++;
      carry = sum / 10;
   }
   // adaug ce a ramas 'in minte' dupa efectuarea adunarilor
   if (carry)
      str[j] = (char)(carry + '0');
   reverse_char(str);
   rm_0(str);
   printf("%s", str);
}

void SolveTask2() {
   const int char_a = 97, alphabet = 26, char_A = 65, char_0 = 48, numbers = 10;
   char option[30] = "\0", input[caesar] = "\0";
   int i = 0;
   scanf("%s", option);
   if (strcmp(option, "caesar") == 0) {

      int K = 0;
      scanf("%d", & K);
      getc(stdin);
      fgets(input, caesar, stdin);
      // elimin newline-ul de la sf sirului
      input[strcspn(input, "\n")] = 0;
      
      decript_c(input, K);
      printf("%s\n", input);

   } else if (strcmp(option, "vigenere") == 0) {
      char K[10] = "\0";
      int key[10] = {0};
     
      getc(stdin);
      fgets(K, 10, stdin);
      fgets(input, caesar, stdin);
      input[strcspn(input, "\n")] = 0;
      K[strcspn(K, "\n")] = 0;

      int lengthK = (int) strlen(K);
      for (i = 0; i < lengthK; i++) {
         key[i] = (int) K[i] - char_A;
      }
      decript_v(input, key, lengthK);

      printf("%s\n", input);
   } else if (strcmp(option, "addition") == 0) {
      int K = 0;
      char N1[addition] = "\0", N2[addition] = "\0";
      scanf("%d", & K);
      getc(stdin);

      fgets(N1, addition, stdin);
      N1[strcspn(N1, "\n")] = 0;
      fgets(N2, addition, stdin);
      N2[strcspn(N2, "\n")] = 0;

      decript_c_numbers(N1, K);
      decript_c_numbers(N2, K);
      rm_0(N1);
      rm_0(N2);

      findsum(N1, N2);
   }
}