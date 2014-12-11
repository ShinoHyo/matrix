#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int size = -1;

void shuffle(int line[])
{
  for(int i=0;i<size;i++){
    int j = rand()%size;
    int tmp = line[i];
    line[i] = line[j];
    line[j] = tmp;
  }
}

void setLine(int line[])
{
  for (int i = 0; i < size; ++i)
  {
    line[i]=i;
  }
  shuffle(line);
}

void setRow(const int row, int matrix[size][size])//rowは現在の行
{
  if (row == 0){
    int line[size];
    setLine(line);
    for (int i = 0; i < size; ++i){
          matrix[row][i]=line[i];
    }
  } else if (row == size-1) {
    for (int i = 0; i<size; ++i){
      matrix[row][i] = size*(size-1)/2;
      for (int j = 0; j < row; ++j){
        matrix[row][i] -= matrix[j][i];
      }
    }
  } else {
    int line[size];
label:
    setLine(line);
    for (int j=row-1; j >= 0; --j){
      for (int i = 0; i < size; ++i){
        if (line[i] == matrix[j][i])
        {
          goto label;
        }
      }
    }

    for (int i = 0; i < size; ++i){
      matrix[row][i] = line[i];
    }
  }
}

void printMatrix(const int matrix[size][size])
{
  for (int j = 0; j < size; ++j)
  {
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", matrix[j][i]);
    }
    puts("");
  }

}


int main(int const argc, char const *argv[])
{
  srand((unsigned) time(NULL));

  if (argv[1] == NULL){
    char input[]= "01";
    puts("行数を入力して下さい");
    fgets(input, sizeof input, stdin);
    size = atoi(input);
  } else {
    size = atoi(argv[1]);
  }
  int matrix[size][size];

  for (int i = 0; i < size; ++i)
  {
    setRow(i, matrix);
  }
  printMatrix(matrix);

  return 0;
}
