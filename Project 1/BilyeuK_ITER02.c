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

    int numCategories;
    int numRenters;

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
void calculateCategoryAverages(Property* property);

// Get the ratings for each renter.
void getRatings(Property* property, int sentinel);

// Print the survey results.
void printPropertyRatings(Property* property);

// Prints the number of nights and the charges for the rental property.
void printNightsCharges(unsigned int nights, int charges);

// placeholder for printSummaryReport
void printSummaryReport(Property* property);

// Runs the rental mode.
bool rentalMode(Property* property, char correctUsername[], char correctPassword[], int minNights, int maxNights, int minRate, int maxRate, int sentinel, int maxAttempts);

// Prints the rental property information.
bool ownerMode(char correctUsername[], char correctPassword[], int maxAttempts);

// Clears the buffer and gets a string from the user.
void clearBufferAndFgets(char* str, int size);


//--------------------start-of-main()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() 
{
    Property property;


    if (ownerMode(CORRECT_ID, CORRECT_PASSCODE, LOGIN_MAX_ATTEMPTS)) 
    {

        setupProperty(&property, MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, MIN_RATE, MAX_RATE, SENTINAL_NEG1);

        bool exitRentalMode = rentalMode(&property, CORRECT_ID, CORRECT_PASSCODE, MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, MIN_RATE, MAX_RATE, SENTINAL_NEG1, LOGIN_MAX_ATTEMPTS);

        if(exitRentalMode)
            printSummaryReport(&property);
       
    }

    return 0;

}

//--------------------start-of-printSummaryReport()-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printSummaryReport(Property* property) 
{
    /*
    * 
    * Prints the rental property summary report.
    * 
    * Parameters:
    * property (Property*): The rental property to print the summary report for.
    * 
    * */
    
    calculateCategoryAverages(property);

    puts("Rental Property Report\n");
    printf("Name: %s\n", property->propName);
    printf("Location: %s\n\n", property->locName);

    puts("Rental       Property       Totals\n");
    puts("Renters      Nights        Charges\n");
    printf("%-13d %-13d $%-13d\n\n", property->totalRenters, property->totalNights, property->totalCharge);

    puts("Category Rating Averages\n");
    printf("Check-in Process: %d\n", property->categoryAverages[0]);
    printf("Cleanliness: %d\n", property->categoryAverages[1]);
    printf("Amenities: %d\n", property->categoryAverages[2]);

    puts("\nExiting AirUCCS\n");
}

//--------------------start-of-setupProperty()-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void setupProperty(Property* property, int minNights, int maxNights, int minRate, int maxRate, int sentinel)
{

    /*
    * 
    * Sets up the rental property.
    * 
    * Parameters:
    * property (Property*): The rental property to set up.
    * minNights (int): The minimum number of nights the user can enter.
    * maxNights (int): The maximum number of nights the user can enter.
    * minRate (int): The minimum rate the user can enter.
    * maxRate (int): The maximum rate the user can enter.
    * sentinel (int): The value that will end the loop.
    * 
    */

    puts("Enter the number of nights until the first discount interval: ");
    property->interval1 = getValidInt(minNights, maxNights, sentinel);

    puts("Enter the number of nights until the second discount interval: ");
    property->interval2 = getValidInt(property->interval1 + 1, maxNights, sentinel);

    puts("Enter the nightly rate: ");
    property->rate = getValidInt(minRate, maxRate, sentinel);

    puts("Enter the discount rate: ");
    property->discount = getValidInt(minRate, property->rate - 1, sentinel);

    puts("Enter the rental property name: ");
    clearBufferAndFgets(property->propName, STRING_LENGTH);

    puts("Enter the rental property location: ");
    clearBufferAndFgets(property->locName, STRING_LENGTH);

    property->totalCharge = 0;
    property->totalNights = 0;
    property->totalRenters = 0;
    property->numRenters = 0;
    property->numCategories = RENTER_SURVEY_CATEGORIES;

    for (int i = 0; i < RENTER_SURVEY_CATEGORIES; ++i) 
    {
        property->categoryAverages[i] = 0;

        for (int ii = 0; ii < VACATION_RENTERS; ++ii) 
        {
            property->reviews[ii][i] = 0;
        }
    }
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

	puts("\nRental Property Information\n\n");
	printf("Location Name: %s\n", property->locName);
	printf("Property Name: %s\n", property->propName);
	printf("First Interval: %d\n", property->interval1);
	printf("Second Interval: %d\n", property->interval2);
	printf("Rate: %d\n", property->rate);
	printf("Discount: %d\n", property->discount);
	puts("\n");

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

bool rentalMode(Property* property, char correctUsername[], char correctPassword[], int minNights, int maxNights, int minRate, int maxRate, int sentinel, int maxAttempts)
{

    /*
    * 
    * Runs the rental mode.
    * 
    * Parameters:
    * property (Property*): The rental property to run the rental mode for.
    * correctUsername (char[]): The correct username for the rental property.
    * correctPassword (char[]): The correct password for the rental property.
    * minNights (int): The minimum number of nights the user can enter.
    * maxNights (int): The maximum number of nights the user can enter.
    * minRate (int): The minimum rate the user can enter.
    * maxRate (int): The maximum rate the user can enter.
    * sentinel (int): The value that will end the loop.
    * 
    * Returns:
    * bool: Whether or not the user wants to exit rental mode.
    * 
    */

    bool exitRentalMode = false;
    int currNights = 0;

    do 
    {
        // reset number of renters
        property->numRenters = 0;

        printRentalPropertyInfo(property);
        printPropertyRatings(property);

        puts("Enter the number of nights you want to rent the property: ");
        currNights += getValidInt(minNights, maxNights, SENTINAL_NEG1);
        
        if (currNights == sentinel)
        {

            bool result = ownerMode(correctUsername, correctPassword, maxAttempts);

            if(result)
            {
                exitRentalMode = true;
            }
			
        }
        else
        {
            property->totalCharge += calculateCharges(property->totalNights, property->interval1, property->interval2, property->rate, property->discount);
            property->totalRenters++;
            property->numRenters++;

            property->totalNights += currNights;

            printNightsCharges(property->totalNights, property->totalCharge);

            getRatings(property, sentinel);
        }
    }
    while (currNights != sentinel);

    return exitRentalMode;
    
}

//--------------------start-of-ownerMode()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool ownerMode(char correctUsername[], char correctPassword[], int maxAttempts)
{
    /*
    * 
    * Runs the owner mode.
    * 
    * Parameters:
    * correctUsername (char[]): The correct username for the rental property.
    * correctPassword (char[]): The correct password for the rental property.
    * maxAttempts (int): The maximum number of login attempts.
    * 
    * Returns:
    * loginSuccess (bool): Whether or not the user successfully logged in.
    * 
    */

    char username[STRING_LENGTH] = "";
    char password[STRING_LENGTH] = "";
    bool loginSuccess = false; 

    int attempts = 0;

    while (attempts < maxAttempts && !loginSuccess)
    {
        puts("Enter your AirUCCS ID: ");
        clearBufferAndFgets(username, STRING_LENGTH);

        puts("Enter your AirUCCS password: ");
        clearBufferAndFgets(password, STRING_LENGTH);

        if(strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0)
        {
            puts("You have successfully logged in.\n");
            loginSuccess = true;
        }
        else
        {
            puts("Incorrect ID or password. Please try again.\n");
            attempts++;
        }
    }

    if(!loginSuccess)
    {
        puts("You have exceeded the maximum number of login attempts.\nExiting AirUCCS.");
    }

    return loginSuccess;
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

void calculateCategoryAverages(Property* property)
{
    /*
    * 
    * Calculate the average rating for each category.
    * 
    * Parameters:
    * property (Property*): The rental property to calculate the averages for.
    * 
    */

    for (size_t ii = 0; ii < property->numCategories; ii++)
    {
        int sum = 0;
        for (int i = 0; i < property->totalRenters; i++)
        {
            sum += property->reviews[i][ii];
        }

        if (property->totalRenters > 0)
        {
            property->categoryAverages[ii] = sum / property->totalRenters;
        }
        else
        {
			property->categoryAverages[ii] = 0;
        }
    }
}

//----------------------start-of-getRatings()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void getRatings(Property* property, int sentinel)
{
    /*
    *
    * Get the ratings for each renter.
    *
    * Parameters:
    * property (Property*): The rental property to get the ratings for.
    * sentinel (int): The value that will end the loop.
    */

    for (int i = 0; i < property->totalRenters; ++i)
    {
        printf("Renter %d:\n", i + 1);
        for (int ii = 0; ii < property->numCategories; ++ii)
        {
            printf("Enter your rating for Category %d: ", ii + 1);
            int rating = getValidInt(1, 5, sentinel);
            property->reviews[i][ii] = rating;
        }
    }
}

//----------------------start-of-printPropertyRatings()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printPropertyRatings(Property* property)
{
    /*
    *
    * Prints the property ratings.
    *
    * Parameters:
    * property (Property*): The rental property to print the ratings for.
    *
    */

    if (property->numRenters > 0)
    {
        puts("Survey Results\n");
        puts("Rating Categories:\t1.Check-in Process\t2.Cleanliness\t3.Amenities\n");

        for (int i = 0; i < property->numRenters; i++)
        {
            printf("Survey %d:\t\t", i + 1);
            for (int ii = 0; ii < property->numCategories; ii++)
            {
                printf("%d\t\t\t", property->reviews[i][ii]);
            }
            puts("\n");
        }
    }
    else
    {
        puts("No Ratings Currently\n");
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
        puts("\nRental Charges\n\n");
        puts("Nights          Charge\n");
        printf("%-15u $%d\n\n", nights, charges);
	}
    else
    {
        puts("There were no rentals.\n");
    }

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
    * */

    // fgets reads until newline or EOF
    if (fgets(str, size, stdin) == NULL) 
    {

    }

    // Remove any newline at the end
    char* newline = strchr(str, '\n');
    if (newline)
    {
        *newline = '\0';
    }
    else
    {
        // Clear the rest of the buffer until newline is found or EOF
        int c;
        while ((c = getchar()) != '\n') {}
    }
}