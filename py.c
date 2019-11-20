#include <python3.6/Python.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "headers/ui.h"
#include "headers/py.h"
#include "headers/util.h"

void executeScript(char *pythonPath, char *argv[]){
   char *cmd = pythonPath; 
   if (execv(cmd, argv) == -1){
      fprintf(stderr, ERROR_CANT_RUN_SCRIPT);
      exit(EXIT_FAILURE);
   }
}
char *getPythonPath(){
   char buf[4096];
   char *path, *pos;
   FILE *fp;
   if (!(fp = popen("which python", "r"))){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   fgets(buf, sizeof(buf), fp);
   TRIM_NEWLINE(buf, pos)
   pclose(fp);
   path = malloc(strlen(buf) + 1);
   CHECK_MALLOC(path)
   strcpy(path, buf);
   return path;

}
char *callMarkovChainScript(char *dataSource, unsigned minWords, unsigned maxWords){
   pid_t pid;
   int fd[2];
   char buf[4096];
   char *puzzle,  *pos, *pythonPath;
   FILE *fp;

   pythonPath = getPythonPath();
   PIPE_AND_CHECK(fd)

   if ((pid = fork()) == -1){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
   else if (pid == 0){
      char *argv[4];
      char *minArg, *maxArg;
      /* 10 for arg, 6 for '--min=', 1 for terminator */
      minArg = malloc(17);
      maxArg = malloc(17);
      CHECK_MALLOC(minArg)
      CHECK_MALLOC(maxArg)
      sprintf(minArg, "--min=%d", minWords);
      sprintf(maxArg, "--max=%d", maxWords);
      argv[0] = pythonPath;
      argv[1] = PATH_MARKOV_SCRIPT; 
      argv[2] = dataSource;
      argv[3] = minArg;
      argv[4] = maxArg;
      argv[5] = NULL;
    
      close(fd[0]);
      dup2(fd[1], STDOUT_FILENO);
      executeScript(pythonPath, argv);
   }
   while (wait(NULL) != -1);
   free(pythonPath);
   close(fd[1]);
   read(fd[0], buf, 4096);
   close(fd[0]);
   TRIM_NEWLINE(buf, pos)
   puzzle = malloc(strlen(buf) + 1);
   CHECK_MALLOC(puzzle)
   strcpy(puzzle, buf);
   free(dataSource);
   return puzzle;
}
