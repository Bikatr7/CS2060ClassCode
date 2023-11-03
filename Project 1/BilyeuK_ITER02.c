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

//Maximum length of a string
#define STRING_LENGTH 80

//Two dimensional array storage amounts for rows and columns of surve data
#define VACATION_RENTERS 5
#define RENTER_SURVEY_CATEGORIES 3

//Rental property login and sentinal values
#define CORRECT_ID "id1"
#define CORRECT_PASSCODE "ABCD"
#define LOGIN_MAX_ATTEMPTS 3
#define SENTINAL_NEG1 -1

//rental property constant ranges
#define MIN_RENTAL_NIGHTS 1
#define MAX_RENTAL_NIGHTS 14
#define MIN_RATE 1
#define MAX_RATE 1000
#define DISCOUNT_MULTIPLIER 2

//--------------------start-of-Property------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
    int interval1;
    int interval2;
    int discount;
    int rate;
    int totalCharge;
    int totalNights;
    int totalRenters;
    int reviews[VACATION_RENTERS][RENTER_SURVEY_CATEGORIES];
    int categoryAverages[RENTER_SURVEY_CATEGORIES];
    char locName[STRING_LENGTH];
    char propName[STRING_LENGTH];
} Property;

//--------------------start-of-Function-Prototypes------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Sets up the rental property.
void setupProperty(Property* property, int minNights, int maxNights, int minRate, int maxRate, int sentinel);

//Prints the rental property information.
void printRentalPropertyInfo(Property* property);

// Gets a valid integer from the user.
int getValidInt(int min, int max, int sentinel);

// Properly scans an integer from a string.
bool scanInt(const char* stringPointer, int* value);

// Calculates the charges for the rental property.
int calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, int rate, int discount);

// Calculate the average rating for each category.
void calculateCategoryAverages(Property* property, int numRenters, int numCategories);

// Get the ratings for each renter.
void getRatings(Property* property, int numRenters, int numCategories, int sentinel);

// Print the survey results.
void printSurveyResults(Property* property, int numRenters, int numCategories);

// Prints the number of nights and the charges for the rental property.
void printNightsCharges(unsigned int nights, int charges);


//--------------------start-of-main()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() 
{


}

//--------------------start-of-setupProperty()-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void setupProperty(Property *property, int minNights, int maxNights, int minRate, int maxRate, int sentinel)
{
    /*
    * 
    * Sets up the rental property.
    * 
    * Parameters:
    * property (Property*): The rental property to set up.
    * 
    * */

    puts("Enter the number of nights until the first discount interval: ");
    int interval1 = getValidInt(minNights, maxNights, sentinel);

    puts("Enter the number of nights until the second discount interval: ");
    int interval2 = getValidInt(minNights, maxNights, sentinel);
    
    puts("Enter the nightly rate : ");
    int rate = getValidInt(minRate, maxRate, sentinel);

    puts("Enter the discount rate: ");
    int discount = getValidInt(minRate, rate, sentinel);

    puts("Enter the location name: ");
    char locName[STRING_LENGTH];
    fgets(locName, STRING_LENGTH, stdin);

    puts("Enter the property name: ");
	char propName[STRING_LENGTH];
	fgets(propName, STRING_LENGTH, stdin);

	property->interval1 = interval1;
	property->interval2 = interval2;
	property->rate = rate;
	property->discount = discount;
	property->totalCharge = 0;
	property->totalNights = 0;
	property->totalRenters = 0;

    // Use strcpy to copy the strings to the property properly
	strcpy(property->locName, locName);
	strcpy(property->propName, propName);

}

//--------------------start-of-printRentalPropertyInfo()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printRentalPropertyInfo(Property *property)
{
	/*
	* 
	* Prints the rental property information.
	* 
	* Parameters:
	* property (Property*): The rental property to print the information for.
	* 
	* */

	printf("\nRental Property Information\n\n");
	printf("Location Name: %s\n", property->locName);
	printf("Property Name: %s\n", property->propName);
	printf("First Interval: %d\n", property->interval1);
	printf("Second Interval: %d\n", property->interval2);
	printf("Rate: %d\n", property->rate);
	printf("Discount: %d\n", property->discount);
	printf("\n");

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

    char inputStr[STRING_LENGTH];
    int value;

    printf("Enter the number of nights you want to rent the property\n");

    // Loop until valid input
    while (1)
    {
        // Get input as a string
        fgets(inputStr, STRING_LENGTH, stdin);

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

//--------------------start-of-rentalMode()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void rentalMode(Property* property)
{

    do 
    {
        printRentalPropertyInfo(property);

    }

}

//--------------------start-of-calculateCharges()-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, int rate, int discount) 
{

    /*
    * 
    * Calculates the charges for the rental property.
    * 
    * Parameters:
    * nights (unsigned int): The number of nights the rental property is rented for.
    * interval1Nights (unsigned int): The number of nights in the first interval.
    * interval2Nights (unsigned int): The number of nights in the second interval.
    * rate (int): The rate for the first interval.
    * discount (int): The discount for the second interval.
    * 
    * Returns:
    * int: The total charge for the rental property.
    * 
    * */


    int totalCharge = 0;

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

//----------------------start-of-calculateCategoryAverages())--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void calculateCategoryAverages(Property* property, int numRenters, int numCategories)
{
    /*
    * 
    * Calculate the average rating for each category.
    * 
    * Parameters:
    * property (Property*): The rental property to calculate the averages for.
    * numRenters (int): The total number of renters.
    * numCategories (int): The total number of categories.
    * 
    */

    for (size_t ii = 0; ii < numCategories; ii++)
    {
        int sum = 0;
        for (int i = 0; i < numRenters; i++)
        {
            sum += property->reviews[i][ii];
        }
        property->categoryAverages[ii] = sum / numRenters;
    }
}

//----------------------start-of-getRatings()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void getRatings(Property* property, int numRenters, int numCategories, int sentinel)
{
    /*
    *
    * Get the ratings for each renter.
    *
    * Parameters:
    * property (Property*): The rental property to get the ratings for.
    * numRenters (int): The total number of renters.
    * numCategories (int): The total number of categories.
    * sentinel (int): The value that will end the loop.
    */

    for (int i = 0; i < numRenters; ++i)
    {
        printf("Renter %d:\n", i + 1);
        for (int ii = 0; ii < numCategories; ++ii)
        {
            printf("Enter your rating for Category %d: ", ii + 1);
            int rating = getValidInt(1, 5, sentinel);
            property->reviews[i][ii] = rating;
        }
    }
}

//----------------------start-of-printSurveyResults()----------------------

void printSurveyResults(Property* property, int numRenters, int numCategories)
{
    /*
    *
    * Print the survey results.
    *
    * Parameters:
    * property (Property*): The rental property to print the survey results for.
    * numRenters (int): The total number of renters.
    * numCategories (int): The total number of categories.
    *
    */

    for (int i = 0; i < numRenters; ++i)
    {
        printf("Survey %d:\t", i + 1);
        for (int ii = 0; ii < numCategories; ++ii)
        {
            printf("\t%-15d\t", property->reviews[i][ii]);
        }
        printf("\n");
    }
}

//--------------------start-of-printNightsCharges()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printNightsCharges(unsigned int nights, int charges) 
{

    /*
    *
    * Prints the number of nights and the charges for the rental property.
    * 
    * Parameters:
    * nights (unsigned int): The number of nights the rental property is rented for.
    * charges (int): The total charge for the rental property.
    * 
    * */

    if(nights > 0)
	{
        printf("\nRental Charges\n\n");
        printf("Nights          Charge\n");
        printf("%-15u $%d\n\n", nights, charges);
	}
    else
    {
        printf("There were no rentals.\n");
    }

}

