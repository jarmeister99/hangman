#include <python3.6/Python.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "headers/ui.h"
#include "headers/py.h"

void executeScript(char *interpreterPath, char *scriptPath, char *argv[]){
   char *cmd = interpreterPath;
   
   fprintf(stderr, "Trying to run: %s\n", interpreterPath);
   if (execv(cmd, argv) == -1){
      fprintf(stderr, ERROR_CANT_RUN_SCRIPT);
      exit(EXIT_FAILURE);
   }
}
char *callMarkovChainScript(char *dataSource){
   pid_t pid;
   int fd[2];
   char buf[4096], pythonPath[4096];
   char *puzzle,  *pos;
   FILE *fp;
   char *interpreterPath;
   char *pythonVersion = "python3.7";

   /* Get python path */
   if (!(fp = popen("which python", "r"))){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   fgets(pythonPath, strlen(pythonPath), fp);
   pclose(fp);
   if (!(interpreterPath = calloc(1, strlen(pythonPath) + strlen(pythonVersion) + 1))){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   printf("Python path is '%s'\n", pythonPath);
   printf("Python version is '%s'\n", pythonVersion);
   printf("Interpreter path is '%s'", interpreterPath);
   strcat(interpreterPath, pythonPath);
   strcat(interpreterPath, pythonVersion);

   if (pipe(fd) == -1){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   if ((pid = fork()) == -1){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   else if (pid == 0){
      char *argv[4];
      argv[0] = interpreterPath;
      argv[1] = PATH_MARKOV_SCRIPT; 
      argv[2] = dataSource;
      argv[3] = NULL;
    
      close(fd[0]);
      dup2(fd[1], STDOUT_FILENO);
      executeScript(interpreterPath, PATH_MARKOV_SCRIPT, argv);
   }
   while (wait(NULL) != -1);
   close(fd[1]);
   read(fd[0], buf, 4096);
   close(fd[0]);
   if ((pos = strchr(buf, '\n')) != NULL){
      *pos = '\0';
   }
   else{
      perror(NULL);
      exit(EXIT_FAILURE);
   }

   if (!(puzzle = malloc(strlen(buf) + 1))){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   strcpy(puzzle, buf);
   free(dataSource);
   return puzzle;
}
