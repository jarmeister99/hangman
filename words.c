#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "headers/words.h"
#include "headers/ui.h"

char* getRandomWord(){
   FILE *wordFile;
   unsigned selectedWordIndex = (rand() % (NUM_WORDS + 1));
   char buffer[MAX_WORD_SIZE];
   char *word = malloc(MAX_WORD_SIZE);
   if (!(wordFile = fopen(WORD_FILE, "r"))){
      perror(NULL);
      exit(EXIT_FAILURE);
   }   
   for (int i = 0; i < selectedWordIndex - 1; i++){
      fgets(buffer, MAX_WORD_SIZE, wordFile);
   }
   fgets(word, MAX_WORD_SIZE, wordFile);

   word[strcspn(word, "\n")] = '\0';
   if (!(word = realloc(word, strlen(word) + 1))){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   if (fclose(wordFile)){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   return word;
}
char** generatePuzzleToSolve(char **puzzle, unsigned numWords){
   char **puzzleToSolve;
   char *word;
   int i, j;
   if (!(puzzleToSolve = calloc(numWords, sizeof(char *)))){
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
   if (!(puzzle = calloc(numWords, sizeof(char *)))){
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
