#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "words.h"
#include "ui.h"

char* getRandomWord(){
   FILE *wordFile;
   unsigned selectedWordIndex = (rand() % (NUMWORDS + 1));
   char *buffer = malloc(sizeof(char) * MAXWORDSIZE);
   char *word = malloc(sizeof(char) * MAXWORDSIZE);
   if (!(wordFile = fopen(WORDFILE, "r"))){
      perror(NULL);
      exit(EXIT_FAILURE);
   }   
   for (int i = 0; i < selectedWordIndex - 1; i++){
      fgets(buffer, sizeof(char) * MAXWORDSIZE, wordFile);
   }
   fgets(word, sizeof(char) * MAXWORDSIZE, wordFile);
   word[strcspn(word, "\n")] = 0;
   if (fclose(wordFile)){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   free(buffer);
   return word;
}
char** generatePuzzleToSolve(char **puzzle, unsigned numWords){
   char **puzzleToSolve;
   char *word;
   int i, j;
   if (!(puzzleToSolve = malloc(sizeof(char*) * numWords))){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   for (i = 0; i < numWords; i++){
      if (!(word = strdup(puzzle[i]))){
         perror(NULL);
         exit(EXIT_FAILURE);
      }
      puzzleToSolve[i] = word;
   }
   for (i = 0; i < numWords; i++){
      for (j = 0; j < strlen(puzzleToSolve[i]); j++){
         puzzleToSolve[i][j] = '_';
      }
   }
   return puzzleToSolve;
}
char** generatePuzzleSolution(unsigned numWords){
   char **puzzle;
   char *word;
   int i;
   if (!(puzzle = malloc(sizeof(char*) * numWords))){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   for (i = 0; i < numWords; i++){
      puzzle[i] = getRandomWord();
   }
   return puzzle;
}
void freePuzzle(char **puzzle, unsigned numWords){
   int i;
   for (i = 0; i < numWords; i++){
      free(puzzle[i]);
   }
   free(puzzle);
}
