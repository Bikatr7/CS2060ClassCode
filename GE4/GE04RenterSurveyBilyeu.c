#include <stdio.h>

#define NUM_RENTERS 5
#define NUM_CATEGORIES 3

int getValidInt(int min, int max);
void printCategories(const char* categories[], size_t totalCategories);
void getRatings(int rentalSurvey[][NUM_CATEGORIES], int numRenters, int numCategories);
void printSurveyResults(int rentalSurvey[][NUM_CATEGORIES], int numRenters, int numCategories);
void calculateCategoryAverages(int rentalSurvey[][NUM_CATEGORIES], float categoryAverages[], int numRenters, int numCategories);
void printCategoryData(float categoryAverages[], int numCategories);

int main()
{

	return 0;

}

//--------------------start-of-getValidInt()----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int getValidInt(int min, int max)
{

    /*
    *
    * Gets a valid integer from the user.
    *
    * Parameters:
    * min (int): The minimum value the user can enter.
    * max (int): The maximum value the user can enter.
    *
    * Returns:
    * int: The valid integer the user entered.
    *
    */

    int nights;
    char ch;

    // Loop until valid input
    while (1)
    {
        int result = scanf("%d", &nights);

        // Check if there are any characters left in the buffer
        ch = getchar();
        if (ch != '\n' && ch != EOF)
        {
            // Clear the rest of the buffer
            while ((ch = getchar()) != '\n' && ch != EOF);
        }

        // Check if the input is an integer
        if (result != 1)
        {
            printf("Error: Not an integer number. Please enter the value again.\n");
        }
        // check if input is within range or sentinel       
        else if ((nights >= min && nights <= max))
        {
            return nights;
        }
        else
        {
            printf("Error: Not within %d and %d. Please enter the value again.\n", min, max);
        }
    }
}

//----------------------start-of-printCategories()----------------------

void printCategories(const char* categories[], size_t totalCategories) 
{

    /*
    * 
    * Print the categories for the survey.
    * 
    * Parameters:
    * const char* categories[]: The array of categories for the survey.
    * size_t totalCategories: The total number of categories in the survey.
    * 
    * Returns:
    * Void.
    * 
    */

    printf("Rating Categories:\t");

    for (size_t i = 0; i < totalCategories; ++i) 
    {
        printf("\t%zu.%s\t", i + 1, categories[i]);
    }

    printf("\n");
}

//----------------------start-of-getRatings()----------------------

void getRatings(int rentalSurvey[][NUM_CATEGORIES], int numRenters, int numCategories) 
{

    /*
    * 
    * Get the ratings for each renter.
    * 
    * Parameters:
    * int rentalSurvey[][NUM_CATEGORIES]: The 2darray of ratings for each renter.
    * int numRenters: The total number of renters.
    * int numCategories: The total number of categories.
    * 
    * Returns:
    * Void.
    * 
    */

    for (int i = 0; i < numRenters; ++i) 
    {
        printf("Renter %d:\n", i + 1);

        for (int ii = 0; ii < numCategories; ++ii) 
        {
            printf("Enter your rating for Category %d: ", ii +1);

            int rating = getValidInt(1, 5);

            rentalSurvey[i][ii] = rating;
        }
    }
}

//----------------------start-of-printSurveyResults()----------------------

void printSurveyResults(int rentalSurvey[][NUM_CATEGORIES], int numRenters, int numCategories) 
{
    /*
    * 
    * Print the survey results.
    * 
    * Parameters:
    * int rentalSurvey[][NUM_CATEGORIES]: The 2darray of ratings for each renter.
    * int numRenters: The total number of renters.
    * int numCategories: The total number of categories.
    * 
    * Returns:
    * void.
    * 
    */

    for (int i = 0; i < numRenters; ++i) 
    {
        printf("Survey %d:\t", i + 1);

        for (int ii = 0; ii < numCategories; ++ii) 
        {
            printf("\t%d\t", rentalSurvey[i][ii]);

        }

        printf("\n");
    }
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
