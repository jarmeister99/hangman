#include <python3.6/Python.h>
#include <sys/wait.h>
#include "headers/ui.h"
#include "headers/py.h"

void executeScript(char *scriptPath, char *argv[]){
   char *cmd = PYTHON_PATH;

   if (execv(cmd, argv) == -1){
      fprintf(stderr, ERROR_CANT_RUN_SCRIPT);
      exit(EXIT_FAILURE);
   }
   printf("DONT SEE THIS\n");
}
char **callMarkovChainScript(char *dataSource){
   /*
   Fork
   PIPE stdout of child to STDIN of parent
   */
   pid_t pid;
   if ((pid = fork()) == -1){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   else if (pid == 0){
      char *argv[4];
      argv[0] = PYTHON_PATH;
      argv[1] = PATH_MARKOV_SCRIPT; 
      argv[2] = dataSource;
      argv[3] = NULL;
      executeScript(PATH_MARKOV_SCRIPT, argv);
   }
   while (wait(NULL) != -1);
}
