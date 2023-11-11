// Kaden Bilyeu
// 11-08-2023
// Graded Exercise 07
// This program maintains a linked list of pets. The user can add pets to the list, remove pets from the list, display the pets in the list, and write the pets in the list to a file.
// The code always aims to maintain proper and secure coding practices.
// Windows 10
// Visual Studio 2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

// macros
#define STRING_LENGTH 80

//--------------------start-of-Pet------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct Pet 
{
    char name[STRING_LENGTH];
    int age;
    struct Pet* next;

} Pet;

// Function prototypes unique to this assignment
int stringCompare(const char* s1, const char* s2);
void insertPet(Pet** head, const char* name, int age);
void displayPets(const Pet* head);
void writePetsToFile(const Pet* head, const char* filename);
Pet* removePet(Pet** head, const char* name);
void deallocatePets(Pet** head);
char getChoice();

// Helper function prototypes from other assignments
void clearBufferAndFgets(char* str, int size);
bool scanInt(const char* stringPointer, int* value);
int getValidInt(int min, int max);

//--------------------start-of-main()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() 
{
    Pet* head = NULL;

    char filename[STRING_LENGTH];
    char name[STRING_LENGTH];
    char choice;

    int age;

    bool isSafe;

    // Insert pets loop
    do 
    {
        puts("Enter pet name: ");
        clearBufferAndFgets(name, sizeof(name));

        puts("Enter pet age: ");

        // Assuming 200 as a realistic maximum age for a pet... turtle right?
        // I know validation is not required for this assignment, but I'm lazy and I already have this function written.
        age = getValidInt(0, 200); 

        insertPet(&head, name, age);

        puts("\nDo you want to add another pet? Please enter (y)es or (n)o: ");

        choice = getChoice();

        puts("");

    } while (tolower(choice) == 'y');

    // Display all pets
    displayPets(head);

    puts("");

    // Remove pets loop
    do 
    {
        puts("Do you want to remove a pet from the list? Please enter (y)es or (n)o: ");

        choice = getChoice();

        if (tolower(choice) == 'y') 
        {
            puts("\nEnter the pet's name to delete: ");
            clearBufferAndFgets(name, sizeof(name));

            Pet* removedPet = removePet(&head, name);
            if (removedPet) 
            {
                printf("Removed: %s\n", removedPet->name);
                free(removedPet);
            }
            else 
            {
                printf("%s was not found in the list\n", name);
            }
        }
        displayPets(head);

    } while (tolower(choice) == 'y' && head != NULL); // Continue only if there are pets left

    // If there are any pets left in the list, write them to a file
    if (head != NULL) 
    {
        puts("\nEnter filename to save the remaining pets: ");
        clearBufferAndFgets(filename, sizeof(filename));

        isSafe = true;

        // check if filename does not end with .txt
        // I know this isn't required but it was an edge case I thought of and I wanted to handle it.
        if (strcmp(filename + strlen(filename) - 4, ".txt") != 0) 
        {
            if (strlen(filename) + 4 > STRING_LENGTH) 
            {
                isSafe = false;
                puts("Filename too long, cannot add .txt extension\n");
            }
            else 
            {
                strcat(filename, ".txt");
            }
        }

        if (isSafe) 
        {
            writePetsToFile(head, filename);
        }
    }

    // kill the list
    deallocatePets(&head);
    puts("Exiting...\n");

    return 0;
}

//--------------------start-of-stringCompare()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int stringCompare(const char* s1, const char* s2) 
{
    /*
    * 
    * This function compares two strings regardless of case and returns an integer value based on the comparison.
    * 
    * Parameters:
    * s1 (const char*) : The first string to compare.
    * s2 (const char*) : The second string to compare.
    * 
    */

    char s1_lower[80];
    char s2_lower[80];

    // null-terminate.
    strncpy(s1_lower, s1, 80);
    s1_lower[79] = '\0'; 

    // null-terminate.
    strncpy(s2_lower, s2, 80);
    s2_lower[79] = '\0';

    // Convert both strings to lowercase.
    for (int i = 0; s1_lower[i]; i++) 
    {
        s1_lower[i] = tolower((unsigned char)s1_lower[i]);
    }
    for (int i = 0; s2_lower[i]; i++) 
    {
        s2_lower[i] = tolower((unsigned char)s2_lower[i]);
    }

    return strcmp(s1_lower, s2_lower);

}

//--------------------start-of-insertPet()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void insertPet(Pet** head, const char* name, int age) 
{
    /*
    * 
    * This function inserts a new pet into the list in alphabetical order.
    * 
    * Parameters:
    * head (Pet**) : A pointer to the head of the list.
    * name (const char*) : The name of the pet to insert.
    * age (int) : The age of the pet to insert.
    * 
    */

    // Try to allocate memory for new pet
    Pet* newPet = (Pet*)malloc(sizeof(Pet));

    // if allocation fails, bail out
    if (newPet == NULL)
    {
        puts("Error allocating memory");
        return;
    }
    //null-terminate
    strncpy(newPet->name, name, 80);
    newPet->name[79] = '\0';
    
    newPet->age = age;
    newPet->next = NULL;

    // Find insertion point
    Pet** tracer = head;

    // While not at the end of the list and the current name is less than the new name
    while (*tracer != NULL && stringCompare((*tracer)->name, name) < 0) 
    {
        tracer = &(*tracer)->next;
    }

    // Insert new_pet into the list
    newPet->next = *tracer;
    *tracer = newPet;
}

//--------------------start-of-displayPets()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void displayPets(const Pet* head) 
{
    /*
    *
    * This function displays the pets in the linked list.
    *
    * Parameters:
    * head (const Pet*) : A pointer to the head of the list.
    *
    */

    // Check if the list is empty
    if (head == NULL)
    {
       puts("The list is empty");
       return;
    }

    puts("\nThe pets in alphabetical order by name:");

    // Traverse the list and print the pets in da list.
    while (head != NULL)
    {
        printf("Pet Name: %s, Pet Age: %d\n", head->name, head->age);
        head = head->next; // Move to next node
    }
}

//--------------------start-of-writePetsToFile()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void writePetsToFile(const Pet* head, const char* filename)
{
    /*
    *
    * This function writes the pets in the linked list to a file.
    *
    * Parameters:
    * head (const Pet*) : A pointer to the head of the list.
    * filename (const char*) : The name of the file to write to.
    *
    */

    // open file for writing
    FILE* file = fopen(filename, "w"); 
    if (file == NULL)
    {
        puts("Error opening file");
        return;
    }

    const Pet* current = head;
    while (current != NULL)
    {
        fprintf(file, "Pet Name: %s, Pet Age: %d\n", current->name, current->age);
        current = current->next; // Move to the next node
    }

    fclose(file);
}

//--------------------start-of-removePet()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Pet* removePet(Pet** head, const char* name)
{
    /*
    *
    * This function removes a pet from the list by name.
    *
    * Parameters:
    * head (Pet**) : A pointer to the head of the list.
    * name (const char*) : The name of the pet to remove.
    *
    * Returns:
    * Pet* : A pointer to the removed pet, or NULL if the pet is not found.
    *
    */

    Pet* temp, * prev;
    temp = *head;
    prev = NULL;

    // Traverse da list to find the pet
    while (temp != NULL && stringCompare(temp->name, name) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    // If the pet was not found
    if (temp == NULL)
    {
        return NULL;
    }

    // Pet found, remove it from da list
    if (prev == NULL)
    {
        // Pet is the first in the list
        *head = temp->next;
    }
    else
    {
        // Pet is in the middle/end
        prev->next = temp->next;
    }

    return temp;
}

//--------------------start-of-deallocatePets()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void deallocatePets(Pet** head)
{
    /*
    *
    * This function deallocates all the pets in the list.
    *
    * Parameters:
    * head (Pet**) : A pointer to the head of the list.
    *
    */

    Pet* current = *head;
    Pet* temp;

    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }

    // kill the head
    *head = NULL;
}

//--------------------start-of-clearBufferAndFgets()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void clearBufferAndFgets(char* str, int size)
{

    /*
    *
    * Clears the buffer and gets a string from the user.
    *
    * Parameters:
    * str (char*): The string to store the user input in.
    * size (int): The size of the string.
    *
    */

    fgets(str, size, stdin);

    // Remove any newline at the end
    char* newline = strchr(str, '\n');
    if (newline)
    {
        *newline = '\0';
    }
    else
    {
        // Clear the rest of the buffer until newline is found or EOF
        while ((getchar()) != '\n') {}
    }
}

//--------------------start-of-getValidInt()----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int getValidInt(int min, int max)
{
    /*
    * Gets a valid integer from the user.
    *
    * Parameters:
    * min (int): The minimum value the user can enter.
    * max (int): The maximum value the user can enter.
    *
    * Returns:
    * value (int): The valid integer the user entered.
    */

    char inputStr[STRING_LENGTH];
    int value;

    // Loop until valid input
    while (1)
    {
        clearBufferAndFgets(inputStr, STRING_LENGTH);

        // *Try* to parse the string to an integer using scanInt
        bool result = scanInt(inputStr, &value);

        // If parsing was successful and the number is within the valid range or it's the sentinel value
        if (result && ((value >= min && value <= max)))
        {
            return value;
        }
        else if (!result)
        {
            puts("Error: Not an integer number. Please enter the value again.");
        }
        else
        {
            printf("Error: Not within %d and %d. Please enter the value again.\n", min, max);
        }
    }
}

//--------------------start-of-scanInt()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool scanInt(const char* stringPointer, int* value)
{
    /*
    *
    * Properly scans an integer from a string.
    *
    * Parameters:
    * stringPointer (const char*): The string to scan the integer from.
    * value (int*): The integer to store the scanned value in.
    *
    * Returns:
    * isValid (bool): Whether or not the integer was scanned successfully.
    *
    */

    bool isValid = false;
    char* end = NULL;

    // Reset errno to detect overflow/underflow
    errno = 0;

    long intTest = strtol(stringPointer, &end, 10);

    // Check if the conversion was successful and if there are no extra characters after the number
    if (end != stringPointer && '\0' == *end && errno != ERANGE && intTest >= INT_MIN && intTest <= INT_MAX)
    {
        *value = (int)intTest;
        isValid = true;
    }

    return isValid;
}

//--------------------start-of-getChoice()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

char getChoice()
{
	/*
	*
	* Gets a valid choice from the user.
	*
	* Returns:
	* choice (char): The valid choice the user entered.
	*
	*/

	char choice;

	// Loop until valid input
	while (1)
	{
		choice = getchar();
		while (getchar() != '\n'); // Clear the input buffer

		if (tolower(choice) == 'y' || tolower(choice) == 'n')
		{
			return choice;
		}
		else
		{
			puts("Error: Invalid choice. Please enter (y)es or (n)o.");
		}
	}
}