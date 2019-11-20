#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/game.h"
#include "headers/ui.h"

int checkVictory(GameData *gd){
   int i;
   for (i = 0; i < strlen(gd->puzzleToSolve); i++){
      if (gd->puzzleToSolve[i] != gd->puzzleSolution[i]){
         return 0;
      }
   }
   return 1;
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
void gameOver(GameData *gd){
   printf("Game over! The puzzle was '%s'\n", gd->puzzleSolution);
   freeGameData(gd);
   exit(0);
}
void victory(GameData *gd){
   printf("You won! The puzzle was '%s'\n", gd->puzzleSolution);
   freeGameData(gd);
   exit(0);
}
void runGame(GameData *gd){
   int incorrectGuesses, validGuesses;
   incorrectGuesses = validGuesses = 0;
   char guessList[36];

   while (!(checkVictory(gd))){
      char guess = 0;
      printf("\n");
      printBar();
      displayHangman(incorrectGuesses, gd->maxGuesses);
      printf("\n");
      displayPuzzle(gd->puzzleToSolve);
      printf("\n");
      printf("You have %d guesses remaining.\n", gd->maxGuesses - incorrectGuesses);
      printf("\n");
      do{
         guess = promptGuess(GUESS_PROMPT, GUESS_PROMPT_HELP);
         printf("\n");
      } while (alreadyGuessed(guess, guessList, validGuesses));
      guessList[validGuesses++] = guess;
      if (!(checkGuess(guess, gd))){
         incorrectGuesses += 1;
         printf("'%c' is not in the puzzle.\n", guess);
      }
      else{
         printf("'%c' is in the puzzle.\n", guess);
      }
      if (incorrectGuesses >= gd->maxGuesses){
         printBar();
         displayHangman(incorrectGuesses, gd->maxGuesses);
         printf("\n");
         gameOver(gd);
      }
   }
   printf("\n");
   victory(gd);
}
