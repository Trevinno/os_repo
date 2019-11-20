#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

//#define tam

int main(void){
  int tam; 

  cin >> tam; 

  int A[tam][tam], B[tam][tam], C[tam][tam];
  int i, j, k;
  srand(time(NULL)); //inicializa random generator

  for(i = 0; i < tam; i++){
    for(j = 0; j < tam; j++){
      A[i][j] = 0;
      B[i][j] = 0;
      C[i][j] = 0;
    }
  }

  for(i = 0; i < tam; i++){
    for(j = 0; j < tam; j++){
        A[i][j] = rand()%100;
        B[i][j] = rand()%100;
    }
  }

  clock_t begin, end;
  double time_spent;
  begin = clock();

  for(i = 0; i < tam; i++)
    for(j = 0; j < tam; j++)
        for(k = 0; k < tam; k++)
          C[i][j] += A[i][k] * B[k][j];

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Elapsed time: %.2lf seconds.\n", time_spent);
  return 0;
}

