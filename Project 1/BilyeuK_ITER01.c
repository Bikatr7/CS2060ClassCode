#include <stdio.h>

// constants
int const SENTINAL_NEG1 = -1;
int unsigned const MIN_RENTAL_NIGHTS = 1;
unsigned int const MAX_RENTAL_NIGHTS = 14;
unsigned int const INTERVAL_1_NIGHTS = 3;
unsigned int const INTERVAL_2_NIGHTS = 6;
double const RENTAL_RATE = 400;
double const DISCOUNT = 50;


//Prints the rental property information.
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int
    interval1Nights, unsigned int interval2Nights, double rate, double discount);

int getValidInt(int min, int max, bool sentinel);

double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int
    interval2Nights, double rate, double discount);

void printNightsCharges(unsigned int nights, double charges);

// I dunno how do document functions in C. So I'll just use docstrings.

//--------------------start-of-main()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    
    return 0;
}

//--------------------start-of-printRentalPropertyInfo()--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int interval1Nights,
    unsigned int interval2Nights, double rate, double discount) {

    /*
    
    Prints the rental property information.

    Parameters:
    minNights (unsigned int): The minimum number of nights the rental property can be rented for.
    maxNights (unsigned int): The maximum number of nights the rental property can be rented for.
	interval1Nights (unsigned int): The number of nights in the first interval.
	interval2Nights (unsigned int): The number of nights in the second interval.
	rate (double): The rate for the first interval.
	discount (double): The discount for the second interval.

    Returns:
    None

    */

    printf("Rental Property can be rented for %u to %u nights.\n", minNights, maxNights);
    printf("$%.2f rate a night for the first %u nights\n", rate, interval1Nights);
    printf("$%.2f discount rate a night for nights %u to %u\n", discount, interval1Nights + 1, interval2Nights);
    printf("$%.2f discount rate a night for each remaining night over %u.\n\n", 2 * discount, interval2Nights);
}
