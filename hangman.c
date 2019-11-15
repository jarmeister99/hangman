#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers/words.h"
#include "headers/ui.h"
#include "headers/game.h"


GameData* createGameData(unsigned maxGuesses, char **puzzleSolution, char **puzzleToSolve, unsigned numWords){
   GameData *gd;
   if (!(gd = malloc(sizeof(GameData)))){
      perror(NULL);
      exit(EXIT_FAILURE);
   }   
   gd->maxGuesses = maxGuesses;
   gd->puzzleSolution = puzzleSolution;
   gd->puzzleToSolve = puzzleToSolve;
   gd->numWords = numWords;
   return gd;
}
int main(int argc, char *argv[]){
   GameData *gd;
   unsigned maxGuesses;
   unsigned numWords;
   char **puzzleSolution;
   char **puzzleToSolve;
   printf("[___~~~___~~~HANGMAN~~~___~~~___]\n");
   srand((unsigned long)time(NULL));
   maxGuesses = promptUnsigned(MAXGUESSES_PROMPT, MAXGUESSES_PROMPT_HELP);
   numWords = promptUnsigned(NUMWORDS_PROMPT, NUMWORDS_PROMPT_HELP);
   puzzleSolution = generatePuzzleSolution(numWords);
   puzzleToSolve = generatePuzzleToSolve(puzzleSolution, numWords);
   gd = createGameData(maxGuesses, puzzleSolution, puzzleToSolve, numWords);
   runGame(gd);
   free(gd);
   exit(0);   
}
