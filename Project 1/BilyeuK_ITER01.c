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
void printRentalPropertyInfo(unsigned int minNights, unsigned int maxNights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);

//Gets a valid integer from the user.
int getValidInt(int min, int max, int sentinel);

// Calculates the charges for the rental property.
double calculateCharges(unsigned int nights, unsigned int interval1Nights, unsigned int interval2Nights, double rate, double discount);

// Prints the number of nights and the charges for the rental property.
void printNightsCharges(unsigned int nights, double charges);

// I dunno how do document functions in C. So I'll just use docstrings.

//--------------------start-of-main()------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main() 
{
    unsigned int totalNightsRented = 0;
    double totalCharges = 0;

    while (1) 
    {
        // Display the rental property information
        printRentalPropertyInfo(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

        // Get the number of nights
        int nights = getValidInt(MIN_RENTAL_NIGHTS, MAX_RENTAL_NIGHTS, SENTINAL_NEG1);

        // If user enters the sentinel value, exit loop and print the total summary
        if (nights == SENTINAL_NEG1) 
        {
            printf("Rental Property Owner Total Summary\n\n");
            printNightsCharges(totalNightsRented, totalCharges);
            break;
        }

        // Calculate the charges
        double charges = calculateCharges(nights, INTERVAL_1_NIGHTS, INTERVAL_2_NIGHTS, RENTAL_RATE, DISCOUNT);

        // Update the total nights and charges
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
    * 
    * Gets a valid integer from the user.
    * 
    * Parameters:
    * min (int): The minimum value the user can enter.
    * max (int): The maximum value the user can enter.
    * sentinel (int): The value that will end the loop.
    * 
    * Returns:
    * int: The valid integer the user entered.
    * 
	*/

    int nights;
    char ch;

    printf("Enter the number of nights you want to rent the property\n");

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
        else if ((nights >= min && nights <= max) || nights == sentinel)
        {
            return nights;
        }
        else
        {
            printf("Error: Not within %d and %d. Please enter the value again.\n", min, max);
        }
    }
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

    if (nights <= interval1Nights) 
    {
        totalCharge = nights * rate;
    }
    else if (nights <= interval2Nights) 
    {
        totalCharge = (interval1Nights * rate) + ((nights - interval1Nights) * (rate - discount));
    }
    else 
    {
        totalCharge = (interval1Nights * rate) + ((interval2Nights - interval1Nights) * (rate - discount)) + ((nights - interval2Nights) * (rate - 2 * discount));
    }

    return totalCharge;
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
