// nume: Ioan Teodorescu
// grupa: 313CB
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bmp_header.h"
#define MAX 1000

// citeste bmp-urile
void read_bmp(char * file, bmp_fileheader * header,
  bmp_infoheader * dibheader, struct_image * bmp_data) {
  FILE * fp = fopen(file, "rb");
  // citeste datele din bmp_fileheader si bmp_infoheader
  fread(header, sizeof( * header), 1, fp);
  fread(dibheader, sizeof( * dibheader), 1, fp);
  // se duce la bitul in care se incepe citirea pozei
  fseek(fp, header -> imageDataOffset, SEEK_SET);
  // alocam memorie si citim poza
  bmp_data -> rgb = (RGB ** ) malloc(dibheader -> height * sizeof(void * ));
  int i = 0;
  for (i = dibheader -> height - 1; i >= 0; i--) {
    bmp_data -> rgb[i] = (RGB * ) malloc(dibheader -> width * sizeof(RGB));
    fread(bmp_data -> rgb[i], dibheader -> width, sizeof(RGB), fp);
  }
  fclose(fp);
}

// printeaza bmp-urile
void write_bmp(char * file, bmp_fileheader * header,
  bmp_infoheader * dibheader, struct_image * bmp_data) {
  FILE * fpw = fopen(file, "w");
  int i = 0;
  // scrie headerul pozei
  fwrite(header, sizeof( * header), 1, fpw);
  fwrite(dibheader, sizeof( * dibheader), 1, fpw);
  // scrie datele din poza (rgb)
  for (i = dibheader -> height - 1; i >= 0; i--)
    fwrite(bmp_data -> rgb[i], dibheader -> width, sizeof(RGB), fpw);
  fclose(fpw);
}

// suprapune doua imagini
void overlap_bmp(bmp_infoheader * dibh_insert, bmp_infoheader * dibh,
  struct_image * bd, struct_image * bd_insert, unsigned int y, unsigned int x) {
  int i = 0, j = 0, m = 0, n = 0, limit_H = 0, limit_W = 0;
  // verific daca inaltimea pozei de inserat este mai mare
  if ((x + dibh_insert -> height) > dibh -> height)
    limit_H = (int) dibh -> height;
  else
    limit_H = (int) dibh_insert -> height;
  // verific daca lungimea pozei de inserat este mai mare
  if ((y + dibh_insert -> width) > dibh -> width)
    limit_W = (int) dibh -> width;
  else
    limit_W = (int) dibh_insert -> width;
  for (i = (int) x; i < limit_H; i++) {
    m = 0;
    for (j = (int) y; j < limit_W; j++) {
      // preiau bitii din poza care trebuie inserata
      int r = bd_insert -> rgb[n][m].red;
      int b = bd_insert -> rgb[n][m].blue;
      int g = bd_insert -> rgb[n][m].green;
      // si le pun peste bitii din poza principala
      bd -> rgb[i][j].red = r;
      bd -> rgb[i][j].green = g;
      bd -> rgb[i][j].blue = b;
      m++;
    }
    n++;
  }
}

void reverse_bmp(bmp_infoheader * dibheader, struct_image * bmp_data) {
  int i = 0, j = 0, n = dibheader -> height;
  for (i = 0; i < n / 2; i++) {
    for (j = 0; j < dibheader -> width; j++) {
      // fac swap intre pixeli
      int r = bmp_data -> rgb[n - i - 1][j].red;
      int b = bmp_data -> rgb[n - i - 1][j].blue;
      int g = bmp_data -> rgb[n - i - 1][j].green;
      bmp_data -> rgb[n - i - 1][j].red = bmp_data -> rgb[i][j].red;
      bmp_data -> rgb[n - i - 1][j].blue = bmp_data -> rgb[i][j].blue;
      bmp_data -> rgb[n - i - 1][j].green = bmp_data -> rgb[i][j].green;
      bmp_data -> rgb[i][j].red = r;
      bmp_data -> rgb[i][j].blue = b;
      bmp_data -> rgb[i][j].green = g;
    }
  }
}

int main() {
  char * s = NULL, * token = NULL, * file = NULL;
  const int ten = 10;
  int i = 0;
  bmp_fileheader header;
  bmp_infoheader dibheader;
  struct_image b_data;
  s = (char * ) malloc(MAX * sizeof(char));
  // citesc comenzile
  while (scanf("%[^\n]%*c", s) == 1) {
    token = (char * ) malloc(MAX * sizeof(char));
    file = (char * ) malloc(MAX * sizeof(char));
    strncat(s, " ", 1);
    // preiau primul cuvant = comanda
    strncpy(token, s, 4);
    token[4] = '\0';
    // obtin numele fisierului
    strncpy(file, s + strlen(token) + 1, strlen(s));
    file[strcspn(file, " ")] = 0;
    // daca am gasit comanda edit, save, etc.
    if (strcmp("edit", token) == 0) {
      read_bmp(file, & header, & dibheader, & b_data);
    } else if (strcmp("save", token) == 0) {
      write_bmp(file, & header, & dibheader, & b_data);
    } else if (strcmp("inse", token) == 0) {
      // aflu imaginea care trebuie inserata alaturi de y si x
      char * file_insert = (char * ) malloc(MAX * sizeof(char));
      strncpy(s, s + strlen("insert") + 1, strlen(s));
      int i = 0;
      while (s[i] != ' ') {
        file_insert[i] = s[i];
        i++;
      }
      i++;
      unsigned int x = 0, y = 0;
      while (s[i] != ' ') {
        y = y * ten + (int)(s[i] - '0');
        i++;
      }
      i++;
      while (s[i] != ' ') {
        x = x * ten + (int)(s[i] - '0');
        i++;
      }
      // declar structurile pentru imagine
      bmp_fileheader header2i;
      bmp_infoheader dibheader2i;
      struct_image b_data_insert;
      // o citesc
      read_bmp(file_insert, & header2i, & dibheader2i, & b_data_insert);
      // inversez imaginea principala
      reverse_bmp(& dibheader, & b_data);
      reverse_bmp(& dibheader2i, & b_data_insert);
      // suprapun imaginile
      overlap_bmp(& dibheader2i, & dibheader, & b_data, & b_data_insert, y, x);
      reverse_bmp(& dibheader, & b_data);
      // am ajuns la poza finala
    } else if (strcmp("quit", token) == 0) {
      // eliberez memoria
      for (i = dibheader.height - 1; i >= 0; i--)
        free(b_data.rgb[i]);
      free(b_data.rgb);
      free(token);
      free(file);
      free(s);
      return 0;
    }
  }
  return 0;
}
