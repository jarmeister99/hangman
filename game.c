#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "ui.h"
#include "words.h"

int checkVictory(GameData *gd){
   int i;
   for (i = 0; i < gd->numWords; i++){
      if (strchr(gd->puzzleToSolve[i], '_')){
         return 0;
      }
   }
   return 1;
}
int checkGuess(char guess, GameData *gd){
   int i, j;
   int ret = 0;
   for (i = 0; i < gd->numWords; i++){
      for (j = 0; j < strlen(gd->puzzleSolution[i]); j++){
         if (gd->puzzleSolution[i][j] == guess){
            gd->puzzleToSolve[i][j] = guess;
            ret++;
         }
      }
   }
   return ret;
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
   freePuzzle(gd->puzzleSolution, gd->numWords);
   freePuzzle(gd->puzzleToSolve, gd->numWords);
   free(gd);
}
void runGame(GameData *gd){
   int incorrectGuesses = 0;
   int validGuesses = 0;
   char guessList[26] = "";
   do{
      char guess = 0;
      printf("You have %d guesses left.\n", gd->maxGuesses - incorrectGuesses);
      displayPuzzle(gd->puzzleToSolve, gd->numWords);
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
