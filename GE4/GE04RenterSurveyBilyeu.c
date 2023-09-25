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

}