#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/game.h"
#include "headers/ui.h"

int checkVictory(GameData *gd){
   return 0;
}
void replaceAll(char guess, GameData *gd){
   int i;
   for (i = 0; i < strlen(gd->puzzleToSolve); i++){
      if (gd->puzzleSolution[i] == guess){
         gd->puzzleToSolve[i] = guess;
      }
   }
}
int checkGuess(char guess, GameData *gd){
   int i;
   for (i = 0; i < strlen(gd->puzzleSolution); i++){
      if (gd->puzzleSolution[i] == guess){
         replaceAll(guess, gd);
         return 1;
      }
   }
   return 0;
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
   free(gd->puzzleToSolve);
   free(gd->puzzleSolution);
   free(gd);
}
void runGame(GameData *gd){
   int incorrectGuesses = 0;
   int validGuesses = 0;
   char guessList[36] = "";
   printf("\n");
   do{
      char guess = 0;
      printf("You have %d guesses left.\n", gd->maxGuesses - incorrectGuesses);
      displayPuzzle(gd->puzzleToSolve);
      do{
         printf("\n");
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
         printf("\nWrong!\n");
      }
      printf("\n");
   } while (incorrectGuesses < gd->maxGuesses);
   printf("Game over!\n");
   printf("Puzzle was: %s\n", gd->puzzleSolution);

   freeGameData(gd);
   exit(0);
}
