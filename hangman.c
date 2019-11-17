#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <python3.6/Python.h>
#include "headers/words.h"
#include "headers/ui.h"
#include "headers/game.h"
#include "headers/py.h"

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
void callMarkovChainPy(char *dataSource){
   
}
int main(int argc, char *argv[]){
   GameData *gd;
   unsigned maxGuesses;
   char *dataSource;
   char *puzzle;

   printf("[___~~~___~~~HANGMAN~~~___~~~___]\n");

   dataSource = promptFile(DATASOURCE_PROMPT);
   puzzle = callMarkovChainScript(dataSource);
   maxGuesses = promptUnsigned(MAXGUESSES_PROMPT, MAXGUESSES_PROMPT_HELP);
   printf("Puzzle: %s\n", puzzle);

   exit(0);   
}
