#include <stdio.h>

int main() {
  int numbers[3][2][1];

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            for (int k = 0; k < 2; ++k)
            {
                numbers[i][j][k] = i+j+k;
            }
        }
    }

  return 0;
}