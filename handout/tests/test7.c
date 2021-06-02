#include <stdio.h>
  
//test case that checks Array accesed withing a struct
struct students {
    int student_id;
    char division;
    float percentages[3];
};
  

int main()
{
    // Initialize a structure
    struct students S
        = { 1, 'A', { 98.5, 77, 89} };
  
  
     for (int i = 0; i < 4; i++) {
        printf("Course %d : %.2f Percentage: \n",i + 1, S.percentages[i]);
    }

    return 0;
}