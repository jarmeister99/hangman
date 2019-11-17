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
   unsigned numWords;
   char **puzzleSolution;
   char **puzzleToSolve;
   char *dataSource;
   char **puzzle;

   printf("[___~~~___~~~HANGMAN~~~___~~~___]\n");
   srand((unsigned long)time(NULL));

   /* Process: 
      1. Ask the user for the path to their data source
      --- Make sure there is a file at that location
      2. Call the Markov chain script using the given data source path. Save the resulting chain.
      3. Use the chain as the puzzle 
   */

   dataSource = promptFile(DATASOURCE_PROMPT);
   callMarkovChainScript(dataSource, &numWords);

   maxGuesses = promptUnsigned(MAXGUESSES_PROMPT, MAXGUESSES_PROMPT_HELP);
   numWords = promptUnsigned(NUMWORDS_PROMPT, NUMWORDS_PROMPT_HELP);

   puzzleToSolve = generatePuzzleToSolve(puzzle, numWords);
   gd = createGameData(maxGuesses, puzzle, puzzleToSolve, numWords);
   runGame(gd);
   free(gd);

   exit(0);   
}
