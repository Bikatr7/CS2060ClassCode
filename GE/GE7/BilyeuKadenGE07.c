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

//--------------------start-of-main()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() 
{

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

}

//--------------------start-of-displayPets()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void displayPets(const Pet* head) 
{

}

//--------------------start-of-writePetsToFile()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void writePetsToFile(const Pet* head, const char* filename) 
{

}

//--------------------start-of-removePet()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


Pet* removePet(Pet** head, const char* name) 
{

}

//--------------------start-of-deallocatePets()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void deallocatePets(Pet** head) 
{

}