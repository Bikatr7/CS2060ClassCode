// Kaden Bilyeu
// 10-26-2023
// Iteration 2
// The goal of this program is to calculate the charges for a rental property. It offers features such as rental summary, etc
// The code always aims to maintain proper and secure coding practices.
// Windows 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <limits.h>

#define LENGTH 100

//Prints the rental property information.
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);

// Gets a valid integer from the user.
int getValidInt(int min, int max, int sentinel);

// Properly scans an integer from a string.
bool scanInt(const char* stringPointer, int* value);

// Calculates the charges for the rental property.
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);

// Prints the number of nights and the charges for the rental property.
void printNightsCharges(unsigned int nights, double charges);

// I dunno how do document functions in C. So I'll just use docstrings.

//--------------------start-of-main()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() 
{

    // constants
    int const SENTINAL_NEG1 = -1;
    int unsigned const MIN_RENTAL_NIGHTS = 1;
    unsigned int const MAX_RENTAL_NIGHTS = 14;
    unsigned int const INTERVAL_1_NIGHTS = 3;
    unsigned int const INTERVAL_2_NIGHTS = 6;
    double const RENTAL_RATE = 400;
    double const DISCOUNT = 50;

    // normal vars
    unsigned int totalNightsRented = 0;
    double totalCharges = 0;

    while (1) 
    {
        // Display the rental property information
        printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

        // Get the number of nights
        int nights = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);

        // If user enters sentinel value, exit loop and print the total summary
        if (nights == SENTINAL_NEG1) 
        {
            printf("Rental Property Owner Total Summary\n\n");
            printNightsCharges(totalNightsRented, totalCharges);
            break;
        }

        // Calculate the charges
        double charges = calculateCharges(nights, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

        // Update total nights and charges
        totalNightsRented += nights;
        totalCharges += charges;

        // Print the nights and charges for the current user
        printNightsCharges(nights, charges);
    }

    return 0;
}

//--------------------start-of-printRentalPropertyInfo()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount) 
{

    /*
    *
    * Prints the rental property information.
    *
    * Parameters:
    * minNights (unsigned int): The minimum number of nights the rental property can be rented for.
    * maxNights (unsigned int): The maximum number of nights the rental property can be rented for.
	* interval1Nights (unsigned int): The number of nights in the first interval.
	* interval2Nights (unsigned int): The number of nights in the second interval.
	* rate (double): The rate for the first interval.
	* discount (double): The discount for the second interval.
    *
    * Returns:
    * None.
    *
    */

    printf("Rental Property can be rented for %u to %u nights.\n", minNights, maxNights);
    printf("$%.2f rate a night for the first %u nights\n", rate, interval1Nights);
    printf("$%.2f discount rate a night for nights %u to %u\n", discount, interval1Nights + 1, interval2Nights);
    printf("$%.2f discount rate a night for each remaining night over %u.\n\n", 2 * discount, interval2Nights);
}

//--------------------start-of-getValidInt()----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int getValidInt(int min, int max, int sentinel)
{
    /*
    * Gets a valid integer from the user.
    * Parameters:
    * min (int): The minimum value the user can enter.
    * max (int): The maximum value the user can enter.
    * sentinel (int): The value that will end the loop.
    * Returns:
    * int: The valid integer the user entered.
    */

    char inputStr[LENGTH];
    int value;

    printf("Enter the number of nights you want to rent the property\n");

    // Loop until valid input
    while (1)
    {
        // Get input as a string
        fgets(inputStr, LENGTH, stdin);

        // Replace newline with null terminator
        char* newline = strchr(inputStr, '\n');
        if (newline)
            *newline = '\0';

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
    * */

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

//--------------------start-of-calculateCharges()-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount) 
{

    /*
    * 
    * Calculates the charges for the rental property.
    * 
    * Parameters:
    * nights (unsigned int): The number of nights the rental property is rented for.
    * interval1Nights (unsigned int): The number of nights in the first interval.
    * interval2Nights (unsigned int): The number of nights in the second interval.
    * rate (double): The rate for the first interval.
    * discount (double): The discount for the second interval.
    * 
    * Returns:
    * double: The total charge for the rental property.
    * 
    * */


    double totalCharge = 0;

    // Interval 0
    if (nights <= interval1Nights) 
    {
        totalCharge = nights * rate;
    }

    // Interval 1
    else if (nights <= interval2Nights) 
    {
        totalCharge = (interval1Nights * rate) + ((nights - interval1Nights) * (rate - discount));
    }

    // Interval 2
    else 
    {
        totalCharge = (interval1Nights * rate) + ((interval2Nights - interval1Nights) * (rate - discount)) + ((nights - interval2Nights) * (rate - 2 * discount));
    }

    return totalCharge;
}

//----------------------start-of-calculateCategoryAverages()----------------------

void calculateCategoryAverages(int rentalSurvey[][NUM_CATEGORIES], float categoryAverages[], int numRenters, int numCategories)
{
    /*
    *
    * Calculate the average rating for each category.
    *
    * Parameters:
    * int rentalSurvey[][NUM_CATEGORIES]: The 2darray of ratings for each renter.
    * float categoryAverages[]: The array of average ratings for each category.
    * int numRenters: The total number of renters.
    * int numCategories: The total number of categories.
    *
    * Returns:
    * void.
    */

    for (int ii = 0; ii < numCategories; ++ii)
    {
        int sum = 0;

        for (int i = 0; i < numRenters; ++i)
        {
            sum += rentalSurvey[i][ii];
        }

        categoryAverages[ii] = (float)sum / numRenters;
    }
}

//--------------------start-of-printNightsCharges()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printNightsCharges(unsigned int nights, double charges) 
{

    /*
    *
    * Prints the number of nights and the charges for the rental property.
    * 
    * Parameters:
    * nights (unsigned int): The number of nights the rental property is rented for.
    * charges (double): The total charge for the rental property.
    * 
    * Returns:
    * None.
    * 
    * */

    if(nights <= 0)
	{
		printf("There were no rentals.\n");
		return;
	}

    printf("\nRental Charges\n\n");
    printf("Nights          Charge\n");
    printf("%-15u $%.2f\n\n", nights, charges);
}
