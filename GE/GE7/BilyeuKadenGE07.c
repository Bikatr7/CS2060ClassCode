// Kaden Bilyeu
// 11-08-2023
// Graded Exercise 07
// *Insert Goal ig*
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
    char name[80];
    int age;
    struct Pet* next;

} Pet;

// Function prototypes Tenative
int stringCompare(const char* s1, const char* s2);
void insertPet(Pet** head, const char* name, int age);
void displayPets(const Pet* head);
void writePetsToFile(const Pet* head, const char* filename);
Pet* removePet(Pet** head, const char* name);
void deallocatePets(Pet** head);
void clearBufferAndFgets(char* str, int size);
bool scanInt(const char* stringPointer, int* value);
int getValidInt(int min, int max, int sentinel);

//--------------------start-of-main()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() 
{
    Pet* head = NULL;
    char name[STRING_LENGTH];
    int age;
    char filename[STRING_LENGTH];
    int choice;

    do 
    {
        // Display Menu
        puts("\n1. Insert Pet\n2. Display Pets\n3. Remove Pet\n4. Write Pets to File\n5. Exit\nEnter your choice: ");
        choice = getValidInt(1, 4, 5);

        switch (choice) 
        {
        
        // Insert Pet
        case 1: 
            printf("Enter pet name: ");
            clearBufferAndFgets(name, sizeof(name));
            printf("Enter pet age: ");
            // Assuming 200 as a realistic maximum age for a pet... turtle right?
            age = getValidInt(0, 200, -1);
            insertPet(&head, name, age);
            break;

        // Display Pets
        case 2:
            displayPets(head);
            break;

        // Remove Pet
        case 3: 
            puts("Enter pet name to remove: ");
            clearBufferAndFgets(name, sizeof(name));
            Pet* removedPet = removePet(&head, name);
            if (removedPet) 
            {
                printf("Removed: %s\n", removedPet->name);
                free(removedPet);
            }
            else 
            {
                puts("Pet not found.\n");
            }
            break;

        // Write Pets to File
        case 4: 
            puts("Enter filename: ");
            clearBufferAndFgets(filename, sizeof(filename));
            writePetsToFile(head, filename);
            break;

        }

    } while (choice != 5);

    puts("Exiting...\n");

    // Clean-up
    deallocatePets(&head);

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
        fprintf(stderr, "Memory allocation failed\n");
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

int getValidInt(int min, int max, int sentinel)
{
    /*
    * Gets a valid integer from the user.
    *
    * Parameters:
    * min (int): The minimum value the user can enter.
    * max (int): The maximum value the user can enter.
    * sentinel (int): The value that will end the loop.
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
        if (result && ((value >= min && value <= max) || value == sentinel))
        {
            return value;
        }
        else if (!result)
        {
            puts("Error: Not an integer number. Please enter the value again.\n");
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