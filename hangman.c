#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <python3.6/Python.h>
#include "headers/ui.h"
#include "headers/game.h"
#include "headers/py.h"

GameData* createGameData(unsigned maxGuesses, char *puzzleSolution, char *puzzleToSolve){
   GameData *gd;
   if (!(gd = malloc(sizeof(GameData)))){
      perror(NULL);
      exit(EXIT_FAILURE);
   }   
   gd->maxGuesses = maxGuesses;
   gd->puzzleSolution = puzzleSolution;
   gd->puzzleToSolve = puzzleToSolve;
   return gd;
}
char* makeBlankPuzzle(char *puzzle){
   int i;
   char *puzzleCopy;
   if (!(puzzleCopy = calloc(1, strlen(puzzle) + 1))){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   for (i = 0; i < strlen(puzzle); i++){
      if (!(isspace(puzzle[i]))){
         puzzleCopy[i] = '_';
      }
      else{
         puzzleCopy[i] = puzzle[i];   
      }
   }
   return puzzleCopy;
}
int main(int argc, char *argv[]){
   GameData *gd;
   unsigned maxGuesses, minWords, maxWords;
   char *dataSource;
   char *puzzle;
   char *toSolve;

   printf("[___~~~___~~~HANGMAN~~~___~~~___]\n");

   dataSource = promptFile(DATASOURCE_PROMPT);
   minWords = promptUnsigned(MINWORDS_PROMPT);
   maxWords = promptUnsigned(MAXWORDS_PROMPT);
   minWords = (minWords > maxWords) ? maxWords : minWords;
   puzzle = callMarkovChainScript(dataSource, minWords, maxWords);

   maxGuesses = promptUnsigned(MAXGUESSES_PROMPT);

   toSolve = makeBlankPuzzle(puzzle);
   gd = createGameData(maxGuesses, puzzle, toSolve);
   runGame(gd);
   exit(0);   
}
