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
void freeGameData(GameData *gd){
   freePuzzle(gd->puzzleSolution, gd->numWords);
   freePuzzle(gd->puzzleToSolve, gd->numWords);
   free(gd);
}
void runGame(GameData *gd){
   int guesses = 0;
   int incorrectGuesses = 0;
   char guess;
   do{
      printf("You have %d guesses left.\n", gd->maxGuesses - incorrectGuesses);
      displayPuzzle(gd->puzzleSolution, gd->numWords);
      displayPuzzle(gd->puzzleToSolve, gd->numWords);
      guess = promptGuess(GUESS_PROMPT, GUESS_PROMPT_HELP);
      if (checkGuess(guess, gd)){
         if (checkVictory(gd)){
            printf("You won in %d guesses!\n", guesses);
            freeGameData(gd);
            exit(0);
         }
         
      }
      else{
         incorrectGuesses++;
      }
   } while(incorrectGuesses < gd->maxGuesses);
   printf("Game over! Try again?\n");
   exit(0);
}
