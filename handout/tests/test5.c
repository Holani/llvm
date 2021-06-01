#include <stdio.h>

int main() {
  int numbers[3][2];

  for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
          numbers[i][j] = j*i;
        }
    }
  return 0;
}