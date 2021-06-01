#include <stdio.h>

/***
** Implement the function below. Function check_bounds takes as input
** the size of the array being accessed, the index of the accessed
** element, and the line number and file in which this access
** occurs. If the access is out of bounds, then the function prints an
** error message.
***/
void check_bounds(long int size, long int index, long int line, char filename[]) {
  printf("Out-of-Bounds Checking...\n");

<<<<<<< Updated upstream
  
  //printf("array size: %i\n, index: %i\n, line: %i\n, filename: %s\n", size, index, line, filename);

  if(index >= size)
  {
    printf("%s:%i: Array Out of Bounds Error.\n", filename,line);
  }
=======
  // print variables
  printf("array size: %i\n, index: %i\n, line: %i\n, filename: %s\n", size, index, line, filename);

  // check if index accessed is larger than the array size
  if (size < index) {
    printf("%s:%i  Array Out of Bounds Error.", filename, line);
  }
  
<<<<<<< Updated upstream
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
  return;
}


