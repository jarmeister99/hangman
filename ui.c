#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ui.h"


unsigned promptUnsigned(const char *prompt, const char *promptHelp){
   int input = -1;
   char buffer[64];
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
      printf("%s%4s",puzzle[i], "");
   }
   printf("\n");
}
char promptGuess(const char *prompt, const char *promptHelp){
   int input = -1;
   char buffer[8];
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
