#include <stdio.h>

#define NUM_RENTERS 5
#define NUM_CATEGORIES 3

void printCategories(const char* categories[], size_t totalCategories);
void getRatings(int rentalSurvey[][NUM_CATEGORIES], int numRenters, int numCategories);
void printSurveyResults(int rentalSurvey[][NUM_CATEGORIES], int numRenters, int numCategories);
void calculateCategoryAverages(int rentalSurvey[][NUM_CATEGORIES], float categoryAverages[], int numRenters, int numCategories);
void printCategoryData(float categoryAverages[], int numCategories);

int main()
{

	return 0;

}

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