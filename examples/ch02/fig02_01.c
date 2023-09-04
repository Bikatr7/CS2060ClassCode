// fig02_01.c
// A first program in C.
#include <stdio.h>

int main(void) {

    int length = 0;
    int width = 0;
    int area = 0;

    int result = 0;

    double divisionResult = 0.0;

    char* string_to_print = "Enter the length";

    puts(string_to_print);

    while (1) {  
        result = scanf("%d", &length);

        while (getchar() != '\n');
        if (result == 1) {
            break;  
        }
        else 
        {
           puts("Invalid input for length. Please enter a number.");
        }
    }

    puts("Enter the width");
    scanf("%d", &width);

    area = length * width;

    printf("Length: %d width: %d and area is %d\n", length, width, area);

    divisionResult = (double) length / width;

    printf("Average Value: %.1f", divisionResult);

    return 0;

} // end function main




/**************************************************************************
 * (C) Copyright 1992-2021 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
