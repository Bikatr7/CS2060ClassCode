// Kaden Bilyeu
// 11-20-2023
// Iteration 3
// The goal of this program is to calculate the charges for a rental property. It offers features such as rental property setup, rental property information, rental property ratings, and a summary report. The program also has a login feature for the rental property owner. The program uses a linked list to store the rental properties. The program also writes the rental property information to a file.
// The code always aims to maintain proper and secure coding practices.
// Windows 10
// Visual Studio 2022

// Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

//Maximum length of a string
#define STRING_LENGTH 80

//Two dimensional array storage amounts for rows and columns of survey data
#define VACATION_RENTERS 5
#define RENTER_SURVEY_CATEGORIES 3

//Rental property login and sentinal values
#define CORRECT_ID "kadenbilyeu"
#define CORRECT_PASSCODE "atottalysecurepassword7!?!"
#define LOGIN_MAX_ATTEMPTS 2
#define SENTINAL_NEG1 -1

//rental property constant ranges
#define MIN_RENTAL_NIGHTS 1
#define MAX_RENTAL_NIGHTS 14
#define MIN_RATE 1
#define MAX_RATE 1000
#define DISCOUNT_MULTIPLIER 2

// file directory
#define PROPERY_FOLDER "C:\\Users\\Tetra\\CS2060Project\\CS2060Project\\"

//--------------------start-of-Property------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
    int interval1;
    int interval2;
    int discount;
    int rate;
    int mutliplier;

    int minNights;
    int maxNights;

    int totalCharge;
    int totalNights;
    int totalRenters;

    int numCategories;
    int numRenters;

    int reviews[VACATION_RENTERS][RENTER_SURVEY_CATEGORIES];

    double categoryAverages[RENTER_SURVEY_CATEGORIES];

    char locName[STRING_LENGTH];
    char propName[STRING_LENGTH];
 
} Property;

//--------------------start-of-PropertyNode------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef struct PropertyNode 
{
    Property data;
    struct PropertyNode* next;

} PropertyNode;

//--------------------start-of-Function-Prototypes------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------Initialization-------------------------/

// Sets up the rental property.
Property* setupProperty(int minNights, int maxNights, int minRate, int maxRate, int sentinel, int numCategories, int maxRenters, int multiplier);

//-------------------------Input-And-Utility-------------------------/

// Gets the user's credentials.
void getUserCredentials(char* username, char* password);

// Clears the buffer and gets a string from the user.
void clearBufferAndFgets(char* str, int size);

// Compares two strings regardless of case and returns an integer value based on the comparison.
int stringCompare(const char* s1, const char* s2);

// Gets a valid integer from the user.
int getValidInt(int min, int max, int sentinel, bool allowSentinel);

// Properly scans an integer from a string.
bool scanInt(const char* stringPointer, int* value);

// Gets a valid choice from the user.
char getSingleCharacterInput();

//-------------------------Core-Calculation-------------------------/

// Calculate the average rating for each category.
int calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, int rate, int discount, int multiplier);

// Calculates the charges for the rental property.
void calculateCategoryAverages(Property* property);

// Calculate the average rating for each category.
double calculateOverallSatisfaction(Property* property);

//-------------------------Data-Output-------------------------/

//Prints the rental property information.
void printRentalPropertyInfo(Property* property);

// Prints all of the rental properties.
void printAllProperties(PropertyNode* head);

// Print the survey results.
void printPropertyRatings(Property* property, const char* CATEGORY_NAMES[RENTER_SURVEY_CATEGORIES]);

// Prints the number of nights and the charges for the rental property.
void printNightsCharges(unsigned int nights, int charges);

// Prints the rental property summary report.
void printSummaryReport(Property* property, const char* CATEGORY_NAMES[RENTER_SURVEY_CATEGORIES]);

// Prints the rental property summary reports.
void printSummaryReports(PropertyNode* head, const char* CATEGORY_NAMES[RENTER_SURVEY_CATEGORIES], const char* directory);

//-------------------------Interactive-Modes-------------------------/

// Runs the rental mode.
bool rentalMode(PropertyNode* head, char correctUsername[], char correctPassword[], int sentinel, int maxAttempts, const char* CATEGORY_NAMES[RENTER_SURVEY_CATEGORIES]);

// Prints the rental property information.
bool ownerMode(char correctUsername[], char correctPassword[], int maxAttempts);

//-------------------------Data-Collection-------------------------/

// Get the ratings for each renter.
void getRatings(Property* property, int sentinel, const char* CATEGORY_NAMES[RENTER_SURVEY_CATEGORIES]);

//-------------------------Linked-List-Util-------------------------/

// Creates a new property node.
PropertyNode* createPropertyNode(Property* property);

// Inserts a property node into the linked list alphabetically.
void insertPropertyAlphabetically(PropertyNode** head, Property* property);

// Selects a property from the linked list.
PropertyNode* selectProperty(PropertyNode* head);

// Frees the linked list memory.
void freePropertyList(PropertyNode** head);

//-------------------------File-IO-------------------------/

// Constructs the filepath.
void constructFilePath(char* filepath, const char* directory, const char* propName);

// Writes the rental property information to a file.
void writeToFile(Property* property, const char* directory);

//--------------------start-of-main()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() 
{

    // Initialize the head of the linked list
    PropertyNode* propertiesHead = NULL;

    const char* CATEGORY_NAMES[RENTER_SURVEY_CATEGORIES] = { "Check-in Process", "Cleanliness", "Amenities" };

    char addAnother = 'y';

    // Check for successful login
    if(ownerMode(CORRECT_ID, CORRECT_PASSCODE, LOGIN_MAX_ATTEMPTS))
    {
        do 
        {
            // Set up the property
            Property* newProperty = setupProperty(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, MIN_RATE, MAX_RATE, SENTINAL_NEG1, RENTER_SURVEY_CATEGORIES, VACATION_RENTERS, DISCOUNT_MULTIPLIER);

            // Insert the property into the linked list
            insertPropertyAlphabetically(&propertiesHead, newProperty);

            puts("Add another property? (y/n): ");
            addAnother = getSingleCharacterInput();

        } while (addAnother == 'y');

        // Run the rental mode
        bool exitRentalMode = rentalMode(propertiesHead, CORRECT_ID, CORRECT_PASSCODE, SENTINAL_NEG1, LOGIN_MAX_ATTEMPTS, CATEGORY_NAMES);

        if (exitRentalMode)
            printSummaryReports(propertiesHead, CATEGORY_NAMES, PROPERY_FOLDER);
    }

    puts("Exiting AirUCCS.");

    freePropertyList(&propertiesHead);

    return 0;
}

//--------------------start-of-setupProperty()-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Property* setupProperty(int minNights, int maxNights, int minRate, int maxRate, int sentinel, int numCategories, int maxRenters, int multiplier)
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
    * numCategories (int): The number of categories for the survey.
    * maxRenters (int): The number of renters for the survey.
    * multiplier (int): The multiplier for the discount.
    *
    */

    // They said dynamically allocate memory for the property, so I assume they want me to use malloc
    Property* property = (Property*)malloc(sizeof(Property));

    if (property == NULL) 
    {
        puts("Error allocating memory for property");
        return NULL;
    }

    printf("Minimum number of nights: %d\n", minNights);
    printf("Maximum number of nights: %d\n", maxNights);
    printf("Minimum rate: $%d\n", minRate);
    printf("Maximum rate: $%d\n", maxRate);

    puts("\nEnter the rental property name: ");
    clearBufferAndFgets(property->propName, STRING_LENGTH);

    puts("Enter the rental property location: ");
    clearBufferAndFgets(property->locName, STRING_LENGTH);

    puts("\nEnter the number of nights until the first discount interval: ");
    property->interval1 = getValidInt(minNights, maxNights, sentinel, false);

    puts("Enter the number of nights until the second discount interval: ");
    property->interval2 = getValidInt(property->interval1, maxNights, sentinel, false);

    puts("Enter the nightly rate: ");
    property->rate = getValidInt(minRate, maxRate, sentinel, false);

    puts("Enter the discount rate: ");
    property->discount = getValidInt(minRate, property->rate - 1, sentinel, false);

    property->totalCharge = 0;
    property->totalNights = 0;
    property->totalRenters = 0;
    property->numRenters = 0;

    property->numCategories = numCategories;
    property->mutliplier = multiplier;
    property->minNights = minNights;
    property->maxNights = maxNights;

    // Initialize the reviews and category averages to 0
    for (size_t i = 0; i < numCategories; ++i)
    {
        property->categoryAverages[i] = 0;

        for (size_t ii = 0; ii < maxRenters; ++ii)
        {
            property->reviews[ii][i] = 0;
        }
    }

    return property;

}

//--------------------start-of-getUserCredentials()-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void getUserCredentials(char* username, char* password)
{

    /*
    *
    * Gets the user's credentials.
    * 
    * Parameters:
    * username (char*): The string to store the username in.
    * password (char*): The string to store the password in.
    * 
    */

    puts("Enter your AirUCCS ID: ");
    clearBufferAndFgets(username, STRING_LENGTH);

    puts("Enter your AirUCCS password: ");
    clearBufferAndFgets(password, STRING_LENGTH);
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

//--------------------start-of-stringCompare()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int stringCompare(const char* s1, const char* s2)
{
    /*
    *
    * Compares two strings regardless of case and returns an integer value based on the comparison.
    *
    * Parameters:
    * s1 (const char*) : The first string to compare.
    * s2 (const char*) : The second string to compare.
    *
    */

    char s1_lower[STRING_LENGTH];
    char s2_lower[STRING_LENGTH];

    // null-terminate.
    strncpy(s1_lower, s1, STRING_LENGTH);
    s1_lower[STRING_LENGTH - 1] = '\0';

    // null-terminate.
    strncpy(s2_lower, s2, STRING_LENGTH);
    s2_lower[STRING_LENGTH - 1] = '\0';

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

//--------------------start-of-getValidInt()----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int getValidInt(int min, int max, int sentinel, bool allowSentinel)
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

    while (1) 
    {
        clearBufferAndFgets(inputStr, STRING_LENGTH);

        if (scanInt(inputStr, &value)) 
        {
            if ((value >= min && value <= max) || (value == sentinel && allowSentinel))
            {
                return value;
            }
        }

        // Cause I didn't like -1 being allowed for the properrty setup integers
        if(allowSentinel)
            printf("Error: Please enter a valid value (%d to %d or %d to exit).\n", min, max, sentinel);
        else
        {
            printf("Error: Please enter a valid value (%d to %d).\n", min, max);
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

//--------------------start-of-getSingleCharacterInput()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

char getSingleCharacterInput()
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
            return tolower(choice);
        }
        else
        {
            puts("Error: Invalid choice. Please enter (y)es or (n)o.");
        }
    }
}

//--------------------start-of-calculateCharges()-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, int rate, int discount, int multiplier)
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
    * multiplier (int): The multiplier for the discount.
    *
    * Returns:
    * int: The total charge for the rental property.
    *
    */

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
        totalCharge = (interval1Nights * rate) + ((interval2Nights - interval1Nights) * (rate - discount)) + ((nights - interval2Nights) * (rate - multiplier * discount));
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
        float sum = 0;
        for (size_t i = 0; i < property->totalRenters; i++)
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

//----------------------start-of-calculateOverallSatisfaction()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

double calculateOverallSatisfaction(Property* property)
{
    /*
    * 
    * Calculate the average rating for each category.
    * 
    * Parameters:
    * property (Property*): The rental property to calculate the averages for.
    * 
    * Returns:
    * total: The overall satisfaction for the rental property.
    */

    double total = 0;

    for (size_t i = 0; i < property->numCategories; ++i)
    {
        total += (double) property->categoryAverages[i];
    }

    if (property->numCategories > 0) 
    {
        total = total / property->numCategories;
    }

    return total;
}

//--------------------start-of-printRentalPropertyInfo()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printRentalPropertyInfo(Property* property)
{
    /*
    *
    * Prints the rental property information.
    *
    * Parameters:
    * property (Property*): The rental property to print the information for.
    *
    */

    puts("\n----------------------------------------");
    puts("Rental Property Information");
    puts("----------------------------------------");
    printf("Name: %-15s\n", property->propName);
    printf("Location: %-15s\n", property->locName);
    printf("Property can be rented for %d to %d nights\n", property->minNights, property->maxNights);
    printf("$%d a night for the first %d nights\n", property->rate, property->interval1);
    printf("$%d discount rate a night for night %d to %d\n", property->discount, property->interval1 + 1, property->interval2);
    printf("$%d discount rate a night for each night over %d\n", property->discount * property->mutliplier, property->interval2);

}

//----------------------start-of-printAllProperties()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printAllProperties(PropertyNode* head) 
{

    /*
    * 
    * Prints all of the rental properties.
    * 
    * Parameters:
    * head (PropertyNode*): The head of the linked list.
    * 
	*/

    PropertyNode* current = head;

    puts("\nAvailable Rental Properties:");
    while (current != NULL) 
    {
        printRentalPropertyInfo(&current->data);
        current = current->next;
    }
}

//----------------------start-of-printPropertyRatings()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printPropertyRatings(Property* property, const char* CATEGORY_NAMES[RENTER_SURVEY_CATEGORIES])
{
    /*
    *
    * Prints the property ratings.
    *
    * Parameters:
    * property (Property*): The rental property to print the ratings for.
    * CATEGORY_NAMES (const char*): The names of the categories for the survey.
    *
    */

    puts("----------------------------------------");
    puts("Property Rating Results");
    puts("----------------------------------------");

    if (property->totalRenters > 0)
    {
        printf("Rating Categories:\t");

        for (size_t i = 0; i < property->numCategories; i++)
        {
            printf("%zu. %s\t", i + 1, CATEGORY_NAMES[i]);
        }

        puts("");

        for (size_t i = 0; i < property->totalRenters; i++)
        {
            printf("Renter %zu Ratings:\t", i + 1);
            for (size_t ii = 0; ii < property->numCategories; ii++)
            {
                printf("%d\t\t\t", property->reviews[i][ii]);
            }

            puts(""); 
        }
    }
    else
    {
        puts("No Ratings Currently");
    }

    puts("----------------------------------------");

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
    */

    if (nights > 0)
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

//--------------------start-of-printSummaryReport()-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printSummaryReport(Property* property, const char* CATEGORY_NAMES[RENTER_SURVEY_CATEGORIES])
{
    /*
    * 
    * Prints the rental property summary report.
    * 
    * Parameters:
    * property (Property*): The rental property to print the summary report for.
    * CATEGORY_NAMES (const char*): The names of the categories for the survey.
    * 
    */
    
    calculateCategoryAverages(property);

    // standard output print
    puts("============================================================");
    puts("                  Rental Property Report                    ");
    puts("============================================================");
    printf("Name: %s\n", property->propName);
    printf("Location: %s\n", property->locName);
    puts("------------------------------------------------------------");
    printf("Total Renters: %d\n", property->totalRenters);
    printf("Total Nights Rented: %d\n", property->totalNights);
    printf("Total Charges Collected: $%d\n", property->totalCharge);
    puts("------------------------------------------------------------");
    puts("Category Rating Averages:");


    // category averages print
    for (size_t i = 0; i < property->numCategories; i++)
	{
		printf("%zu. %s: %.1f/5\n", i + 1, CATEGORY_NAMES[i], property->categoryAverages[i]);
	}

    // overall satisfaction print
    puts("------------------------------------------------------------");
    printf("Overall Satisfaction: %.1f/5\n", calculateOverallSatisfaction(property));

}

//--------------------start-of-printSummaryReports()-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printSummaryReports(PropertyNode* head, const char* CATEGORY_NAMES[RENTER_SURVEY_CATEGORIES], const char* DIRECTORY)
{

    /*
    * 
    * Prints the rental property summary reports.
    * 
    * Parameters:
    * head (PropertyNode*): The head of the linked list.
    * CATEGORY_NAMES (const char*): The names of the categories for the survey.
    * DIRECTORY (const char*): The directory to write the file to.
    * 
	*/

    PropertyNode* current = head;

    while (current != NULL)
    {
        printSummaryReport(&current->data, CATEGORY_NAMES);
        writeToFile(&current->data, DIRECTORY);
        current = current->next;
    }

    // Goodbye message outside the loop cause it's only supposed to print once, and i kept having a f*** ton of problems with it due to sleep deprivation
    puts("============================================================");
    puts("Thank you for using AirUCCS. Have a great day!");
    puts("============================================================");
}

//--------------------start-of-rentalMode()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool rentalMode(PropertyNode* head, char correctUsername[], char correctPassword[], int sentinel, int maxAttempts, const char* CATEGORY_NAMES[RENTER_SURVEY_CATEGORIES])
{
    /*
    * 
    * Runs the rental mode.
    * 
    * Parameters:
    * head (PropertyNode*): The head of the linked list.
    * correctUsername (char[]): The correct username for the rental property.
    * correctPassword (char[]): The correct password for the rental property.
    * sentinel (int): The value that will end the loop.
    * maxAttempts (int): The maximum number of login attempts.
    * CATEGORY_NAMES (const char*): The names of the categories for the survey.
    * 
    * Returns:
    * exitRentalMode (bool): Whether or not the user wants to exit the rental mode.
    * 
	*/

    PropertyNode* selectedProperty;

    bool exitRentalMode = false;

    bool printNotFound = false;

    int currNights = 0;
    int currCharge = 0;

    while (!exitRentalMode)
    {
        printAllProperties(head);

    	if(printNotFound)
		{
			puts("\nError: Property not found.");
			printNotFound = false;
		}

        selectedProperty = selectProperty(head);
        if(selectedProperty)
        {
            puts("\nEnter the number of nights you want to rent the property: ");
            currNights = getValidInt(selectedProperty->data.minNights, selectedProperty->data.maxNights, sentinel, true);

            if(currNights == sentinel)
            {
                exitRentalMode = ownerMode(correctUsername, correctPassword, maxAttempts);

            }
            // If we're not exiting rental mode, calculate the charges and other stuff
            else
            {
                currCharge = calculateCharges(currNights, selectedProperty->data.interval1, selectedProperty->data.interval2, selectedProperty->data.rate, selectedProperty->data.discount, DISCOUNT_MULTIPLIER);

                selectedProperty->data.totalCharge += currCharge;
                selectedProperty->data.totalRenters++;
                selectedProperty->data.totalNights += currNights;

                printNightsCharges(currNights, currCharge);

                getRatings(&selectedProperty->data, sentinel, CATEGORY_NAMES);
            }
        }
        else
        {
            printNotFound = true;
        }
    }

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

        getUserCredentials(username, password);

        // Assuming they want case insensitive comparison, didn't see it specify in the assignment
        if(strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0)
        {
            puts("\nYou have successfully logged in.\n");
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
        puts("You have exceeded the maximum number of login attempts.");
    }

    return loginSuccess;
}



//----------------------start-of-getRatings()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void getRatings(Property* property, int sentinel, const char* CATEGORY_NAMES[RENTER_SURVEY_CATEGORIES])
{
    /*
    *
    * Get the ratings for each renter.
    *
    * Parameters:
    * property (Property*): The rental property to get the ratings for.
    * sentinel (int): The value that will end the loop.
    * CATEGORY_NAMES (const char*): The names of the categories for the survey.
    * 
    */

    const int MIN_STARS = 1;
    const int MAX_STARS = 5;

    printf("Renter %d:\n", property->totalRenters);
    for (size_t ii = 0; ii < property->numCategories; ++ii)
    {
        printf("Enter your rating for Category %zu (%s): ", ii + 1, CATEGORY_NAMES[ii]);
        int rating = getValidInt(MIN_STARS, MAX_STARS, sentinel, false);
        property->reviews[property->totalRenters-1][ii] = rating;
    }
}

//----------------------start-of-createPropertyNode()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PropertyNode* createPropertyNode(Property* property) 
{

    /*
    * 
    * Creates a new property node.
    * 
    * Parameters:
    * property (Property*): The rental property to create the node for.
    * 
    * Returns:
    * newNode (PropertyNode*): The new property node.
    * 
	*/

    PropertyNode* newNode = (PropertyNode*)malloc(sizeof(PropertyNode));

    if (newNode == NULL) 
    {
        puts("Error allocating memory");
        return NULL;
    }

    newNode->data = *property;
    newNode->next = NULL;

    return newNode;
}

//----------------------start-of-insertPropertyAlphabetically()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void insertPropertyAlphabetically(PropertyNode** head, Property* property) 
{

    /*
    * 
    * Inserts a property node into the linked list alphabetically.
    * 
    * Parameters:
    * head (PropertyNode**): The head of the linked list.
    * property (Property*): The rental property to insert into the linked list.
    * 
	*/

    PropertyNode* newNode = createPropertyNode(property);

    if (*head == NULL || stringCompare((*head)->data.propName, property->propName) >= 0) 
    {
        newNode->next = *head;
        *head = newNode;
    }
    else 
    {
        PropertyNode* current = *head;

        while (current->next != NULL && stringCompare(current->next->data.propName, property->propName) < 0) 
        {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }
}

//----------------------start-of-selectProperty()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

PropertyNode* selectProperty(PropertyNode* head) 
{

    /*
    *
    * Selects a property from the linked list.
    * 
    * Parameters:
    * head (PropertyNode*): The head of the linked list.
    * 
    * Returns:
    * current (PropertyNode*): The selected property node.
    * 
    */

    char propName[STRING_LENGTH];
    PropertyNode* current = head;

    puts("\nEnter the name of the property you want to rent: ");
    clearBufferAndFgets(propName, STRING_LENGTH);

    while (current != NULL) 
    {
        if (stringCompare(current->data.propName, propName) == 0)
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

//----------------------start-of-freePropertyList()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void freePropertyList(PropertyNode** head) 
{

    /*
    * 
    * Frees the linked list memory.
    * 
    * Parameters:
    * head (PropertyNode**): The head of the linked list.
    * 
    */

    PropertyNode* current = *head;
    PropertyNode* nextNode = NULL;

    while (current != NULL) 
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    *head = NULL; // Set head to NULL after freeing the list
}

//----------------------start-of-constructFilePath()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void constructFilePath(char* filepath, const char* DIRECTORY, const char* PROPERTY_NAME) 
{

    /*
    * 
    * Constructs the filepath.
    * 
    * Parameters:
    * filepath (char*): The filepath to construct.
    * DIRECTORY (const char*): The directory to write the file to.
    * PROPERTY_NAME (const char*): The name of the rental property.
    * 
	*/

    char safePropName[STRING_LENGTH + 150];

    strncpy(safePropName, PROPERTY_NAME, STRING_LENGTH + 150);
    safePropName[STRING_LENGTH + 149] = '\0';

    // Replace spaces with underscores
    for (int i = 0; safePropName[i] != '\0'; i++) 
    {
        if (safePropName[i] == ' ') 
        {
            safePropName[i] = '_';
        }
    }

    // Construct the filepath
    strncpy(filepath, DIRECTORY, STRING_LENGTH + 150);
    filepath[STRING_LENGTH + 149] = '\0';

    strcat(filepath, safePropName);
    strcat(filepath, ".txt");
}

//--------------------start-of-writeToFile()-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void writeToFile(Property* property, const char* DIRECTORY) 
{

    /*
    * 
    * Writes the rental property information to a file.
    * 
    * Parameters:
    * property (Property*): The rental property to write to the file.
    * DIRECTORY (const char*): The directory to write the file to.
    * 
    */

    char filename[STRING_LENGTH + 150];

    constructFilePath(filename, DIRECTORY, property->propName);

    FILE* file = fopen(filename, "w");
    if (file == NULL) 
    {
        puts("Error opening file");
        return;
    }

    // Writing property details to the file
    fprintf(file, "Property Name: %s\nLocation: %s\nTotal Nights Rented: %d\nTotal Charges: $%d\n", property->propName, property->locName, property->totalNights, property->totalCharge);

    fclose(file);
}