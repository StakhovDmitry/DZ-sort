#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(void) {
  int length = 0, n = 0;
  int i = 0;
  int max = 0, min = 0;
  char * number = (char * ) malloc((n + 1) * sizeof(char));
  int * arr = (int * ) malloc((length + 1) * sizeof(int));
  int support;
  FILE* file;
  if ((file = fopen("numbers.txt", "r")) == NULL) {
      printf("Cannot open file.\n");
      exit(1);
  }
  char buffer = getc(file);
  while (buffer != EOF) {
      if (buffer != '\n' && buffer != EOF) {
          n++;
          number = (char*)realloc(number, (n) * sizeof(char));
          *(number + n - 1) = buffer;
      }
      else {
          n++;
          number = (char*)realloc(number, (n) * sizeof(char));
          *(number + n - 1) = '\0';
          length++;
          arr = (int*)realloc(arr, (length) * sizeof(int));
          sscanf(number, "%d", (arr + length - 1));
          n = 0;
          number = (char*)realloc(number, (n + 1) * sizeof(char));
      }
      buffer = getc(file);
  } 

  clock_t begin = clock();
 

  max = arr[0];
  min = arr[0];
  for (i = 1; i < length; i++) {
      if (arr[i] > max) {
          max = arr[i];
      }
      if (arr[i] < min) {
          min = arr[i];
      }
  }

  max++;
  FILE* Sortfile;

  if ((Sortfile = fopen("Counting_sort", "w")) == NULL) {
      printf("Cannot open file.\n");
      exit(1);
  }
  if (min < 0) {
      min = -min++;
      int* tnuoc = (int*)malloc((min) * sizeof(int));
      for (i = 0; i < min; i++) {
          tnuoc[i] = 0;
      }
      for (i = 0; i < length; i++) {
          if (arr[i] < 0) {
              tnuoc[-arr[i]]++;
          }
      }
      for (i = min; i > 0; i = i - 1) {
          if (tnuoc[i] != 0) {
              for (int j = 0; j < tnuoc[i]; j++) {
                  fprintf(Sortfile,"%d\n", -i);
              }
          }
      }
  }

  int* count = (int*)malloc((max) * sizeof(int));
  for (i = 0; i < max; i++) {
        count[i] = 0;
  }
  for (i = 0; i < length; i++) {
      if (arr[i] >= 0) {
          count[arr[i]]++;
      }
  }
  for (i = 0; i < max; i++) {
     if (count[i] != 0) {
         for (int j = 0; j < count[i]; j++) {
             fprintf(Sortfile, "%i\n", i);
         }
     }
  }
  clock_t finish = clock();
  double time_spent = (double)(finish - begin) / CLOCKS_PER_SEC;
  printf("\n%lf", time_spent);
  return(0);
}