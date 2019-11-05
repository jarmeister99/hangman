#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ui.h"


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
void displayPuzzle(char **puzzle, unsigned numWords){
   for (int i = 0; i < numWords; i++){
      printf("%s%4s", puzzle[i], "");
   }
   printf("\n");
}
char promptGuess(const char *prompt, const char *promptHelp){
   int input = -1;
   char buffer[8] = "";
   do{
      printf("%s", prompt);
      if (!(fgets(buffer, 64, stdin))){
         perror(NULL);
      }
      if (isalpha(buffer[0])){
         return buffer[0];
      }
      else{
         printf("%s", promptHelp);
      }
   } while (!(isalpha(input)));
   return -1;
}
void displayGuessList(char guessList[], int numGuesses){
   int i;
   printf("ALREADY GUESSED:");
   for (i = 0; i < numGuesses; i++){
      printf(" %c", guessList[i]);
   }
   printf("\n");
}
/* 7 stages total, 0 if perfect, 7 if loss */
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
