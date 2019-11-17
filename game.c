#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/game.h"
#include "headers/ui.h"

int checkVictory(GameData *gd){
}
int checkGuess(char guess, GameData *gd){
}
int alreadyGuessed(char guess, char guessList[], int validGuesses){
   int i;
   for (i = 0; i < validGuesses; i++){
      if (guess == guessList[i]){
         printf("You already guessed %c - try again!\n", guess);
         displayGuessList(guessList, validGuesses);
         return 1;
      }
   }
   return 0;
}
void freeGameData(GameData *gd){
}
void runGame(GameData *gd){
   int incorrectGuesses = 0;
   int validGuesses = 0;
   char guessList[36] = "";
   printf("\n\n");
   do{
      char guess = 0;
      printf("You have %d guesses left.\n", gd->maxGuesses - incorrectGuesses);
      printf("%s\n", gd->puzzleSolution);
      printf("%s\n", gd->puzzleToSolve);
      do{
         guess = promptGuess(GUESS_PROMPT, GUESS_PROMPT_HELP);
      } while (alreadyGuessed(guess, guessList, validGuesses));
      guessList[validGuesses++] = guess;
      if (checkGuess(guess, gd)){
         if (checkVictory(gd)){
            displayHangman(incorrectGuesses, gd->maxGuesses);
            printf("You won in %d guesses with %d guesses to spare!\n", validGuesses, gd->maxGuesses - incorrectGuesses);
            freeGameData(gd);
            exit(0);
         }
         
      }
      else{
         incorrectGuesses++;
         displayHangman(incorrectGuesses, gd->maxGuesses);
      }
   } while (incorrectGuesses < gd->maxGuesses);
   printf("Game over! Try again?\n");
   freeGameData(gd);
   exit(0);
}
