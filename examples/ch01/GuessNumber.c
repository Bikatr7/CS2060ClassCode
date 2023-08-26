// Randomly generate numbers between a min and max for user to guess.


// imports
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// preprocessor constant directives
#define MIN 1
#define MAX 1000

// function signatures
void guessGame(void); 
bool isCorrect(int guess, int answer); 

int main(void) {
   
    // sets the seed for random generation as the current time
   //srand(time(0)); 

   // prints out greeting and calles the guessGame function
   puts("Hello Kaden Bilyeu");
   guessGame();

} // end main



// the guessGame function, handles the game mechanic
void guessGame(void) {
    
    // declares & initializes the user guess & response
   int response =0;
   int guess = 0;

   // a do while loop, so it asks a use for a number first with instructions, and keeps asking the user while their guess is wrong
   do {

      //  answer is a random number between 1 & 1000
      int answer = 1 + rand() % 1000;

      // prints a formatted string to the user
      printf("I have a number between %d and %d.\n", MIN, MAX);

      // prints an unformatted string to the user
      puts("Can you guess my number?\n" 
           "Please type your first guess.");

      // prints a formatted string to the user
      printf("%s", "? ");
      

      // asks the user for a int and dumps it into guess
      scanf("%d", &guess);

      // while user is not correct
      while (!isCorrect(guess, answer)) {
         scanf("%d", &guess);
      }


      puts("\nExcellent! You guessed the number!\n"
         "Would you like to play again?");
      printf("%s", "Please type (1=yes, 2=no)? ");
      scanf("%d", &response);
      puts("");

   } while (response == 1);
} // end function guessGame

// isCorrect function, determines if the user was correct
bool isCorrect(int guess, int answer) {

    // boolean value holding true/false, if user was correct
    bool correct = false;

   // if guess & answer match, user was correct
   if (guess == answer) {
      correct = true;
   }

   // determines the print message
   if (guess < answer) {
      printf( "%s", "Too low. Try again.\n? " );
   }
   else {
      printf( "%s", "Too high. Try again.\n? " );
   }

   return correct;
} // end function isCorrect



/**************************************************************************
 * (C) Copyright 1992-2012 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
