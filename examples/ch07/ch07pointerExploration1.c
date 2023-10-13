/*******************
 Understanding pointers

 Add comments to explain the code
**************/

#include <stdio.h>


int main ()
{
	// Initalize houseNum
	int houseNum = 13;
	int calcHouseNum1 = 0;
	int calcHouseNum2 = 0;
	int *houseNumPtr = &houseNum;
	
	// prints raw var
	printf("houseNum %d\n", houseNum);

	// prints var address
	printf("&houseNum %p\n\n", &houseNum);

	// prints int value at the pointer address
	printf ("*houseNumPtr  %d\n", *houseNumPtr);

	// prints the address of the value the pointer is pointing to
	printf ("houseNumPtr %p\n\n", houseNumPtr);

	// prints the address of the pointer
	printf ("&houseNumPtr %p\n\n", &houseNumPtr);

	// adds the values that the pointer is pointing to together
	calcHouseNum1 =  *houseNumPtr + *houseNumPtr;

	printf("*houseNumPtr + *houseNumPtr is %d\n\n", calcHouseNum1);

	// same as above but with a different method
	calcHouseNum2 = 2 * (*houseNumPtr);

	printf("2 * (*houseNumPtr) is %d\n\n", calcHouseNum2);

	// shows that dereferencing a pointer and then referencing it again is the same as the original pointer
	printf("\n&*houseNumPtr = %p"
		"\n*&houseNumPtr = %p\n", &*houseNumPtr, *&houseNumPtr);
			
	return 0;
}
