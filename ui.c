#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "headers/ui.h"


unsigned promptUnsigned(const char *prompt, const char *promptHelp){
   int input = -1;
   char buffer[64] = "";
   do{
      printf("%s", prompt);
      if (!(fgets(buffer, 64, stdin))){
         perror(NULL);
      }
      input = atoi(buffer);
      if (input <= 0){
         printf("%s", promptHelp);
      }
   } while (input <= 0);
   return (unsigned)input;
}
void displayPuzzle(char *puzzle){
   int i;
   int br = 0;
   for (i = 0; i < strlen(puzzle); i++){
      if (puzzle[i] == '_'){ 
         printf("%c ", puzzle[i]);
      }
      else if (isspace(puzzle[i])){
         if (br > 30){
            printf("\n");
            br = 0;
         }
         else{
            printf("   ");
         }
      }
      else{
         printf("%c", puzzle[i]);
      }
      br++;
   }
   printf("\n");
}
char promptGuess(const char *prompt, const char *promptHelp){
   char buffer[8] = "";
   do{
      printf("%s", prompt);
      if (!(fgets(buffer, 64, stdin))){
         perror(NULL);
      }
      if (isalpha(buffer[0]) || isdigit(buffer[0])){
         return buffer[0];
      }
      else{
         printf("%s", promptHelp);
      }
   } while (1);
   return -1;
}
char* promptFile(const char *prompt){
   int input = -1;
   int maxInputLength = 128;
   FILE *fptr;
   char *buffer;
   char *pos;
   if (!(buffer = malloc(maxInputLength))){
      perror(NULL);
   }
   do{
      printf("%s", prompt);
      if (!(fgets(buffer, maxInputLength, stdin))){
         perror(NULL);
         continue;
      }
      if ((pos = strchr(buffer, '\n')) != NULL){
         *pos = '\0';
      }

      if (!(fptr = fopen(buffer, "r"))){
         printf("%s", ERROR_CANT_FIND_FILE);
      }
      else{
         free(fptr);
         return buffer;
      }
      
   } while (1);
   return buffer;
}
void displayGuessList(char guessList[], int numGuesses){
   int i;
   printf("ALREADY GUESSED:");
   for (i = 0; i < numGuesses; i++){
      printf(" %c", guessList[i]);
   }
   printf("\n");
}
void displayHangman(unsigned incorrectGuesses, unsigned maxGuesses){
   float ratio;
   if (incorrectGuesses == 0){
      printf(HANGMAN_STAGE_01);
      return;
   }
   else if (incorrectGuesses == maxGuesses){
      printf(HANGMAN_STAGE_07);
      return;
   }
   ratio = incorrectGuesses / (float) maxGuesses;
   if (ratio < 0.20f){
      printf(HANGMAN_STAGE_02);
   }
   else if (ratio < 0.40f){
      printf(HANGMAN_STAGE_03);
   }
   else if (ratio < 0.60f){
      printf(HANGMAN_STAGE_04);
   }
   else if (ratio < 0.80f){
      printf(HANGMAN_STAGE_05);
   }
   else{
      printf(HANGMAN_STAGE_06);
   }

}
